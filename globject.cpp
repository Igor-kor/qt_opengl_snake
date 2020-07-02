#include "globject.h"

GLObject::GLObject(char* _TextureName,int _Vershin,int _Izmerenii)
{
    //qDebug("GLObject new( %s, %i, %i)", _TextureName,_Vershin,_Izmerenii);
    Izmerenii = _Izmerenii;
    Vershin = _Vershin;
    //выделим всю память
    Texture = new GLuint;
    TextureName = new char[strlen(_TextureName)+1];
    strcpy(TextureName,_TextureName);

    TextureArray = new GLfloat[Izmerenii * Vershin];
    IndexArray = new GLubyte[4];
    VertexArray = new GLfloat[Izmerenii * Vershin];
}

void GLObject::generateTextures()
{
    //qDebug("GLObject generateTextures");
    glGenTextures(1, Texture);

    QImage texture1;
    texture1.load(TextureName);
    texture1 = QGLWidget::convertToGLFormat(texture1);
    glBindTexture(GL_TEXTURE_2D, Texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)texture1.width(), (GLsizei)texture1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture1.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void GLObject::DrawObject(float x, float y, int _width, int _heigth, int numbTexture)
{
    if(x!=0||y!=0){
        for(int i = 0; i < Izmerenii*Vershin; i+=Izmerenii)
        {
            VertexArray[i]+=x;
            VertexArray[i+1]+=y;
        }
    }
    //qDebug("GLObject DravObject");
    glBindTexture(GL_TEXTURE_2D, *Texture);
    glVertexPointer(Izmerenii, GL_FLOAT, 0, VertexArray);
    // glColorPointer(4, GL_FLOAT, 0, zmeykaColorArray);
    glTexCoordPointer(Izmerenii, GL_FLOAT,0, TextureArray);
    glDrawElements(GL_QUADS, Vershin, GL_UNSIGNED_BYTE, IndexArray);
    if(x!=0||y!=0){
        for(int i = 0; i < Izmerenii*Vershin; i+=Izmerenii)
        {
            VertexArray[i]-=x;
            VertexArray[i+1]-=y;
        }
    }
}

