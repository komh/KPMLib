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

#ifndef KWINDOW_H
#define KWINDOW_H

#define INCL_WIN
#include <os2.h>

#include <map>
#include <string>

#define STR2PSZ( s )   ( reinterpret_cast< PSZ >( s ))
#define CSTR2PSZ( s )  ( reinterpret_cast< PSZ >( const_cast< char* >( s )))
#define PSZ2STR( s )   ( reinterpret_cast< char* >( s ))
#define PCSZ2STR( s)   ( reinterpret_cast< char* >( const_cast< PSZ >( s )))

#define KWND_DESKTOP ( reinterpret_cast< KWindow* >( HWND_DESKTOP ))
#define KWND_OBJECT  ( reinterpret_cast< KWindow* >( HWND_OBJECT ))
#define KWND_TOP     ( reinterpret_cast< KWindow* >( HWND_TOP ))
#define KWND_BOTTOM  ( reinterpret_cast< KWindow* >( HWND_BOTTOM ))

class KWindow
{
public :
    KWindow();
    virtual ~KWindow();

    virtual bool CreateWindow( const KWindow* pkwndP, 
                               const std::string& strName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    virtual bool DestroyPointer( HPOINTER hptr ) const
    {
        return WinDestroyPointer( hptr );
    }

    virtual bool DestroyWindow();

    virtual HPOINTER LoadPointer( HMODULE hmodResource,
                                  ULONG idPointer ) const
    {
        return WinLoadPointer( HWND_DESKTOP, hmodResource, idPointer );
    }

    virtual bool MapWindowPoints( const KWindow* pkwndTo, PPOINTL prgptl,
                                  LONG cwpt ) const
    {
        return  WinMapWindowPoints( _hwnd,
                                    pkwnd2hwnd( pkwndTo ), prgptl, cwpt );
    }

    virtual ULONG MessageBox( const std::string& strText, 
                              const std::string& strCaption,
                              ULONG flStyle ) const
    {
        return WinMessageBox( HWND_DESKTOP, _hwnd,
                              strText.c_str(), strCaption.c_str(),
                              0xFFFF, flStyle );
    }

    virtual ULONG MessageBox( const std::string& strText, 
                              const std::string& strCaption,
                              ULONG id, ULONG flStyle ) const
    {
        return WinMessageBox( HWND_DESKTOP, _hwnd,
                              strText.c_str(), strCaption.c_str(),
                              id, flStyle );
    }

    virtual bool PostMsg( ULONG ulMsg, MPARAM mp1 = 0, MPARAM mp2 = 0 ) const
    {
        return WinPostMsg( _hwnd, ulMsg, mp1, mp2 );
    }

    virtual HAB QueryAnchorBlock() const
    {
        return WinQueryAnchorBlock( _hwnd );
    }

    virtual bool QueryPointerPos( PPOINTL pptlPoint ) const
    {
        return WinQueryPointerPos( HWND_DESKTOP, pptlPoint );
    }

    virtual ULONG QueryTaskSizePos( PSWP pswp ) const
    {
        return WinQueryTaskSizePos( QueryAnchorBlock(), 0, pswp );
    }

    virtual HPOINTER QuerySysPointer( LONG lID, bool fCopy ) const
    {
        return WinQuerySysPointer( HWND_DESKTOP, lID, fCopy );
    }

    virtual LONG QuerySysValue( LONG iSysValue ) const
    {
        return WinQuerySysValue( HWND_DESKTOP, iSysValue );
    }

    virtual bool QueryWindow( LONG lCode, KWindow& kwndRelated ) const;

    virtual bool QueryWindowPos( PSWP pswp ) const
    {
        return WinQueryWindowPos( _hwnd, pswp );
    }

    virtual PVOID QueryWindowPtr( LONG index ) const
    {
        return WinQueryWindowPtr( _hwnd, index );
    }

    virtual bool QueryWindowRect( PRECTL prcl ) const
    {
        return WinQueryWindowRect( _hwnd, prcl );
    }

    virtual LONG QueryWindowText( std::string& strBuffer ) const
    {
        LONG lLength   = QueryWindowTextLength() + 1;
        PCH  pchBuffer = new CHAR[ lLength ];
        LONG rc;

        rc = WinQueryWindowText( _hwnd, lLength, pchBuffer );

        strBuffer = pchBuffer;

        delete[] pchBuffer;

        return rc;
    }

    virtual LONG QueryWindowTextLength() const
    {
        return WinQueryWindowTextLength( _hwnd );
    }

    virtual ULONG QueryWindowULong( LONG index ) const
    {
        return WinQueryWindowULong( _hwnd, index );
    }

    virtual USHORT QueryWindowUShort( LONG index ) const
    {
        return WinQueryWindowUShort( _hwnd, index );
    }

    virtual bool RegisterClass( HAB hab, const std::string& strClassName,
                                ULONG flStyle, ULONG cbWindowData );

    virtual bool RestoreWindowPos( const std::string& strAppName,
                                   const std::string& strKeyName ) const
    {
        return WinRestoreWindowPos( strAppName.c_str(), strKeyName.c_str(),
                                    _hwnd );
    }

    virtual MRESULT SendMsg( ULONG ulMsg,
                             MPARAM mp1 = 0, MPARAM mp2 = 0 ) const
    {
        return WinSendMsg( _hwnd, ulMsg, mp1, mp2 );
    }

    virtual bool SetActiveWindow() const
    {
        return WinSetActiveWindow( HWND_DESKTOP, _hwnd );
    }

    virtual bool SetFocus( bool fSet = true ) const
    {
        return WinSetFocus( HWND_DESKTOP, fSet ? _hwnd  : HWND_DESKTOP );
    }

    virtual bool SetWindowPos( const KWindow* pkwndRel, LONG x, LONG y,
                               LONG cx, LONG cy, ULONG fl ) const
    {
        return WinSetWindowPos( _hwnd, pkwnd2hwnd( pkwndRel ),
                                x, y, cx, cy, fl );
    }

    virtual bool SetWindowPtr( LONG lb, PVOID p ) const
    {
        return WinSetWindowPtr( _hwnd, lb, p );
    }

    virtual bool SetWindowText( const std::string& strString ) const
    {
        return WinSetWindowText( _hwnd, strString.c_str());
    }

    virtual bool SetWindowUShort( LONG index, USHORT us ) const
    {
        return WinSetWindowUShort( _hwnd, index, us );
    }

    virtual bool SetWindowULong( LONG index, ULONG ul ) const
    {
        return WinSetWindowULong( _hwnd, index, ul );
    }

    virtual bool ShowWindow( BOOL fNewVisibility ) const
    {
        return WinShowWindow( _hwnd, fNewVisibility );
    }

    virtual bool StoreWindowPos( const std::string& strAppName,
                                 const std::string& strKeyName ) const
    {
        return WinStoreWindowPos( strAppName.c_str(), strKeyName.c_str(),
                                  _hwnd );
    }

    virtual bool WindowFromID( ULONG id, KWindow& kwnd ) const;

    HWND GetHWND() const { return _hwnd; }
    virtual void SetHWND( HWND hwnd );

    const KWindow& GetParent() const { return *_pkwndParent; }
    const KWindow& GetOwner() const { return *_pkwndOwner; }

    const std::string& GetClassName() const { return _strClassName; }
    virtual void SetClassName( PCSZ pcszClassName );
    virtual void SetClassName( const std::string& strClassName )
    {
        _strClassName = strClassName;
    }

    virtual bool MoveToCenter( bool horz = true, bool vert = true ) const;

    virtual bool Resize( LONG cx, LONG cy ) const
    {
        return SetWindowPos( 0, 0, 0, cx, cy, SWP_SIZE );
    }

    virtual bool Move( LONG x, LONG y ) const
    {
        return SetWindowPos( 0, x, y, 0, 0, SWP_MOVE );
    }

    virtual bool Place( const KWindow* pkwnd ) const
    {
        return SetWindowPos( pkwnd, 0, 0, 0, 0, SWP_ZORDER );
    }

    virtual bool Maximize() const
    {
        return SetWindowPos( 0, 0, 0, 0, 0, SWP_MAXIMIZE );
    }

    virtual bool Minimize() const
    {
        return SetWindowPos( 0, 0, 0, 0, 0, SWP_MINIMIZE );
    }

    virtual bool Restore() const
    {
        return SetWindowPos( 0, 0, 0, 0, 0, SWP_RESTORE );
    }

protected :
    friend HWND pkwnd2hwnd( const KWindow* pkwnd );

    virtual MRESULT KDefWndProc( ULONG msg, MPARAM mp1 = 0, MPARAM mp2 = 0 )
    {
        return _pfnwpOldProc ? _pfnwpOldProc( _hwnd, msg, mp1, mp2 ) :
                               WinDefWindowProc( _hwnd, msg, mp1, mp2 );
    }

    virtual MRESULT KWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 );

