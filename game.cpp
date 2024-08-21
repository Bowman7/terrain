#include"game.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

Game::Game(){

  //shader
  cubeShader.Init("cube.vert","cube.frag");

  cube.SetID(cubeShader.GetID());
  //translate cube
  cube.MoveCube(pos1);
  //load tex
  cubeTex = LoadTexture("marble2.jpeg");


  //for fault in formation
  fault_formation.CreateFaultFormation(257,500,0.0f,100.0f);
  
  //load file in terrain
  terrainShader.Init("terrain.vert","terrain.frag");
  terrain.SetID(terrainShader.GetID());
  terrain.LoadTerrain("height2.save");
  terrain.CreateTriangleList();
  
  
}

Game::~Game(){

}


void Game::Update(glm::vec3 camFront,float fov){
  camera.UpdateCameraFront(camFront,fov);

  cube.Update(camera.GetViewMatrix());
  terrain.Update(camera.GetViewMatrix());
 
}

void Game::HandleInput(int val){
  camera.HandleInput(val);
}

void Game::Draw(){
  //cube.Draw(cubeTex);
  terrain.Render();

}


//load texture
unsigned int Game::LoadTexture(const char* filename){
  unsigned int texture;
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
  if (data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
  else
    {
      std::cout << "Failed to load texture" << std::endl;
    }
  stbi_image_free(data);

  return texture;
}
//load rgba texture
//load texture
unsigned int Game::LoadTextureA(const char* filename){
  unsigned int texture;
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
  if (data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
  else
    {
      std::cout << "Failed to load texture" << std::endl;
    }
  stbi_image_free(data);

  return texture;
}
