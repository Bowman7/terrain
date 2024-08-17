#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

class Plane{
public:
  Plane();
  ~Plane();
  void SetID(unsigned int id){
    this->ID = id;
  }
  void Draw(unsigned int );
  void Update(glm::mat4);
  
  void setMat4(const std::string &name, const glm::mat4 &mat,unsigned int id) const
  {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  void MovePlane(glm::vec3 val){
    model = glm::translate(model,val);
  }

private:
  //set the model pos
  glm::mat4 model = glm::mat4(1.0f);
  
  glm::mat4 lookMat;
  unsigned int ID;
  unsigned int VAO,VBO,EBO;
  //vertices
  float planeVertices[30] = {
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f								
    };
};
