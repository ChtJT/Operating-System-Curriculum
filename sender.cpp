#include "sender.h"
#include <sys/msg.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <random>
#include "receiver.h"

Sender::Sender(int msgID, SemaphoreManager& semMgr, BufferPool& bufPool)
    : messageID(msgID), semaphoreManager(semMgr), bufferPool(bufPool) {}

QString Sender::sendMessage() {
    // 0. N numbers
//    if (bufferPool.getMessageChainCount() >= 10) {
//        // 当消息链中的消息数量达到N时，首先接收第一个消息
//        m_receiver.receiveMessage(); // 假设 m_receiver 是 Receiver 的一个实例
//    }
    if(bufferPool.getNumberOfQueMessages()>=10) return QString("The bufferpoll is full");
    // 1. 等待空闲缓冲区
    semaphoreManager.getEmptySem().acquire();
    // 在获取空闲缓冲区后记录缓冲池状态
    QString status1 = bufferPool.getStatus();

    // 2. 选择一个空闲缓冲区
    pthread_mutex_lock(&semaphoreManager.getBufferMutex());
    MyMsgBuf* temp = bufferPool.select();
    bufferPool.que_num(1);
    pthread_mutex_unlock(&semaphoreManager.getBufferMutex());
    // 在选择缓冲区后记录缓冲池状态
    QString status2 = bufferPool.getStatus();

    // 设置消息内容
    int type = rand() % 4 + 1;  // 例如，随机选择一个类型
    temp->mymsg.mtype = type;
    sprintf(temp->mymsg.mtext, "%zu", getpid());

    // 3. 发送消息
    pthread_mutex_lock(&semaphoreManager.getQueueMutex());
    int reval = msgsnd(messageID, &temp->mymsg, sizeof(temp->mymsg.mtext), MSG_NOERROR|IPC_NOWAIT);
    if(reval == -1) {
        // 处理错误
    } else {
        semaphoreManager.getMsgTypeSem(type).release();
    }
    pthread_mutex_unlock(&semaphoreManager.getQueueMutex());

    return QString("process %1 send a message!\ncur_bytes %2\nnumber_of_que_messages %3")
        .arg(getpid()).arg(bufferPool.getCurBytes()).arg(bufferPool.getNumberOfQueMessages());
}

QString Sender::getBufferPoolStatus() const {
    return bufferPool.getStatus();
}

QString Sender::getMessageChainStatus() const {
    return bufferPool.getMessageChainStatus();
}
