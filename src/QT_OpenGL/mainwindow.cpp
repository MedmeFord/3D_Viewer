#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->save_set_checkBox->setChecked(
      this->ui->GLwidget->mySettings.value("save_params").toInt());
  if (ui->save_set_checkBox->isChecked() == 1)
    ui->dot_spinBox->setValue(
        this->ui->GLwidget->mySettings.value("dot_thickness").toInt());
  ui->line_spinBox->setValue(
      this->ui->GLwidget->mySettings.value("line_thickness").toDouble());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::error_message(QString message) {
  QMessageBox messageBox;
  messageBox.critical(0, "Error", message);
  messageBox.setFixedSize(500, 200);
}

void MainWindow::on_open_file_Button_clicked() {
  QString filters("OBJ (*.obj)");
  byt_file_name = QFileDialog::getOpenFileName(0, "Open file",
                                               QDir::currentPath(), filters);
  byt = byt_file_name.toLocal8Bit();
  file_name = byt.data();
  this->ui->GLwidget->filename = file_name;
  this->ui->GLwidget->openFile();
  ui->labelFileName->setText(byt_file_name.section("/", -1, -1));
  ui->labelCountOfFacets->setText(
      QString::number(this->ui->GLwidget->obj->count_of_facets / 2));
  ui->labelCountOfVertex->setText(
      QString::number(this->ui->GLwidget->obj->count_of_vertexes));
  check_has_file = 1;
}

void MainWindow::on_scale_SpinBox_valueChanged(double arg1) {
  this->ui->GLwidget->z_position = arg1;
  this->ui->GLwidget->update();
}

void MainWindow::on_model_scale_SpinBox_valueChanged(double arg1) {
  if (arg1 > modelScale) {
    for (int i = 1; i <= arg1 - modelScale; i++)
      scale_obj(this->ui->GLwidget->obj, 1.1);
  } else {
    for (int i = 1; i <= modelScale - arg1; i++)
      scale_obj(this->ui->GLwidget->obj, 1 / 1.1);
  }
  modelScale = arg1;
  this->ui->GLwidget->update();
}

void MainWindow::on_transl_x_SpinBox_valueChanged(double arg1) {
  if (arg1 > xScale) {
    for (int i = 0; i < arg1 - xScale; i++)
      move_obj(this->ui->GLwidget->obj, 1.1, 1);
  } else {
    for (int i = 0; i < xScale - arg1; i++)
      move_obj(this->ui->GLwidget->obj, -1.1, 1);
  }
  xScale = arg1;
  this->ui->GLwidget->update();
}

void MainWindow::on_trans_y_SpinBox_valueChanged(double arg1) {
  if (arg1 > yScale) {
    for (int i = 0; i < arg1 - yScale; i++)
      move_obj(this->ui->GLwidget->obj, 1.1, 2);
  } else {
    for (int i = 0; i < yScale - arg1; i++)
      move_obj(this->ui->GLwidget->obj, -1.1, 2);
  }
  yScale = arg1;
  this->ui->GLwidget->update();
}

void MainWindow::on_trans_z_SpinBox_valueChanged(double arg1) {
  if (arg1 > zScale) {
    for (int i = 0; i < arg1 - zScale; i++)
      move_obj(this->ui->GLwidget->obj, 1.1, 3);
  } else {
    for (int i = 0; i < zScale - arg1; i++)
      move_obj(this->ui->GLwidget->obj, -1.1, 3);
  }
  zScale = arg1;
  this->ui->GLwidget->update();
}

void MainWindow::on_rotate_x_SpinBox_valueChanged(double arg1) {
  if (arg1 > step) {
    for (int i = 0; i < arg1 - step; i++)
      rotate_x(this->ui->GLwidget->obj, 1, 0);
  } else {
    for (int i = 0; i < step - arg1; i++)
      rotate_x(this->ui->GLwidget->obj, -1, 0);
  }
  step = arg1;
  this->ui->GLwidget->update();
}

void MainWindow::on_rotate_y_SpinBox_valueChanged(double arg1) {
  if (arg1 > step) {
    for (int i = 0; i < arg1 - step; i++)
      rotate_x(this->ui->GLwidget->obj, 1, 2);
  } else {
    for (int i = 0; i < step - arg1; i++)
      rotate_x(this->ui->GLwidget->obj, -1, 2);
  }
  step = arg1;
  this->ui->GLwidget->update();
}

void MainWindow::on_rotate_z_SpinBox_valueChanged(double arg1) {
  if (arg1 > step) {
    for (int i = 0; i < arg1 - step; i++)
      rotate_x(this->ui->GLwidget->obj, 1, 1);
  } else {
    for (int i = 0; i < step - arg1; i++)
      rotate_x(this->ui->GLwidget->obj, -1, 1);
  }
  step = arg1;
  this->ui->GLwidget->update();
}

