#include "semaphoremanager.h"

SemaphoreManager::SemaphoreManager(int value):semaphore(value){

}

SemaphoreManager::~SemaphoreManager()
{
}

// 获取信号量
void SemaphoreManager::P()
{
    semaphore.acquire();
}
// 释放信号量
void SemaphoreManager::V()
{
    semaphore.release();
}
