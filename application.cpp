#include "application.h"
#include <QDebug>

Application::Application(QObject *parent) : QObject(parent)
{
    m_isRunning = false;
}

void Application::start()
{
    update_isRunning(true);

    ResourceManager::getInstance()->reset();
    ResourceManager::getInstance()->set_isRunning(true);

    for (int i = 0; i < ResourceManager::getInstance()->get_threadCount(); ++i) {
        Philosopher *philosopher = new Philosopher(i);

        connect(philosopher, &Philosopher::waitingForks, [=](){
            emit waitingForks(i);
        });
        connect(philosopher, &Philosopher::startEating, [=](){
            emit startEating(i);
        });
        connect(philosopher, &Philosopher::doneEating, [=](){
            emit doneEating(i);
        });

        philosopher->start();
        m_philosopherList << philosopher;
    }
}

void Application::stop()
{
    ResourceManager::getInstance()->set_isRunning(false);

    for (Philosopher *philosopher : m_philosopherList) {
        philosopher->wait();
    }

    qDeleteAll(m_philosopherList);
    m_philosopherList.clear();

    update_isRunning(false);
}
