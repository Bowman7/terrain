#include"game.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

Game::Game(){

  //shader
  cubeShader.Init("cube.vert","cube.frag");

  cube[0].SetID(cubeShader.GetID());
  cube[1].SetID(cubeShader.GetID());
  //translate cube
  cube[0].MoveCube(pos1);
  cube[1].MoveCube(pos2);
  //load tex
  cubeTex = LoadTexture("marble2.jpeg");

  //for plane
  planeShader.Init("plane.vert","plane.frag");

  plane.SetID(planeShader.GetID());

  planeTex  = LoadTextureA("metal2.png");
  
}

Game::~Game(){

}


void Game::Update(glm::vec3 camFront,float fov){
  camera.UpdateCameraFront(camFront,fov);

  cube[0].Update(camera.GetViewMatrix());
  cube[1].Update(camera.GetViewMatrix());
  //for plane
  plane.Update(camera.GetViewMatrix());
}

void Game::HandleInput(int val){
  camera.HandleInput(val);
}

void Game::Draw(){
  cube[0].Draw(cubeTex);
  cube[1].Draw(cubeTex);
  //plane
  plane.Draw(planeTex);
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
