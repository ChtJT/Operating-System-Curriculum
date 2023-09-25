#include "bufferpool.h"

BufferPool::BufferPool(int n, int m)
    : head(nullptr), tail(nullptr), usedBuffers(0)
{
    for(int i = 0; i < n; i++)
    {
        MessageNode* newNode = new MessageNode();
        newNode->message = QString(m, ' '); // 创建一个长度为m的空字符串
        newNode->next = nullptr;

        if(!head)
        {
            head = newNode;
            tail = head;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    m_size = n;
}
BufferPool::~BufferPool()
{
    while(head)
    {
        MessageNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// 从链表的头部取出一个节点
bool BufferPool::getBuffer(MessageNode*& msgNode)
{
    QMutexLocker locker(&mutex);
    if(!head)
        return false;
    msgNode = head;
    head = head->next;
    if(!head)
        tail = nullptr;
    usedBuffers++;    // 增加
    emit bufferChanged("Buffer taken.");
    emit buffersUsedChanged(usedBuffers);
    return true;
}

// 将节点添加回链表的尾部
bool BufferPool::releaseBuffer(MessageNode*& msgNode)
{
    QMutexLocker locker(&mutex);
    if(!tail)
    {
        head = msgNode;
        tail = head;
    }
    else
    {
        tail->next = msgNode;
        tail = msgNode;
    }
    msgNode->next = nullptr;
    msgNode = nullptr;
     usedBuffers--;    //
    emit bufferChanged("Buffer released.");
    emit buffersUsedChanged(usedBuffers);
    return true;
}
