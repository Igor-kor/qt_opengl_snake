#include "ZmeykaEL.h"

#ifndef RIGHT
#define RIGHT 1
#endif

#ifndef LEFT
#define LEFT 2
#endif

#ifndef UP
#define UP 3
#endif

#ifndef DOWN
#define DOWN 4
#endif

#ifndef RIGHT_GRANICA
#define RIGHT_GRANICA 100
#endif

#ifndef LEFT_GRANICA
#define LEFT_GRANICA 0
#endif

#ifndef UP_GRANICA
#define UP_GRANICA 0
#endif

#ifndef DOWN_GRANICA
#define DOWN_GRANICA 100
#endif

#ifndef SizeZmeika
#define SizeZmeika 500
#endif

#ifndef SIZE_BUFFER_ZMEIKA
#define SIZE_BUFFER_ZMEIKA 20
#endif


class ZMEYKA
{
   private:
          int UpGranica;
          int RightGranica;
          int LeftGranica;
          int DownGranica;
          int Size;
          int Napravlenie;
          ZMEYKAEL BufferStek[SIZE_BUFFER_ZMEIKA]; 
   public:
          ZMEYKAEL* zmeyka;
          void StartPosition();
          void StartPosition(int N,int x,int y,int Size); 
          void GoZmeyka(int KeyDown); 
          void ZmeykaRight();
          void ZmeykaLeft();
          void ZmeykaUp();
          void ZmeykaDown();
          bool ZmeykaEat(ZMEYKAEL eat);
          bool ZmeykaDied();
          void ZmeykaIncrease();
          ZMEYKA();
          ZMEYKA(int size_zmeyka,int up,int left, int right, int down);
          ~ZMEYKA();
          int GetSize();
          void SetNapravlenie(int N);
          int GetNapravlenie(); 
};
