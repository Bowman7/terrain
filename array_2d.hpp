#pragma once


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

//temp init
template<typename T>

class Array2D{
public:
  Array2D(){}

  Array2D(int Cols,int Rows){
    InitArray2D(Cols,Rows);
  }
  //init and allocate size to ptr
  void InitArray2D(int Cols,int Rows){
    this->cols = Cols;
    this->rows = Rows;
    
    if(ptr){
      free(ptr);
    }
    //allocate memeory to point
    ptr = (Type*)malloc(cols*rows*sizeof(Type));
  }
  
  //init a certain val to ptr
  void InitArray2D(int Cols,int Rows,Type InitVal){
    //allocate mem first
    InitArray2D(Cols,Rows);

    for(int i=0;i<Cols*Rows;i++){
      ptr[i] = InitVal;
    }
  }

  //ptr point to some data
  void InitArray2D(int Cols,int Rows,void* pData){
    this->cols = Cols;
    this->rows = Rows;

    if(ptr){
      free(ptr);
    }

    ptr = (Type*)pData;
  }

  //destroy
  ~Array2D(){
    Destroy();
  }

  void Destroy(){
    if(ptr){
      free(ptr);
      ptr = NULL;
    }
  }

  //get value at certain add
  Type* GetAddr(int Col,int Row) const {
    size_t Index = ClacIndex(Col,Row);

    return &ptr[Index];
  }

  //return base addr
  Type* GetBaseAddr() const {
    return ptr;
  }

  //size
  int GetSize() const {
    return rows*cols;
  }

  //in bytes
  int GetSizeInBytes(){
    return GetSize()*sizeof(Type);
  }
  //direct referenc to data
  const Type& Get(int Col,int Row){
    return *GetAddr(Col,Row);
  }

  //return with index
  const Type& Get(int index){

    if(index >= rows*cols){
      printf("Index exceeds size\n");
    }

    return ptr[index];
  }
  //same but with AT
  Type& At(int Col, int Row)
  {
    size_t Index = CalcIndex(Col, Row);
    
    return ptr[Index];
  }

  //set val
  void Set(int Col,int Row, const Type& Val){
    *GetAddr(Col,Row) = Val;
  }

  //set with index
  void Set(int Index,const Type& Val){
    if(Index>=rows*cols){
      printf("Index exceeds size\n");
    }
    ptr[Index] = Val;
  }

  //get MinMax
  void GetMinMax(Type& Min,Type& Max){
    Max = Min = ptr[0];

    for(int i=1;i<rows*cols;i++){
      if(ptr[i]<Min){
	Min = ptr[i];
      }
      if(ptr[i]>Max){
	Max = ptr[i];
      }
    }
  }

  //normalize
  void Normalize(Type MinRange,Type MaxRange){
    Type Min,Max;

    GetMinMax(Min,Max);
    if(Max<=Min){
      return;
    }

    Type MinMaxDelta = Max - Min;
    Type MinMaxRange = MaxRange - MinRange;

    for(int i=0;i<rows*cols;i++){
      ptr[i] = ((ptr[i]-Min)/MinMaxDelta) * MinMaxRange + MinRange;
    }
  }

  //print floats
  void PrintFloat(){
    for(int y =0;i<rows;y++){
      printf("%d: ",y);
      for(int x = 0;x<cols;x++){
	float f = (float)ptr[y*rows+x];
	printf("%.6f ",f);
      }
      printf("\n");
    }
  }
private:
  //calculate index
  size_t CalcIndex(int Col,int Row){
    if(Col < 0){
      printf("Col is less than 0\n");
    }
    if(Col >= cols){
      printf("Column overflow\n");
    }
    if(Row<0){
      printf("Row is less than 0\n");
    }
    if(Row>=rows){
      printf("Rows overflow\n");
    }

    size_t index = Row* cols+Col;

    return index;
  }
  
  Type* ptr = NULL;
  int cols = 0;
  int rows = 0;
};
