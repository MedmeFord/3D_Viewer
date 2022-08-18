#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include<string>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    ui->inform->setText(ui->widget->filename_global);
    ui->facinf->setText(ui->widget->cof2);
    ui->Vertinf->setText(ui->widget->vert2);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->widget->pluspsize();
    create_screen();
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->widget->minpsize();
    create_screen();
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->widget->pls();
    create_screen();
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->widget->mls();
    create_screen();
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->widget->line_type = 1;
    ui->widget->update();
    create_screen();
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->widget->line_type = 0;
    ui->widget->update();
    create_screen();
}


void MainWindow::on_pushButton_9_clicked()
{
     ui->widget->splits += 1;
     create_screen();
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->widget->splits -= 1;
    create_screen();
}


void MainWindow::on_pushButton_13_clicked()
{
    ui->widget->shift += 1;
    ui->widget->cor = 0;
    ui->widget->dir = 1;
    ui->widget->shiftflag = 1;
    ui->widget->update();
    create_screen();
}


void MainWindow::on_pushButton_14_clicked()
{
    ui->widget->shift += 1;
    ui->widget->cor = 0;
    ui->widget->dir = 0;
    ui->widget->shiftflag = 1;
    ui->widget->update();
    create_screen();
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->widget->shift += 1;
    ui->widget->cor = 1;
    ui->widget->dir = 1;
    ui->widget->shiftflag = 1;
    ui->widget->update();
    create_screen();
}


void MainWindow::on_pushButton_15_clicked()
{
    ui->widget->shift += 1;
    ui->widget->cor = 1;
    ui->widget->dir = 0;
    ui->widget->shiftflag = 1;
    ui->widget->update();
    create_screen();
}


void MainWindow::on_pushButton_12_clicked()
{
    ui->widget->shift += 1;
    ui->widget->cor = 2;
    ui->widget->dir = 1;
    ui->widget->shiftflag = 1;
    ui->widget->update();
    create_screen();
}


void MainWindow::on_pushButton_16_clicked()
{
    ui->widget->shift += 1;
    ui->widget->cor = 2;
    ui->widget->dir = 0;
    ui->widget->shiftflag = 1;
    ui->widget->update();
    create_screen();
}





void MainWindow::on_pushButton_18_clicked()
{
    ui->widget->lessflag = 1;
    ui->widget->moreless = 0;
    create_screen();
}


void MainWindow::on_pushButton_19_clicked()
{
    ui->widget->lessflag = 1;
    ui->widget->moreless = 1;
    create_screen();
}


void MainWindow::on_radioButton_clicked()
{
    ui->widget->point = 0;
    create_screen();
}


void MainWindow::on_radioButton_2_clicked()
{
    ui->widget->point = 1;
    create_screen();
}


void MainWindow::on_radioButton_3_clicked()
{
    ui->widget->point = 2;
    create_screen();
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->widget->pr = ui->PR->text().toDouble();
    ui->widget->pg = ui->PG->text().toDouble();
    ui->widget->pb = ui->PB->text().toDouble();
    ui->widget->update();
    create_screen();
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->widget->lr = ui->PR_2->text().toDouble();
    ui->widget->lg = ui->PG_2->text().toDouble();
    ui->widget->lb = ui->PB_2->text().toDouble();
    ui->widget->update();
    create_screen();
}


void MainWindow::on_pushButton_52_clicked()
{
    ui->widget->fr = ui->PR_5->text().toDouble();
    ui->widget->fg = ui->PG_5->text().toDouble();
    ui->widget->fb = ui->PB_5->text().toDouble();
    ui->widget->update();
    create_screen();
}

void MainWindow::on_rotxr_clicked()
{
    ui->widget->angle = 45;
    ui->widget->rcor = 1;
    ui->widget->rotflag = 1;
    ui->widget->update();
    create_screen();

}


void MainWindow::on_rotxl_clicked()
{
    ui->widget->angle = -45;
    ui->widget->rcor = 1;
    ui->widget->rotflag = 1;
    ui->widget->update();
    create_screen();
}


void MainWindow::on_rotyup_clicked()
{
    ui->widget->angle = 45;
    ui->widget->rcor = 0;
    ui->widget->rotflag = 1;
    ui->widget->update();
    create_screen();

}


void MainWindow::on_rotyd_clicked()
{
    ui->widget->angle = -45;
    ui->widget->rcor = 0;
    ui->widget->rotflag = 1;
    ui->widget->update();
    create_screen();

}


void MainWindow::on_rotzr_clicked()
{
    ui->widget->angle = 45;
    ui->widget->rcor = 2;
    ui->widget->rotflag = 1;
    ui->widget->update();
    create_screen();


}


void MainWindow::on_rotzl_clicked()
{
    ui->widget->angle = -45;
    ui->widget->rcor = 2;
    ui->widget->rotflag = 1;
    ui->widget->update();
    create_screen();

}


void MainWindow::on_pushButton_17_clicked()
{
    ui->widget->filename();
    ui->widget->reload();
    ui->widget->update();
    ui->widget->write_config();
    ui->widget->open_config();
    ui->inform->setText(ui->widget->filename_global);
    ui->facinf->setText(ui->widget->cof2);
    ui->Vertinf->setText(ui->widget->vert2);
}


void MainWindow::on_pushButton_26_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "BMP (*.bmp);; JPEG (*.jpeg)");
        ui->widget->grab().save(file);
}


void MainWindow::on_pushButton_27_clicked()
{
    ui->widget->screenflag = 1;
}

void MainWindow::create_screen()
{
    if (ui->widget->screenflag == 1) {
        mas_image.push_back(ui->widget->grab().toImage());
    }
}



void MainWindow::on_pushButton_28_clicked()
{
    ui->widget->screenflag = 0;
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save screenshot"), "", tr("GIF screenshot (*.gif);;GIF screenshot (*.gif)"));
        QGifImage gif(QSize(5000, 5000));
        QVector<QRgb> ctable;
        ctable << qRgb(255, 255, 255)
               << qRgb(0, 0, 0)
               << qRgb(255, 0, 0)
               << qRgb(0, 255, 0)
               << qRgb(0, 0, 255)
               << qRgb(255, 255, 0)
               << qRgb(0, 255, 255)
               << qRgb(255, 0, 255);

        gif.setGlobalColorTable(ctable, Qt::black);
        gif.setDefaultTransparentColor(Qt::black);
        gif.setDefaultDelay(100);

        for (QVector<QImage>::Iterator img = mas_image.begin(); img != mas_image.end(); ++img) {
            gif.addFrame(*img);
        }
        gif.save(fileName);
}


//void MainWindow::on_radioButton_4_clicked()
//{
//    ui->widget->proectionflag = 1;
//     ui->widget->update();
//}


//void MainWindow::on_radioButton_5_clicked()
//{
//    ui->widget->proectionflag = 0;
//     ui->widget->update();
//}

