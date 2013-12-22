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

#ifndef @PROG_UPPER_NAME@_CLIENT_H
#define @PROG_UPPER_NAME@_CLIENT_H

#define INCL_WIN
#include <os2.h>

#include "KPMLib.h"

class @PROG_NAME@Client : public KWindow
{
public :
    @PROG_NAME@Client();
    virtual ~@PROG_NAME@Client();

protected :
    virtual MRESULT KDefWndProc( ULONG msg, MPARAM mp1 = 0, MPARAM mp2 = 0 );
    virtual MRESULT KWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 );

    virtual MRESULT OnPlAltered( HINI hiniUser, HINI hiniSystem );
    virtual MRESULT OnActivate( USHORT usActive, HWND hwnd );
    virtual MRESULT OnAppTerminateNotify( HAPP happ, ULONG flRetCode );
    virtual MRESULT OnAdjustWindowPos( PSWP pswp, ULONG flZero );
    virtual MRESULT OnBeginDrag( POINTS pts, bool fPointer );
    virtual MRESULT OnBeginSelect( POINTS pts, bool fPointer );
    virtual MRESULT OnButton1Click( POINTS pts, USHORT fsHit, USHORT fsFlags );
    virtual MRESULT OnButton1DblClk( POINTS pts, USHORT fsHit, USHORT fsFlags );
    virtual MRESULT OnButton1Down( POINTS pts, USHORT fsHit, USHORT fsFlags );
    virtual MRESULT OnButton1MotionEnd( POINTS pts, USHORT fsHit );
    virtual MRESULT OnButton1MotionStart( POINTS pts, USHORT fsHit );
    virtual MRESULT OnButton1Up( POINTS pts, USHORT fsHit, USHORT fsFlags );
    virtual MRESULT OnButton2Click( POINTS pts, USHORT fsHit, USHORT fsFlags );
    virtual MRESULT OnButton2DblClk( POINTS pts, USHORT fsHit, USHORT fsFlags );
    virtual MRESULT OnButton2Down( POINTS pts, USHORT fsHit, USHORT fsFlags );
    virtual MRESULT OnButton2MotionEnd( POINTS pts, USHORT fsHit );
    virtual MRESULT OnButton2MotionStart( POINTS pts, USHORT fsHit );
    virtual MRESULT OnButton2Up( POINTS pts, USHORT fsHit, USHORT fsFlags );
    virtual MRESULT OnButton3Click( POINTS pts, USHORT fsHit, USHORT fsFlags );
    virtual MRESULT OnButton3DblClk( POINTS pts, USHORT fsHit, USHORT fsFlags );
    virtual MRESULT OnButton3Down( POINTS pts, USHORT fsHit, USHORT fsFlags );
    virtual MRESULT OnButton3MotionEnd( POINTS pts, USHORT fsHit );
    virtual MRESULT OnButton3MotionStart( POINTS pts, USHORT fsHit );
    virtual MRESULT OnButton3Up( POINTS pts, USHORT fsHit, USHORT fsFlags );
    virtual MRESULT OnCalcFrameRect( PRECTL prcl, bool fFrame );
    virtual MRESULT OnCalcValidRects( PRECTL prcl, PSWP pswp );
    virtual MRESULT OnChar( USHORT fsFlags, UCHAR ucRepeat, UCHAR ucScanCode,
                            USHORT usCh, USHORT usVk );
    virtual MRESULT OnChord( USHORT fsHit );
    virtual MRESULT OnClose();
    virtual MRESULT OnCommand( USHORT usCmd, USHORT ulSource,
                               bool fPointer );
    virtual MRESULT CmdSrcPushButton( USHORT usCmd, bool fPointer );
    virtual MRESULT CmdSrcMenu( USHORT usCmd, bool fPointer );
    virtual MRESULT CmdSrcAccelerator( USHORT usCmd, bool fPointer );
    virtual MRESULT CmdSrcFontDlg( USHORT usCmd, bool fPointer );
    virtual MRESULT CmdSrcFileDlg( USHORT usCmd, bool fPointer );
    virtual MRESULT CmdSrcOther( USHORT usCmd, bool fPointer );
    virtual MRESULT CmdSrcUser( USHORT usCmd, USHORT usSource, bool fPointer );
    virtual MRESULT OnContextMenu( POINTS pts, bool fPointer );
    virtual MRESULT OnControl( USHORT id, USHORT usNotifyCode,
                               ULONG ulControlSpec );
    virtual MRESULT OnControlPointer( USHORT id, HPOINTER hptrNew );
    virtual MRESULT OnCreate( PVOID pCtrlData, PCREATESTRUCT pcs );
    virtual MRESULT OnCtlColorChange();
    virtual MRESULT OnDestroy();
    virtual MRESULT OnDrawItem( USHORT id, ULONG ulControlSpec );
    virtual MRESULT OnEnable( bool fNewEnabledState );
    virtual MRESULT OnEndDrag( POINTS pts, bool fPointer );
    virtual MRESULT OnEndSelect( POINTS pts, bool fPointer );
    virtual MRESULT OnError( USHORT usErrorCode );
    virtual MRESULT OnFocusChange( HWND hwndFocus, bool fSetFocus,
                                   USHORT fsFocusChange );
    virtual MRESULT OnFormatFrame( PSWP pswp, PRECTL prcl );
    virtual MRESULT OnHelp( USHORT usCmd, USHORT usSource, bool fPointer );
    virtual MRESULT HelpCmdSrcPushButton( USHORT usCmd, bool fPointer );
    virtual MRESULT HelpCmdSrcMenu( USHORT usCmd, bool fPointer );
    virtual MRESULT HelpCmdSrcAccelerator( USHORT usCmd, bool fPointer );
    virtual MRESULT HelpCmdSrcFontDlg( USHORT usCmd, bool fPointer );
    virtual MRESULT HelpCmdSrcFileDlg( USHORT usCmd, bool fPointer );
    virtual MRESULT HelpCmdSrcOther( USHORT usCmd, bool fPointer );
    virtual MRESULT HelpCmdSrcUser( USHORT usCmd, USHORT usSource,
                                    bool fPointer );
    virtual MRESULT OnHitTest( POINTS pts );
    virtual MRESULT OnHScroll( USHORT id, SHORT sSlider, USHORT usCmd );
    virtual MRESULT HSbLineLeft( USHORT id, SHORT sSlider );
    virtual MRESULT HSbLineRight( USHORT id, SHORT sSlider );
    virtual MRESULT HSbPageLeft( USHORT id, SHORT sSlider );
    virtual MRESULT HSbPageRight( USHORT id, SHORT sSlider );
    virtual MRESULT HSbSliderPosition( USHORT id, SHORT sSlider );
    virtual MRESULT HSbSliderTrack( USHORT id, SHORT sSlider );
    virtual MRESULT HSbEndScroll( USHORT id, SHORT sSlider );
    virtual MRESULT OnInitDlg( HWND hwndFocus, PVOID pCreate );
    virtual MRESULT OnInitMenu( SHORT sMenuID, HWND hwnd );
    virtual MRESULT OnJournalNotify( ULONG ulCommand, USHORT fsQueueStatus,
                                     USHORT usParam );
    virtual MRESULT OnMatchMnemonic( USHORT usMatch );
    virtual MRESULT OnMeasureItem( SHORT sID, ULONG ulControlSpec );
    virtual MRESULT OnMenuEnd( USHORT usID, HWND hwnd );
    virtual MRESULT OnMenuSelect( USHORT usItem, bool fPost, HWND hwnd );
    virtual MRESULT OnMinMaxFrame( PSWP pswp );
    virtual MRESULT OnMouseMap( ULONG ulPhysButton, ULONG ulMappedButton );
    virtual MRESULT OnMouseMove( SHORT sxMouse, SHORT syMouse,
                                 USHORT uswHitTest, USHORT fsFlags );
    virtual MRESULT OnMove();
    virtual MRESULT OnMsgBoxDismiss( HWND hwnd, ULONG ulButtonID );
    virtual MRESULT OnMsgBoxInit( HWND hwnd, LONG idWindow );
    virtual MRESULT OnNextMenu( HWND hwndMenu, USHORT usPrev );
    virtual MRESULT OnNull();
    virtual MRESULT OnOpen( bool fPointer, POINTS pts );
    virtual MRESULT OnPActivate( bool fActive, HWND hwnd );
    virtual MRESULT OnPaint();
    virtual MRESULT OnPControl( USHORT id, USHORT usNotify, ULONG ulZero );
    virtual MRESULT OnPPaint();
    virtual MRESULT OnPresParamChanged( ULONG idAttrType );
    virtual MRESULT OnPSetFocus( HWND hwnd, bool fFocus );
    virtual MRESULT OnPSize( SHORT scxOld, SHORT scyOld,
                             SHORT scxNew, SHORT scyNew );
    virtual MRESULT OnPSysColorChange( ULONG ulOptions );
    virtual MRESULT OnQueryAccelTable();
    virtual MRESULT OnQueryConvertPos( PRECTL pCursorPos );
    virtual MRESULT OnQueryCtlType();
    virtual MRESULT OnQueryDlgCode( PQMSG pQmsg );
    virtual MRESULT OnQueryHelpInfo();
    virtual MRESULT OnQueryTrackInfo( USHORT usTFlags, PTRACKINFO pti );
    virtual MRESULT OnQueryWindowParams( PWNDPARAMS pwp );
    virtual MRESULT OnQuit();
    virtual MRESULT OnRealizePalette();
    virtual MRESULT OnSaveApplication();
    virtual MRESULT OnSem1( ULONG flAccumBits );
    virtual MRESULT OnSem2( ULONG flAccumBits );
    virtual MRESULT OnSem3( ULONG flAccumBits );
    virtual MRESULT OnSem4( ULONG flAccumBits );
    virtual MRESULT OnSetAccelTable( HACCEL haccelNew );
    virtual MRESULT OnSetFocus( HWND hwnd, bool fFocus );
    virtual MRESULT OnSetHelpInfo( LONG lHelpInfo );
    virtual MRESULT OnSetSelection( bool fSel );
    virtual MRESULT OnSetWindowParams( PWNDPARAMS pwp );
    virtual MRESULT OnShow( bool fShow );
    virtual MRESULT OnSingleSelect( POINTS pts, bool fPointer );
    virtual MRESULT OnSize( SHORT scxOld, SHORT scyOld,
                            SHORT scxNew, SHORT scyNew );
    virtual MRESULT OnSubstituteString( USHORT usIndex );
    virtual MRESULT OnSysColorChange( ULONG flOptions );
    virtual MRESULT OnSysCommand( USHORT usCmd, USHORT usSource,
                                  bool fPointer );
    virtual MRESULT SysCmdSrcPushButton( USHORT usCmd, bool fPointer );
    virtual MRESULT SysCmdSrcMenu( USHORT usCmd, bool fPointer );
    virtual MRESULT SysCmdSrcAccelerator( USHORT usCmd, bool fPointer );
    virtual MRESULT SysCmdSrcFontDlg( USHORT usCmd, bool fPointer );
    virtual MRESULT SysCmdSrcFileDlg( USHORT usCmd, bool fPointer );
    virtual MRESULT SysCmdSrcOther( USHORT usCmd, bool fPointer );
    virtual MRESULT SysCmdSrcUser( USHORT usCmd, USHORT usSource,
                                   bool fPointer );
    virtual MRESULT OnSysValueChanged( USHORT usChangedFirst,
                                       USHORT usChangedLast );
    virtual MRESULT OnTextEdit( bool fPointer, POINTS pts );
    virtual MRESULT OnTimer( USHORT idTimer );
    virtual MRESULT OnTrackFrame( USHORT fsTrackFlags );
    virtual MRESULT OnTranslateAccel( PQMSG pqmsg );
#if 0
    virtual MRESULT OnTranslateMnemonic( PQMSG pqmsg );
#endif
    virtual MRESULT OnUpdateFrame( ULONG flCreateFlags );
    virtual MRESULT OnVRNDisabled( PVOID mp1, PVOID mp2 );
    virtual MRESULT OnVRNEnabled( bool fVisRgnChanged, PVOID mp2 );
    virtual MRESULT OnVScroll( USHORT id, SHORT sSlider, USHORT usCmd );
    virtual MRESULT VSbLineUp( USHORT id, SHORT sSlider );
    virtual MRESULT VSbLineDown( USHORT id, SHORT sSlider );
    virtual MRESULT VSbPageUp( USHORT id, SHORT sSlider );
    virtual MRESULT VSbPageDown( USHORT id, SHORT sSlider );
    virtual MRESULT VSbSliderPosition( USHORT id, SHORT sSlider );
    virtual MRESULT VSbSliderTrack( USHORT id, SHORT sSlider );
    virtual MRESULT VSbEndScroll( USHORT id, SHORT sSlider );
    virtual MRESULT OnWindowPosChanged( PSWP pswp, ULONG flAwp );
};
#endif

