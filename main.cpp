#include "mainwindow.h"
#include <QWidget>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("OS7");
    w.setFixedSize(1200,900);
    w.show();
    return a.exec();
}
