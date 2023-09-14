#include "mainwindow.h"
#include "QTextEdit"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    button1->setGeometry(100,750,300,100);
    button2->setGeometry(450,750,300,100);
    button3->setGeometry(800,750,300,100);
    textedit1->setGeometry(100,100,1000,600);

}

MainWindow::~MainWindow()
{
}



