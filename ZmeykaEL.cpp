#include "ZmeykaEL.h"
#include <stdlib.h>

void ZMEYKAEL::Randomized(int maxX, int maxY)
{
x = rand()%maxX; 
y = rand()%maxY;      
}

bool ZMEYKAEL::Real()
{
  return  (this->GetPositionX() == this->GetPositionY() && this->GetPositionX() == -1) != 1;            
}

ZMEYKAEL::ZMEYKAEL(){
   this->sbros();
}

void ZMEYKAEL::sbros(){
    x=-1;
    y=-1;     
}

void ZMEYKAEL::SetPosition(int KorX,int KorY)
{
x = KorX;
y = KorY;        
}

int ZMEYKAEL::GetPositionX()
{
return x;       
}

int ZMEYKAEL::GetPositionY()
{
return y;       
}


bool ZMEYKAEL::operator ==(ZMEYKAEL const & point)
{
 return x == point.x && y == point.y;      
}

bool ZMEYKAEL::operator !=(ZMEYKAEL const & point)
{
return (x != point.x && y != point.y);      
}


void ZMEYKAEL::SetPosition(ZMEYKAEL setZmeyka)
{
x = setZmeyka.GetPositionX();
y = setZmeyka.GetPositionY();      
}