    virtual MRESULT OnPlAltered( HINI hiniUser, HINI hiniSystem )
    {
        return KDefWndProc( PL_ALTERED, MPFROMLONG( hiniUser ),
                            MPFROMLONG( hiniSystem ));
    }

    virtual MRESULT OnActivate( USHORT usActive, HWND hwnd )
    {
        return KDefWndProc( WM_ACTIVATE, MPFROMSHORT( usActive ),
                            MPFROMHWND( hwnd ));
    }

    virtual MRESULT OnAppTerminateNotify( HAPP happ, ULONG flRetCode )
    {
        return KDefWndProc( WM_APPTERMINATENOTIFY, MPFROMLONG( happ ),
                            MPFROMLONG( flRetCode ));
    }

    virtual MRESULT OnAdjustWindowPos( PSWP pswp, ULONG flZero )
    {
        return KDefWndProc( WM_ADJUSTWINDOWPOS, MPFROMP( pswp ),
                            MPFROMLONG( flZero ));
    }

    virtual MRESULT OnBeginDrag( POINTS pts, bool fPointer )
    {
        return KDefWndProc( WM_BEGINDRAG,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROMLONG( fPointer ));
    }

    virtual MRESULT OnBeginSelect( POINTS pts, bool fPointer )
    {
        return KDefWndProc( WM_BEGINSELECT,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROMLONG( fPointer ));
    }

