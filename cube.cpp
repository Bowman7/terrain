#include"cube.hpp"

Cube::Cube(){
  glGenVertexArrays(1,&VAO);
  glGenBuffers(1,&VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(cubeVertices),&cubeVertices,GL_STATIC_DRAW);

  //for coords
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
  //for tex coords
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));

  glBindVertexArray(0);
  
  
}

Cube::~Cube(){
  
}

void Cube::Update(glm::mat4 look){
  this->lookMat = look;
}
void Cube::Draw(unsigned int cubeTex){
  glUseProgram(ID);

  //glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view  = lookMat;
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
  //set them
  setMat4("model",model,ID);
  setMat4("projection",projection,ID);
  setMat4("view",view,ID);

  glBindTexture(GL_TEXTURE_2D,cubeTex);
  glBindVertexArray(VAO);
  
  glDrawArrays(GL_TRIANGLES,0,36);

  glBindVertexArray(0);
  
  
}
