#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("OS7");
    setFixedSize(1200, 900);

    sendButton = new QPushButton(this);
    receiveButton = new QPushButton(this);
    helpButton = new QPushButton(this);
    m_logTextEdit = new QTextEdit(this);

    sendButton->setGeometry(950,150,200,100);
    receiveButton->setGeometry(950,400,200,100);
    helpButton->setGeometry(950,650,200,100);
    m_logTextEdit->setGeometry(100,100,700,700);

    sendButton->setText(tr("Send"));
    receiveButton->setText(tr("Receive"));
    helpButton->setText(tr("Help"));

    m_logTextEdit->setReadOnly(true);

    connect(sendButton, &QPushButton::clicked, this, &MainWindow::sendMessages);
    connect(receiveButton, &QPushButton::clicked, this, &MainWindow::receiveMessages);
    connect(helpButton, &QPushButton::clicked, this, &MainWindow::helpMessages);

    m_logTextEdit->setStyleSheet("font: 25 14pt '微软雅黑 Light';"
                                 "color: rgb(31,31,31);"
                                 "padding-left:20px;"
                                 "background-color: rgb(255, 255, 255);"
                                 "border:2px solid rgb(20,196,188);border-radius:15px;");

    this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(251,102,102, 200), stop:1 rgba(20,196,188, 210));");

    sendButton->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                              "border: none;border-radius:15px;}"
                              "QPushButton:hover{background-color: rgb(0,255,255);}"//hover
                              "QPushButton:pressed{background-color: rgb(22,218,208);}");

    receiveButton->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                 "border: none;border-radius:15px;}"
                                 "QPushButton:hover{background-color: rgb(0,255,255);}"//hover
                                 "QPushButton:pressed{background-color: rgb(22,218,208);}");

    helpButton->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                              "border: none;border-radius:15px;}"
                              "QPushButton:hover{background-color: rgb(0,255,255);}"//hover
                              "QPushButton:pressed{background-color: rgb(22,218,208);}");

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

      // Ensure the thread is not already running
    receiveThreads[randomIndex]->start();  // Start the chosen thread
    m_logTextEdit->append("The receiveThread is " + QString::number(randomIndex));

        // Wait for the thread to finish if you want to immediately reflect the result on the GUI.
        // receiveThreads[randomIndex]->wait();

        // Display the buffer pool status
    QString bufferPoolStatus = senders[randomIndex]->getBufferPoolStatus();  // Assuming the buffer pool status can be fetched from any Sender instance
    m_logTextEdit->append("Buffer Pool Status: " + bufferPoolStatus);

        // Display the message chain status
    QString messageChainStatus = senders[randomIndex]->getMessageChainStatus();  // Assuming the message chain status can be fetched from any Sender instance
    m_logTextEdit->append("Message Chain Status: " + messageChainStatus);
}

void MainWindow::sendMessages() {
    int randomIndex = rand() % 3;  // Choose a random thread index

    //if (!sendThreads[randomIndex]->isRunning()) {  // Ensure the thread is not already running
        sendThreads[randomIndex]->start();  // Start the chosen thread
        m_logTextEdit->append("The sendThread is " + QString::number(randomIndex));
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

//    } else {
//        // If the chosen thread is already running, you can either wait or choose another one.
//        m_logTextEdit->append("Thread " + QString::number(randomIndex + 1) + " is already running. Please try again.");
//    }
}

void MainWindow::helpMessages(){

}