    virtual MRESULT OnButton1Click( POINTS pts, USHORT fHit, USHORT fsFlags )
    {
        return KDefWndProc( WM_BUTTON1CLICK,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROM2SHORT( fHit, fsFlags ));
    }

    virtual MRESULT OnButton1DblClk( POINTS pts, USHORT fHit, USHORT fsFlags )
    {
        return KDefWndProc( WM_BUTTON1DBLCLK,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROM2SHORT( fHit, fsFlags ));
    }

    virtual MRESULT OnButton1Down( POINTS pts, USHORT fHit, USHORT fsFlags )
    {
        return KDefWndProc( WM_BUTTON1DOWN,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROM2SHORT( fHit, fsFlags ));
    }

    virtual MRESULT OnButton1MotionEnd( POINTS pts, USHORT fsHit )
    {
        return KDefWndProc( WM_BUTTON1MOTIONEND,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROMSHORT( fsHit ));
    }

    virtual MRESULT OnButton1MotionStart( POINTS pts, USHORT fsHit )
    {
        return KDefWndProc( WM_BUTTON1MOTIONSTART,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROMSHORT( fsHit ));
    }

    virtual MRESULT OnButton1Up( POINTS pts, USHORT fHit, USHORT fsFlags )
    {
        return KDefWndProc( WM_BUTTON1UP,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROM2SHORT( fHit, fsFlags ));
    }

    virtual MRESULT OnButton2Click( POINTS pts, USHORT fHit, USHORT fsFlags )
    {
        return KDefWndProc( WM_BUTTON2CLICK,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROM2SHORT( fHit, fsFlags ));
    }

    virtual MRESULT OnButton2DblClk( POINTS pts, USHORT fHit, USHORT fsFlags )
    {
        return KDefWndProc( WM_BUTTON2DBLCLK,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROM2SHORT( fHit, fsFlags ));
    }

    virtual MRESULT OnButton2Down( POINTS pts, USHORT fHit, USHORT fsFlags )
    {
        return KDefWndProc( WM_BUTTON2DOWN,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROM2SHORT( fHit, fsFlags ));
    }

    virtual MRESULT OnButton2MotionEnd( POINTS pts, USHORT fsHit )
    {
        return KDefWndProc( WM_BUTTON2MOTIONEND,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROMSHORT( fsHit ));
    }

    virtual MRESULT OnButton2MotionStart( POINTS pts, USHORT fsHit )
    {
        return KDefWndProc( WM_BUTTON2MOTIONSTART,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROMSHORT( fsHit ));
    }

    virtual MRESULT OnButton2Up( POINTS pts, USHORT fHit, USHORT fsFlags )
    {
        return KDefWndProc( WM_BUTTON2UP,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROM2SHORT( fHit, fsFlags ));
    }

    virtual MRESULT OnButton3Click( POINTS pts, USHORT fHit, USHORT fsFlags )
    {
        return KDefWndProc( WM_BUTTON3CLICK,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROM2SHORT( fHit, fsFlags ));
    }

    virtual MRESULT OnButton3DblClk( POINTS pts, USHORT fHit, USHORT fsFlags )
    {
        return KDefWndProc( WM_BUTTON3DBLCLK,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROM2SHORT( fHit, fsFlags ));
    }

    virtual MRESULT OnButton3Down( POINTS pts, USHORT fHit, USHORT fsFlags )
    {
        return KDefWndProc( WM_BUTTON3DOWN,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROM2SHORT( fHit, fsFlags ));
    }

