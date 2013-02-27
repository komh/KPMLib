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

#ifndef KFRAMEWINDOW_H
#define KFRAMEWINDOW_H

#define INCL_WIN
#include <os2.h>

#include <string>

#include "KWindow.h"
#include "KScrollBar.h"
#include "KMenu.h"
#include "KTitleBar.h"

class KFrameWindow : public KWindow
{
public :
    KFrameWindow() : KWindow() {}
    virtual ~KFrameWindow() {}

    virtual bool CreateStdWindow( KWindow* pkwndP, ULONG flStyle,
                                  PULONG pflCreateFlags,
                                  const string& strTitle, ULONG flClientStyle,
                                  HMODULE hmodResources, ULONG ulId,
                                  KWindow& kwndClient );

    KWindow& GetClient() { return _kwndClient; }
    KScrollBar& GetHorzScroll() { return _kwndHorzScroll; }
    KMenu& GetMenu() { return _kwndMenu; }
    KMenu& GetMinMax() { return _kwndMinMax; }
    KMenu& GetSysMenu() { return _kwndSysMenu; }
    KTitleBar& GetTitleBar() { return _kwndTitleBar; }
    KScrollBar& GetVertScroll() { return _kwndVertScroll; }

protected :
    KWindow    _kwndClient;
    KScrollBar _kwndHorzScroll;
    KMenu      _kwndMenu;
    KMenu      _kwndMinMax;
    KMenu      _kwndSysMenu;
    KTitleBar  _kwndTitleBar;
    KScrollBar _kwndVertScroll;
};
#endif
