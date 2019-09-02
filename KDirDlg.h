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

#ifndef KDIR_DLG_H
#define KDIR_DLG_H

#define INCL_WIN
#include <os2.h>

#include "KPMLib.h"

class KDirDlg : public KFileDlg
{
public :
    KDirDlg() : KFileDlg() {}
    ~KDirDlg() {}

    virtual bool FileDlg( const KWindow* pkwndP, const KWindow* pkwndO );

protected :
    virtual MRESULT KWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 );
    virtual MRESULT OnInitDlg( HWND hwnd, PVOID pcreate );
    virtual MRESULT OnControl( USHORT id, USHORT usCode, ULONG ulParam );

private :
    KStaticText _kstFile;
    KStaticText _kstDir;
    KListBox    _klbDir;
    KStaticText _kstDrive;
    KComboBox   _kcbDrive;
    KButton     _kbtnOk;
    KButton     _kbtnCancel;

    MRESULT OnSetFocusToLB();
};
#endif
