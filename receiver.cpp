#include "receiver.h"
#include <sys/msg.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

Receiver::Receiver(int msgID, SemaphoreManager& semMgr, BufferPool& bufPool)
    : messageID(msgID), semaphoreManager(semMgr), bufferPool(bufPool) {}

QString Receiver::receiveMessage() {
    if(bufferPool.getMessageChainCount()<=0) return QString("The Message Chain is empty");
    // 2. 获取消息链的头部
    pthread_mutex_lock(&semaphoreManager.getBufferMutex());
    MyMsgBuf* temp = bufferPool.getFirstMessage();
    if (!temp) {
        pthread_mutex_unlock(&semaphoreManager.getBufferMutex());
        return QString("No message to receive.");
    }

    // 从消息链中删除这个消息
    bufferPool.release(temp);
    bufferPool.que_num(0); // 更新number_of_que_messages和cur_bytes的值

    pthread_mutex_unlock(&semaphoreManager.getBufferMutex());

    semaphoreManager.getEmptySem().release();

    return QString("process %1 received a message from %2\ncur_bytes %3\nnumber_of_que_messages %4")
        .arg(getpid()).arg(temp->mymsg.mtype).arg(bufferPool.getCurBytes()).arg(bufferPool.getNumberOfQueMessages());
}