    virtual MRESULT OnButton3MotionEnd( POINTS pts, USHORT fsHit )
    {
        return KDefWndProc( WM_BUTTON3MOTIONEND,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROMSHORT( fsHit ));
    }

    virtual MRESULT OnButton3MotionStart( POINTS pts, USHORT fsHit )
    {
        return KDefWndProc( WM_BUTTON3MOTIONSTART,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROMSHORT( fsHit ));
    }

    virtual MRESULT OnButton3Up( POINTS pts, USHORT fHit, USHORT fsFlags )
    {
        return KDefWndProc( WM_BUTTON3UP,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROM2SHORT( fHit, fsFlags ));
    }

    virtual MRESULT OnCalcFrameRect( PRECTL prcl, bool fFrame )
    {
        return KDefWndProc( WM_CALCFRAMERECT, MPFROMP( prcl ),
                            MPFROMLONG( fFrame ));
    }

    virtual MRESULT OnCalcValidRects( PRECTL prcl, PSWP pswp )
    {
        return KDefWndProc( WM_CALCVALIDRECTS, MPFROMP( prcl ),
                            MPFROMP( pswp ));
    }

    virtual MRESULT OnChar( USHORT fsFlags, UCHAR ucRepeat, UCHAR ucScanCode,
                            USHORT usCh, USHORT usVk )
    {
        return KDefWndProc( WM_CHAR,
                            MPFROMSH2CH( fsFlags, ucRepeat, ucScanCode ),
                            MPFROM2SHORT( usCh, usVk ));
    }

    virtual MRESULT OnChord( USHORT fsHit )
    {
        return KDefWndProc( WM_CHORD, 0, MPFROMSHORT( fsHit ));
    }

    virtual MRESULT OnClose() { return KDefWndProc( WM_CLOSE ); }
    virtual MRESULT OnCommand( USHORT usCmd, USHORT ulSource,
                               bool fPointer );

