class ZMEYKAEL
{
     private:
              int x;
              int y;
     public:
         ZMEYKAEL();
         void sbros();
         int GetPositionX();
         int GetPositionY();
         void SetPosition(int x,int y);
         void SetPosition(ZMEYKAEL setZmeyka);
         bool Real();
         void Randomized(int maxX, int maxY);
         bool operator== (ZMEYKAEL const & point);
         bool operator!= (ZMEYKAEL const & point);
};
