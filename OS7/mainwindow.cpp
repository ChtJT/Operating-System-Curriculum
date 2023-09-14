#include "mainwindow.h"

#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_bufferPool(new BufferPool(10, this)),  // assuming pool size is 10 messages for demonstration
    m_sender(new Sender(m_bufferPool, 1, this)),
    m_receiver(new Receiver(m_bufferPool, this)),
    m_shouldStop(false)
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

    // Connect the signals to the slots
    connect(button1, &QPushButton::clicked, this, &MainWindow::startThreads);
    connect(button2, &QPushButton::clicked, this, &MainWindow::stopThreads);
    connect(button3, &QPushButton::clicked, this, &MainWindow::closeApplication);

    // Connect Sender and Receiver to QTextEdit for displaying messages
    connect(m_sender, &Sender::messageToSend, m_textEdit, &QTextEdit::append);
    connect(m_receiver, &Receiver::onMessageToSend, m_textEdit, &QTextEdit::append);

    // Connect Sender and Receiver for message transmission
    connect(m_sender, &Sender::messageToSend, m_receiver, &Receiver::onMessageToSend);
}

void MainWindow::startThreads() {
    m_shouldStop = false;
    if (!m_sender->isRunning()) {
        m_sender->start();
    }

    if (!m_receiver->isRunning()) {
        m_receiver->start();
    }
}

void MainWindow::stopThreads() {
    m_shouldStop = true;
    if (m_sender->isRunning()) {
        m_sender->wait();
    }

    if (m_receiver->isRunning()) {
        m_receiver->wait();
    }
}

void MainWindow::closeApplication() {
    stopThreads();

}

MainWindow::~MainWindow() {
    stopThreads();
}
