#ifndef KPMAPP_H
#define KPMAPP_H

#define INCL_WIN
#include <os2.h>

#include "KPMThread.h"

class KPMApp : public KPMThread
{
public :
    KPMApp() : KPMThread() {};
    virtual ~KPMApp() {};

    virtual int Run();
};
#endif

