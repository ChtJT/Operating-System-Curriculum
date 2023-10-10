#ifndef SENDER_H
#define SENDER_H

#include "bufferpool.h"
#include "semaphoremanager.h"
#include "receiver.h"
#include <QObject>

class Sender : public QObject{
public:
    Sender(int msgID, SemaphoreManager& semMgr, BufferPool& bufPool);
    QString sendMessage();
    QString getBufferPoolStatus() const;
    QString getMessageChainStatus() const;

private:
    //Receiver &m_receiver;
    int messageID;//消息ID
    SemaphoreManager& semaphoreManager;//信号量管理器的引用
    BufferPool& bufferPool;//缓冲池的引用
};

#endif // SENDER_H
