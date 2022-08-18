#include "widget.h"
#include "mainwindow.h"
#include <QApplication>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main;
    main.show();
    return a.exec();
}