void MainWindow::on_color_Button_clicked() {
  colors = QColorDialog::getColor(Qt::yellow, this);
  if (ui->comboBox->currentIndex() == 0) {
    this->ui->GLwidget->r_line = colors.redF();
    this->ui->GLwidget->g_line = colors.greenF();
    this->ui->GLwidget->b_line = colors.blueF();

  } else if (ui->comboBox->currentIndex() == 1) {
    this->ui->GLwidget->r_point = colors.redF();
    this->ui->GLwidget->g_point = colors.greenF();
    this->ui->GLwidget->b_point = colors.blueF();

  } else if (ui->comboBox->currentIndex() == 2) {
    this->ui->GLwidget->r_bg = colors.redF();
    this->ui->GLwidget->g_bg = colors.greenF();
    this->ui->GLwidget->b_bg = colors.blueF();
  }
  this->ui->GLwidget->update();
}

void MainWindow::on_horizontalSlider_x_valueChanged(int value) {
  this->ui->transl_x_SpinBox->setValue(value);
  this->ui->GLwidget->update();
}

void MainWindow::on_horizontalSlider_y_valueChanged(int value) {
  this->ui->trans_y_SpinBox->setValue(value);
  this->ui->GLwidget->update();
}

void MainWindow::on_horizontalSlider_z_valueChanged(int value) {
  this->ui->trans_z_SpinBox->setValue(value);
  this->ui->GLwidget->update();
}

void MainWindow::on_dial_x_valueChanged(int value) {
  this->ui->rotate_x_SpinBox->setValue(value);
  this->ui->GLwidget->update();
}

void MainWindow::on_dial_y_valueChanged(int value) {
  this->ui->rotate_y_SpinBox->setValue(value);
  this->ui->GLwidget->update();
}

void MainWindow::on_dial_z_valueChanged(int value) {
  this->ui->rotate_z_SpinBox->setValue(value);
  this->ui->GLwidget->update();
}

void MainWindow::on_frustum_check_clicked(bool checked) {
  this->ui->GLwidget->frust_check = checked;
  this->ui->GLwidget->update();
}

void MainWindow::on_checkLines_clicked(bool checked) {
  this->ui->GLwidget->line_check = checked;
  this->ui->GLwidget->update();
}

void MainWindow::on_optim_model_Button_clicked() {
  if (check_has_file) {
    double res;
    double maxSize = ui->GLwidget->obj->vertex_arr[3];
    for (int i = 3; i < ui->GLwidget->obj->count_of_vertexes; i += 1) {
      if (maxSize < ui->GLwidget->obj->vertex_arr[i])
        maxSize = ui->GLwidget->obj->vertex_arr[i];
    }
    res = (330 - maxSize) * 0.14;
    ui->model_scale_SpinBox->setValue(res);
  } else {
    error_message("Выберите OBJ файл");
  }
}

void MainWindow::on_save_set_checkBox_clicked(bool checked) {
  this->ui->GLwidget->save_param_check = checked;
  this->ui->GLwidget->update();
}

void MainWindow::on_dot_spinBox_valueChanged(int arg1) {
  this->ui->GLwidget->dot_thickness = arg1;
  this->ui->GLwidget->update();
}

void MainWindow::on_line_spinBox_valueChanged(double arg1) {
  this->ui->GLwidget->line_thickness = arg1;
  this->ui->GLwidget->update();
}

void MainWindow::on_sqr_point_checkBox_clicked(bool checked) {
  this->ui->GLwidget->sqr_point_check = checked;
  this->ui->GLwidget->update();
}

void MainWindow::on_save_as_Button_clicked() {
  if (check_open_file_button) {
    this->ui->GLwidget->wtimer();
    //    check_open_file_button = 0;
  } else {
    error_message("Выберите путь");
    //    check_open_file_button = 0;
  }
}

void MainWindow::on_jpeg_pushButton_clicked() {
  QString filters("JPEG (*.jpeg);;BMP (*.bmp)");
  QString defaultFilter("JPEG (*.jpeg)");
  QString fname_screen = QFileDialog::getSaveFileName(
      0, "Save file", QDir::currentPath(), filters, &defaultFilter);
  this->ui->GLwidget->jpegFile(fname_screen);
}

void MainWindow::on_bXYToZero_clicked() {
  this->ui->GLwidget->xRot = 0;
  this->ui->GLwidget->yRot = 0;
  this->ui->GLwidget->update();
}

void MainWindow::on_sbSizeOfPerspective_valueChanged(int arg1) {
  this->ui->GLwidget->sizeofperspective = arg1;
  this->ui->GLwidget->update();
}

void MainWindow::on_sbSizeOfNearVal_valueChanged(int arg1) {
  this->ui->GLwidget->sizeofnearval = arg1;
  this->ui->GLwidget->update();
}

void MainWindow::on_sbSizeOfFarVal_valueChanged(int arg1) {
  this->ui->GLwidget->sizeoffarval = arg1;
  this->ui->GLwidget->update();
}

void MainWindow::on_pbSaveDirectory_clicked() {
  QString filters("GIF (*.gif)");
  QString defaultFilter("GIF (*.gif)");
  this->ui->GLwidget->fname_gif = "";
  this->ui->GLwidget->fname_gif = QFileDialog::getSaveFileName(
      0, "Save GIF", QDir::currentPath(), filters, &defaultFilter);
  ui->leDirectory->setText(this->ui->GLwidget->fname_gif);
  check_open_file_button = 1;
}
