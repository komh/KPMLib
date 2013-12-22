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

#include "@PROG_NAME@.h"

#include "@PROG_NAME@Client.h"

@PROG_NAME@Client::@PROG_NAME@Client() : KWindow()
{
}

@PROG_NAME@Client::~@PROG_NAME@Client()
{
}

MRESULT @PROG_NAME@Client::KDefWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    return KWindow::KDefWndProc( msg, mp1, mp2 );
}

MRESULT @PROG_NAME@Client::KWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    return KWindow::KWndProc( msg, mp1, mp2 );
}

MRESULT @PROG_NAME@Client::OnPlAltered( HINI hiniUser, HINI hiniSystem )
{
    return KWindow::OnPlAltered( hiniUser, hiniSystem );
}

MRESULT @PROG_NAME@Client::OnActivate( USHORT usActive, HWND hwnd )
{
    return KWindow::OnActivate( usActive, hwnd );
}

MRESULT @PROG_NAME@Client::OnAppTerminateNotify( HAPP happ, ULONG flRetCode )
{
    return KWindow::OnAppTerminateNotify( happ, flRetCode );
}

MRESULT @PROG_NAME@Client::OnAdjustWindowPos( PSWP pswp, ULONG flZero )
{
    return KWindow::OnAdjustWindowPos( pswp, flZero );
}

MRESULT @PROG_NAME@Client::OnBeginDrag( POINTS pts, bool fPointer )
{
    return KWindow::OnBeginDrag( pts, fPointer );
}

MRESULT @PROG_NAME@Client::OnBeginSelect( POINTS pts, bool fPointer )
{
    return KWindow::OnBeginSelect( pts, fPointer );
}

MRESULT @PROG_NAME@Client::OnButton1Click( POINTS pts, USHORT fsHit,
                                           USHORT fsFlags )
{
    return KWindow::OnButton1Click( pts, fsHit, fsFlags );
}

MRESULT @PROG_NAME@Client::OnButton1DblClk( POINTS pts, USHORT fsHit,
                                            USHORT fsFlags )
{
    return KWindow::OnButton1DblClk( pts, fsHit, fsFlags );
}

MRESULT @PROG_NAME@Client::OnButton1Down( POINTS pts, USHORT fsHit,
                                          USHORT fsFlags )
{
    return KWindow::OnButton1Down( pts, fsHit, fsFlags );
}

MRESULT @PROG_NAME@Client::OnButton1MotionEnd( POINTS pts, USHORT fsHit )
{
    return KWindow::OnButton1MotionEnd( pts, fsHit );
}

MRESULT @PROG_NAME@Client::OnButton1MotionStart( POINTS pts, USHORT fsHit )
{
    return KWindow::OnButton1MotionStart( pts, fsHit );
}

MRESULT @PROG_NAME@Client::OnButton1Up( POINTS pts, USHORT fsHit,
                                        USHORT fsFlags )
{
    return KWindow::OnButton1Up( pts, fsHit, fsFlags );
}

MRESULT @PROG_NAME@Client::OnButton2Click( POINTS pts, USHORT fsHit,
                                           USHORT fsFlags )
{
    return KWindow::OnButton2Click( pts, fsHit, fsFlags );
}

MRESULT @PROG_NAME@Client::OnButton2DblClk( POINTS pts, USHORT fsHit,
                                            USHORT fsFlags )
{
    return KWindow::OnButton2DblClk( pts, fsHit, fsFlags );
}

MRESULT @PROG_NAME@Client::OnButton2Down( POINTS pts, USHORT fsHit,
                                          USHORT fsFlags )
{
    return KWindow::OnButton2Down( pts, fsHit, fsFlags );
}

MRESULT @PROG_NAME@Client::OnButton2MotionEnd( POINTS pts, USHORT fsHit )
{
    return KWindow::OnButton2MotionEnd( pts, fsHit );
}

MRESULT @PROG_NAME@Client::OnButton2MotionStart( POINTS pts, USHORT fsHit )
{
    return KWindow::OnButton2MotionStart( pts, fsHit );
}

MRESULT @PROG_NAME@Client::OnButton2Up( POINTS pts, USHORT fsHit,
                                        USHORT fsFlags )
{
    return KWindow::OnButton2Up( pts, fsHit, fsFlags );
}

