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

    int  GetTID() const { return _tid; }
    void SetTID( int tid ) { _tid = tid; }

    HAB  GetHAB() const { return _hab; }
    void SetHAB( HAB hab ) { _hab = hab; }

    HMQ  GetHMQ() const { return _hmq; }
    void SetHMQ( HMQ hmq ) { _hmq = hmq; }

private :
    int _tid;

    HAB _hab;
    HMQ _hmq;
};
#endif

