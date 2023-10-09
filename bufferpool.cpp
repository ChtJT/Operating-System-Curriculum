#include "bufferpool.h"
#include <stdlib.h>
#include <QDebug>

BufferPool::BufferPool() {
    head = nullptr;
    head_free = nullptr;
    for (int i = 0; i < N; i++) {
        MyMsgBuf* temp = new MyMsgBuf();
        temp->next = nullptr;
        temp->next_free = nullptr;
        temp->isUsed = false;

        if (!head_free) {
            head_free = temp;
        } else {
            MyMsgBuf* ptr = head_free;
            while (ptr->next_free) {
                ptr = ptr->next_free;
            }
            ptr->next_free = temp;
        }
    }

    cur_bytes = 0;
    number_of_que_messages = 0;
}

MyMsgBuf* BufferPool::select() {
    if (!head_free) {
        return nullptr;
    }

    MyMsgBuf* temp = head_free;
    head_free = head_free->next_free;
    temp->next_free = nullptr;
    temp->isUsed = true;

    if (!head) {
        head = temp;
    } else {
        MyMsgBuf* current = head;
        while (current &&current->next) {
            if (!current) {  // 额外的检查，以避免段错误
                return nullptr;
            }
            current = current->next;
        }
        current->next = temp;
    }
    return temp;
}

void BufferPool::que_num(int sr){
    if(sr == 1){
        cur_bytes += sizeof(MyMsg);
        number_of_que_messages++;
    }
    else{
        cur_bytes -= sizeof(MyMsg);
        number_of_que_messages--;
    }
}

void BufferPool::release(MyMsgBuf* temp) {
    if (!temp || !head) return;  // 额外的检查，以避免段错误

    if (head == temp) {
        head = head->next;
    } else {
        MyMsgBuf* prev = head;
        while (prev->next && prev->next != temp) {
            if (!prev) {  // 额外的检查，以避免段错误
                return;
            }
            prev = prev->next;
        }
        if (prev->next == temp) {
            prev->next = temp->next;
        }
    }

    temp->isUsed = false;
    temp->next = nullptr;

    if (!head_free) {
        head_free = temp;
    } else {
        MyMsgBuf* ptr = head_free;
        while (ptr->next_free) {
            if (!ptr) {  // 额外的检查，以避免段错误
                return;
            }
            ptr = ptr->next_free;
        }
        ptr->next_free = temp;
    }
}

QString BufferPool::getStatus() {
    QString status = "Buffer Pool: [";
    MyMsgBuf* current = head;
    while (current) {
        status += (current->isUsed ? "Used" : "Free");
        current = current->next;
        if (current) {
            status += ", ";
        }
    }
    status += "]";
    return status;
}

QString BufferPool::getMessageChainStatus() const {
    QString status;
    MyMsgBuf* current = head;
    if (!current) {
        qDebug() << "Message chain is empty.";
    }
    while (current != nullptr) {
        status += QString("Msg ID: %1, Content: %2\n").arg(current->mymsg.mtype).arg(current->mymsg.mtext);
        current = current->next;
    }
    return status;
}

int BufferPool::getMessageChainCount() const {
    int count = 0;
    MyMsgBuf* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}


MyMsgBuf* BufferPool::getFirstMessage() const{
    return head;
}

BufferPool::~BufferPool() {
    MyMsgBuf* temp;
    while(head) {
        temp = head;
        head = head->next;
        delete temp;
    }
}