MRESULT @PROG_NAME@Client::OnButton3Click( POINTS pts, USHORT fsHit,
                                           USHORT fsFlags )
{
    return KWindow::OnButton3Click( pts, fsHit, fsFlags );
}

MRESULT @PROG_NAME@Client::OnButton3DblClk( POINTS pts, USHORT fsHit,
                                            USHORT fsFlags )
{
    return KWindow::OnButton3DblClk( pts, fsHit, fsFlags );
}

MRESULT @PROG_NAME@Client::OnButton3Down( POINTS pts, USHORT fsHit,
                                          USHORT fsFlags )
{
    return KWindow::OnButton3Down( pts, fsHit, fsFlags );
}

MRESULT @PROG_NAME@Client::OnButton3MotionEnd( POINTS pts, USHORT fsHit )
{
    return KWindow::OnButton3MotionEnd( pts, fsHit );
}

MRESULT @PROG_NAME@Client::OnButton3MotionStart( POINTS pts, USHORT fsHit )
{
    return KWindow::OnButton3MotionStart( pts, fsHit );
}

MRESULT @PROG_NAME@Client::OnButton3Up( POINTS pts, USHORT fsHit,
                                        USHORT fsFlags )
{
    return KWindow::OnButton3Up( pts, fsHit, fsFlags );
}

MRESULT @PROG_NAME@Client::OnCalcFrameRect( PRECTL prcl, bool fFrame )
{
    return KWindow::OnCalcFrameRect( prcl, fFrame );
}

MRESULT @PROG_NAME@Client::OnCalcValidRects( PRECTL prcl, PSWP pswp )
{
    return KWindow::OnCalcValidRects( prcl, pswp );
}

MRESULT @PROG_NAME@Client::OnChar( USHORT fsFlags, UCHAR ucRepeat,
                                   UCHAR ucScanCode, USHORT usCh,
                                   USHORT usVk )
{
    return KWindow::OnChar( fsFlags, ucRepeat, ucScanCode, usCh, usVk );
}

MRESULT @PROG_NAME@Client::OnChord( USHORT fsHit )
{
    return KWindow::OnChord( fsHit );
}

MRESULT @PROG_NAME@Client::OnClose()
{
    return KWindow::OnClose();
}

MRESULT @PROG_NAME@Client::OnCommand( USHORT usCmd, USHORT ulSource,
                                      bool fPointer )
{
    return KWindow::OnCommand( usCmd, ulSource, fPointer );
}