    virtual MRESULT CmdSrcPushButton( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_PUSHBUTTON, fPointer ));
    }

    virtual MRESULT CmdSrcMenu( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_MENU, fPointer ));
    }

    virtual MRESULT CmdSrcAccelerator( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_ACCELERATOR, fPointer ));
    }

    virtual MRESULT CmdSrcFontDlg( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_FONTDLG, fPointer ));
    }

    virtual MRESULT CmdSrcFileDlg( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_FILEDLG, fPointer ));
    }

    virtual MRESULT CmdSrcOther( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_OTHER, fPointer ));
    }

    virtual MRESULT CmdSrcUser( USHORT usCmd, USHORT usSource, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( usSource, fPointer ));
    }

    virtual MRESULT OnContextMenu( POINTS pts, bool fPointer )
    {
        return KDefWndProc( WM_CONTEXTMENU,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROM2SHORT( 0, fPointer ));
    }

    virtual MRESULT OnControl( USHORT id, USHORT usNotifyCode,
                               ULONG ulControlSpec )
    { return KDefWndProc( WM_CONTROL, MPFROM2SHORT( id, usNotifyCode ),
                          MPFROMLONG( ulControlSpec )); }

    virtual MRESULT OnControlPointer( USHORT id, HPOINTER hptrNew )
    {
        return KDefWndProc( WM_CONTROLPOINTER, MPFROMSHORT( id ),
                            MPFROMLONG( hptrNew ));
    }

    virtual MRESULT OnCreate( PVOID pCtrlData, PCREATESTRUCT pcs )
    {
        return KDefWndProc( WM_CREATE, MPFROMP( pCtrlData ), MPFROMP( pcs ));
    }

    virtual MRESULT OnCtlColorChange()
    {
        return KDefWndProc( WM_CTLCOLORCHANGE );
    }

    virtual MRESULT OnDestroy() { return KDefWndProc( WM_DESTROY ); }

    virtual MRESULT OnDrawItem( USHORT id, ULONG ulControlSpec )
    {
        return KDefWndProc( WM_DRAWITEM, MPFROMSHORT( id ),
                            MPFROMLONG( ulControlSpec ));
    }

    virtual MRESULT OnEnable( bool fNewEnabledState )
    {
        return KDefWndProc( WM_ENABLE, MPFROMLONG( fNewEnabledState ));
    }

    virtual MRESULT OnEndDrag( POINTS pts, bool fPointer )
    {
        return KDefWndProc( WM_ENDDRAG, *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROMLONG( fPointer ));
    }

    virtual MRESULT OnEndSelect( POINTS pts, bool fPointer )
    {
        return KDefWndProc( WM_ENDSELECT, *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROMLONG( fPointer ));
    }

    virtual MRESULT OnError( USHORT usErrorCode )
    {
        return KDefWndProc( WM_ERROR, MPFROMSHORT( usErrorCode ));
    }

    virtual MRESULT OnFocusChange( HWND hwndFocus, bool fSetFocus,
                                   USHORT fsFocusChange )
    {
        return KDefWndProc( WM_FOCUSCHANGE, MPFROMHWND( hwndFocus ),
                            MPFROM2SHORT( fSetFocus, fsFocusChange ));
    }

    virtual MRESULT OnFormatFrame( PSWP pswp, PRECTL prcl )
    {
        return KDefWndProc( WM_FORMATFRAME, MPFROMP( pswp ), MPFROMP( prcl ));
    }

    virtual MRESULT OnHelp( USHORT usCmd, USHORT usSource, bool fPointer );

    virtual MRESULT HelpCmdSrcPushButton( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_PUSHBUTTON, fPointer ));
    }

    virtual MRESULT HelpCmdSrcMenu( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_PUSHBUTTON, fPointer ));
    }

    virtual MRESULT HelpCmdSrcAccelerator( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_ACCELERATOR, fPointer ));
    }

    virtual MRESULT HelpCmdSrcFontDlg( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_FONTDLG, fPointer ));
    }

    virtual MRESULT HelpCmdSrcFileDlg( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_FILEDLG, fPointer ));
    }

    virtual MRESULT HelpCmdSrcOther( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_OTHER, fPointer ));
    }

    virtual MRESULT HelpCmdSrcUser( USHORT usCmd, USHORT usSource,
                                    bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( usSource, fPointer ));
    }

    virtual MRESULT OnHitTest( POINTS pts )
    {
        return KDefWndProc( WM_HITTEST, *reinterpret_cast< MPARAM* >( &pts ));
    }

    virtual MRESULT OnHScroll( USHORT id, SHORT sSlider, USHORT usCmd );

    virtual MRESULT HSbLineLeft( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_LINELEFT ));
    }

    virtual MRESULT HSbLineRight( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_LINERIGHT ));
    }

    virtual MRESULT HSbPageLeft( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_PAGELEFT ));
    }

    virtual MRESULT HSbPageRight( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_PAGERIGHT ));
    }

    virtual MRESULT HSbSliderPosition( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_SLIDERPOSITION ));
    }

    virtual MRESULT HSbSliderTrack( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_SLIDERTRACK ));
    }

    virtual MRESULT HSbEndScroll( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_ENDSCROLL ));
    }

    virtual MRESULT OnInitDlg( HWND hwndFocus, PVOID pCreate )
    {
        return KDefWndProc( WM_INITDLG, MPFROMHWND( hwndFocus ),
                            MPFROMP( pCreate ));
    }

    virtual MRESULT OnInitMenu( SHORT sMenuID, HWND hwnd )
    {
        return KDefWndProc( WM_INITMENU, MPFROMSHORT( sMenuID ),
                            MPFROMHWND( hwnd ));
    }

    virtual MRESULT OnJournalNotify( ULONG ulCommand, USHORT fsQueueStatus,
                                     USHORT usParam )
    {
        return KDefWndProc( WM_JOURNALNOTIFY, MPFROMLONG( ulCommand ),
                            MPFROM2SHORT( fsQueueStatus, usParam ));
    }

    virtual MRESULT OnMatchMnemonic( USHORT usMatch )
    {
        return KDefWndProc( WM_MATCHMNEMONIC, MPFROMSHORT( usMatch ));
    }

    virtual MRESULT OnMeasureItem( SHORT sID, ULONG ulControlSpec )
    {
        return KDefWndProc( WM_MEASUREITEM, MPFROMSHORT ( sID ),
                            MPFROMLONG( ulControlSpec ));
    }

    virtual MRESULT OnMenuEnd( USHORT usID, HWND hwnd )
    {
        return KDefWndProc( WM_MENUEND, MPFROMSHORT( usID ),
                            MPFROMHWND( hwnd ));
    }

    virtual MRESULT OnMenuSelect( USHORT usItem, bool fPost, HWND hwnd )
    {
        return KDefWndProc( WM_MENUSELECT, MPFROM2SHORT( usItem, fPost ),
                            MPFROMHWND( hwnd ));
    }

    virtual MRESULT OnMinMaxFrame( PSWP pswp )
    {
        return KDefWndProc( WM_MINMAXFRAME, MPFROMP( pswp ));
    }

    virtual MRESULT OnMouseMap( ULONG ulPhysButton, ULONG ulMappedButton )
    {
        return KDefWndProc( WM_MOUSEMAP, MPFROMLONG( ulPhysButton ),
                            MPFROMLONG( ulMappedButton ));
    }

    virtual MRESULT OnMouseMove( SHORT sxMouse, SHORT syMouse,
                                 USHORT uswHitTest, USHORT fsFlags )
    {
        return KDefWndProc( WM_MOUSEMOVE, MPFROM2SHORT( sxMouse, syMouse ),
                            MPFROM2SHORT( uswHitTest, fsFlags ));
    }

    virtual MRESULT OnMove() { return KDefWndProc( WM_MOVE ); }

    virtual MRESULT OnMsgBoxDismiss( HWND hwnd, ULONG ulButtonID )
    {
        return KDefWndProc( WM_MSGBOXDISMISS, MPFROMHWND( hwnd ),
                            MPFROMLONG( ulButtonID ));
    }

    virtual MRESULT OnMsgBoxInit( HWND hwnd, LONG idWindow )
    {
        return KDefWndProc( WM_MSGBOXINIT, MPFROMHWND( hwnd ),
                            MPFROMLONG( idWindow ));
    }

    virtual MRESULT OnNextMenu( HWND hwndMenu, USHORT usPrev )
    {
        return KDefWndProc( WM_NEXTMENU, MPFROMHWND( hwndMenu ),
                            MPFROMSHORT( usPrev ));
    }

    virtual MRESULT OnNull() { return KDefWndProc( WM_NULL ); }

    virtual MRESULT OnOpen( bool fPointer, POINTS pts )
    {
        return KDefWndProc( WM_OPEN, MPFROMLONG( fPointer ),
                            *reinterpret_cast< MPARAM* >( &pts ));
    }

    virtual MRESULT OnPActivate( bool fActive, HWND hwnd )
    {
        return KDefWndProc( WM_PACTIVATE, MPFROMLONG( fActive ),
                            MPFROMHWND( hwnd ));
    }

    virtual MRESULT OnPaint() { return KDefWndProc( WM_PAINT ); }

    virtual MRESULT OnPControl( USHORT id, USHORT usNotify, ULONG ulZero )
    {
        return KDefWndProc( WM_PCONTROL, MPFROM2SHORT( id, usNotify ),
                            MPFROMLONG( ulZero ));
    }

    virtual MRESULT OnPPaint() { return KDefWndProc( WM_PPAINT ); }

    virtual MRESULT OnPresParamChanged( ULONG idAttrType )
    {
        return KDefWndProc( WM_PRESPARAMCHANGED, MPFROMLONG( idAttrType ));
    }

    virtual MRESULT OnPSetFocus( HWND hwnd, bool fFocus )
    {
        return KDefWndProc( WM_PSETFOCUS, MPFROMHWND( hwnd ),
                            MPFROMLONG( fFocus ));
    }

    virtual MRESULT OnPSize( SHORT scxOld, SHORT scyOld,
                             SHORT scxNew, SHORT scyNew )
    {
        return KDefWndProc( WM_PSIZE, MPFROM2SHORT( scxOld, scyOld ),
                            MPFROM2SHORT( scxNew, scyNew ));
    }

    virtual MRESULT OnPSysColorChange( ULONG ulOptions )
    {
        return KDefWndProc( WM_PSYSCOLORCHANGE, MPFROMLONG( ulOptions ));
    }

    virtual MRESULT OnQueryAccelTable()
    {
        return KDefWndProc( WM_QUERYACCELTABLE );
    }

    virtual MRESULT OnQueryConvertPos( PRECTL pCursorPos )
    {
        return KDefWndProc( WM_QUERYCONVERTPOS, MPFROMP( pCursorPos ));
    }

    virtual MRESULT OnQueryCtlType() { return KDefWndProc( WM_QUERYCTLTYPE ); }

    virtual MRESULT OnQueryDlgCode( PQMSG pQmsg )
    {
        return KDefWndProc( WM_QUERYDLGCODE, MPFROMP( pQmsg ));
    }

    virtual MRESULT OnQueryHelpInfo()
    {
        return KDefWndProc( WM_QUERYHELPINFO );
    }

    virtual MRESULT OnQueryTrackInfo( USHORT usTFlags, PTRACKINFO pti )
    {
        return KDefWndProc( WM_QUERYTRACKINFO, MPFROMSHORT( usTFlags ),
                            MPFROMP( pti ));
    }

    virtual MRESULT OnQueryWindowParams( PWNDPARAMS pwp )
    {
        return KDefWndProc( WM_QUERYWINDOWPARAMS, MPFROMP( pwp ));
    }

    virtual MRESULT OnQuit() { return KDefWndProc( WM_QUIT ); }

    virtual MRESULT OnRealizePalette()
    {
        return KDefWndProc( WM_REALIZEPALETTE );
    }

    virtual MRESULT OnSaveApplication()
    {
        return KDefWndProc( WM_SAVEAPPLICATION );
    }

    virtual MRESULT OnSem1( ULONG flAccumBits )
    {
        return KDefWndProc( WM_SEM1, MPFROMLONG( flAccumBits ));
    }

    virtual MRESULT OnSem2( ULONG flAccumBits )
    {
        return KDefWndProc( WM_SEM2, MPFROMLONG( flAccumBits ));
    }

    virtual MRESULT OnSem3( ULONG flAccumBits )
    {
        return KDefWndProc( WM_SEM3, MPFROMLONG( flAccumBits ));
    }

    virtual MRESULT OnSem4( ULONG flAccumBits )
    {
        return KDefWndProc( WM_SEM4, MPFROMLONG( flAccumBits ));
    }

    virtual MRESULT OnSetAccelTable( HACCEL haccelNew )
    {
        return KDefWndProc( WM_SETACCELTABLE, MPFROMLONG( haccelNew ));
    }

    virtual MRESULT OnSetFocus( HWND hwnd, bool fFocus )
    {
        return KDefWndProc( WM_SETFOCUS, MPFROMHWND( hwnd ),
                            MPFROMLONG( fFocus ));
    }

    virtual MRESULT OnSetHelpInfo( LONG lHelpInfo )
    {
        return KDefWndProc( WM_SETHELPINFO, MPFROMLONG( lHelpInfo ));
    }

    virtual MRESULT OnSetSelection( bool fSel )
    {
        return KDefWndProc( WM_SETSELECTION, MPFROMLONG( fSel ));
    }

    virtual MRESULT OnSetWindowParams( PWNDPARAMS pwp )
    {
        return KDefWndProc( WM_SETWINDOWPARAMS, MPFROMP( pwp ));
    }

    virtual MRESULT OnShow( bool fShow )
    {
        return KDefWndProc( WM_SHOW, MPFROMLONG( fShow ));
    }

    virtual MRESULT OnSingleSelect( POINTS pts, bool fPointer )
    {
        return KDefWndProc( WM_SINGLESELECT,
                            *reinterpret_cast< MPARAM* >( &pts ),
                            MPFROMLONG( fPointer ));
    }

    virtual MRESULT OnSize( SHORT scxOld, SHORT scyOld,
                            SHORT scxNew, SHORT scyNew )
    {
        return KDefWndProc( WM_SIZE, MPFROM2SHORT( scxOld, scyOld ),
                            MPFROM2SHORT( scxNew, scyNew ));
    }

    virtual MRESULT OnSubstituteString( USHORT usIndex )
    {
        return KDefWndProc( WM_SUBSTITUTESTRING, MPFROMSHORT( usIndex ));
    }

    virtual MRESULT OnSysColorChange( ULONG flOptions )
    {
        return KDefWndProc( WM_SYSCOLORCHANGE, MPFROMLONG( flOptions ));
    }

    virtual MRESULT OnSysCommand( USHORT usCmd, USHORT usSource,
                                  bool fPointer );
    virtual MRESULT SysCmdSrcPushButton( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_PUSHBUTTON, fPointer ));

    }

    virtual MRESULT SysCmdSrcMenu( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_MENU, fPointer ));

    }

    virtual MRESULT SysCmdSrcAccelerator( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_ACCELERATOR, fPointer ));

    }

    virtual MRESULT SysCmdSrcFontDlg( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_FONTDLG, fPointer ));

    }

    virtual MRESULT SysCmdSrcFileDlg( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_FILEDLG, fPointer ));

    }

    virtual MRESULT SysCmdSrcOther( USHORT usCmd, bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( CMDSRC_OTHER, fPointer ));

    }

    virtual MRESULT SysCmdSrcUser( USHORT usCmd, USHORT usSource,
                                   bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMSHORT( usCmd ),
                            MPFROM2SHORT( usSource, fPointer ));

    }

    virtual MRESULT OnSysValueChanged( USHORT usChangedFirst,
                                       USHORT usChangedLast )
    {
        return KDefWndProc( WM_SYSVALUECHANGED, MPFROMSHORT( usChangedFirst ),
                            MPFROMSHORT( usChangedLast ));
    }

    virtual MRESULT OnTextEdit( bool fPointer, POINTS pts )
    {
        return KDefWndProc( WM_TEXTEDIT, MPFROMLONG( fPointer ),
                            *reinterpret_cast< MPARAM* >( &pts ));
    }

    virtual MRESULT OnTimer( USHORT idTimer )
    {
        return KDefWndProc( WM_TIMER, MPFROMSHORT( idTimer ));
    }

    virtual MRESULT OnTrackFrame( USHORT fsTrackFlags )
    {
        return KDefWndProc( WM_TRACKFRAME, MPFROMSHORT( fsTrackFlags ));
    }

    virtual MRESULT OnTranslateAccel( PQMSG pqmsg )
    {
        return KDefWndProc( WM_TRANSLATEACCEL, MPFROMP( pqmsg ));
    }

