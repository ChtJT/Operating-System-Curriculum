#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    startButton = new QPushButton("开始", this);
    pauseButton = new QPushButton("暂停", this);
    terminateButton = new QPushButton("终止", this);
    textEdit = new QTextEdit(this);
    bufferPoolProgress = new QProgressBar(this);
    bufferPoolProgress->setRange(0, 10);  // 设置范围为0到10
    bufferPoolProgress->setValue(10);
    messageList = new QListWidget(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(startButton);
    layout->addWidget(pauseButton);
    layout->addWidget(terminateButton);
    layout->addWidget(bufferPoolProgress);
    layout->addWidget(messageList);
    layout->addWidget(textEdit);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Connect buttons to slots
    connect(startButton, &QPushButton::clicked, this, &MainWindow::start);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::pause);
    connect(terminateButton, &QPushButton::clicked, this, &MainWindow::terminate);

    bufferPool = new BufferPool(10, 100); // 创建10个大小为100的缓冲区
    semaphoreManager = new SemaphoreManager();

    const int numSenders = 10;
    const int numReceivers = 10;
    for (int i = 0; i < numSenders; ++i) {
        Sender* sender = new Sender(bufferPool, semaphoreManager);
        senders.append(sender);
        QThread* thread = new QThread;
        senderThreads.append(thread);
        sender->moveToThread(thread);
        connect(thread, &QThread::started, sender, &Sender::send);
        thread->start();
    }
    for (int i = 0; i < numReceivers; ++i) {
        Receiver* receiver = new Receiver(bufferPool, semaphoreManager);
        receivers.append(receiver);
        QThread* thread = new QThread;
        receiverThreads.append(thread);
        receiver->moveToThread(thread);
        connect(thread, &QThread::started, receiver, &Receiver::receive);
        thread->start();
    }

    for (int i = 0; i < senders.size(); ++i) {
        Sender* sender = senders[i];
        connect(sender, &Sender::messageSent, this, [&](const QString& message){
            textEdit->append("Sent: " + message);
            updateMessageDisplay(message, true);
        });
    }

    // Connect signals for each receiver
    for (int i = 0; i < receivers.size(); ++i) {
        Receiver* receiver = receivers[i];
        connect(receiver, &Receiver::messageReceived, this, [&](const QString& message){
            textEdit->append("Received: " + message);
            updateMessageDisplay(message, false);
        });
    }

    // Connect signals for the buffer pool
    connect(bufferPool, &BufferPool::bufferChanged, this, &MainWindow::updateBufferDisplay);
    connect(bufferPool, &BufferPool::buffersUsedChanged, this, &MainWindow::updateBufferPoolDisplay);


}

MainWindow::~MainWindow()
{
    // Stop and delete all sender threads and sender instances
    for (int i = 0; i < senders.size(); ++i) {
        senderThreads[i]->quit();
        senderThreads[i]->wait();
        delete senderThreads[i];
        delete senders[i];
    }

    // Stop and delete all receiver threads and receiver instances
    for (int i = 0; i < receivers.size(); ++i) {
        receiverThreads[i]->quit();
        receiverThreads[i]->wait();
        delete receiverThreads[i];
        delete receivers[i];
    }

    // Delete other instances
    delete bufferPool;
    delete semaphoreManager;
}


void MainWindow::start() {
    // Iterate over all senders and receivers to start them
    for (int i = 0; i < senders.size(); ++i) {
        senders[i]->restart();
        if (!senderThreads[i]->isRunning()) {
            senderThreads[i]->start();
        }
    }
    for (int i = 0; i < receivers.size(); ++i) {
        receivers[i]->restart();
        if (!receiverThreads[i]->isRunning()) {
            receiverThreads[i]->start();
        }
    }
    textEdit->append("Started.");
}



void MainWindow::pause() {
    for (int i = 0; i < senders.size(); ++i) {
        senders[i]->setShouldRun(false);
    }
    for (int i = 0; i < receivers.size(); ++i) {
        receivers[i]->setShouldRun(false);
    }
    textEdit->append("Paused.");
}

void MainWindow::terminate() {
    for (int i = 0; i < senders.size(); ++i) {
        senders[i]->setShouldRun(false);
        senderThreads[i]->quit();
        senderThreads[i]->wait();
    }
    for (int i = 0; i < receivers.size(); ++i) {
        receivers[i]->setShouldRun(false);
        receiverThreads[i]->quit();
        receiverThreads[i]->wait();
    }
    textEdit->append("Terminated.");
}


void MainWindow::updateBufferDisplay(const QString& status) {
    // 更新缓冲池进度条
    messageList->addItem(status);
}

void MainWindow::updateMessageDisplay(const QString& message, bool isSent) {
    if (isSent) {
        textEdit->append("Sent: " + message);
    } else {
        textEdit->append("Received: " + message);
    }
}

void MainWindow::updateBufferPoolDisplay(int usedBuffers) {
    bufferPoolProgress->setValue(10 - usedBuffers);
}