MRESULT @PROG_NAME@Client::CmdSrcPushButton( USHORT usCmd, bool fPointer )
{
    return KWindow::CmdSrcPushButton( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::CmdSrcMenu( USHORT usCmd, bool fPointer )
{
    return KWindow::CmdSrcMenu( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::CmdSrcAccelerator( USHORT usCmd, bool fPointer )
{
    return KWindow::CmdSrcAccelerator( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::CmdSrcFontDlg( USHORT usCmd, bool fPointer )
{
    return KWindow::CmdSrcFontDlg( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::CmdSrcFileDlg( USHORT usCmd, bool fPointer )
{
    return KWindow::CmdSrcFileDlg( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::CmdSrcOther( USHORT usCmd, bool fPointer )
{
    return KWindow::CmdSrcOther( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::CmdSrcUser( USHORT usCmd, USHORT usSource,
                                       bool fPointer )
{
    return KWindow::CmdSrcUser( usCmd, usSource, fPointer );
}

MRESULT @PROG_NAME@Client::OnContextMenu( POINTS pts, bool fPointer )
{
    return KWindow::OnContextMenu( pts, fPointer );
}

MRESULT @PROG_NAME@Client::OnControl( USHORT id, USHORT usNotifyCode,
                                      ULONG ulControlSpec )
{
    return KWindow::OnControl( id, usNotifyCode, ulControlSpec );
}

MRESULT @PROG_NAME@Client::OnControlPointer( USHORT id, HPOINTER hptrNew )
{
    return KWindow::OnControlPointer( id, hptrNew );
}

MRESULT @PROG_NAME@Client::OnCreate( PVOID pCtrlData, PCREATESTRUCT pcs )
{
    return KWindow::OnCreate( pCtrlData, pcs );
}

MRESULT @PROG_NAME@Client::OnCtlColorChange()
{
    return KWindow::OnCtlColorChange();
}

MRESULT @PROG_NAME@Client::OnDestroy()
{
    return KWindow::OnDestroy();
}

MRESULT @PROG_NAME@Client::OnDrawItem( USHORT id, ULONG ulControlSpec )
{
    return KWindow::OnDrawItem( id, ulControlSpec );
}

MRESULT @PROG_NAME@Client::OnEnable( bool fNewEnabledState )
{
    return KWindow::OnEnable( fNewEnabledState );
}

MRESULT @PROG_NAME@Client::OnEndDrag( POINTS pts, bool fPointer )
{
    return KWindow::OnEndDrag( pts, fPointer );
}

MRESULT @PROG_NAME@Client::OnEndSelect( POINTS pts, bool fPointer )
{
    return KWindow::OnEndSelect( pts, fPointer );
}

MRESULT @PROG_NAME@Client::OnError( USHORT usErrorCode )
{
    return KWindow::OnError( usErrorCode );
}

MRESULT @PROG_NAME@Client::OnFocusChange( HWND hwndFocus, bool fSetFocus,
                                          USHORT fsFocusChange )
{
    return KWindow::OnFocusChange( hwndFocus, fSetFocus, fsFocusChange );
}

MRESULT @PROG_NAME@Client::OnFormatFrame( PSWP pswp, PRECTL prcl )
{
    return KWindow::OnFormatFrame( pswp, prcl );
}

MRESULT @PROG_NAME@Client::OnHelp( USHORT usCmd, USHORT usSource,
                                   bool fPointer )
{
    return KWindow::OnHelp( usCmd, usSource, fPointer );
}

MRESULT @PROG_NAME@Client::HelpCmdSrcPushButton( USHORT usCmd, bool fPointer )
{
    return KWindow::HelpCmdSrcPushButton( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::HelpCmdSrcMenu( USHORT usCmd, bool fPointer )
{
    return KWindow::HelpCmdSrcMenu( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::HelpCmdSrcAccelerator( USHORT usCmd,
                                                  bool fPointer )
{
    return KWindow::HelpCmdSrcAccelerator( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::HelpCmdSrcFontDlg( USHORT usCmd, bool fPointer )
{
    return KWindow::HelpCmdSrcFontDlg( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::HelpCmdSrcFileDlg( USHORT usCmd, bool fPointer )
{
    return KWindow::HelpCmdSrcFileDlg( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::HelpCmdSrcOther( USHORT usCmd, bool fPointer )
{
    return KWindow::HelpCmdSrcOther( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::HelpCmdSrcUser( USHORT usCmd, USHORT usSource,
                                           bool fPointer )
{
    return KWindow::HelpCmdSrcUser( usCmd, usSource, fPointer );
}

MRESULT @PROG_NAME@Client::OnHitTest( POINTS pts )
{
    return KWindow::OnHitTest( pts );
}

MRESULT @PROG_NAME@Client::OnHScroll( USHORT id, SHORT sSlider, USHORT usCmd )
{
    return KWindow::OnHScroll( id, sSlider, usCmd );
}

MRESULT @PROG_NAME@Client::HSbLineLeft( USHORT id, SHORT sSlider )
{
    return KWindow::HSbLineLeft( id, sSlider );
}

MRESULT @PROG_NAME@Client::HSbLineRight( USHORT id, SHORT sSlider )
{
    return KWindow::HSbLineRight( id, sSlider );
}

MRESULT @PROG_NAME@Client::HSbPageLeft( USHORT id, SHORT sSlider )
{
    return KWindow::HSbPageLeft( id, sSlider );
}

MRESULT @PROG_NAME@Client::HSbPageRight( USHORT id, SHORT sSlider )
{
    return KWindow::HSbPageRight( id, sSlider );
}

MRESULT @PROG_NAME@Client::HSbSliderPosition( USHORT id, SHORT sSlider )
{
    return KWindow::HSbSliderPosition( id, sSlider );
}

MRESULT @PROG_NAME@Client::HSbSliderTrack( USHORT id, SHORT sSlider )
{
    return KWindow::HSbSliderTrack( id, sSlider );
}

MRESULT @PROG_NAME@Client::HSbEndScroll( USHORT id, SHORT sSlider )
{
    return KWindow::HSbEndScroll( id, sSlider );
}

MRESULT @PROG_NAME@Client::OnInitDlg( HWND hwndFocus, PVOID pCreate )
{
    return KWindow::OnInitDlg( hwndFocus, pCreate );
}

MRESULT @PROG_NAME@Client::OnInitMenu( SHORT sMenuID, HWND hwnd )
{
    return KWindow::OnInitMenu( sMenuID, hwnd );
}

MRESULT @PROG_NAME@Client::OnJournalNotify( ULONG ulCommand,
                                            USHORT fsQueueStatus,
                                            USHORT usParam )
{
    return KWindow::OnJournalNotify( ulCommand, fsQueueStatus, usParam );
}

MRESULT @PROG_NAME@Client::OnMatchMnemonic( USHORT usMatch )
{
    return KWindow::OnMatchMnemonic( usMatch );
}

MRESULT @PROG_NAME@Client::OnMeasureItem( SHORT sID, ULONG ulControlSpec )
{
    return KWindow::OnMeasureItem( sID, ulControlSpec );
}

MRESULT @PROG_NAME@Client::OnMenuEnd( USHORT usID, HWND hwnd )
{
    return KWindow::OnMenuEnd( usID, hwnd );
}

MRESULT @PROG_NAME@Client::OnMenuSelect( USHORT usItem, bool fPost,
                                         HWND hwnd )
{
    return KWindow::OnMenuSelect( usItem, fPost, hwnd );
}

MRESULT @PROG_NAME@Client::OnMinMaxFrame( PSWP pswp )
{
    return KWindow::OnMinMaxFrame( pswp );
}

MRESULT @PROG_NAME@Client::OnMouseMap( ULONG ulPhysButton,
                                       ULONG ulMappedButton )
{
    return KWindow::OnMouseMap( ulPhysButton, ulMappedButton );
}

MRESULT @PROG_NAME@Client::OnMouseMove( SHORT sxMouse, SHORT syMouse,
                                        USHORT uswHitTest, USHORT fsFlags )
{
    return KWindow::OnMouseMove( sxMouse, syMouse, uswHitTest, fsFlags );
}

MRESULT @PROG_NAME@Client::OnMove()
{
    return KWindow::OnMove();
}

MRESULT @PROG_NAME@Client::OnMsgBoxDismiss( HWND hwnd, ULONG ulButtonID )
{
    return KWindow::OnMsgBoxDismiss( hwnd, ulButtonID );
}

MRESULT @PROG_NAME@Client::OnMsgBoxInit( HWND hwnd, LONG idWindow )
{
    return KWindow::OnMsgBoxInit( hwnd, idWindow );
}

MRESULT @PROG_NAME@Client::OnNextMenu( HWND hwndMenu, USHORT usPrev )
{
    return KWindow::OnNextMenu( hwndMenu, usPrev );
}

MRESULT @PROG_NAME@Client::OnNull()
{
    return KWindow::OnNull();
}

MRESULT @PROG_NAME@Client::OnOpen( bool fPointer, POINTS pts )
{
    return KWindow::OnOpen( fPointer, pts );
}

MRESULT @PROG_NAME@Client::OnPActivate( bool fActive, HWND hwnd )
{
    return KWindow::OnPActivate( fActive, hwnd );
}

MRESULT @PROG_NAME@Client::OnPaint()
{
    KWindowPS kwps;
    RECTL     rcl;

    kwps.BeginPaint( this, 0, &rcl );

    kwps.FillRect( &rcl, SYSCLR_WINDOW );

    QueryWindowRect( &rcl );

    kwps.DrawText( -1, "This is @PROG_NAME@ program !!!", &rcl,
                   SYSCLR_WINDOWTEXT, SYSCLR_WINDOW,
                   DT_CENTER | DT_VCENTER );

    kwps.EndPaint();

    return 0;
}

MRESULT @PROG_NAME@Client::OnPControl( USHORT id, USHORT usNotify,
                                       ULONG ulZero )
{
    return KWindow::OnPControl( id, usNotify, ulZero );
}

MRESULT @PROG_NAME@Client::OnPPaint()
{
    return KWindow::OnPPaint();
}

MRESULT @PROG_NAME@Client::OnPresParamChanged( ULONG idAttrType )
{
    return KWindow::OnPresParamChanged( idAttrType );
}

MRESULT @PROG_NAME@Client::OnPSetFocus( HWND hwnd, bool fFocus )
{
    return KWindow::OnPSetFocus( hwnd, fFocus );
}

MRESULT @PROG_NAME@Client::OnPSize( SHORT scxOld, SHORT scyOld,
                                    SHORT scxNew, SHORT scyNew )
{
    return KWindow::OnPSize( scxOld, scyOld, scxNew, scyNew );
}

MRESULT @PROG_NAME@Client::OnPSysColorChange( ULONG ulOptions )
{
    return KWindow::OnPSysColorChange( ulOptions );
}

MRESULT @PROG_NAME@Client::OnQueryAccelTable()
{
    return KWindow::OnQueryAccelTable();
}

MRESULT @PROG_NAME@Client::OnQueryConvertPos( PRECTL pCursorPos )
{
    return KWindow::OnQueryConvertPos( pCursorPos );
}

MRESULT @PROG_NAME@Client::OnQueryCtlType()
{
    return KWindow::OnQueryCtlType();
}

MRESULT @PROG_NAME@Client::OnQueryDlgCode( PQMSG pQmsg )
{
    return KWindow::OnQueryDlgCode( pQmsg );
}

MRESULT @PROG_NAME@Client::OnQueryHelpInfo()
{
    return KWindow::OnQueryHelpInfo();
}

MRESULT @PROG_NAME@Client::OnQueryTrackInfo( USHORT usTFlags, PTRACKINFO pti )
{
    return KWindow::OnQueryTrackInfo( usTFlags, pti );
}

MRESULT @PROG_NAME@Client::OnQueryWindowParams( PWNDPARAMS pwp )
{
    return KWindow::OnQueryWindowParams( pwp );
}

MRESULT @PROG_NAME@Client::OnQuit()
{
    return KWindow::OnQuit();
}

MRESULT @PROG_NAME@Client::OnRealizePalette()
{
    return KWindow::OnRealizePalette();
}

MRESULT @PROG_NAME@Client::OnSaveApplication()
{
    return KWindow::OnSaveApplication();
}

MRESULT @PROG_NAME@Client::OnSem1( ULONG flAccumBits )
{
    return KWindow::OnSem1( flAccumBits );
}

MRESULT @PROG_NAME@Client::OnSem2( ULONG flAccumBits )
{
    return KWindow::OnSem2( flAccumBits );
}

MRESULT @PROG_NAME@Client::OnSem3( ULONG flAccumBits )
{
    return KWindow::OnSem3( flAccumBits );
}

MRESULT @PROG_NAME@Client::OnSem4( ULONG flAccumBits )
{
    return KWindow::OnSem4( flAccumBits );
}

MRESULT @PROG_NAME@Client::OnSetAccelTable( HACCEL haccelNew )
{
    return KWindow::OnSetAccelTable( haccelNew );
}

MRESULT @PROG_NAME@Client::OnSetFocus( HWND hwnd, bool fFocus )
{
    return KWindow::OnSetFocus( hwnd, fFocus );
}

MRESULT @PROG_NAME@Client::OnSetHelpInfo( LONG lHelpInfo )
{
    return KWindow::OnSetHelpInfo( lHelpInfo );
}

MRESULT @PROG_NAME@Client::OnSetSelection( bool fSel )
{
    return KWindow::OnSetSelection( fSel );
}

MRESULT @PROG_NAME@Client::OnSetWindowParams( PWNDPARAMS pwp )
{
    return KWindow::OnSetWindowParams( pwp );
}

MRESULT @PROG_NAME@Client::OnShow( bool fShow )
{
    return KWindow::OnShow( fShow );
}

MRESULT @PROG_NAME@Client::OnSingleSelect( POINTS pts, bool fPointer )
{
    return KWindow::OnSingleSelect( pts, fPointer );
}

MRESULT @PROG_NAME@Client::OnSize( SHORT scxOld, SHORT scyOld,
                                   SHORT scxNew, SHORT scyNew )
{
    return KWindow::OnSize( scxOld, scyOld, scxNew, scyNew );
}

MRESULT @PROG_NAME@Client::OnSubstituteString( USHORT usIndex )
{
    return KWindow::OnSubstituteString( usIndex );
}

MRESULT @PROG_NAME@Client::OnSysColorChange( ULONG flOptions )
{
    return KWindow::OnSysColorChange( flOptions );
}

MRESULT @PROG_NAME@Client::OnSysCommand( USHORT usCmd, USHORT usSource,
                                         bool fPointer )
{
    return KWindow::OnSysCommand( usCmd, usSource, fPointer );
}

MRESULT @PROG_NAME@Client::SysCmdSrcPushButton( USHORT usCmd, bool fPointer )
{
    return KWindow::SysCmdSrcPushButton( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::SysCmdSrcMenu( USHORT usCmd, bool fPointer )
{
    return KWindow::SysCmdSrcMenu( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::SysCmdSrcAccelerator( USHORT usCmd, bool fPointer )
{
    return KWindow::SysCmdSrcAccelerator( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::SysCmdSrcFontDlg( USHORT usCmd, bool fPointer )
{
    return KWindow::SysCmdSrcFontDlg( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::SysCmdSrcFileDlg( USHORT usCmd, bool fPointer )
{
    return KWindow::SysCmdSrcFileDlg( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::SysCmdSrcOther( USHORT usCmd, bool fPointer )
{
    return KWindow::SysCmdSrcOther( usCmd, fPointer );
}

MRESULT @PROG_NAME@Client::SysCmdSrcUser( USHORT usCmd, USHORT usSource,
                                          bool fPointer )
{
    return KWindow::SysCmdSrcUser( usCmd, usSource, fPointer );
}

MRESULT @PROG_NAME@Client::OnSysValueChanged( USHORT usChangedFirst,
                                              USHORT usChangedLast )
{
    return KWindow::OnSysValueChanged( usChangedFirst, usChangedLast );
}

MRESULT @PROG_NAME@Client::OnTextEdit( bool fPointer, POINTS pts )
{
    return KWindow::OnTextEdit( fPointer, pts );
}

MRESULT @PROG_NAME@Client::OnTimer( USHORT idTimer )
{
    return KWindow::OnTimer( idTimer );
}

MRESULT @PROG_NAME@Client::OnTrackFrame( USHORT fsTrackFlags )
{
    return KWindow::OnTrackFrame( fsTrackFlags );
}

MRESULT @PROG_NAME@Client::OnTranslateAccel( PQMSG pqmsg )
{
    return KWindow::OnTranslateAccel( pqmsg );
}

#if 0
MRESULT @PROG_NAME@Client::OnTranslateMnemonic( PQMSG pqmsg )
{
    return KWindow::OnTranslateMnemonic( pqmsg );
}
#endif

MRESULT @PROG_NAME@Client::OnUpdateFrame( ULONG flCreateFlags )
{
    return KWindow::OnUpdateFrame( flCreateFlags );
}

MRESULT @PROG_NAME@Client::OnVRNDisabled( PVOID mp1, PVOID mp2 )
{
    return KWindow::OnVRNDisabled( mp1, mp2 );
}

MRESULT @PROG_NAME@Client::OnVRNEnabled( bool fVisRgnChanged, PVOID mp2 )
{
    return KWindow::OnVRNEnabled( fVisRgnChanged, mp2 );
}

MRESULT @PROG_NAME@Client::OnVScroll( USHORT id, SHORT sSlider, USHORT usCmd )
{
    return KWindow::OnVScroll( id, sSlider, usCmd );
}

MRESULT @PROG_NAME@Client::VSbLineUp( USHORT id, SHORT sSlider )
{
    return KWindow::VSbLineUp( id, sSlider );
}

MRESULT @PROG_NAME@Client::VSbLineDown( USHORT id, SHORT sSlider )
{
    return KWindow::VSbLineDown( id, sSlider );
}

MRESULT @PROG_NAME@Client::VSbPageUp( USHORT id, SHORT sSlider )
{
    return KWindow::VSbPageUp( id, sSlider );
}

MRESULT @PROG_NAME@Client::VSbPageDown( USHORT id, SHORT sSlider )
{
    return KWindow::VSbPageDown( id, sSlider );
}

MRESULT @PROG_NAME@Client::VSbSliderPosition( USHORT id, SHORT sSlider )
{
    return KWindow::VSbSliderPosition( id, sSlider );
}

MRESULT @PROG_NAME@Client::VSbSliderTrack( USHORT id, SHORT sSlider )
{
    return KWindow::VSbSliderTrack( id, sSlider );
}

MRESULT @PROG_NAME@Client::VSbEndScroll( USHORT id, SHORT sSlider )
{
    return KWindow::VSbEndScroll( id, sSlider );
}

MRESULT @PROG_NAME@Client::OnWindowPosChanged( PSWP pswp, ULONG flAwp )
{
    return KWindow::OnWindowPosChanged( pswp, flAwp );
}

