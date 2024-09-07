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

  //terrain
  terrainShader.Init("terrain.vert","terrain.frag");
  midpoint.SetID(terrainShader.GetID());
  
  
  midpoint.CreateMidpointDisplacement(Size,MinHeight,MaxHeight,0.5f); 
  
}

Game::~Game(){

}


void Game::Update(glm::vec3 camFront,float fov,float filter){
  //update and create again
  if(this->filter != filter){
    newFilter = true;
    this->filter = filter;
  }
  if(newFilter){
    midpoint.CreateMidpointDisplacement(Size,MinHeight,MaxHeight,0.5f);
    newFilter = false;
  }
  
  camera.UpdateCameraFront(camFront,fov);

  cube.Update(camera.GetViewMatrix());
  //faultFormation.Update(camera.GetViewMatrix());
  midpoint.Update(camera.GetViewMatrix());
}

void Game::HandleInput(int val){
  camera.HandleInput(val);
}

void Game::Draw(){
  //cube.Draw(cubeTex);
  //faultFormation.Render();
  midpoint.Render();
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
