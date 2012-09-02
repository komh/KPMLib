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
    virtual MRESULT OnChar( USHORT fsFlags, UCHAR ucRepeat, UCHAR ucScanCode,
                            USHORT usCh, USHORT usVk )
    {
        return KDefWndProc( WM_CHAR,
                            MPFROMSH2CH( fsFlags, ucRepeat, ucScanCode ),
                            MPFROM2SHORT( usCh, usVk ));
    }

    virtual MRESULT OnClose() { return KDefWndProc( WM_CLOSE, 0, 0 ); }

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

    virtual MRESULT OnControl( USHORT id, USHORT usNotifyCode,
                               ULONG ulControlSpec );
    virtual MRESULT BnClicked( USHORT id )
    { return KDefWndProc( WM_CONTROL, MPFROM2SHORT( id, BN_CLICKED ), 0 ); }

    virtual MRESULT BnDblClicked( USHORT id )
    { return KDefWndProc( WM_CONTROL, MPFROM2SHORT( id, BN_DBLCLICKED ), 0 ); }

    virtual MRESULT BnPaint( USHORT id, ULONG ulControlSpec )
    {
        return KDefWndProc( WM_CONTROL, MPFROM2SHORT( id, BN_PAINT ),
                            MPFROMLONG( ulControlSpec ));
    }

    virtual MRESULT OnCreate( PVOID pCtrlData, PCREATESTRUCT pcs )
    { return KDefWndProc( WM_CREATE, MPFROMP( pCtrlData ), MPFROMP( pcs )); }

    virtual MRESULT OnDestroy() { return KDefWndProc( WM_DESTROY, 0, 0 ); }
    virtual MRESULT OnDrawItem( USHORT idMenu, ULONG ulControlSpec )
    {
        return KDefWndProc( WM_DRAWITEM, MPFROMSHORT( idMenu ),
                            MPFROMLONG( ulControlSpec ));
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

    virtual MRESULT OnInitMenu( SHORT sMenuID, HWND hwnd )
    {
        return KDefWndProc( WM_INITMENU, MPFROMSHORT( sMenuID ),
                            MPFROMHWND( hwnd ));
    }

    virtual MRESULT OnMatchMnemonic( USHORT usMatch )
    { return KDefWndProc( WM_MATCHMNEMONIC, MPFROMSHORT( usMatch ), 0 ); }

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

    virtual MRESULT OnNextMenu( HWND hwndMenu, USHORT usPrev )
    {
        return KDefWndProc( WM_NEXTMENU, MPFROMHWND( hwndMenu ),
                            MPFROMSHORT( usPrev ));
    }

    virtual MRESULT OnPaint() { return KDefWndProc( WM_PAINT, 0, 0 ); }

    virtual MRESULT OnQueryDlgCode( PQMSG pQmsg )
    { return KDefWndProc( WM_QUERYDLGCODE, MPFROMP( pQmsg ), 0 ); }

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

    virtual MRESULT OnTrackFrame( USHORT fsTrackFlags )
    { return KDefWndProc( WM_TRACKFRAME, MPFROMSHORT( fsTrackFlags ), 0 ); }

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

private :
    PFNWP _pfnwpOldProc;

    MRESULT KDefWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
    {
        return _pfnwpOldProc ? _pfnwpOldProc( _hwnd, msg, mp1, mp2 ) :
                               WinDefWindowProc( _hwnd, msg, mp1, mp2 );
    }
};
#endif

