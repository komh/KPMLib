/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Mozilla browser.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2000
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Stuart Parmenter <pavlov@netscape.com>
 *   KO Myung-Hun <komh@chollian.net>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#define INCL_WIN
#include <os2.h>

#include <cstring>

#include "KPMLib.h"

#include "KDirDlg.h"

#define UM_SETFOCUS_TO_LB ( WM_USER + 1 )

MRESULT KDirDlg::KWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    if( msg == UM_SETFOCUS_TO_LB )
        return OnSetFocusToLB();

    return KFileDlg::KWndProc( msg, mp1, mp2 );
}

MRESULT KDirDlg::OnInitDlg( HWND hwnd, PVOID pcreate )
{
    SWP swpFileST;
    SWP swpDirST;
    SWP swpDirLB;
    SWP swpDriveST;
    SWP swpDriveCB;
    SWP swpDriveCBEF;
    SWP swpOK;
    SWP swpCancel;

    ULONG ulCurY, ulCurX;
    LONG  lScreenX, lScreenY, lDlgFrameX, lDlgFrameY, lTitleBarY;

    lScreenX   = QuerySysValue(SV_CXSCREEN);
    lScreenY   = QuerySysValue(SV_CYSCREEN);
    lDlgFrameX = QuerySysValue(SV_CXDLGFRAME);
    lDlgFrameY = QuerySysValue(SV_CYDLGFRAME);
    lTitleBarY = QuerySysValue(SV_CYTITLEBAR);

    WindowFromID(DID_FILENAME_TXT, _kstFile);
    WindowFromID(DID_DIRECTORY_TXT, _kstDir);
    WindowFromID(DID_DIRECTORY_LB, _klbDir);
    WindowFromID(DID_DRIVE_TXT, _kstDrive);
    WindowFromID(DID_DRIVE_CB, _kcbDrive);
    WindowFromID(DID_OK, _kbtnOk);
    WindowFromID(DID_CANCEL, _kbtnCancel);

#define SPACING 10
    // Reposition drives combobox
    ulCurY = SPACING;
    ulCurX = SPACING + lDlgFrameX;
    _kbtnOk.QueryWindowPos(&swpOK);
    _kbtnOk.SetWindowPos(0, ulCurX, ulCurY, 0, 0, SWP_MOVE);
    ulCurY += swpOK.cy + SPACING;
    _kbtnCancel.QueryWindowPos(&swpCancel);
    _kbtnCancel.SetWindowPos(0, ulCurX+swpOK.cx+10, SPACING, 0, 0, SWP_MOVE);
    _klbDir.QueryWindowPos(&swpDirLB);
    _klbDir.SetWindowPos(0, ulCurX, ulCurY, swpDirLB.cx, swpDirLB.cy,
                         SWP_MOVE | SWP_SIZE);
    ulCurY += swpDirLB.cy + SPACING;
    _kstDir.QueryWindowPos(&swpDirST);
    _kstDir.SetWindowPos(0, ulCurX, ulCurY, swpDirST.cx, swpDirST.cy,
                         SWP_MOVE | SWP_SIZE);
    ulCurY += swpDirST.cy + SPACING;
    _kcbDrive.QueryWindowPos(&swpDriveCB);
    KEntryField kefCBEdit;
    _kcbDrive.WindowFromID(CBID_EDIT, kefCBEdit);
    kefCBEdit.QueryWindowPos(&swpDriveCBEF);
    _kcbDrive.SetWindowPos(0, ulCurX, ulCurY-(swpDriveCB.cy-swpDriveCBEF.cy)+5,
                           swpDirLB.cx, swpDriveCB.cy, SWP_SIZE | SWP_MOVE);
    ulCurY += swpDriveCBEF.cy + SPACING;
    _kstDrive.QueryWindowPos(&swpDriveST);
    _kstDrive.SetWindowPos(0, ulCurX, ulCurY, swpDriveST.cx, swpDriveST.cy,
                           SWP_MOVE | SWP_SIZE);
    ulCurY += swpDriveST.cy + SPACING;
    _kstFile.QueryWindowPos(&swpFileST);
    _kstFile.SetWindowPos(0, ulCurX, ulCurY, swpFileST.cx, swpFileST.cy,
                          SWP_MOVE | SWP_SIZE);
    ulCurY += swpFileST.cy + SPACING;

    KEnumWindows kenum;
    KWindow      kwndNext;

    // Hide unused stuff
    kenum.BeginEnumWindows(this);
    while (kenum.GetNextWindow(kwndNext))
    {
        USHORT usID = kwndNext.QueryWindowUShort(QWS_ID);
        if (usID != DID_FILENAME_TXT &&
            usID != DID_DIRECTORY_TXT &&
            usID != DID_DIRECTORY_LB &&
            usID != DID_DRIVE_TXT &&
            usID != DID_DRIVE_CB &&
            usID != DID_OK &&
            usID != DID_CANCEL &&
            usID != FID_TITLEBAR &&
            usID != FID_SYSMENU &&
            usID != FID_MINMAX)
        {
            kwndNext.ShowWindow(false);
        }
    }
    kenum.EndEnumWindows();

    SetWindowPos(KWND_TOP,
                 (lScreenX/2)-((swpDirLB.cx+2*SPACING+2*lDlgFrameX)/2),
                 (lScreenY/2)-((ulCurY+2*lDlgFrameY+lTitleBarY)/2),
                 swpDirLB.cx+2*SPACING+2*lDlgFrameX,
                 ulCurY+2*lDlgFrameY+lTitleBarY,
                 SWP_MOVE | SWP_SIZE);

    // Give the focus to the directory list box
    PostMsg(UM_SETFOCUS_TO_LB);

    return KFileDlg::OnInitDlg(hwnd, pcreate);
}

