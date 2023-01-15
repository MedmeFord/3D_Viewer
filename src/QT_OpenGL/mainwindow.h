#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_open_file_Button_clicked();

  void on_scale_SpinBox_valueChanged(double arg1);

  void on_model_scale_SpinBox_valueChanged(double arg1);

  void on_transl_x_SpinBox_valueChanged(double arg1);

  void on_trans_y_SpinBox_valueChanged(double arg1);

  void on_trans_z_SpinBox_valueChanged(double arg1);

  void on_rotate_x_SpinBox_valueChanged(double arg1);

  void on_rotate_y_SpinBox_valueChanged(double arg1);

  void on_rotate_z_SpinBox_valueChanged(double arg1);

  void on_color_Button_clicked();

  void on_horizontalSlider_x_valueChanged(int value);

  void on_horizontalSlider_y_valueChanged(int value);

  void on_horizontalSlider_z_valueChanged(int value);

  void on_dial_x_valueChanged(int value);

  void on_dial_y_valueChanged(int value);

  void on_dial_z_valueChanged(int value);

  void on_checkLines_clicked(bool checked);

  void on_frustum_check_clicked(bool checked);

  void on_optim_model_Button_clicked();

  void on_save_set_checkBox_clicked(bool checked);

  void on_dot_spinBox_valueChanged(int arg1);

  void on_line_spinBox_valueChanged(double arg1);

  void on_sqr_point_checkBox_clicked(bool checked);

  void on_save_as_Button_clicked();

  void on_jpeg_pushButton_clicked();

  void on_bXYToZero_clicked();

  void on_sbSizeOfPerspective_valueChanged(int arg1);

  void on_sbSizeOfNearVal_valueChanged(int arg1);

  void on_sbSizeOfFarVal_valueChanged(int arg1);

  void on_pbSaveDirectory_clicked();

  void error_message(QString message);

 public:
  QString byt_file_name;
  QByteArray byt;
  int check_open_file_button = 0, check_has_file = 0;
  double modelScale = 1, xScale = 0, yScale = 0, zScale = 1, step = 0;
  char *file_name;
  QColor colors;

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
