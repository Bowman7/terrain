#include"faultFormation.hpp"


void FaultFormation::CreateFaultFormation(int TerrainSize,int Iterations,
					  float MinHeight,float MaxHeight,float filter){
  terrainSize = TerrainSize;
  minHeight = MinHeight;
  maxHeight = MaxHeight;

  heightMap.InitArray2D(terrainSize,terrainSize,0.0f);

  CreateFaultFormationInternal(Iterations,MinHeight,MaxHeight,filter);

  heightMap.Normalize(MinHeight,MaxHeight);
  
  triangleList.CreateTriangleList(terrainSize,terrainSize,this);

}

//apply fir filter
void FaultFormation::ApplyFIRFilter(float filter){
  //left to right
  for(int z =0;z<terrainSize;z++){
    float PrevVal = heightMap.Get(0,z);
    for(int x=1;x<terrainSize;x++){
      PrevVal = FIRFilterSinglePoint(x,z,PrevVal,filter);
    }
  }
  
  //right to left
  for(int z =0;z<terrainSize;z++){
    float PrevVal = heightMap.Get(terrainSize-1,z);
    for(int x=terrainSize-2;x>=0;x--){
      PrevVal = FIRFilterSinglePoint(x,z,PrevVal,filter);
    }
  }

  // bottom to top
  for(int x=0;x<terrainSize;x++){
    float PrevVal = heightMap.Get(x,0);
    for(int z =1;z<terrainSize;z++){
      PrevVal = FIRFilterSinglePoint(x,z,PrevVal,filter);
    }
  }

  //top to bottom
  for(int x=0;x<terrainSize;x++){
    float PrevVal = heightMap.Get(x,terrainSize-1);
    for(int z =terrainSize-2;z>=0;z--){
      PrevVal = FIRFilterSinglePoint(x,z,PrevVal,filter);
    }
  }
  
}
//single point fir filter
float FaultFormation::FIRFilterSinglePoint(int x,int z, float PrevVal,float filter){
  float curVal = heightMap.Get(x,z);
  float newVal = filter * PrevVal +(1-filter) * curVal;
  heightMap.Set(x,z,newVal);
  return newVal;
}
//internal fault
void FaultFormation::CreateFaultFormationInternal(int Iterations,
						  float MinHeight,float MaxHeight,float filter){

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

  
  //apply fir filter
  ApplyFIRFilter(filter);
  
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