MRESULT KDirDlg::OnControl( USHORT id, USHORT usCode, ULONG ulParam )
{
    PFILEDLG pfiledlg = reinterpret_cast< PFILEDLG >
                            (QueryWindowPtr(QWL_USER));

    KWindowPS kwps;
    SWP       swp;
    RECTL     rectlString = {0,0,1000,1000};
    char*     ptr = NULL;
    int       iHalfLen;
    int       iLength;
    CHAR      szString[CCHMAXPATH];

    strcpy(szString, pfiledlg->szFullFile);
    iLength = strlen(pfiledlg->szFullFile);
    /* If we are not just a drive */
    if (iLength > 3) {
        if (szString[iLength-1] == '\\') {
            szString[iLength-1] = '\0';
            iLength--;
        }
    }

    kwps.GetPS( &_kstFile );
    _kstFile.QueryWindowPos(&swp);

    kwps.DrawText(iLength, szString, &rectlString, 0, 0,
                  DT_BOTTOM | DT_QUERYEXTENT | DT_TEXTATTRS);
    while(rectlString.xRight > swp.cx)
    {
        iHalfLen = iLength / 2;
        if(iHalfLen == 2)
            break;

        ptr = szString + iHalfLen;
        memmove(ptr - 1, ptr, strlen(ptr) + 1);
        szString[iHalfLen - 2] = '.';
        szString[iHalfLen - 1] = '.';
        szString[iHalfLen]     = '.';
        iLength = strlen(szString);
        rectlString.xLeft = rectlString.yBottom = 0;
        rectlString.xRight = rectlString.yTop = 1000;
        kwps.DrawText(iLength, szString, &rectlString, 0, 0,
                      DT_BOTTOM | DT_QUERYEXTENT | DT_TEXTATTRS);
    }

    kwps.ReleasePS();
    _kstFile.SetWindowText(szString);

    return KFileDlg::OnControl( id, usCode, ulParam );
}

MRESULT KDirDlg::OnSetFocusToLB()
{
    _klbDir.SetFocus();

    return 0;
}

bool KDirDlg::FileDlg(const KWindow* pkwndP, const KWindow* pkwndO)
{
    int   len = GetFullFile().length();
    char *p;

    CHAR  szFullFile[CCHMAXPATH];
    strcpy( szFullFile, GetFullFile().c_str());

    // Remove the trailing back-slash
    while (len > 0 && szFullFile[len - 1] == '\\')
        len--;

    // To prevent from treating the last components of szFullFile as
    // a filename
    strncpy(szFullFile + len, "\\^",
            sizeof(szFullFile) - len - 1);

    SetFullFile( szFullFile );
    bool rc = KFileDlg::FileDlg(pkwndP, pkwndO);

    strcpy( szFullFile, GetFullFile().c_str());

    // Remove a temporary filename part
    p = strrchr( szFullFile, '\\');
    // Except x:\ case
    if (p && (p - szFullFile) == 2)
        p++;

    if (p)
        *p = '\0';

    SetFullFile(szFullFile);

    return rc;
}
