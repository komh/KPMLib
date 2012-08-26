#ifndef KPMAPP_H
#define KPMAPP_H

#define INCL_WIN
#include <os2.h>

class KPMApp
{
public :
    KPMApp();
    virtual ~KPMApp();

    virtual void Run();

    HAB GetHAB() const { return _hab; }
    HMQ GetHMQ() const { return _hmq; }

protected :
    HAB _hab;
    HMQ _hmq;
};
#endif

