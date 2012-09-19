#ifndef KPM_THREAD_H
#define KPM_THREAD_H

#define INCL_WIN
#include <os2.h>

class KPMThread
{
public :
    KPMThread() : _tid( 0 ), _hab( 0 ), _hmq( 0 ) {}
    virtual ~KPMThread() {}

    virtual int Run() = 0;

    int GetTID() const { return _tid; }
    HAB GetHAB() const { return _hab; }
    HMQ GetHMQ() const { return _hmq; }

protected :
    int _tid;

    HAB _hab;
    HMQ _hmq;
};
#endif

