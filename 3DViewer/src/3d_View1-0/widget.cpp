#include "widget.h"
#include "ui_widget.h"
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>

#define FILE_PATH "/Users/grisella/develop/C8_3DViewer_v1.0-0/src/3d_View1-0/conf.txt"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setWindowTitle("Threed");
    setGeometry(400, 200, 800, 600);
    z = 0;
    x = 0;
    open_config();
    connect(&tmr, SIGNAL(timeout()), this, SLOT(changeZ()));
    tmr.start(100);
    filename();
    cof = converter(&arr, &arr2, &count_of_facets, &min, &max, &vert, filename_global);
    cof2 = QString::number(cof);
    vert2 = QString::number(vert);

}

void Widget::open_config() {
    char str[512] = {'\0'};
    char num[512] = {'\0'};
    FILE *txt =  fopen(FILE_PATH, "rt");
      if (txt != NULL) {
          int count = 0;
          while(fgets(str, 511, txt) != NULL) {
                  int k = 0;
                  for (int i = 0; str[i] != '\0'; i++) {
                      num[k++] = str[i];
                  }
                  if (count == 0) fr = atoi(num);
                  if (count == 1) fg = atoi(num);
                  if (count == 2) fb = atoi(num);
                  if (count == 3) pr = atoi(num);
                  if (count == 4) pg = atoi(num);
                  if (count == 5) pb = atoi(num);
                  if (count == 6) lr = atoi(num);
                  if (count == 7) lg = atoi(num);
                  if (count == 8) lb = atoi(num);
                  if (count == 9) line_type = atoi(num);
                  if (count == 10) splits = atoi(num);
                  if (count == 11) shift = atof(num);
                  if (count == 12) cor = atoi(num);
                  if (count == 13) dir = atoi(num);
                  if (count == 14) angle = atof(num);
                  if (count == 15) rcor = atoi(num);
                  if (count == 16) max = atoi(num);
                  if (count == 17) min = atoi(num);
                  if (count == 18) moreless = atoi(num);
                  if (count == 19) point = atoi(num);
                  if (count == 20) pointsize = atoi(num);
                  if (count == 21) linesize = atoi(num);
                  for (int i = 1; str[i] != '\0'; i++) {
                      str[i] = '\0';
                  }
                  count++;
            }
             fclose(txt);
        }
      else {
          printf("NETU !");
      }
}

void Widget::write_config() {
    FILE *txt =  fopen(FILE_PATH, "wt");
      if (txt != NULL) {
          fprintf(txt, "%d\n", fr);
          fprintf(txt, "%d\n", fg);
          fprintf(txt, "%d\n", fb);
          fprintf(txt, "%d\n", pr);
          fprintf(txt, "%d\n", pg);
          fprintf(txt, "%d\n", pb);
          fprintf(txt, "%d\n", lr);
          fprintf(txt, "%d\n", lg);
          fprintf(txt, "%d\n", lb);
          fprintf(txt, "%d\n", line_type);
          fprintf(txt, "%d\n", splits);
          fprintf(txt, "%lf\n", shift);
          fprintf(txt, "%d\n", cor);
          fprintf(txt, "%d\n", dir);
          fprintf(txt, "%lf\n", angle);
          fprintf(txt, "%d\n", rcor);
          fprintf(txt, "%d\n", max);
          fprintf(txt, "%d\n", min);
          fprintf(txt, "%d\n", moreless);
          fprintf(txt, "%d\n", point);
          fprintf(txt, "%d\n", pointsize);
          fprintf(txt, "%d\n", linesize);
          fclose(txt);
        }
      else {
          printf("NETU!");
      }
}

Widget::~Widget()
{
    write_config();
    free(arr);
    free(arr2);
}

void Widget::initializeGL() {

}

void Widget::filename() {
        QString path_to_file = QFileDialog::getOpenFileName(NULL, "Open", "/Users/", "*.obj");


  char* filename = new char[path_to_file.length()];
  QByteArray barr = path_to_file.toLatin1();
  strlcpy(filename, barr, path_to_file.length() + 1);
filename_global = filename;

}



void Widget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (qFabs(min) > max) {
            max = qFabs(min);
        } else if (max > qFabs(min)) {
            min = -max;
        }
    if (min <= 0 && min > -15) {
            min *= 5;
            max *= 5;
    } else {
        min*=1.2;
        max*=1.2;
    }
    glOrtho(min,max,min,max,min,max);
//    glFrustum(min,max,min,max,min,max);

}


void Widget::paintGL() {
    glTranslatef(0, 0, -4);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(fr, fg, fb, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);


    if (shiftflag) {
        LomatMatrix(&arr, vert, shift, cor, dir);
        shiftflag = 0;
    }

    if (rotflag) {
        Rmat(&arr, angle, rcor, vert);
        rotflag = 0;
    }

    if (lessflag) {
        lesser(&arr, vert, moreless);
        lessflag = 0;
    }






    glVertexPointer(3, GL_DOUBLE, 0, arr);
    glEnableClientState(GL_VERTEX_ARRAY);

    if (point == 1) {
    glEnable(GL_POINT_SMOOTH);
    }



    glPointSize(pointsize); // pointsize

    glColor3d(pr, pg, pb); // point color

    if(point){
    glDrawArrays(GL_POINTS, 0, vert);
    }


    glColor3d(lr, lg, lb); // line color

    glLineWidth(linesize);
    if (line_type) {
        glLineStipple(splits, 0x3333);
       glEnable(GL_LINE_STIPPLE);
    }

    glDrawElements(GL_LINES, count_of_facets, GL_UNSIGNED_INT, arr2);

    glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_LINE_STIPPLE);
}


void Widget::changeZ() {
    x = 0.00;
    update();
}



void Widget::mousePressEvent(QMouseEvent* mo) {
    mPos=mo->pos();
}

void Widget::mouseMoveEvent(QMouseEvent* mo) {
    xRot = 5/M_PI * (mo -> pos().y()-mPos.y());
    yRot = 5/M_PI * (mo -> pos().x()-mPos.x());
    update();
}

void Widget::pluspsize() {
    pointsize += 5;
}

void Widget::minpsize() {
    pointsize -= 5;
}

void Widget::pls() {
    linesize += 1;
}

void Widget::mls() {
    linesize -= 1;
}

void Widget::reload() {
    converter(&arr, &arr2, &count_of_facets, &min, &max, &vert, filename_global);

}



