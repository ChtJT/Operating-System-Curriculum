#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include <QObject>
#include <QQueue>
#include <QString>


class BufferPool : public QObject
{
    Q_OBJECT
public:
    explicit BufferPool(int n, QObject *parent = nullptr);

    bool storeMessage(const QString &msg);
    QString fetchMessage();
private:
    int m_size;
    QQueue<QString> m_messages;
};

#endif // BUFFERPOOL_H
