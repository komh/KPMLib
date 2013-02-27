/*
    KPMLib, C++ encapsulation class library for OS/2 PM
    Copyright (C) 2012-2013 by KO Myung-Hun <komh@chollian.net>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software Foundation,
    Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
*/

#define INCL_DOS
#define INCL_WIN
#include <os2.h>

#include <cstdlib>

#include "KPMSubThread.h"

bool KPMSubThread::BeginThread( void* arg, int cbStackSize )
{
    HEV  hevDone;
    bool rc = false;

    DosCreateEventSem( NULL, &hevDone, 0, FALSE );

    void* apArg[] = { this, &hevDone, arg };

    _tid = _beginthread( ThreadStart, 0, cbStackSize, apArg );

    if( _tid != -1 )
    {
        DosWaitEventSem( hevDone, SEM_INDEFINITE_WAIT );

        rc = true;
    }

    DosCloseEventSem( hevDone );

    return rc;
}

bool KPMSubThread::WaitThread( bool fWait )
{
    TID tid = _tid;

    if( DosWaitThread( &tid, fWait ? DCWW_WAIT : DCWW_NOWAIT ))
        return false;

    return true;
}

void KPMSubThread::ThreadStart( void* arg )
{
    void**        ppArg    = reinterpret_cast< void** >( arg );
    KPMSubThread* thread   = reinterpret_cast< KPMSubThread* >( ppArg[ 0 ]);
    PHEV          phevDone = reinterpret_cast< PHEV >( ppArg[ 1 ]);

    arg = ppArg[ 2 ];

    DosPostEventSem( *phevDone );

    thread->PMThreadStart( arg );
}

void KPMSubThread::PMThreadStart( void* arg )
{
    _hab = WinInitialize( 0 );
    _hmq = WinCreateMsgQueue( _hab, 0 );

    ThreadMain( arg );

    WinDestroyMsgQueue( _hmq );
    WinTerminate( _hab );
}