#if 0
    virtual MRESULT OnTranslateMnemonic( PQMSG pqmsg )
    {
        return KDefWndProc( WM_TRANSLATEMNEMONIC, MPFROMP( pqmsg ));
    }
#endif

    virtual MRESULT OnUpdateFrame( ULONG flCreateFlags )
    {
        return KDefWndProc( WM_UPDATEFRAME, MPFROMLONG( flCreateFlags ));
    }

    virtual MRESULT OnVRNDisabled( PVOID mp1, PVOID mp2 )
    {
        return KDefWndProc( WM_VRNDISABLED, MPFROMP( mp1 ), MPFROMP( mp2 ));
    }

    virtual MRESULT OnVRNEnabled( bool fVisRgnChanged, PVOID mp2 )
    {
        return KDefWndProc( WM_VRNENABLED, MPFROMLONG( fVisRgnChanged ),
                            MPFROMP( mp2 ));
    }

    virtual MRESULT OnVScroll( USHORT id, SHORT sSlider, USHORT usCmd );

    virtual MRESULT VSbLineUp( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_LINEUP ));
    }

    virtual MRESULT VSbLineDown( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_LINEDOWN ));
    }

    virtual MRESULT VSbPageUp( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_PAGEUP ));
    }

    virtual MRESULT VSbPageDown( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_PAGEDOWN ));
    }

    virtual MRESULT VSbSliderPosition( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_SLIDERPOSITION ));
    }

    virtual MRESULT VSbSliderTrack( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_SLIDERTRACK ));
    }

    virtual MRESULT VSbEndScroll( USHORT id, SHORT sSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMSHORT( id ),
                            MPFROM2SHORT( sSlider, SB_ENDSCROLL ));
    }

    virtual MRESULT OnWindowPosChanged( PSWP pswp, ULONG flAwp )
    {
        return KDefWndProc( WM_WINDOWPOSCHANGED, MPFROMP( pswp ),
                            MPFROMLONG( flAwp ));
    }

