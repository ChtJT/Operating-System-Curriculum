#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include "sender.h"
#include "receiver.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Sender& sender, Receiver& receiver, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendMessages();
    void receiveMessages();

private:
    Sender& m_sender;
    Receiver& m_receiver;

    QPushButton* sendButton;
    QPushButton* receiveButton;
    QTextEdit* m_logTextEdit;
};

#endif // MAINWINDOW_H
