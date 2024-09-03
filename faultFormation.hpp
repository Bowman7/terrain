#pragma once 

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"baseTerrain.hpp"

class FaultFormation : public BaseTerrain{
public:
  FaultFormation(){}
  ~FaultFormation(){}

  void CreateFaultFormation(int TerrainSize,int Iterations,float MinHeight,float MaxHeight,float);
 
  
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

  void ApplyFIRFilter(float);
  float FIRFilterSinglePoint(int x,int z, float PrevVal,float filter);
  void CreateFaultFormationInternal(int,float,float,float);
  void GenRandomTerrainPoints(TerrainPoint&,TerrainPoint&);
  
};
  
