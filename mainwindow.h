#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QThread>
#include <array>
#include <QObject>
#include <QFileDialog>
#include <QCoreApplication>
#include <QMessageBox>
#include "sender.h"
#include "receiver.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendMessages();
    void receiveMessages();
    void helpMessages();

private:
    QPushButton* sendButton;
    QPushButton* receiveButton;
    QPushButton* helpButton;
    QTextEdit* m_logTextEdit;

    // 线程数组
    SemaphoreManager semMgr;
    BufferPool bufPool;
    std::vector<Sender*> senders;
    std::array<QThread*, 3> sendThreads;
    std::vector<Receiver*> receivers;
    std::vector<QThread*> receiveThreads;

};

#endif // MAINWINDOW_H
