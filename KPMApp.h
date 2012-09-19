#ifndef KPMAPP_H
#define KPMAPP_H

#define INCL_WIN
#include <os2.h>

#include "KPMMainThread.h"

class KPMApp : public KPMMainThread
{
public :
    KPMApp() : KPMMainThread() {};
    virtual ~KPMApp() {};

    virtual int Run();
};
#endif

