#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include <QFileDialog>
#include <QOpenGLWidget>
#include <QtOpenGL>

#include "qgifimage.h"

extern "C" {
#include "../s21_3dv.h"
}

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  GLWidget(QWidget *parent);
  int frust_check = 0, line_check = 0, save_param_check = 0, dot_thickness,
      sqr_point_check = 0, time = 0;
  int sizeofperspective, sizeofnearval, sizeoffarval;
  float xRot, yRot, zRot;
  QPoint mPos;
  QSettings mySettings;
  QTimer *tmr = new QTimer();
  QGifImage *gif = new QGifImage;
  struct data *obj;
  QString fname_gif;
  char *filename;
  double z_position = -600;
  double r_line, g_line, b_line, r_point, g_point, b_point, r_bg, g_bg, b_bg;
  double line_thickness;
  void openFile();
  void drawCube();
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void save_settings();
  void get_settings();
  void wtimer();
  void jpegFile(QString name);

 public:
 signals:
  //

 public slots:
  void gifFile();
};

#endif  // GLWIDGET_H