private :
    static std::map< HWND, KWindow* > _mapHWND;

    static void AddHWND( HWND hwnd, KWindow* pkwnd )
    {
        _mapHWND[ hwnd ] = pkwnd;
    }

    static void RemoveHWND( HWND hwnd ) { _mapHWND.erase( hwnd ); }

    static KWindow* FindHWND( HWND hwnd )
    {
        std::map< HWND, KWindow* >::iterator it = _mapHWND.find( hwnd );

        return ( it == _mapHWND.end()) ? 0 : it->second;
    }

    static MRESULT EXPENTRY WndProc( HWND hwnd, ULONG msg, MPARAM mp1,
                                     MPARAM mp2 );

    HWND _hwnd;

    std::string _strClassName;
    PFNWP  _pfnwpOldProc;

    KWindow* _pkwndParent;
    KWindow* _pkwndOwner;
};

inline
ULONG MessageBox( const KWindow* pkwndO, const std::string& strText,
                  const std::string& strCaption, ULONG flStyle )
{
    return WinMessageBox( HWND_DESKTOP, pkwnd2hwnd( pkwndO ),
                          strText.c_str(), strCaption.c_str(),
                          0xFFFF, flStyle );
}

inline
ULONG MessageBox( const KWindow* pkwndO, const std::string& strText,
                  const std::string& strCaption, ULONG id, ULONG flStyle )
{
    return WinMessageBox( HWND_DESKTOP, pkwnd2hwnd( pkwndO ),
                          strText.c_str(), strCaption.c_str(),
                          id, flStyle );
}

inline
bool MapWindowPoints( const KWindow* pkwndFrom, const KWindow* pkwndTo,
                      PPOINTL prgptl, LONG cwpt )
{
    return WinMapWindowPoints( pkwnd2hwnd( pkwndFrom ), pkwnd2hwnd( pkwndTo ),
                               prgptl, cwpt );
}
#endif
