#include"faultformation.hpp"


void FaultFormation::CreateFaultFormation(int TerrainSize,int Iterations,
					  float MinHeight,float MaxHeight){
  this->TerrainSize = TerrainSize;
  this->minHeight = MinHeight;
  this->maxHeight = MaxHeight;

  //init float array for storing heights
  InitFloatPtr();

  //create internal fault formation
  CreateFaultFormationInternal(Iterations,MinHeight,MaxHeight);
  //normalize in file
  Normalize(MinHeight,MaxHeight);
  //now print all this
  for(int z=0;z<247;z++){
    for(int x = 0;x<247;x++){
      printf(" %f ",file[x]);
    }
  }
  //save this in a file
  FILE *fptr;
  fptr = fopen("height2.save","wb");

  for(int z =0;z<TerrainSize;z++){
    for(int x =0;x<TerrainSize;x++){
      fprintf(fptr,"%f",file[x]);
    }
  }

  fclose(fptr);
  
}

//get min max

void FaultFormation::GetMinMax(float &min,float &max){
  min =max = file[0];

  for(int i=0;i<247*247;i++){
    if(file[i]<min){
      min  = file[i];
    }

    if(file[i]>max){
      max = file[i];
    }
  }

 
}
//normalize
void FaultFormation::Normalize(float MinHeight,float MaxHeight){
  float Min,Max;

  GetMinMax(Min,Max);

  if(Max<=Min){
    return;
  }

  float MinMaxDelta = Max-Min;
  float MinMaxRange = MaxHeight - MinHeight;

  for(int i=0;i<247*247;i++){
    file[i] = ((file[i]-Min)/MinMaxDelta)*MinMaxRange+MinHeight;
  }
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

    for(int z =0;z<TerrainSize;z++){
      for(int x =0;x<TerrainSize;x++){
	int DirX_in = x - p1.x;
	int DirZ_in = z - p1.z;

	int CrossProduct = DirX_in * DirZ - DirX * DirZ_in;
	
	if(CrossProduct>0){
	  float CurHeight = GetIndex(x,z);
	  SetVal(x,z,CurHeight+Height);
	}
      }
    }
  }
 
  
}
//generate random terrain points
void FaultFormation::GenRandomTerrainPoints(TerrainPoint &p1,TerrainPoint &p2){

  p1.x = rand()%TerrainSize;
  p1.z = rand()%TerrainSize;

  int count = 0;
  do{
    p2.x = rand()%TerrainSize;
    p2.z = rand()%TerrainSize;

    if(count++ == 1000){
      printf("Endless loop detected\n");
      assert(0);
    }
  }while(p1.IsEqual(p2));
}
//init float ptr
void FaultFormation::InitFloatPtr(){
  float *temp = (float*)malloc(TerrainSize*TerrainSize*sizeof(float));

  for(int i=0;i<TerrainSize;i++){
    for(int j=0;j<TerrainSize;j++){
      temp[i] = 10.0f;
    }
  }

  file = temp;
}
