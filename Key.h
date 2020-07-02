#ifndef KEY_KONTROL_COUNT
#define KEY_KONTROL_COUNT 4 
#endif
class Key
{
      public:
int KeyDown;
   
bool FDown;   
int KeyFun;

void Snap();   
Key();     
};

 Key::Key()
{
FDown = false;
KeyDown = 0;     
}

void Key::Snap()
{
  if(GetKeyState(KeyDown) < 0)  FDown = true;
  else  FDown = false;
}


class KeyControl
{
      public:
      //можно динамически выделять без константы
Key key[KEY_KONTROL_COUNT];
int sleep;
void (*fun)(int);   

void Control();
KeyControl(void (*fun2)(int));      
};

void KeyControl::Control()
{
     int k = 0;
     while(true){
     //делаем снимок всех кнопок
     for(int i=0; i<KEY_KONTROL_COUNT; i++)
     key[i].Snap();
     //далее обрабатываем
     for(int i=0; i<KEY_KONTROL_COUNT; i++)
     if(key[i].FDown){
        fun(key[i].KeyFun);
         Sleep(5*(sleep-k));
         return;
     }
     Sleep(5);
     if(k >= sleep){
          fun(0);
          break;
          }
     k++;
     } 
}

KeyControl::KeyControl(void (*fun2)(int))
{
 fun = fun2;
 sleep = 40;
 key[0].KeyDown = VK_LEFT;
 key[0].KeyFun = LEFT;     
 key[1].KeyDown = VK_DOWN;
 key[1].KeyFun = DOWN; 
 key[2].KeyDown = VK_RIGHT;
 key[2].KeyFun = RIGHT; 
 key[3].KeyDown = VK_UP;
 key[3].KeyFun = UP;                   
}
