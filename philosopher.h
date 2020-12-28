#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <QThread>
#include "resourcemanager.h"

class Philosopher : public QThread
{
    Q_OBJECT
    void run() override {
        ResourceManager *resourceManager = ResourceManager::getInstance();

        while(resourceManager->get_isRunning()) {
            emit waitingForks(m_threadIndex);
            for (int i = 0; i < resourceManager->get_resourcePerThread(); i++) {
                resourceManager->requestResource(m_threadIndex);
            }
            emit startEating(m_threadIndex);


            if (resourceManager->get_isRunning())
                msleep(resourceManager->get_sleepMseconds());

            resourceManager->releaseResources(m_threadIndex);
            emit doneEating(m_threadIndex);

            if (resourceManager->get_isRunning())
                msleep(resourceManager->get_sleepMseconds());
        }
    }


public:
    explicit Philosopher(int threadIndex,  QObject *parent = nullptr)
        : QThread(parent),
          m_threadIndex(threadIndex) {}


signals:
    void waitingForks(int threadIndex);
    void startEating(int threadIndex);
    void doneEating(int threadIndex);

private:
    int m_threadIndex;
};

#endif // PHILOSOPHER_H
