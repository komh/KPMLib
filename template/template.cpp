/*
    @PROG_NAME@
    Copyright (C) 2013 by KO Myung-Hun <komh@chollian.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#define INCL_WIN
#include <os2.h>

#include "KPMLib.h"

#include "@PROG_NAME@Client.h"

#include "@PROG_NAME@.h"

@PROG_NAME@::@PROG_NAME@() : KPMApp()
{
}

@PROG_NAME@::~@PROG_NAME@()
{
}

int @PROG_NAME@::Run()
{
    @PROG_NAME@Client kclient;
    kclient.RegisterClass( GetHAB(), WC_@PROG_UPPER_NAME@,
                           CS_MOVENOTIFY, sizeof( PVOID ));

    ULONG flFrameFlags;
    flFrameFlags = FCF_SYSMENU | FCF_TITLEBAR | FCF_MINMAX | FCF_SIZEBORDER |
                   FCF_SHELLPOSITION | FCF_TASKLIST;

    KFrameWindow kframe;
    kframe.CreateStdWindow( KWND_DESKTOP,            // parent window handle
                            WS_VISIBLE,              // frame window style
                            &flFrameFlags,           // window style
                            @PROG_UPPER_NAME@_TITLE, // window title
                            0,                       // default client style
                            0,                       // resource in exe file
                            ID_@PROG_UPPER_NAME@,    // frame window id
                            kclient                  // client window handle
                          );

    if( kframe.GetHWND())
    {
        KPMApp::Run();

        kframe.DestroyWindow();
    }

    return 0;
}

int main()
{
    @PROG_NAME@ @PROG_LOWER_NAME@;

    return @PROG_LOWER_NAME@.Run();
}
