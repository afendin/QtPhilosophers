#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QObject>
#include <QVector>
#include <QMutex>
#include <QWaitCondition>
#include "qttricks/qqmlhelpers.h"


class ResourceManager : public QObject
{
    Q_OBJECT
    SINGLETON(ResourceManager)
    QML_WRITABLE_PROPERTY(int, threadCount)
    QML_WRITABLE_PROPERTY(int, resourceCount)
    QML_READONLY_PROPERTY(int, available)
    QML_WRITABLE_PROPERTY(int, resourcePerThread)
    QML_WRITABLE_PROPERTY(int, sleepMseconds)
    QML_WRITABLE_PROPERTY(bool, isRunning)
public:
    explicit ResourceManager(QObject *parent = nullptr);
    void     requestResource(int threadIndex);
    void     releaseResources(int threadIndex);
    void     reset();

signals:

private:
    QMutex m_lock;
    QWaitCondition m_condition;
    QVector<int> m_allocated;
    bool isSafe();
    bool wouldBeSafe(int threadIndex);
};

#endif // RESOURCEMANAGER_H
