#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QTime>
#include <QMediaPlayer>
#include "Zmeyka.h"
#include "globject.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLuint zmeykaTextureGL[2];
    bool gameover;
    int frames;
    QTime time;
    GLObject* zmeyaObj;
    GLObject* headzmeyaObj;
    GLObject* eatObj;
    GLObject* backgroundObj;
    GLObject* gameoverObj;
    QMediaPlayer* eatmusic;
    QMediaPlayer* scrimer;
    QMediaPlayer* music;
    ZMEYKA one;
    ZMEYKAEL eat;
    bool key_press;
    explicit GLWidget(QWidget* parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int nWidth, int nHeight);
    void keyPressEvent(QKeyEvent *ke);
    void generateTextures(GLuint* , char* ,int,bool);
    void initializeObjects();

    GLfloat zmeykaVertexArray[4][2];
    GLfloat zmeykaColorArray[4][2];
    GLubyte zmeykaIndexArray[1][4];
public slots:
    void mainLoop();
};

#endif // GLWIDGET_H
