#ifndef KPM_SUB_THREAD_H
#define KPM_SUB_THREAD_H

#define INCL_WIN
#include <os2.h>

#include "KPMThread.h"

class KPMSubThread : protected KPMThread
{
public :
    KPMSubThread() : KPMThread() {}
    virtual ~KPMSubThread() {}

    virtual bool BeginThread( void *arg = 0, int cbStackSize = 1024 * 1024 );
    virtual bool WaitThread( bool fWait = true );

protected :
    virtual int  Run() { return 0; }
    virtual void ThreadMain( void* arg ) { return; }

private :
    static void ThreadStart( void* arg );

    void PMThreadStart( void* arg );
};
#endif
