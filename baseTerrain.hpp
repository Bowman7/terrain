#pragma once


#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"array_2d.hpp"
#include"triangle_list.hpp"

class BaseTerrain{
public:
  BaseTerrain(){}

  void LoadFromFile(const char*);
  void LoadHeightMapFile(const char*);
  void Update(glm::mat4);
  void SetID(unsigned int id);
  
  void Render();
  
  float GetHeight(int x,int z) const {
    return heightMap.Get(x,z);
  }
protected:
  int terrainSize = 0;
  float minHeight = 0.0f;
  float maxHeight = 0.0f;
  Array2D<float> heightMap;
  TriangleList triangleList;
};
