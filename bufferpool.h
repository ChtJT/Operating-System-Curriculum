#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include <pthread.h>
#include <sys/types.h>
#include <QString>

const int M = 128;
const int N = 10;

// 添加 MyMsg 结构体。
struct MyMsg {
    long long mtype;
    char mtext[M];
};

// 在 BufferPool 类中添加链表结构来管理消息。
struct MyMsgBuf {
    MyMsg mymsg;
    int userid;
    bool isUsed;
    MyMsgBuf* next;
    MyMsgBuf* next_free;
};

class BufferPool {
public:
    BufferPool();
    ~BufferPool();
    MyMsgBuf* select();       // 从链表中选择一个消息
    MyMsgBuf* getFirstMessage() const;
    void release(MyMsgBuf*);  // 释放一个消息
    QString getStatus();
    QString getMessageChainStatus() const;
    int getCurBytes() const { return cur_bytes; }
    int getNumberOfQueMessages() const { return number_of_que_messages; }
    void que_num(int);
    int getMessageChainCount() const;
private:
    int cur_bytes;
    int number_of_que_messages;
    MyMsgBuf* head;
    MyMsgBuf* head_free;
};
#endif // BUFFERPOOL_H
