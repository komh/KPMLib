#ifndef KPM_MAIN_THREAD_H
#define KPM_MAIN_THREAD_H

#define INCL_WIN
#include <os2.h>

#include "KPMThread.h"

class KPMMainThread : public KPMThread
{
public :
    KPMMainThread();
    virtual ~KPMMainThread();

    virtual int Run() { return 0; }
};
#endif

