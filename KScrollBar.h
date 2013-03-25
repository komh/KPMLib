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

#ifndef KSCROLL_BAR_H
#define KSCROLL_BAR_H

#include <string>

#include "KWindow.h"

class KScrollBar : public KWindow
{
public :
    KScrollBar() : KWindow() {};
    virtual ~KScrollBar() {};

    virtual bool CreateWindow( const KWindow* pkwndP, const string& strName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    virtual SHORT QueryPos() const
    {
        return SHORT1FROMMR( SendMsg( SBM_QUERYPOS ));
    }

    virtual void QueryRange( SHORT& sFirst, SHORT& sLast ) const
    {
        MRESULT mr = SendMsg( SBM_QUERYRANGE );

        sFirst = SHORT1FROMMR( mr );
        sLast  = SHORT2FROMMR( mr );
    }

    virtual bool SetPos( SHORT sSlider ) const
    {
        return SendMsg( SBM_SETPOS, MPFROMSHORT( sSlider ));
    }

    virtual bool SetPosP( SHORT sSlider ) const
    {
        return PostMsg( SBM_SETPOS, MPFROMSHORT( sSlider ));
    }

    virtual bool SetScrollBar( SHORT sSlider,
                               SHORT sFirst, SHORT sLast ) const
    {
        return SendMsg( SBM_SETSCROLLBAR, MPFROMSHORT( sSlider ),
                        MPFROM2SHORT( sFirst, sLast ));
    }

    virtual bool SetScrollBarP( SHORT sSlider,
                                SHORT sFirst, SHORT sLast ) const
    {
        return PostMsg( SBM_SETSCROLLBAR, MPFROMSHORT( sSlider ),
                        MPFROM2SHORT( sFirst, sLast ));
    }

    virtual bool SetThumbSize( SHORT sVisible, SHORT sTotal ) const
    {
        return SendMsg( SBM_SETTHUMBSIZE, MPFROM2SHORT( sVisible, sTotal ));
    }

    virtual bool SetThumbSizeP( SHORT sVisible, SHORT sTotal ) const
    {
        return PostMsg( SBM_SETTHUMBSIZE, MPFROM2SHORT( sVisible, sTotal ));
    }
};
#endif
