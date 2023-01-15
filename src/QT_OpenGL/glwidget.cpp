#include "glwidget.h"

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

void GLWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  obj = (struct data*)malloc(sizeof(struct data));
  obj->count_of_facets = 0;
  obj->count_of_vertexes = 0;
  sizeofperspective = 300;
  sizeoffarval = 1000;
  sizeofnearval = 200;
  get_settings();
}

void GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void GLWidget::paintGL() {
  glClearColor(r_bg, g_bg, b_bg, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (frust_check == 1)
    glFrustum(-sizeofperspective, sizeofperspective, -sizeofperspective,
              sizeofperspective, sizeofnearval, sizeoffarval);
  else
    glOrtho(-sizeofperspective, sizeofperspective, -sizeofperspective,
            sizeofperspective, sizeofnearval, sizeoffarval);

  glTranslatef(0, 0, z_position);
  glRotated(xRot, 1, 0, 0);
  glRotated(yRot, 0, 1, 0);
  save_settings();
  drawCube();
}

void GLWidget::mousePressEvent(QMouseEvent* mo) { mPos - mo->pos(); }

void GLWidget::mouseMoveEvent(QMouseEvent* mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

void GLWidget::drawCube() {
  glVertexPointer(3, GL_DOUBLE, 0, obj->vertex_arr);
  glEnableClientState(GL_VERTEX_ARRAY);
  if (sqr_point_check == 0) glEnable(GL_POINT_SMOOTH);

  glColor3d(r_point, g_point, b_point);
  glDrawArrays(GL_POINTS, 1, obj->count_of_vertexes / 3 - 1);
  glLineWidth(line_thickness);
  glColor3d(r_line, g_line, b_line);

  if (line_check) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x00FF);

    glDrawElements(GL_LINES, obj->count_of_facets, GL_UNSIGNED_INT,
                   obj->facets_arr);
  } else {
    glDisable(GL_LINE_STIPPLE);
    glDrawElements(GL_LINES, obj->count_of_facets, GL_UNSIGNED_INT,
                   obj->facets_arr);
  }

  glPointSize(dot_thickness);

  glDisable(GL_POINT_SMOOTH);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::openFile() {
  read_obj_file(filename, obj);
  update();
}

void GLWidget::save_settings() {
  mySettings.setValue("r_line", r_line);
  mySettings.setValue("g_line", g_line);
  mySettings.setValue("b_line", b_line);
  mySettings.setValue("r_point", r_point);
  mySettings.setValue("g_point", g_point);
  mySettings.setValue("b_point", b_point);
  mySettings.setValue("r_bg", r_bg);
  mySettings.setValue("g_bg", g_bg);
  mySettings.setValue("b_bg", b_bg);
  mySettings.setValue("save_params", save_param_check);
  mySettings.setValue("dot_thickness", dot_thickness);
  mySettings.setValue("line_thickness", line_thickness);
}

void GLWidget::get_settings() {
  save_param_check = mySettings.value("save_params").toInt();
  if (save_param_check == 1) {
    r_line = mySettings.value("r_line").toDouble();
    g_line = mySettings.value("g_line").toDouble();
    b_line = mySettings.value("b_line").toDouble();
    r_point = mySettings.value("r_point").toDouble();
    g_point = mySettings.value("g_point").toDouble();
    b_point = mySettings.value("b_point").toDouble();
    r_bg = mySettings.value("r_bg").toDouble();
    g_bg = mySettings.value("g_bg").toDouble();
    b_bg = mySettings.value("b_bg").toDouble();
    dot_thickness = mySettings.value("dot_thickness").toInt();
    line_thickness = mySettings.value("line_thickness").toDouble();
  } else {
    r_line = 1, g_line = 1, b_line = 1, r_point = 0, g_point = 1, b_point = 1,
    r_bg = 0.2, g_bg = 0.2, b_bg = 0.2, dot_thickness = 5, line_thickness = 1;
  }
}

void GLWidget::wtimer() {
  tmr->start(100);
  connect(tmr, SIGNAL(timeout()), this, SLOT(gifFile()));
}

void GLWidget::gifFile() {
  time++;
  QImage image = GLWidget::grabFramebuffer();
  gif->setDefaultDelay(10);
  gif->addFrame(image);

  if (time == 50) {
    tmr->stop();
    gif->save(fname_gif);
    time = 0;
    image.QImage::bits();
  }
}

void GLWidget::jpegFile(QString name) {
  QImage image = GLWidget::grabFramebuffer();
  image.save(name, nullptr, 80);
}
