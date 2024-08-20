#include"terrain.hpp"

Terrain::Terrain(){

  
}
Terrain::~Terrain(){

}

void Terrain::Update(glm::mat4 look){
  lookMat = look;
}
void Terrain::LoadTerrain(const char* filename){
  FILE *fptr;

  fptr = fopen(filename,"rb");
  if(fptr == NULL){
    printf("Could not open file\n");
    exit(-1);
  }

  //find file size
  fseek(fptr,0,SEEK_END);
  long size = ftell(fptr);
  fseek(fptr,0,SEEK_SET);

  float* file = (float*)malloc(size);
  

  fread(file,1,size,fptr);
  

  //file after read
  int numElements =size/sizeof(float);
  printf("NUm elements: %d\n",numElements);

  int dimensions = sqrt(numElements);
  printf("Dimensions: %d\n",dimensions);
  
  for(int i=0;i<numElements;i++){
    //printf(" %f ",file[i]);
  }

  row = dimensions;
  col = dimensions;
  file_size = size;
  file_data = file;
  printf("row: %d col: %d filesize: %ld\n",row,col,file_size);
  printf("File data: \n");
  for(int i=0;i<numElements;i++){
    //printf(" %f ",file_data[i]);
  }
  fclose(fptr);
}
//create triagnel list
void Terrain::CreateTriangleList(){
 
  m_width = row;
  m_depth = col;
  printf("int tlist w: %d depth: %d\n",m_width,m_depth);
  
  //init states
  glGenVertexArrays(1,&VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1,&VBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);

  glGenBuffers(1,&EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(0*sizeof(float)));

  //populate vertex buffer
  std::vector<Vertex> Vertices;
  Vertices.resize(m_width * m_depth);
  printf("Vertices size: %ld\n",Vertices.size());

  long unsigned int index =0;

  for(int z =0;z<m_depth;z++){
    for(int x =0;x<m_width;x++){
      assert(index< Vertices.size());
      float y = file_data[index];
      Vertices[index].InitVertex(world_scale*x,y,world_scale*z);
      index++;
    }
  }
  //populate indices
  std::vector<unsigned int>Indices;
  int NumQuads = (m_width-1)*(m_depth-1);
  Indices.resize(NumQuads*6);

  //fill indices
  long unsigned int Index = 0;

  for(int z =0;z<m_depth-1;z++){
    for(int x =0;x<m_width-1;x++){
      unsigned int IndexBottomLeft =z*m_width+x;
      unsigned int IndexTopLeft = (z+1)*m_width +x;
      unsigned int IndexTopRight = (z+1)*m_width +(x+1);
      unsigned int IndexBottomRight = z*m_width +(x+1);

      //add top left triangle
      Indices[Index++] = IndexBottomLeft;
      Indices[Index++] = IndexTopLeft;
      Indices[Index++] = IndexTopRight;

      //add bottom right triangle
      Indices[Index++] = IndexBottomLeft;
      Indices[Index++] = IndexBottomRight;
      Indices[Index++] = IndexTopRight;
      
    }
  }

  
  glBufferData(GL_ARRAY_BUFFER,sizeof(Vertices[0])*Vertices.size(),&Vertices[0],GL_STATIC_DRAW);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Indices[0])*Indices.size(),&Indices[0],
	       GL_STATIC_DRAW);
  
}
//init vertex
void Terrain::Vertex::InitVertex(float x,float y, float z){
  this->x = x;
  this->y = y;
  this->z = z;
}
//render
void Terrain::Render(){
  glUseProgram(ID);
  
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::scale(model,glm::vec3(0.01f));
  glm::mat4 view = lookMat;
  glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

  //set them
  setMat4("model",model,ID);
  setMat4("projection",projection,ID);
  setMat4("view",view,ID);
  
  glBindVertexArray(VAO);

  //glDrawArrays(GL_POINTS,0,m_depth*m_width);
  glDrawElements(GL_TRIANGLES,(m_depth-1)*(m_width-1)*6,GL_UNSIGNED_INT,NULL);

  glBindVertexArray(0);
}
