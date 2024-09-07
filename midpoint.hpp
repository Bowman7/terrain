#pragma once 

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include<random>

#include"baseTerrain.hpp"

class Midpoint : public BaseTerrain{
public:
  Midpoint(){}
  ~Midpoint(){}

  void CreateMidpointDisplacement(int,float,float,float);
  void CreateMidpointDisplacementNow(float roughness);
  void DiamondStep(int ,float);
  void SquareStep(int,float);
  float RandomFloatRange(float,float);
  
private:
  int TerrainSize;
  float MinHeight;
  float MaxHeight;
};
  
