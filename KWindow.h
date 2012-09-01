#ifndef KWINDOW_H
#define KWINDOW_H

#define INCL_WIN
#include <os2.h>

#define PMLITERAL( s ) ( reinterpret_cast < PCSZ >( s ))

#define KWND_DESKTOP ( reinterpret_cast< KWindow* >( HWND_DESKTOP ))
#define KWND_OBJECT  ( reinterpret_cast< KWindow* >( HWND_OBJECT ))
#define KWND_TOP     ( reinterpret_cast< KWindow* >( HWND_TOP ))
#define KWND_BOTTOM  ( reinterpret_cast< KWindow* >( HWND_BOTTOM ))

class KWindow
{
public :
    KWindow();
    virtual ~KWindow();

    virtual bool RegisterClass( HAB hab, PCSZ pcszClassName, ULONG flStyle,
                                ULONG cbWindowData );
    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );
    virtual bool DestroyWindow() { return WinDestroyWindow( _hwnd ); }
    virtual bool SetWindowText( PCSZ pcszString )
    { return WinSetWindowText( _hwnd, pcszString ); }

    virtual bool WindowFromID( ULONG id, KWindow& kwnd );
    virtual bool ShowWindow( BOOL fNewVisibility )
    { return WinShowWindow( _hwnd, fNewVisibility ); }

    virtual ULONG MessageBox( PCSZ pcszText, PCSZ pcszCaption, ULONG flStyle )
    {
        return WinMessageBox( HWND_DESKTOP, _hwnd, pcszText, pcszCaption,
                              0xFFFF, flStyle );
    }

    virtual ULONG MessageBox( PCSZ pcszText, PCSZ pcszCaption, ULONG id,
                              ULONG flStyle )
    {
        return WinMessageBox( HWND_DESKTOP, _hwnd, pcszText, pcszCaption,
                              id, flStyle );
    }

    virtual MRESULT SendMsg( ULONG ulMsg, MPARAM mp1 = 0, MPARAM mp2 = 0 )
    { return WinSendMsg( _hwnd, ulMsg, mp1, mp2 ); }

    virtual bool PostMsg( ULONG ulMsg, MPARAM mp1 = 0, MPARAM mp2 = 0 )
    { return WinPostMsg( _hwnd, ulMsg, mp1, mp2 ); }

    virtual HAB QueryAnchorBlock() { return WinQueryAnchorBlock( _hwnd ); }
    virtual ULONG QueryTaskSizePos( PSWP pswp )
    { return WinQueryTaskSizePos( QueryAnchorBlock(), 0, pswp ); }

    virtual bool SetWindowPos( KWindow* pkwndRel, LONG x, LONG y,
                               LONG cx, LONG cy, ULONG fl )
    {
        return WinSetWindowPos( _hwnd, pkwnd2hwnd( pkwndRel ),
                                x, y, cx, cy, fl );
    }

    virtual HPS BeginPaint( HPS hps, PRECTL prcl )
    { return WinBeginPaint( _hwnd, hps, prcl); }

    virtual bool EndPaint( HPS hps ) { return WinEndPaint( hps ); }
    virtual bool FillRect( HPS hps, PRECTL prcl, LONG lColor )
    { return WinFillRect( hps, prcl, lColor ); }
    virtual bool QueryWindowRect( PRECTL prcl )
    { return WinQueryWindowRect( _hwnd, prcl ); }
    virtual LONG DrawText( HPS hps, LONG cchText, PCCH lpchText, PRECTL prcl,
                           LONG clrFore, LONG clrBack, ULONG flCmd )
    {
        return WinDrawText( hps, cchText, lpchText, prcl, clrFore, clrBack,
                            flCmd );
    }

    HWND GetHWND() const { return _hwnd; }
    virtual void SetHWND( HWND hwnd );

    PCSZ GetClassName() const { return _pcszClassName; }
    virtual void SetClassName( PCSZ pcszClassName );

