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

#include <cstring>

#include "KDialog.h"

struct CreateParams
{
    USHORT   cb;
    PVOID    pCreate;
    KDialog* pkdlg;
};

KDialog::KDialog() : KFrameWindow()
{
    _ulResult = 0;
}

KDialog::~KDialog()
{
}

void KDialog::DlgBox( KWindow* pkwndP, KWindow* pkwndO, HMODULE hmod,
                      ULONG idDlg, PVOID pCreateParams )
{
    HWND hwndP = pkwnd2hwnd( pkwndP );
    HWND hwndO = pkwnd2hwnd( pkwndO );

    CreateParams cp = { sizeof( cp ), pCreateParams, this };

    _ulResult = WinDlgBox( hwndP, hwndO, DlgProc, hmod, idDlg, &cp );
}

bool KDialog::LoadDlg( KWindow* pkwndP, KWindow* pkwndO, HMODULE hmod,
                       ULONG idDlg, PVOID pCreateParams )
{
    HWND hwndP = pkwnd2hwnd( pkwndP );
    HWND hwndO = pkwnd2hwnd( pkwndO );

    CreateParams cp = { sizeof( cp ), pCreateParams, this };

    return WinLoadDlg( hwndP, hwndO, DlgProc, hmod, idDlg, &cp );
}

MRESULT EXPENTRY KDialog::DlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1,
                                   MPARAM mp2 )
{
    if( msg == WM_INITDLG )
    {
        CreateParams* pcp = reinterpret_cast< CreateParams* >( mp2 );

        mp2 = pcp->pCreate;

        KDialog* pkdlg = pcp->pkdlg;

        // Subclass to KWindow::WndProc()
        pkdlg->SetHWND( hwndDlg );

        // Pass the control to KWindow::WndProc()
        return pkdlg->KWndProc( msg, mp1, mp2 );
    }

    return WinDefDlgProc( hwndDlg, msg, mp1, mp2 );
}

