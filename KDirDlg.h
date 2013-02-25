/*
 * Copyright (c) 2012 by KO Myung-Hun <komh@chollian.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms,
 * with or without modification, are permitted provided
 * that the following conditions are met:
 *
 *   Redistributions of source code must retain the above
 *   copyright notice, this list of conditions and the
 *   following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following
 *   disclaimer in the documentation and/or other materials
 *   provided with the distribution.
 *
 *   Neither the name of the copyright holder nor the names
 *   of any other contributors may be used to endorse or
 *   promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
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
