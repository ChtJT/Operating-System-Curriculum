#include "semaphoremanager.h"

SemaphoreManager::SemaphoreManager()
    : emptySem(10),   // 初始化为10，与代码1中的N相同
    fullSem(0) {
    pthread_mutex_init(&bufferMutex, NULL);
    pthread_mutex_init(&queueMutex, NULL);
    pthread_mutex_init(&fileMutex, NULL);

    for(int i = 0; i < 4; ++i) {
        msgTypeSem[i].release(0); // 初始化为0
    }
}

SemaphoreManager::~SemaphoreManager() {
    pthread_mutex_destroy(&bufferMutex);
    pthread_mutex_destroy(&queueMutex);
    pthread_mutex_destroy(&fileMutex);
    // QSemaphore 的析构函数将自动处理资源的释放
}


pthread_mutex_t& SemaphoreManager::getBufferMutex() {
    return bufferMutex;
}

pthread_mutex_t& SemaphoreManager::getQueueMutex() {
    return queueMutex;
}

pthread_mutex_t& SemaphoreManager::getFileMutex() {
    return fileMutex;
}

QSemaphore& SemaphoreManager::getEmptySem() {
    return emptySem;
}

QSemaphore& SemaphoreManager::getFullSem() {
    return fullSem;
}

QSemaphore& SemaphoreManager::getMsgTypeSem(int index) {
    return msgTypeSem[index];
}
