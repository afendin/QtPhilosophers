#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QThread>
#include "resourcemanager.h"
#include "philosopher.h"

class Application : public QObject
{
    Q_OBJECT
    QML_READONLY_PROPERTY(bool, isRunning)
public:
    explicit Application(QObject *parent = nullptr);

public slots:
    void start();
    void stop();

signals:
    void waitingForks(int threadIndex);
    void startEating(int threadIndex);
    void doneEating(int threadIndex);

private:
    QList<Philosopher*> m_philosopherList;
};

#endif // APPLICATION_H
