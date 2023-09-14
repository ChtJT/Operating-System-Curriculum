#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QTextEdit>
#include <QString>
class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString text="在MainWIndow里放一个text显示状态";
    QTextEdit *textedit1=new QTextEdit("text",this);
    QPushButton *button1=new QPushButton("开始",this);
    QPushButton *button2=new QPushButton("停止",this);
    QPushButton *button3=new QPushButton("结束",this);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//    void buttonCreate();
//    void textCreate();
};

#endif // MAINWINDOW_H
