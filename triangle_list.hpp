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


//fwd dec for base terrain as triangle list is called in game first
class BaseTerrain;

class TriangleList{
public:
  TriangleList();

  void CreateTriangleList(int Width,int Depth,const BaseTerrain* Terrain);
  void Render();
  void InitIndices(std::vector<unsigned int>&);
  
  void SetID(unsigned int id){
    this->ID=id;
  }
  void Update(glm::mat4 look){
    lookMat = look;
  }
  void setMat4(const std::string &name, const glm::mat4 &mat,unsigned int id) const
  {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }
  void setFloat(const std::string &name, float value,unsigned int ID) const
  { 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
  }
 
private:
   struct Vertex{
    float x;
    float y;
    float z;

     void InitVertex(const BaseTerrain*,int x,int z);
  };
  void PopulateBuffers(const BaseTerrain*);
  void InitVertices(const BaseTerrain* Terrain,std::vector<Vertex>&Vertices);
  void InitVertex(const BaseTerrain* Terrain,int x,int z);
  int width = 0;
  int depth = 0;
  unsigned int VAO,VBO,EBO;
  unsigned int ID;
  glm::mat4 lookMat;
};
