#include"faultFormation.hpp"


void FaultFormation::CreateFaultFormation(int TerrainSize,int Iterations,
					  float MinHeight,float MaxHeight){
  terrainSize = TerrainSize;
  minHeight = MinHeight;
  maxHeight = MaxHeight;

  heightMap.InitArray2D(terrainSize,terrainSize,0.0f);

  CreateFaultFormationInternal(Iterations,MinHeight,MaxHeight);

  heightMap.Normalize(MinHeight,MaxHeight);
  
  triangleList.CreateTriangleList(terrainSize,terrainSize,this);
  
  
}


//internal fault
void FaultFormation::CreateFaultFormationInternal(int Iterations,
						  float MinHeight,float MaxHeight){

  float DeltaHeight = MaxHeight - MinHeight;

  for(int curIter = 0;curIter<Iterations;curIter++){
    float IterationRatio = ((float)curIter/(float)Iterations);
    float Height = MaxHeight - IterationRatio * DeltaHeight;

    TerrainPoint p1,p2;

    GenRandomTerrainPoints(p1,p2);

    int DirX = p2.x - p1.x;
    int DirZ = p2.z - p1.z;

    for(int z =0;z<terrainSize;z++){
      for(int x =0;x<terrainSize;x++){
	int DirX_in = x - p1.x;
	int DirZ_in = z - p1.z;

	int CrossProduct = DirX_in * DirZ - DirX * DirZ_in;
	
	if(CrossProduct>0){
	  float CurHeight = heightMap.Get(x,z);
	  heightMap.Set(x,z,CurHeight+Height);
	}
      }
    }
  }
  /*
  //print after fault formation;
  for(int z=0;z<247;z++){
    for(int x = 0;x<247;x++){
      printf(" %f ",file[x]);
    }
  }
  */
  
}
//generate random terrain points
void FaultFormation::GenRandomTerrainPoints(TerrainPoint &p1,TerrainPoint &p2){

  p1.x = rand()%terrainSize;
  p1.z = rand()%terrainSize;

  int count = 0;
  do{
    p2.x = rand()%terrainSize;
    p2.z = rand()%terrainSize;

    if(count++ == 1000){
      printf("Endless loop detected\n");
      assert(0);
    }
  }while(p1.IsEqual(p2));
}
