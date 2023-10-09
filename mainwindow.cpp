#include "mainwindow.h"

MainWindow::MainWindow(Sender& sender, Receiver& receiver, QWidget *parent)
    : QMainWindow(parent),
    m_sender(sender),
    m_receiver(receiver)
{
    setWindowTitle("Message Sender and Receiver");
    resize(1000, 800);

    sendButton = new QPushButton(this);
    receiveButton = new QPushButton(this);
    sendButton->setFixedSize(100,100);
    receiveButton->setFixedSize(100,100);
    receiveButton->move(100, 0);
    sendButton->setText(tr("Send"));
    receiveButton->setText(tr("Receive"));

    connect(sendButton, &QPushButton::clicked, this, &MainWindow::sendMessages);
    connect(receiveButton, &QPushButton::clicked, this, &MainWindow::receiveMessages);

    m_logTextEdit = new QTextEdit(this);
    m_logTextEdit->setFixedSize(800, 800);
    m_logTextEdit->move(200,0);
    m_logTextEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete sendButton;
    delete receiveButton;
    delete m_logTextEdit;
}

void MainWindow::receiveMessages() {
    QString receiveLog = m_receiver.receiveMessage();
    m_logTextEdit->append(receiveLog);

    // Display the buffer pool status
    QString bufferPoolStatus = m_sender.getBufferPoolStatus();
    m_logTextEdit->append("Buffer Pool Status: " + bufferPoolStatus);

    // Display the message chain status
    QString messageChainStatus = m_sender.getMessageChainStatus();
    m_logTextEdit->append("Message Chain Status: " + messageChainStatus);
}

void MainWindow::sendMessages() {
    QString sendLog = m_sender.sendMessage();
    m_logTextEdit->append(sendLog);

    // Display the buffer pool status
    QString bufferPoolStatus = m_sender.getBufferPoolStatus();
    m_logTextEdit->append("Buffer Pool Status: " + bufferPoolStatus);

    // Display the message chain status
    QString messageChainStatus = m_sender.getMessageChainStatus();
    m_logTextEdit->append("Message Chain Status: " + messageChainStatus);
}
