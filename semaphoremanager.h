#ifndef SEMAPHOREMANAGER_H
#define SEMAPHOREMANAGER_H

// 将sem_t替换为QSemaphore。
#include <QSemaphore>

class SemaphoreManager {
public:
    SemaphoreManager();
    ~SemaphoreManager();

    pthread_mutex_t& getBufferMutex();
    pthread_mutex_t& getQueueMutex();
    pthread_mutex_t& getFileMutex();
    QSemaphore& getEmptySem();
    QSemaphore& getFullSem();
    QSemaphore& getMsgTypeSem(int index);

private:
    pthread_mutex_t bufferMutex;   // 用于缓冲区链操作的互斥信号量
    pthread_mutex_t queueMutex;    // 用于消息队列操作的互斥信号量
    pthread_mutex_t fileMutex;     // 用于文件操作的互斥信号量
    QSemaphore emptySem;                // 描述空闲缓冲区的数目的信号量
    QSemaphore fullSem;                 // 描述满的缓冲区的数目的信号量
    QSemaphore msgTypeSem[4];           // 描述不同类型的消息的数目的信号量
};

#endif // SEMAPHOREMANAGER_H
