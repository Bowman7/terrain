#pragma once


#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

class Terrain{
public:
  Terrain();
  ~Terrain();
  void Update(glm::mat4);
  void SetID(unsigned int id){
    this->ID = id;
  }
  
  void LoadTerrain(const char*);
  void DrawTerrain();

  //to populate traingle list
  void CreateTriangleList();
  void Render();

  void setMat4(const std::string &name, const glm::mat4 &mat,unsigned int id) const
  {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }
  void setFloat(const std::string &name, float value,unsigned int ID) const
  { 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
  }
private:
  glm::mat4 lookMat;
  int row,col;
  long file_size;
  float *file_data;
  //for triangle list
  struct Vertex{
    float x;
    float y;
    float z;

    void InitVertex(float x, float y,float z);
  };
  int m_width = 0;
  int m_depth = 0;
  unsigned int VAO,VBO,EBO;
  unsigned int ID;
  float world_scale  = 4.0f;
  
};
