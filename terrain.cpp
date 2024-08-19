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

  int dimensions = sqrt(numElements);
  
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
      Vertices[index].InitVertex(x,z);
      index++;
    }
  }

  glBufferData(GL_ARRAY_BUFFER,sizeof(Vertices[0])*Vertices.size(),&Vertices[0],GL_STATIC_DRAW);
  
}
//init vertex
void Terrain::Vertex::InitVertex(float x, float z){
  this->x = x;
  this->y =0.0f;
  this->z = z;
}
//render
void Terrain::Render(){
  glUseProgram(ID);
  
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = lookMat;
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

  //set them
  setMat4("model",model,ID);
  setMat4("projection",projection,ID);
  setMat4("view",view,ID);
  
  glBindVertexArray(VAO);

  glDrawArrays(GL_POINTS,0,m_depth*m_width);

  glBindVertexArray(0);
}
