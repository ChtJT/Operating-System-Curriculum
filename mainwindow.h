#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QListWidget>


#include "bufferpool.h"
#include "semaphoremanager.h"
#include "sender.h"
#include "receiver.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateBufferDisplay(const QString& status);
    void updateMessageDisplay(const QString& message, bool isSent);
    void updateBufferPoolDisplay(int usedBuffers);

private:
    void start();
    void pause();
    void terminate();

    BufferPool* bufferPool;
    SemaphoreManager* semaphoreManager;
    QList<Sender*> senders;
    QList<Receiver*> receivers;
    QList<QThread*> senderThreads;
    QList<QThread*> receiverThreads;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *terminateButton;
    QTextEdit *textEdit;
    QProgressBar *bufferPoolProgress;
    QListWidget *messageList;
};

#endif // MAINWINDOW_H
