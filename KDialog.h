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

#ifndef KDIALOG_H
#define KDIALOG_H

#define INCL_WIN
#include <os2.h>

#include <string>

#include "KFrameWindow.h"

class KDialog : public KFrameWindow
{
public :
    KDialog();
    virtual ~KDialog();

    virtual USHORT CheckButton( USHORT usID, USHORT usChkState ) const
    {
        return WinCheckButton( GetHWND(), usID, usChkState );
    }

    virtual bool DismissDlg( ULONG ulResult ) const
    {
        return WinDismissDlg( GetHWND(), ulResult );
    }

    virtual void DlgBox( KWindow* pkwndP, KWindow* pkwndO, HMODULE hmod,
                         ULONG idDlg, PVOID pCreateParams = 0 );
    virtual bool LoadDlg( KWindow* pkwndP, KWindow* pkwndO, HMODULE hmod,
                          ULONG idDlg, PVOID pCreateParams = 0 );
    virtual void ProcessDlg() { _ulResult = WinProcessDlg( GetHWND()); }

    virtual USHORT QueryButtonCheckstate( USHORT usID ) const
    {
        return WinQueryButtonCheckstate( GetHWND(), usID );
    }

    virtual ULONG QueryDlgItemText( ULONG idItem, std::string& strText ) const
    {
        LONG  lMaxText = QueryDlgItemTextLength( idItem ) + 1;
        PSZ   pszText  = new CHAR[ lMaxText ];
        ULONG rc;

        rc = WinQueryDlgItemText( GetHWND(), idItem, lMaxText, pszText );

        strText = pszText;

        delete[] pszText;

        return rc;
    }

    virtual LONG QueryDlgItemTextLength( ULONG idItem ) const
    {
        return WinQueryDlgItemTextLength( GetHWND(), idItem );
    }

    virtual MRESULT SendDlgItemMsg( ULONG idItem, ULONG msg, MPARAM mp1,
                                    MPARAM mp2 ) const
    {
        return WinSendDlgItemMsg( GetHWND(), idItem, msg, mp1, mp2 );
    }

    virtual bool SetDlgItemText( ULONG idItem, 
                                 const std::string& strText ) const
    {
        return WinSetDlgItemText( GetHWND(), idItem, strText.c_str());
    }

    ULONG GetResult() const { return _ulResult; }

protected :
    virtual MRESULT KDefWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
    {
        return WinDefDlgProc( GetHWND(), msg, mp1, mp2 );
    }

private :
    ULONG _ulResult;

    static MRESULT EXPENTRY DlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1,
                                     MPARAM mp2 );
};
#endif
