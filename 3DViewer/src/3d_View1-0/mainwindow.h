#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "widget.h"
#include <QVector>
#include <QImage>
#include "../QtGifImage-master/src/gifimage/qgifimage.h"
#include <QPainter>
#include <QPixmap>
#include <QSize>





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<QImage> mas_image;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_16_clicked();

    void on_rotxr_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void create_screen();


    void on_pushButton_52_clicked();

    void on_rotxl_clicked();

    void on_rotyup_clicked();

    void on_rotyd_clicked();

    void on_rotzr_clicked();

    void on_rotzl_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

//    void on_radioButton_4_clicked();

//    void on_radioButton_5_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
