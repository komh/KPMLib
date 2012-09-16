#ifndef KPM_THREAD_H
#define KPM_THREAD_H

#define INCL_WIN
#include <os2.h>

class KPMThread
{
public :
    KPMThread();
    virtual ~KPMThread();

    virtual int Run() { return 0; }

    HAB GetHAB() const { return _hab; }
    HMQ GetHMQ() const { return _hmq; }

protected :
    HAB _hab;
    HMQ _hmq;
};
#endif

