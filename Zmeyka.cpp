#include "Zmeyka.h"
ZMEYKA::ZMEYKA()
{  
zmeyka = new  ZMEYKAEL[SizeZmeika];                  
this->StartPosition();    
Size = SizeZmeika;
UpGranica = UP_GRANICA;
RightGranica = RIGHT_GRANICA;
LeftGranica = LEFT_GRANICA;
DownGranica = DOWN_GRANICA;
}

ZMEYKA::ZMEYKA(int size_zmeyka,int up,int left, int right, int down)
{
zmeyka = new  ZMEYKAEL[size_zmeyka];                  
this->StartPosition();    
Size = size_zmeyka;  
UpGranica = up;
RightGranica = right;
LeftGranica = left;
DownGranica = down;
}

ZMEYKA::~ZMEYKA()
{
delete [] zmeyka;                 
}

void ZMEYKA::StartPosition()
{
 Napravlenie = UP;
 zmeyka[0].SetPosition(1,5);  
 zmeyka[1].SetPosition(1,6);
 zmeyka[2].SetPosition(1,7);
 zmeyka[3].SetPosition(1,8);        
}  
//нужно выставить первый элемент змейки на чтото
void ZMEYKA::ZmeykaRight()
{
  if(zmeyka->GetPositionX() == this->RightGranica){
  zmeyka->SetPosition(this->LeftGranica,zmeyka->GetPositionY());                                          
  }
  else zmeyka->SetPosition(zmeyka->GetPositionX()+1,zmeyka->GetPositionY());
  Napravlenie = RIGHT;
}

void ZMEYKA::ZmeykaLeft()
{
if(zmeyka->GetPositionX() == this->LeftGranica){
  zmeyka->SetPosition(this->RightGranica,zmeyka->GetPositionY());                                           
  }
  else zmeyka->SetPosition(zmeyka->GetPositionX()-1,zmeyka->GetPositionY());
  Napravlenie = LEFT;
}

void ZMEYKA::ZmeykaUp()
{
 if(zmeyka->GetPositionY() == this->UpGranica){
  zmeyka->SetPosition(zmeyka->GetPositionX(), this->DownGranica);                                           
  }
  else zmeyka->SetPosition(zmeyka->GetPositionX(),zmeyka->GetPositionY()-1);
  Napravlenie = UP;  
}

void ZMEYKA::ZmeykaDown()
{
 if(zmeyka->GetPositionY() == this->DownGranica){
  zmeyka->SetPosition(zmeyka->GetPositionX(), this->UpGranica);                                           
  }
  else zmeyka->SetPosition(zmeyka->GetPositionX(),zmeyka->GetPositionY()+1);
  Napravlenie = DOWN;
}

void ZMEYKA::GoZmeyka(int KeyDown)
{
  for (int i = this->GetSize()-1; i > 0; i--){
    if(zmeyka[i].Real()) zmeyka[i].SetPosition(zmeyka[i-1]);     
    }
    //исключаем задания направления в саму змейку
  if(KeyDown == RIGHT && Napravlenie == LEFT || KeyDown == LEFT && Napravlenie == RIGHT
  || KeyDown == UP && Napravlenie == DOWN || KeyDown == DOWN && Napravlenie == UP) KeyDown = 0;
  switch (KeyDown){
  case RIGHT:
       this->ZmeykaRight();
       break;
  case LEFT:
       this->ZmeykaLeft();
       break;
  case UP:
       this->ZmeykaUp();
       break;
  case DOWN:
       this->ZmeykaDown();
       break;
  default:
           switch (Napravlenie){
               case RIGHT:
                   this->ZmeykaRight();
                   break;
               case LEFT:
                    this->ZmeykaLeft();
                    break;
               case UP:
                    this->ZmeykaUp();
                    break;
               case DOWN:
                    this->ZmeykaDown();
                     break;        
           }   
   break;
  }   
}

 bool ZMEYKA::ZmeykaDied()
 {
  for(int i = 0; i < this->GetSize()-1; i++){
      for(int j = i+1; j < this->GetSize()-1; j++)
          if(zmeyka[i]== zmeyka[j] && zmeyka[i].Real()) return true;            
  }
 return false;    
 }

bool ZMEYKA::ZmeykaEat(ZMEYKAEL eat)
{
int i=0;
  if(zmeyka[0] == eat){
  while(BufferStek[i].Real())i++;
  BufferStek[i].SetPosition(eat); 
  return true;                                  
  }   
 return false;  
}

void ZMEYKA::ZmeykaIncrease()
{
  bool FlIncrease = true;
  int EndIncrease = 0;
  if(BufferStek[0].Real()){
     for(int i = 0; i < this->GetSize()-1; i++){
          if(zmeyka[i]==BufferStek[0])
              FlIncrease = false;         
     }                    
  } 
 if(FlIncrease){
 while(zmeyka[EndIncrease].Real()) EndIncrease++;
 zmeyka[EndIncrease].SetPosition(BufferStek[0]);
     for(int k = 0; k < SIZE_BUFFER_ZMEIKA-1; k++)
         BufferStek[k] = BufferStek[k+1]; 
 }  
}

int ZMEYKA::GetSize()
{
 return Size;      
}

void ZMEYKA::SetNapravlenie(int N)
{
  Napravlenie = N;   
}

int ZMEYKA::GetNapravlenie()
{
return Napravlenie;    
}

void ZMEYKA::StartPosition(int N,int x,int y,int Size)
{
 Napravlenie = N;
 int tempI=0;
 while(this->zmeyka[tempI].Real()){
     this->zmeyka[tempI].sbros();
     tempI++;
     }
 for (int i=0;i<Size;i++)
 zmeyka[i].SetPosition(x,y++);                 
}
