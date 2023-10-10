#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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

    for(int i=0; i < 3;i++){
        // Create a new Sender instance for each thread
        Sender* threadSender = new Sender(1, semMgr, bufPool);
        senders.push_back(threadSender);

        QThread* thread = new QThread();
        threadSender->moveToThread(thread);  // Move the new Sender instance to the thread

        connect(thread, &QThread::started, threadSender, &Sender::sendMessage);
        sendThreads[i] = thread;
    }
    for(int i=0; i < 3; i++){
        // Create a new Receiver instance for each thread
        Receiver* threadReceiver = new Receiver(1, semMgr, bufPool);
        receivers.push_back(threadReceiver);

        QThread* thread = new QThread();
        threadReceiver->moveToThread(thread);  // Move the new Receiver instance to the thread

        connect(thread, &QThread::started, threadReceiver, &Receiver::receiveMessage);
        receiveThreads.push_back(thread);
    }

}

MainWindow::~MainWindow()
{
    for (Sender* sender : senders) {
        delete sender;
    }
    for (QThread* thread : sendThreads) {
        thread->quit();
        thread->wait();
        delete thread;
    }
    for (Receiver* receiver : receivers) {
        delete receiver;
    }
    for (QThread* thread : receiveThreads) {
        thread->quit();
        thread->wait();
        delete thread;
    }
    delete sendButton;
    delete receiveButton;
    delete m_logTextEdit;
}

void MainWindow::receiveMessages() {
    int randomIndex = rand() % 3;  // Choose a random thread index

    if (!receiveThreads[randomIndex]->isRunning()) {  // Ensure the thread is not already running
        receiveThreads[randomIndex]->start();  // Start the chosen thread

        // Wait for the thread to finish if you want to immediately reflect the result on the GUI.
        // receiveThreads[randomIndex]->wait();

        // Display the buffer pool status
        QString bufferPoolStatus = senders[randomIndex]->getBufferPoolStatus();  // Assuming the buffer pool status can be fetched from any Sender instance
        m_logTextEdit->append("Buffer Pool Status: " + bufferPoolStatus);

        // Display the message chain status
        QString messageChainStatus = senders[randomIndex]->getMessageChainStatus();  // Assuming the message chain status can be fetched from any Sender instance
        m_logTextEdit->append("Message Chain Status: " + messageChainStatus);

    } else {
        m_logTextEdit->append("Thread " + QString::number(randomIndex + 1) + " is already running. Please try again.");
    }
}

void MainWindow::sendMessages() {
    int randomIndex = rand() % 3;  // Choose a random thread index

    if (!sendThreads[randomIndex]->isRunning()) {  // Ensure the thread is not already running
        sendThreads[randomIndex]->start();  // Start the chosen thread
        // Wait for the thread to finish if you want to immediately reflect the result on the GUI.
        // sendThreads[randomIndex]->wait();
        // Get the log and status from the Sender instance corresponding to the chosen thread
//        QString sendLog = senders[randomIndex]->sendMessage();
//        m_logTextEdit->append(sendLog);

        // Display the buffer pool status
        QString bufferPoolStatus = senders[randomIndex]->getBufferPoolStatus();
        m_logTextEdit->append("Buffer Pool Status: " + bufferPoolStatus);

        // Display the message chain status
        QString messageChainStatus = senders[randomIndex]->getMessageChainStatus();
        m_logTextEdit->append("Message Chain Status: " + messageChainStatus);

    } else {
        // If the chosen thread is already running, you can either wait or choose another one.
        m_logTextEdit->append("Thread " + QString::number(randomIndex + 1) + " is already running. Please try again.");
    }
}
