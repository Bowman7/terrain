#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"shader.hpp"
#include"cube.hpp"
#include"camera.hpp"
#include"plane.hpp"
#include"baseTerrain.hpp"
#include"faultFormation.hpp"
#include"midpoint.hpp"

class Game{
public:
  Game();
  ~Game();
  void Update(glm::vec3,float,float);
  void HandleInput(int);
  void Draw();
  unsigned int LoadTexture(const char*);
  unsigned int LoadTextureA(const char*);


private:
  Camera camera;
  //terrain 
  //BaseTerrain baseTerrain;
  //FaultFormation faultFormation;
  Midpoint midpoint;
  Shader terrainShader;
  
  Shader cubeShader;
  Cube cube;
  unsigned int cubeTex;

  //pos1
  glm::vec3 pos1 = {-1.0f,0.0f,-1.0f};
  glm::vec3 pos2 = {2.0f,0.0f,0.0f};
  //for fault fomration
  float filter = 0.0f;
  
  int Size = 256;
  int Iterations = 500;
  float MinHeight = 0.0f;
  float MaxHeight = 300.0f;
  bool newFilter = false;
};
