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

    virtual HPS BeginPaint( HPS hps, PRECTL prcl )
    { return WinBeginPaint( _hwnd, hps, prcl); }

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );
    virtual bool DestroyWindow();
    virtual LONG DrawText( HPS hps, LONG cchText, PCCH lpchText, PRECTL prcl,
                           LONG clrFore, LONG clrBack, ULONG flCmd )
    {
        return WinDrawText( hps, cchText, lpchText, prcl, clrFore, clrBack,
                            flCmd );
    }

    virtual bool EndPaint( HPS hps ) { return WinEndPaint( hps ); }
    virtual bool FillRect( HPS hps, PRECTL prcl, LONG lColor )
    { return WinFillRect( hps, prcl, lColor ); }

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

    virtual bool PostMsg( ULONG ulMsg, MPARAM mp1 = 0, MPARAM mp2 = 0 )
    { return WinPostMsg( _hwnd, ulMsg, mp1, mp2 ); }

    virtual HAB QueryAnchorBlock() { return WinQueryAnchorBlock( _hwnd ); }
    virtual ULONG QueryTaskSizePos( PSWP pswp )
    { return WinQueryTaskSizePos( QueryAnchorBlock(), 0, pswp ); }

    virtual bool QueryWindowRect( PRECTL prcl )
    { return WinQueryWindowRect( _hwnd, prcl ); }

    virtual bool RegisterClass( HAB hab, PCSZ pcszClassName, ULONG flStyle,
                                ULONG cbWindowData );
    virtual MRESULT SendMsg( ULONG ulMsg, MPARAM mp1 = 0, MPARAM mp2 = 0 )
    { return WinSendMsg( _hwnd, ulMsg, mp1, mp2 ); }

    virtual bool SetWindowPos( KWindow* pkwndRel, LONG x, LONG y,
                               LONG cx, LONG cy, ULONG fl )
    {
        return WinSetWindowPos( _hwnd, pkwnd2hwnd( pkwndRel ),
                                x, y, cx, cy, fl );
    }

    virtual bool SetWindowText( PCSZ pcszString )
    { return WinSetWindowText( _hwnd, pcszString ); }

    virtual bool ShowWindow( BOOL fNewVisibility )
    { return WinShowWindow( _hwnd, fNewVisibility ); }

    virtual bool WindowFromID( ULONG id, KWindow& kwnd );

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
    virtual MRESULT OnChar( ULONG flFlags, ULONG ulRepeat, ULONG ulScanCode,
                            ULONG ulCh, ULONG ulVk )
    {
        return KDefWndProc( WM_CHAR,
                            MPFROMSH2CH( flFlags, ulRepeat, ulScanCode ),
                            MPFROM2SHORT( ulCh, ulVk ));
    }

    virtual MRESULT OnClose() { return KDefWndProc( WM_CLOSE, 0, 0 ); }

    virtual MRESULT OnCommand( ULONG ulCmd, ULONG ulSource,
                               bool fPointer );
    virtual MRESULT CmdSrcPushButton( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_PUSHBUTTON, fPointer ));
    }

    virtual MRESULT CmdSrcMenu( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_MENU, fPointer ));
    }

    virtual MRESULT CmdSrcAccelerator( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_ACCELERATOR, fPointer ));
    }

    virtual MRESULT CmdSrcFontDlg( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_FONTDLG, fPointer ));
    }

    virtual MRESULT CmdSrcFileDlg( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_FILEDLG, fPointer ));
    }

    virtual MRESULT CmdSrcOther( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_OTHER, fPointer ));
    }

    virtual MRESULT CmdSrcUser( ULONG ulCmd, ULONG ulSource, bool fPointer )
    {
        return KDefWndProc( WM_COMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( ulSource, fPointer ));
    }

    virtual MRESULT OnControl( ULONG id, ULONG ulNotifyCode,
                               ULONG ulControlSpec );
    virtual MRESULT BnClicked( ULONG id )
    { return KDefWndProc( WM_CONTROL, MPFROM2SHORT( id, BN_CLICKED ), 0 ); }

    virtual MRESULT BnDblClicked( ULONG id )
    { return KDefWndProc( WM_CONTROL, MPFROM2SHORT( id, BN_DBLCLICKED ), 0 ); }

    virtual MRESULT BnPaint( ULONG id, ULONG ulControlSpec )
    {
        return KDefWndProc( WM_CONTROL, MPFROM2SHORT( id, BN_PAINT ),
                            MPFROMLONG( ulControlSpec ));
    }

    virtual MRESULT OnCreate( PVOID pCtrlData, PCREATESTRUCT pcs )
    { return KDefWndProc( WM_CREATE, MPFROMP( pCtrlData ), MPFROMP( pcs )); }

    virtual MRESULT OnDestroy() { return KDefWndProc( WM_DESTROY, 0, 0 ); }
    virtual MRESULT OnDrawItem( ULONG idMenu, ULONG ulControlSpec )
    {
        return KDefWndProc( WM_DRAWITEM, MPFROMLONG( idMenu ),
                            MPFROMLONG( ulControlSpec ));
    }

    virtual MRESULT OnHelp( ULONG ulCmd, ULONG ulSource, bool fPointer );
    virtual MRESULT HelpCmdSrcPushButton( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_PUSHBUTTON, fPointer ));
    }

    virtual MRESULT HelpCmdSrcMenu( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_PUSHBUTTON, fPointer ));
    }

    virtual MRESULT HelpCmdSrcAccelerator( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_ACCELERATOR, fPointer ));
    }

    virtual MRESULT HelpCmdSrcFontDlg( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_FONTDLG, fPointer ));
    }

    virtual MRESULT HelpCmdSrcFileDlg( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_FILEDLG, fPointer ));
    }

    virtual MRESULT HelpCmdSrcOther( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_OTHER, fPointer ));
    }

    virtual MRESULT HelpCmdSrcUser( ULONG ulCmd, ULONG ulSource,
                                    bool fPointer )
    {
        return KDefWndProc( WM_HELP, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( ulSource, fPointer ));
    }

    virtual MRESULT OnHScroll( ULONG id, LONG lSlider, ULONG ulCmd );
    virtual MRESULT HSbLineLeft( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_LINELEFT ));
    }

    virtual MRESULT HSbLineRight( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_LINERIGHT ));
    }

    virtual MRESULT HSbPageLeft( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_PAGELEFT ));
    }

    virtual MRESULT HSbPageRight( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_PAGERIGHT ));
    }

    virtual MRESULT HSbSliderPosition( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_SLIDERPOSITION ));
    }

    virtual MRESULT HSbSliderTrack( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_SLIDERTRACK ));
    }

    virtual MRESULT HSbEndScroll( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_HSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_ENDSCROLL ));
    }

    virtual MRESULT OnInitMenu( ULONG ulMenuID, HWND hwnd )
    {
        return KDefWndProc( WM_INITMENU, MPFROMLONG( ulMenuID ),
                            MPFROMHWND( hwnd ));
    }

    virtual MRESULT OnMatchMnemonic( ULONG ulMatch )
    { return KDefWndProc( WM_MATCHMNEMONIC, MPFROMLONG( ulMatch ), 0 ); }

    virtual MRESULT OnMeasureItem( ULONG ulID, ULONG ulControlSpec )
    {
        return KDefWndProc( WM_MEASUREITEM, MPFROMLONG ( ulID ),
                            MPFROMLONG( ulControlSpec ));
    }

    virtual MRESULT OnMenuEnd( ULONG ulID, HWND hwnd )
    {
        return KDefWndProc( WM_MENUEND, MPFROMLONG( ulID ),
                            MPFROMHWND( hwnd ));
    }

    virtual MRESULT OnMenuSelect( ULONG ulItem, bool fPost, HWND hwnd )
    {
        return KDefWndProc( WM_MENUSELECT, MPFROM2SHORT( ulItem, fPost ),
                            MPFROMHWND( hwnd ));
    }

    virtual MRESULT OnNextMenu( HWND hwndMenu, ULONG ulPrev )
    {
        return KDefWndProc( WM_NEXTMENU, MPFROMHWND( hwndMenu ),
                            MPFROMLONG( ulPrev ));
    }

    virtual MRESULT OnPaint() { return KDefWndProc( WM_PAINT, 0, 0 ); }

    virtual MRESULT OnQueryDlgCode( PQMSG pQmsg )
    { return KDefWndProc( WM_QUERYDLGCODE, MPFROMP( pQmsg ), 0 ); }

    virtual MRESULT OnSysCommand( ULONG ulCmd, ULONG ulSource,
                                  bool fPointer );
    virtual MRESULT SysCmdSrcPushButton( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_PUSHBUTTON, fPointer ));

    }

    virtual MRESULT SysCmdSrcMenu( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_MENU, fPointer ));

    }

    virtual MRESULT SysCmdSrcAccelerator( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_ACCELERATOR, fPointer ));

    }

    virtual MRESULT SysCmdSrcFontDlg( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_FONTDLG, fPointer ));

    }

    virtual MRESULT SysCmdSrcFileDlg( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_FILEDLG, fPointer ));

    }

    virtual MRESULT SysCmdSrcOther( ULONG ulCmd, bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( CMDSRC_OTHER, fPointer ));

    }

    virtual MRESULT SysCmdSrcUser( ULONG ulCmd, ULONG ulSource, bool fPointer )
    {
        return KDefWndProc( WM_SYSCOMMAND, MPFROMLONG( ulCmd ),
                            MPFROM2SHORT( ulSource, fPointer ));

    }

    virtual MRESULT OnTrackFrame( ULONG flTrackFlags )
    { return KDefWndProc( WM_TRACKFRAME, MPFROMLONG( flTrackFlags ), 0 ); }

    virtual MRESULT OnVScroll( ULONG id, LONG lSlider, ULONG ulCmd );
    virtual MRESULT VSbLineUp( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_LINEUP ));
    }

    virtual MRESULT VSbLineDown( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_LINEDOWN ));
    }

    virtual MRESULT VSbPageUp( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_PAGEUP ));
    }

    virtual MRESULT VSbPageDown( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_PAGEDOWN ));
    }

    virtual MRESULT VSbSliderPosition( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_SLIDERPOSITION ));
    }

    virtual MRESULT VSbSliderTrack( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_SLIDERTRACK ));
    }

    virtual MRESULT VSbEndScroll( ULONG id, LONG lSlider )
    {
        return KDefWndProc( WM_VSCROLL, MPFROMLONG( id ),
                            MPFROM2SHORT( lSlider, SB_ENDSCROLL ));
    }

private :
    PFNWP _pfnwpOldProc;

    MRESULT KDefWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
    {
        return _pfnwpOldProc ? _pfnwpOldProc( _hwnd, msg, mp1, mp2 ) :
                               WinDefWindowProc( _hwnd, msg, mp1, mp2 );
    }
};
#endif

