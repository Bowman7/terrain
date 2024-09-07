#include"midpoint.hpp"

void Midpoint::CreateMidpointDisplacement(int terrainSize,float MinHeight,float MaxHeight,float roughness){
  this->TerrainSize = terrainSize;
  this->MinHeight = MinHeight;
  this->MaxHeight = MaxHeight;

  heightMap.InitArray2D(TerrainSize,TerrainSize,0.0f);

  CreateMidpointDisplacementNow(roughness);

  heightMap.Normalize(MinHeight,MaxHeight);

  triangleList.CreateTriangleList(TerrainSize,TerrainSize,this);
}
void Midpoint::CreateMidpointDisplacementNow(float roughness){
  int RectSize = TerrainSize;
  float CurHeight = (float)RectSize/2.0f;
  float HeightReduced = pow(2.0f,-roughness);

  while(RectSize>0){
    DiamondStep(RectSize,CurHeight);
    SquareStep(RectSize,CurHeight);

    RectSize /=2;
    CurHeight *= HeightReduced;
  }
}

void Midpoint::DiamondStep(int RectSize,float CurHeight){
  int HalfRectSize = RectSize/2;

  for(int y=0;y<TerrainSize;y+=RectSize){
    for(int x =0;x<TerrainSize;x+=RectSize){
      int next_x = (x+RectSize)%TerrainSize;
      int next_y = (y+RectSize)%TerrainSize;

      float TopLeft = heightMap.Get(x,y);
      float TopRight = heightMap.Get(next_x,y);
      float BottomLeft = heightMap.Get(x,next_y);
      float BottomRight = heightMap.Get(next_x,next_y);

      int mid_x = x+HalfRectSize;
      int mid_y = y+HalfRectSize;

      float RandValue = RandomFloatRange(CurHeight,-CurHeight);
      float MidPoint =(TopLeft+TopRight+BottomLeft+BottomRight)/4.0f;

      heightMap.Set(mid_x,mid_y,MidPoint+RandValue);
    }
  }
}

void Midpoint::SquareStep(int RectSize,float CurHeight){
  int HalfRectSize = RectSize/2;

  for(int y=0;y<TerrainSize;y+=RectSize){
    for(int x=0;x<TerrainSize;x+=RectSize){
      int next_x=(x+RectSize)%TerrainSize;
      int next_y=(y+RectSize)%TerrainSize;

      int mid_x = x+HalfRectSize;
      int mid_y = y+HalfRectSize;
      
      int prev_mid_x = (x-HalfRectSize+TerrainSize)%TerrainSize;
      int prev_mid_y = (y-HalfRectSize+TerrainSize)%TerrainSize;

      float CurTopLeft = heightMap.Get(x,y);
      float CurTopRight = heightMap.Get(next_x,y);
      float CurBottomLeft = heightMap.Get(x,next_y);
      float CurCentre = heightMap.Get(mid_x,mid_y);
      float PrevXMid = heightMap.Get(prev_mid_x,mid_y);
      float PrevYMid = heightMap.Get(mid_x,prev_mid_y);

      float RandValue = RandomFloatRange(CurHeight,-CurHeight);
      float CurLeftMid = (PrevXMid+CurCentre+CurTopLeft+CurBottomLeft)/4.0f;
      float CurTopMid = (CurTopLeft+CurCentre+ CurTopRight+PrevYMid)/4.0f;

      heightMap.Set(mid_x,y,CurTopMid+RandValue);
      heightMap.Set(x,mid_y,CurLeftMid+RandValue);
    }
  }
}

float Midpoint::RandomFloatRange(float h1,float h2){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float>dis(h1,h2);

  return dis(gen);
}
