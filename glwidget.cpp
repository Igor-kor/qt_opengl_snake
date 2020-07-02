#include <QKeyEvent>
#include "glwidget.h"
GLWidget::GLWidget(QWidget* parent) : QGLWidget(parent)
{
    //qDebug("GLWidget new");
    gameover = false;
    one.StartPosition(20,20,20,10);
    eat.Randomized(100,100);
    one.SetNapravlenie(1);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mainLoop()));
    timer->start(50);

    scrimer = new QMediaPlayer;
    connect(scrimer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    scrimer->setMedia(QUrl::fromLocalFile("s.mp3"));
    scrimer->setVolume(100);

    eatmusic = new QMediaPlayer;
    connect(eatmusic, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    eatmusic->setMedia(QUrl::fromLocalFile("keke.mp3"));
    eatmusic->setVolume(50);
    eatmusic->play();
}

void GLWidget::initializeGL()
{
    //qDebug("GLWidget initializeGL");
    qglClearColor(Qt::gray);
    glEnable(GL_TEXTURE_2D);

    //this->generateTextures(zmeykaTextureGL,":/cubeOne.jpg",1,true);
    initializeObjects();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void GLWidget::paintGL()
{
    //qDebug("GLWidget paintGL");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,102,106,-1,1,0);

    if(gameover)
    {
        gameoverObj->DrawObject(0,0,0,0,0);
    }
    else
    {
        backgroundObj->DrawObject(0,0,0,0,0);
        //snake
        int tempSizeZmeyka =0;
        headzmeyaObj->DrawObject(one.zmeyka[0].GetPositionX(),one.zmeyka[0].GetPositionY(),1,1,0);
        for(int i = 1; i<one.GetSize()-1; i++)
        {
            if(one.zmeyka[i].Real())
            {
                tempSizeZmeyka++;
                zmeyaObj->DrawObject(one.zmeyka[i].GetPositionX(),one.zmeyka[i].GetPositionY(),1,1,0);
            }
        }

        //eat
        eatObj->DrawObject(eat.GetPositionX(),eat.GetPositionY(),0,0,0);



    //score
     glColor4f(1,0,0,1);
     renderText(0, 105 , 1, QString::fromUtf8("Ваша змейка %1:").arg(tempSizeZmeyka));
    }
     //fps
     QString framesPerSecond;
        framesPerSecond.setNum(frames /(time.elapsed() / 1000.0), 'f', 2);
        renderText(80, 105 , 1, QString::fromUtf8("FPS:%1").arg(framesPerSecond));
        if (!(frames % 100))
        {
            time.start();
            frames = 0;
        }
        frames ++;
}

void GLWidget::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void GLWidget::keyPressEvent(QKeyEvent *ke)
{
    //qDebug("GLWidget keyPressEvent");
    switch (ke->key())
       {

             case Qt::Key_Up:
                    if(one.GetNapravlenie() != UP && one.GetNapravlenie() != DOWN && key_press)
                    {
                        one.SetNapravlenie(UP);//it is BUG in  glOrtho(101,0,101,0,1,0);
                        key_press = false;
                    }
                    break;

             case Qt::Key_Down:
                    if(one.GetNapravlenie() != UP && one.GetNapravlenie() != DOWN && key_press)
                    {
                        one.SetNapravlenie(DOWN);//it is BUG in  glOrtho(101,0,101,0,1,0);
                        key_press = false;
                    }
                    break;

             case Qt::Key_Right:
                    if(one.GetNapravlenie() != RIGHT && one.GetNapravlenie() != LEFT && key_press)
                    {
                        one.SetNapravlenie(RIGHT);//it is BUG in  glOrtho(101,0,101,0,1,0);
                        key_press = false;
                    }
                    break;

             case Qt::Key_Left:
                    if(one.GetNapravlenie() != RIGHT && one.GetNapravlenie() != LEFT && key_press)
                    {
                        one.SetNapravlenie(LEFT);//it is BUG in  glOrtho(101,0,101,0,1,0);
                        key_press = false;
                    }
                    break;
             case 32: //space
                    if(gameover)
                    {
                        gameover = false;
                        one.StartPosition(20,20,20,10);
                        eat.Randomized(100,100);
                        one.SetNapravlenie(1);
                        //qDebug("Enter");
                    }
                    break;
       }
}

void GLWidget::mainLoop()
{
    //qDebug("GLWidget mainLoop");
    key_press = true;
    one.GoZmeyka(0);
    if(one.ZmeykaDied())
    {
        gameover = true;
        scrimer->play();
    }
    if(one.ZmeykaEat(eat))
    {
        eat.Randomized(100,100);
        eatmusic->stop();
        eatmusic->play();
    }
    one.ZmeykaIncrease();
    updateGL();
}

void GLWidget::generateTextures(GLuint* textureGL, char* textureImage,int texturesize,bool firsttexture = true)
{
    //qDebug("GLWidget generateTextures");
    if(firsttexture)glGenTextures(texturesize, textureGL);

    QImage texture1;
    texture1.load(textureImage);
    texture1 = QGLWidget::convertToGLFormat(texture1);
    glBindTexture(GL_TEXTURE_2D, *textureGL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)texture1.width(), (GLsizei)texture1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture1.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void GLWidget::initializeObjects()
{
    //qDebug("GLWidget initializeObjects");
    eatObj = new GLObject(":/eattexture.jpg",4,2);
    backgroundObj = new GLObject(":/backgroundtexture.jpg",4,2);
    zmeyaObj = new GLObject(":/zmeykatexture.jpg",4,2);
    gameoverObj = new GLObject(":/gameovertexture2.jpg",4,2);
    headzmeyaObj = new GLObject(":/headtexture.jpg",4,2);

    eatObj->generateTextures();
    backgroundObj->generateTextures();
    zmeyaObj->generateTextures();
    gameoverObj->generateTextures();
    headzmeyaObj->generateTextures();

    //====zmeya
    zmeyaObj->IndexArray[0] = 0;
    zmeyaObj->IndexArray[1] = 3;
    zmeyaObj->IndexArray[2] = 2;
    zmeyaObj->IndexArray[3] = 1;

    zmeyaObj->TextureArray[0] = 0.0;
    zmeyaObj->TextureArray[1] = 0.0;

    zmeyaObj->TextureArray[2] = 1.0;
    zmeyaObj->TextureArray[3] = 0.0;

    zmeyaObj->TextureArray[4] = 1.0;
    zmeyaObj->TextureArray[5] = 1.0;

    zmeyaObj->TextureArray[6] = 0.0;
    zmeyaObj->TextureArray[7] = 1.0;

    //1
    zmeyaObj->VertexArray[0] = 0.0;
    zmeyaObj->VertexArray[1] = 1.0;

    //2
    zmeyaObj->VertexArray[2] = 1.0;
    zmeyaObj->VertexArray[3] = 1.0;

    //3
    zmeyaObj->VertexArray[4] = 1.0;
    zmeyaObj->VertexArray[5] = 0.0;

    //4
    zmeyaObj->VertexArray[6] = 0.0;
    zmeyaObj->VertexArray[7] = 0.0;
    //=====zmeya

    //====head
    headzmeyaObj->IndexArray[0] = 0;
    headzmeyaObj->IndexArray[1] = 3;
    headzmeyaObj->IndexArray[2] = 2;
    headzmeyaObj->IndexArray[3] = 1;

    headzmeyaObj->TextureArray[0] = 0.0;
    headzmeyaObj->TextureArray[1] = 0.0;

    headzmeyaObj->TextureArray[2] = 1.0;
    headzmeyaObj->TextureArray[3] = 0.0;

    headzmeyaObj->TextureArray[4] = 1.0;
    headzmeyaObj->TextureArray[5] = 1.0;

    headzmeyaObj->TextureArray[6] = 0.0;
    headzmeyaObj->TextureArray[7] = 1.0;

    //1
    headzmeyaObj->VertexArray[0] = 0.0;
    headzmeyaObj->VertexArray[1] = 1.0;

    //2
    headzmeyaObj->VertexArray[2] = 1.0;
    headzmeyaObj->VertexArray[3] = 1.0;

    //3
    headzmeyaObj->VertexArray[4] = 1.0;
    headzmeyaObj->VertexArray[5] = 0.0;

    //4
    headzmeyaObj->VertexArray[6] = 0.0;
    headzmeyaObj->VertexArray[7] = 0.0;
    //=====head


    //====eat
    eatObj->IndexArray[0] = 0;
    eatObj->IndexArray[1] = 3;
    eatObj->IndexArray[2] = 2;
    eatObj->IndexArray[3] = 1;

    eatObj->TextureArray[0] = 0.0;
    eatObj->TextureArray[1] = 0.0;

    eatObj->TextureArray[2] = 1.0;
    eatObj->TextureArray[3] = 0.0;

    eatObj->TextureArray[4] = 1.0;
    eatObj->TextureArray[5] = 1.0;

    eatObj->TextureArray[6] = 0.0;
    eatObj->TextureArray[7] = 1.0;

    //1
    eatObj->VertexArray[0] = 0.0;
    eatObj->VertexArray[1] = 1.0;

    //2
    eatObj->VertexArray[2] = 1.0;
    eatObj->VertexArray[3] = 1.0;

    //3
    eatObj->VertexArray[4] = 1.0;
    eatObj->VertexArray[5] = 0.0;

    //4
    eatObj->VertexArray[6] = 0.0;
    eatObj->VertexArray[7] = 0.0;
    //=====eat

    //====background
    backgroundObj->IndexArray[0] = 0;
    backgroundObj->IndexArray[1] = 3;
    backgroundObj->IndexArray[2] = 2;
    backgroundObj->IndexArray[3] = 1;

    backgroundObj->TextureArray[0] = 0.0;
    backgroundObj->TextureArray[1] = 0.0;

    backgroundObj->TextureArray[2] = 1.0;
    backgroundObj->TextureArray[3] = 0.0;

    backgroundObj->TextureArray[4] = 1.0;
    backgroundObj->TextureArray[5] = 1.0;

    backgroundObj->TextureArray[6] = 0.0;
    backgroundObj->TextureArray[7] = 1.0;

    //1
    backgroundObj->VertexArray[0] = -1.0;
    backgroundObj->VertexArray[1] = 106.0;

    //2
    backgroundObj->VertexArray[2] = 102.0;
    backgroundObj->VertexArray[3] = 106.0;

    //3
    backgroundObj->VertexArray[4] = 102.0;
    backgroundObj->VertexArray[5] = -1.0;

    //4
    backgroundObj->VertexArray[6] = -1.0;
    backgroundObj->VertexArray[7] = -1.0;
    //=====background


    //====gameover
    gameoverObj->IndexArray[0] = 0;
    gameoverObj->IndexArray[1] = 3;
    gameoverObj->IndexArray[2] = 2;
    gameoverObj->IndexArray[3] = 1;

    gameoverObj->TextureArray[0] = 0.0;
    gameoverObj->TextureArray[1] = 0.0;

    gameoverObj->TextureArray[2] = 1.0;
    gameoverObj->TextureArray[3] = 0.0;

    gameoverObj->TextureArray[4] = 1.0;
    gameoverObj->TextureArray[5] = 1.0;

    gameoverObj->TextureArray[6] = 0.0;
    gameoverObj->TextureArray[7] = 1.0;

    //1
    gameoverObj->VertexArray[0] = -1.0;
    gameoverObj->VertexArray[1] = 106.0;

    //2
    gameoverObj->VertexArray[2] = 102.0;
    gameoverObj->VertexArray[3] = 106.0;

    //3
    gameoverObj->VertexArray[4] = 102.0;
    gameoverObj->VertexArray[5] = -1.0;

    //4
    gameoverObj->VertexArray[6] = -1.0;
    gameoverObj->VertexArray[7] = -1.0;
    //=====gameover
}
