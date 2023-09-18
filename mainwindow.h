#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QList>
#include "bufferpool.h"
#include "sender.h"
#include "receiver.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startThreads();
    void stopThreads();
    void closeApplication();

private:
    QTextEdit *m_textEdit;
    BufferPool *m_bufferPool;
    QList<Sender*> m_senders;
    QList<Receiver*> m_receivers;
};

#endif // MAINWINDOW_H
