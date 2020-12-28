#include "resourcemanager.h"
#include <QDebug>

ResourceManager::ResourceManager(QObject *parent) : QObject(parent)
{
    m_threadCount = 5;
    m_resourceCount = 5;
    m_available = 5;
    m_resourcePerThread = 2;
    m_sleepMseconds = 2000;
    m_isRunning = false;
    connect(this, &ResourceManager::resourceCountChanged, this, &ResourceManager::update_available);
}

void ResourceManager::requestResource(int threadIndex)
{
    QMutexLocker locker(&m_lock);
    assert(isSafe());
    while (!wouldBeSafe(threadIndex)) {
        m_condition.wait(&m_lock);
    }
    m_allocated[threadIndex]++;
    update_available(m_available - 1);
    assert(isSafe());
}

void ResourceManager::releaseResources(int threadIndex)
{
    QMutexLocker locker(&m_lock);
    m_allocated[threadIndex] -= m_resourcePerThread;
    update_available(m_available + m_resourcePerThread);
    m_condition.wakeAll();
}

void ResourceManager::reset()
{
    m_allocated = QVector<int>(m_threadCount, 0);
    update_available(m_resourceCount);
}

bool ResourceManager::isSafe()
{
    int toBeAvailable = m_available;

    // Number of resources needed by thread j to finish
    int need[m_threadCount];
    // Array of threads that are guaranteed to finish
    bool finish[m_threadCount];

    // Initialize arrays
    for (int j = 0; j < m_threadCount; ++j) {
        finish[j] = false;
        need[j] = m_resourcePerThread - m_allocated[j];
    }

    // Until all threads can finish
    int finishCount = 0;
    while (finishCount < m_threadCount) {
        bool found = false;
        for (int j = 0; j < m_threadCount; j++) {
            if (finish[j] == true)
                continue;

            // If thread j needs resources less than available
            if (need[j] <= toBeAvailable) {
                // It will eventually  finish
                finish[j] = true;
                // And will release its resources
                toBeAvailable += m_allocated[j];
                finishCount++;
                found = true;
            }
        }

        // If we haven't found any thread that will eventually finish
        // during the last check, we are in unsafe state
        if (found == false)
            return false;
    }

    return true;
}

bool ResourceManager::wouldBeSafe(int threadIndex)
{
    if (m_available == 0)
        return false;

    bool result = false;
    m_available--;
    m_allocated[threadIndex]++;
    result = isSafe();
    m_available++;
    m_allocated[threadIndex]--;
    return result;
}
