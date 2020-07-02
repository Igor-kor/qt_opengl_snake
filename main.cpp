#include <QApplication>
#include "glwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GLWidget scene;
    scene.resize(700,700);
    scene.resizeGL(700, 700);
    scene.show();
    return a.exec();
}
