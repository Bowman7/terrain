#pragma once 

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

class FaultFormation{
public:
  FaultFormation(){}
  ~FaultFormation(){}

  void CreateFaultFormation(int TerrainSize,int Iterations,float MinHeight,float MaxHeight);
  void InitFloatPtr();
  void CreateFaultFormationInternal(int,float,float);
  float GetIndex(int x,int z){
    int ind = z*247 + x;
    return file[ind];
  }
  void SetVal(int x,int z,float val){
    int index = z*247 + x;
    file[index] = val;
  }
  void Normalize(float,float);
  void GetMinMax(float&,float&);
  float* GetFile(){
    return file;
  }
private:

  struct TerrainPoint{
    int x =0;
    int z =0;

    void Print(){
      printf("x: %d z: %d\n",x,z);
    }

    bool IsEqual(TerrainPoint &p){
      return ((x == p.x) && (z == p.z));
    }
  };

  void GenRandomTerrainPoints(TerrainPoint&,TerrainPoint&);
  
  int TerrainSize;
  float minHeight;
  float maxHeight;
  float *file;
  
};
  
