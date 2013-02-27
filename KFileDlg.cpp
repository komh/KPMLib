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

#include "KFileDlg.h"

KFileDlg::KFileDlg() : KDialog()
{
    memset( &_fild, 0, sizeof( _fild ));

    _ppszITypeList  = 0;
    _ppszIDriveList = 0;
}

KFileDlg::~KFileDlg()
{
    if( _fild.papszFQFilename )
        WinFreeFileDlgList( _fild.papszFQFilename );

    delete[] _ppszITypeList;
    delete[] _ppszIDriveList;
}

bool KFileDlg::FileDlg( const KWindow* pkwndP, const KWindow* pkwndO )
{
    HWND hwndP = pkwnd2hwnd( pkwndP );
    HWND hwndO = pkwnd2hwnd( pkwndO );

    if( !_fild.fl )
        _fild.fl |= FDS_OPEN_DIALOG | FDS_CENTER;

    _fild.pfnDlgProc = FileDlgProc;
    _fild.ulUser     = reinterpret_cast< ULONG >( this );

    _hwnd = WinFileDlg( hwndP, hwndO, &_fild );

    return _hwnd;
}

MRESULT EXPENTRY KFileDlg::FileDlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1,
                                        MPARAM mp2 )
{
    if( msg == WM_INITDLG )
    {
        PFILEDLG pfild = reinterpret_cast< PFILEDLG >
                            ( WinQueryWindowPtr( hwndDlg, 0 ));

        KFileDlg* pkfdlg = reinterpret_cast< KFileDlg* >( pfild->ulUser );

        // Subclass to KWindow::WndProc()
        pkfdlg->SetHWND( hwndDlg );

        // Pass the control to KWindow::WndProc()
        return pkfdlg->KWndProc( msg, mp1, mp2 );
    }

    return WinDefFileDlgProc( hwndDlg, msg, mp1, mp2 );
}

