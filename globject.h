#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <QGLWidget>

class GLObject
{
public:
    GLuint* Texture;
    char* TextureName;
    GLfloat* VertexArray;
    GLfloat* TextureArray;
    GLubyte* IndexArray;
    int Izmerenii;
    int Vershin;
    void generateTextures();
    GLObject(char* _TextureName,int _Vershin,int _Izmerenii);
    void DrawObject(float x, float y, int _width, int _heigth, int numbTexture);
};

#endif // GLOBJECT_H
