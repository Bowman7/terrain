#include"triangle_list.hpp"
#include"baseTerrain.hpp"

TriangleList::TriangleList(){
  
}

void TriangleList::CreateTriangleList(int Width,int Depth,const BaseTerrain *Terrain){
  width = Width;
  depth = Depth;

  //init states
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);

  glGenBuffers(1,&EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(0*sizeof(float)));

  //populate buffer
  PopulateBuffers(Terrain);
}

//init vertex
void TriangleList::Vertex::InitVertex(const BaseTerrain* Terrain,int x,int z){
  float y = Terrain->GetHeight(x,z);
  float worldScale = 4.0f;
  this->x = x * worldScale;
  this->y = y;
  this->z = z * worldScale; 
  
}
//init vertices
void TriangleList::InitVertices(const BaseTerrain* Terrain,std::vector<Vertex>&Vertices){

  long unsigned int index = 0;
  
  for(int z =0;z<depth;z++){
    for(int x =0;x<width;x++){
      assert(index< Vertices.size());
      Vertices[index].InitVertex(Terrain,x,z);
      index++;
    }
  }
}

//populate buffers
void TriangleList::PopulateBuffers(const BaseTerrain *Terrain){
  std::vector<Vertex> Vertices;

  Vertices.resize(width*depth);

  InitVertices(Terrain,Vertices);

  //pop indices
  std::vector<unsigned int>Indices;
  int NumQuads = (width-1)*(depth-1);
  Indices.resize(NumQuads*6);
  InitIndices(Indices);

  glBufferData(GL_ARRAY_BUFFER,sizeof(Vertices[0])*Vertices.size(),&Vertices[0],GL_STATIC_DRAW);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Indices[0])*Indices.size(),
	       &Indices[0],GL_STATIC_DRAW);
  
}

//init indices
void TriangleList::InitIndices(std::vector<unsigned int> &Indices){
  int Index = 0;
  
  for(int z=0;z<depth-1;z++){
    for(int x =0;x<width-1;x++){
      unsigned int BottomLeft = z*width + x;
      unsigned int BottomRight = z*width + x+1;
      unsigned int TopLeft = (z+1)*width + x;
      unsigned int TopRight = (z+1)*width + x+1;

      //add top left riangle
      Indices[Index++] = BottomLeft;
      Indices[Index++] = TopRight;
      Indices[Index++] = TopLeft;

      //bottom right triangle
      Indices[Index++] = TopRight;
      Indices[Index++] = BottomLeft;
      Indices[Index++] = BottomRight;
    }
  }
}
//render
void TriangleList::Render(){
  glUseProgram(ID);

  
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::scale(model,glm::vec3(0.01f));
  glm::mat4 view = lookMat;
  glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

  //set them
  setMat4("model",model,ID);
  setMat4("projection",projection,ID);
  setMat4("view",view,ID);

  //set min max
  setFloat("minHeight",0.0f,ID);
  setFloat("maxHeight",300.0f,ID);
  glBindVertexArray(VAO);

  //glDrawArrays(GL_POINTS,0,depth*width);
  glDrawElements(GL_TRIANGLES,(depth-1)*(width-1)*6,GL_UNSIGNED_INT,NULL);

  glBindVertexArray(0);
}