protected :
    HWND     _hwnd;
    PCSZ     _pcszClassName;

    friend HWND pkwnd2hwnd( const KWindow* kwnd );

    static MRESULT EXPENTRY WndProc( HWND hwnd, ULONG msg, MPARAM mp1,
                                     MPARAM mp2 );

    virtual MRESULT KWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 );
    virtual MRESULT OnCreate( PVOID pCtrlData, PCREATESTRUCT pcs )
    { return KDefWndProc( WM_CREATE, MPFROMP( pCtrlData ), MPFROMP( pcs )); }

    virtual MRESULT OnDestroy() { return KDefWndProc( WM_DESTROY, 0, 0 ); }
    virtual MRESULT OnPaint() { return KDefWndProc( WM_PAINT, 0, 0 ); }
    virtual MRESULT OnCommand( ULONG ulCmd, ULONG ulSource,
                               bool fPointer );
    virtual MRESULT CmdSrcPushButton( ULONG ulCmd, bool fPointer )
    { return 0; }

    virtual MRESULT CmdSrcMenu( ULONG ulCmd, bool fPointer ) { return 0; }
    virtual MRESULT CmdSrcAccelerator( ULONG ulCmd, bool fPointer )
    { return 0; }

    virtual MRESULT CmdSrcFontDlg( ULONG ulCmd, bool fPointer ) { return 0; }
    virtual MRESULT CmdSrcFileDlg( ULONG ulCmd, bool fPointer ) { return 0; }
    virtual MRESULT CmdSrcOther( ULONG ulCmd, bool fPointer ) { return 0; }
    virtual MRESULT CmdSrcUser( ULONG ulCmd, bool fPointer ) { return 0; }

    virtual MRESULT OnControl( ULONG id, ULONG ulNotifyCode,
                               ULONG ulControlSpec );
    virtual MRESULT BnClicked( ULONG id ) { return 0; }
    virtual MRESULT BnDblClicked( ULONG id ) { return 0; }
    virtual MRESULT BnPaint( ULONG id, ULONG ulControlSpec ) { return 0; }

    virtual MRESULT OnHScroll( ULONG id, LONG lSlider, ULONG ulCmd );
    virtual MRESULT HSbLineLeft( ULONG id, LONG lSlider ) { return 0; }
    virtual MRESULT HSbLineRight( ULONG id, LONG lSlider ) { return 0; }
    virtual MRESULT HSbPageLeft( ULONG id, LONG lSlider ) { return 0; }
    virtual MRESULT HSbPageRight( ULONG id, LONG lSlider ) { return 0; }
    virtual MRESULT HSbSliderPosition( ULONG id, LONG lSlider ) { return 0; }
    virtual MRESULT HSbSliderTrack( ULONG id, LONG lSlider ) { return 0; }
    virtual MRESULT HSbEndScroll( ULONG id, LONG lSlider ) { return 0; }

    virtual MRESULT OnVScroll( ULONG id, LONG lSlider, ULONG ulCmd );
    virtual MRESULT VSbLineUp( ULONG id, LONG lSlider ) { return 0; }
    virtual MRESULT VSbLineDown( ULONG id, LONG lSlider ) { return 0; }
    virtual MRESULT VSbPageUp( ULONG id, LONG lSlider ) { return 0; }
    virtual MRESULT VSbPageDown( ULONG id, LONG lSlider ) { return 0; }
    virtual MRESULT VSbSliderPosition( ULONG id, LONG lSlider ) { return 0; }
    virtual MRESULT VSbSliderTrack( ULONG id, LONG lSlider ) { return 0; }
    virtual MRESULT VSbEndScroll( ULONG id, LONG lSlider ) { return 0; }

    virtual MRESULT OnSysCommand( ULONG ulCmd, ULONG ulSource,
                                  bool fPointer );
    virtual MRESULT SysCmdSrcPushButton( ULONG ulCmd, bool fPointer )
    { return 0; }

    virtual MRESULT SysCmdSrcMenu( ULONG ulCmd, bool fPointer ) { return 0; }
    virtual MRESULT SysCmdSrcAccelerator( ULONG ulCmd, bool fPointer )
    { return 0; }

    virtual MRESULT SysCmdSrcFontDlg( ULONG ulCmd, bool fPointer )
    { return 0; }

    virtual MRESULT SysCmdSrcFileDlg( ULONG ulCmd, bool fPointer )
    { return 0; }

    virtual MRESULT SysCmdSrcOther( ULONG ulCmd, bool fPointer ) { return 0; }
    virtual MRESULT SysCmdSrcUser( ULONG ulCmd, bool fPointer ) { return 0; }

    virtual MRESULT OnTrackFrame( ULONG flTrackFlags )
    { return KDefWndProc( WM_TRACKFRAME, MPFROMLONG( flTrackFlags ), 0 ); }

    virtual MRESULT OnHelp( ULONG ulCmd, ULONG ulSource, bool fPointer );
    virtual MRESULT HelpCmdSrcPushButton( ULONG ulCmd, bool fPointer )
    { return 0; }

    virtual MRESULT HelpCmdSrcMenu( ULONG ulCmd, bool fPointer ) { return 0; }
    virtual MRESULT HelpCmdSrcAccelerator( ULONG ulCmd, bool fPointer )
    { return 0; }

    virtual MRESULT HelpCmdSrcFontDlg( ULONG ulCmd, bool fPointer )
    { return 0; }

    virtual MRESULT HelpCmdSrcFileDlg( ULONG ulCmd, bool fPointer )
    { return 0; }

    virtual MRESULT HelpCmdSrcOther( ULONG ulCmd, bool fPointer )
    { return 0; }

    virtual MRESULT HelpCmdSrcUser( ULONG ulCmd, bool fPointer ) { return 0; }

    virtual MRESULT OnChar( ULONG flFlags, ULONG ulRepeat, ULONG ulScanCode,
                            ULONG ulCh, ULONG ulVk )
    {
        return KDefWndProc( WM_CHAR,
                            MPFROMSH2CH( flFlags, ulRepeat, ulScanCode ),
                            MPFROM2SHORT( ulCh, ulVk ));
    }

    virtual MRESULT OnClose() { return KDefWndProc( WM_CLOSE, 0, 0 ); }

private :
    PFNWP _pfnwpOldProc;

    MRESULT KDefWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
    { return _pfnwpOldProc ? _pfnwpOldProc( _hwnd, msg, mp1, mp2 ) :
                             WinDefWindowProc( _hwnd, msg, mp1, mp2 ); }
};
#endif

