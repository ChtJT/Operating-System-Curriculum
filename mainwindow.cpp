#include "mainwindow.h"
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

    MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_bufferPool(new BufferPool(10, this)) // assuming pool size is 10 messages for demonstration
{
    m_textEdit = new QTextEdit(this);
    QPushButton *button1 = new QPushButton("Start", this);
    QPushButton *button2 = new QPushButton("Stop", this);
    QPushButton *button3 = new QPushButton("End", this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_textEdit);
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Initialize multiple senders and receivers
    for (int i = 0; i < 3; ++i) {
        Sender *sender = new Sender(m_bufferPool, i + 1, this);
        m_senders.append(sender);
        connect(sender, &Sender::messageToSend, m_textEdit, &QTextEdit::append);
    }

    for (int i = 0; i < 2; ++i) {
        Receiver *receiver = new Receiver(m_bufferPool, this);
        m_receivers.append(receiver);
    }

    // Connect the signals to the slots
    connect(button1, &QPushButton::clicked, this, &MainWindow::startThreads);
    connect(button2, &QPushButton::clicked, this, &MainWindow::stopThreads);
    connect(button3, &QPushButton::clicked, this, &MainWindow::closeApplication);

    // Connect senders and receivers for message transmission
    for (Sender *sender : m_senders) {
        for (Receiver *receiver : m_receivers) {
            connect(sender, &Sender::messageToSend, receiver, &Receiver::onMessageToSend);
        }
    }
}

void MainWindow::startThreads() {
    for (Sender *sender : m_senders) {
        if (!sender->isRunning()) {
            sender->start();
        }
    }

    for (Receiver *receiver : m_receivers) {
        if (!receiver->isRunning()) {
            receiver->start();
        }
    }
}

void MainWindow::stopThreads() {
    for (Sender *sender : m_senders) {
        if (sender->isRunning()) {
            sender->terminate();
            sender->wait();
        }
    }

    for (Receiver *receiver : m_receivers) {
        if (receiver->isRunning()) {
            receiver->terminate();
            receiver->wait();
        }
    }
}

void MainWindow::closeApplication() {
    stopThreads();
    QMainWindow::close();
}

MainWindow::~MainWindow() {
    stopThreads();
    qDeleteAll(m_senders);
    qDeleteAll(m_receivers);
}
