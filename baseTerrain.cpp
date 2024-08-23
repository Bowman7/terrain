#include"baseTerrain.hpp"

//load from file
void BaseTerrain::LoadFromFile(const char* Filename){
  LoadHeightMapFile(Filename);

  triangleList.CreateTriangleList(terrainSize,terrainSize,this);

}
//set id
void BaseTerrain::SetID(unsigned int id){
  triangleList.SetID(id);
}
//update
void BaseTerrain::Update(glm::mat4 look){
  triangleList.Update(look);
}
void BaseTerrain::LoadHeightMapFile(const char* Filename){
  FILE *fptr;

  fptr = fopen(Filename,"rb");
  if(fptr == NULL){
    printf("Could not open file");
    exit(-1);
  }
  //find file size
  fseek(fptr,0,SEEK_END);
  long size = ftell(fptr);
  fseek(fptr,0,SEEK_SET);

  unsigned char* file =(unsigned char*)malloc(size);

  fread(file,1,size,fptr);

  fclose(fptr);

  //num elements
  int numElements = size/sizeof(float);

  int dimensions = sqrt(numElements);

  terrainSize = dimensions;
  heightMap.InitArray2D(terrainSize,terrainSize,file);

  //heightMap.PrintFloat();
}
//render
void BaseTerrain::Render(){
  triangleList.Render();
}
