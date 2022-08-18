#ifndef WIDGET_H
#define WIDGET_H
#define GL_SILENCE_DEPRECATION

#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QBasicTimer>
#include <QStringList>
#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QOpenGLFunctions>
#include <QGuiApplication>
#include <QTimer>
#include <QMouseEvent>
#include <QMainWindow>
#include <QFileDialog>
#include <QVector>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QSize>


#ifdef __cplusplus
extern "C"{
#endif
    #include "brain.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class Widget;}
QT_END_NAMESPACE

class Widget : public QOpenGLWidget
{
    Q_OBJECT
private:
    float z;
    float x;
    float xRot, yRot, zRot;
    QPoint mPos;
    QTimer tmr;
    void drawCube(float a);
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void initializeGL() override;

    double *arr = NULL;
    int *arr2 = NULL;
    int count_of_facets = 0;






public:

    Widget(QWidget *parent = nullptr);
    ~Widget();
    int fr = 0;
    int fg = 0;
    int fb = 0;
    int pr = 200;
    int pg = 0;
    int pb = 0;
    int lr = 0;
    int lg = 200;
    int lb = 0;
    int line_type = 0;
    int splits = 7;
    double shift = 0;
    int cor = 0;
    int dir = 0;
    double angle = 0;
    int rcor = 0;
    int max = 0;
    int min = 0;
    int moreless = 0;
    int point = 0;
    int pointsize = 10;
    int linesize = 1;
    //
    char *filename_global;
    char *info;
    int cof = 0;
    int vert = 0;
    int screenflag = 0;
    QString cof2;
    QString vert2;
    int shiftflag = 0;
    int rotflag = 0;
    int lessflag = 0;
    int proectionflag = 1;





    void glMatixMode();






private:
    Ui::Widget *ui;
public slots:
    void changeZ();
    void pluspsize();
    void minpsize();
    void pls();
    void mls();
    void filename();
    void reload();
    void open_config();
    void write_config();
//    void zagolovok();
private slots:
};

#endif // WIDGET_H
