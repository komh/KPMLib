#define INCL_WIN
#include <os2.h>

#include <stdlib.h>
#include <string.h>

#include "KWindow.h"

struct CreateParams
{
    PVOID    pPresParams;
    KWindow* pkwnd;
};

HWND pkwnd2hwnd( const KWindow* kwnd )
{
    if( kwnd == 0 )           return NULLHANDLE;
    if( kwnd == KWND_DESKTOP) return HWND_DESKTOP;
    if( kwnd == KWND_OBJECT)  return HWND_OBJECT;
    if( kwnd == KWND_TOP )    return HWND_TOP;
    if( kwnd == KWND_BOTTOM ) return HWND_BOTTOM;

    return kwnd->_hwnd;
}

KWindow::KWindow()
{
    _hwnd          = 0;
    _pcszClassName = 0;
    _pfnwpOldProc  = 0;
}

KWindow::~KWindow()
{
    if( _pfnwpOldProc )
        WinSubclassWindow( _hwnd, _pfnwpOldProc );

    if( HIUSHORT( _pcszClassName ) != 0xFFFF )
        free( reinterpret_cast< void * >( const_cast< PSZ >
                                            ( _pcszClassName )));
}

void KWindow::SetHWND( HWND hwnd )
{
    _hwnd = hwnd;

    if( !hwnd )
        return;

    if( !WinQueryWindowPtr( hwnd, 0 ))
    {
        WinSetWindowPtr( hwnd, 0, this );

        _pfnwpOldProc = WinSubclassWindow( hwnd, WndProc );
    }

    UCHAR szClassName[ 512 ];
    WinQueryClassName( hwnd, sizeof( szClassName ), szClassName );
    _pcszClassName = reinterpret_cast< PCSZ >
                            ( strdup( reinterpret_cast< const char * >
                                        ( szClassName )));
}

bool KWindow::RegisterClass( HAB hab, PCSZ pcszClassName, ULONG flStyle,
                             ULONG cbWindowData )
{
    _pcszClassName = reinterpret_cast< PCSZ >(
                        strdup( reinterpret_cast< const char * >
                                    ( pcszClassName )));

    return WinRegisterClass( hab, pcszClassName, WndProc, flStyle,
                             sizeof( PVOID ) + cbWindowData );
}

void KWindow::SetClassName( PCSZ pcszClassName )
{
    // pre-defined class such as WC_FRAME ?
    if( HIUSHORT( pcszClassName ) == 0xFFFF )
        _pcszClassName = pcszClassName;
    else
        _pcszClassName = reinterpret_cast< PCSZ >(
                            strdup( reinterpret_cast< const char * >
                                        ( pcszClassName )));
}

bool KWindow::CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                            ULONG flStyle, LONG x, LONG y, LONG cx, LONG cy,
                            const KWindow* pkwndO, const KWindow* pkwndS,
                            ULONG id, PVOID pCtlData, PVOID pPresParams )
{
    HWND hwndP = pkwnd2hwnd( pkwndP );
    HWND hwndO = pkwnd2hwnd( pkwndO );
    HWND hwndS = pkwnd2hwnd( pkwndS );

    CreateParams cp = { pPresParams, this };

    _hwnd = WinCreateWindow( hwndP, _pcszClassName, pcszName,flStyle,
                             x, y, cx, cy, hwndO, hwndS,
                             id, pCtlData, &cp );

    // For pre-registered class
    if( !WinQueryWindowPtr( _hwnd, 0 ))
    {
        WinSetWindowPtr( _hwnd, 0, this );

        _pfnwpOldProc = WinSubclassWindow( _hwnd, WndProc );
    }

    return _hwnd;
}

bool KWindow::WindowFromID( ULONG id, KWindow& kwnd )
{
    HWND     hwnd;

    hwnd = WinWindowFromID( _hwnd, id );
    if( !hwnd )
        return false;

    kwnd.SetHWND( hwnd );

    return true;
}

MRESULT EXPENTRY KWindow::WndProc( HWND hwnd, ULONG msg, MPARAM mp1,
                                   MPARAM mp2 )
{
    KWindow* pkwnd = reinterpret_cast< KWindow* >
                        ( WinQueryWindowPtr( hwnd, 0 ));

    if( msg == WM_CREATE )
    {
        PCREATESTRUCT pcs = reinterpret_cast< PCREATESTRUCT >( mp2 );
        CreateParams* pcp = reinterpret_cast< CreateParams* >
                                ( pcs->pPresParams );

        pkwnd = pcp->pkwnd;
        WinSetWindowPtr( hwnd, 0, pkwnd );

        pcs->pPresParams = pcp->pPresParams;
    }

    return pkwnd->KWndProc( msg, mp1, mp2 );
}

MRESULT KWindow::KWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch( msg )
    {
        case WM_CREATE  : return OnCreate( PVOIDFROMMP( mp1 ),
                                           reinterpret_cast< PCREATESTRUCT >
                                                ( PVOIDFROMMP( mp2 )));
        case WM_DESTROY : return OnDestroy();
        case WM_PAINT   : return OnPaint();
        case WM_COMMAND : return OnCommand( SHORT1FROMMP( mp1 ),
                                            SHORT1FROMMP( mp2 ),
                                            SHORT2FROMMP( mp2 ));
        case WM_CONTROL : return OnControl( SHORT1FROMMP( mp1 ),
                                            SHORT2FROMMP( mp1 ),
                                            LONGFROMMP( mp2 ));
        case WM_HSCROLL : return OnHScroll( SHORT1FROMMP( mp1 ),
                                            SHORT1FROMMP( mp2 ),
                                            SHORT2FROMMP( mp2 ));
        case WM_VSCROLL : return OnVScroll( SHORT1FROMMP( mp1 ),
                                            SHORT1FROMMP( mp2 ),
                                            SHORT2FROMMP( mp2 ));
        case WM_TRACKFRAME : return OnTrackFrame( SHORT1FROMMP( mp1 ));
    }

    return KDefWndProc( msg, mp1, mp2 );
}

MRESULT KWindow::OnCommand( ULONG ulCmd, ULONG ulSource, bool fPointer )
{
    switch( ulSource )
    {
        case CMDSRC_PUSHBUTTON  : return CmdSrcPushButton( ulCmd, fPointer );
        case CMDSRC_MENU        : return CmdSrcMenu( ulCmd, fPointer );
        case CMDSRC_ACCELERATOR : return CmdSrcAccelerator( ulCmd, fPointer );
        case CMDSRC_FONTDLG     : return CmdSrcFontDlg( ulCmd, fPointer );
        case CMDSRC_FILEDLG     : return CmdSrcFileDlg( ulCmd, fPointer );
        case CMDSRC_OTHER       : return CmdSrcOther( ulCmd, fPointer );
    }

    return CmdSrcUser( ulCmd, fPointer );
}

MRESULT KWindow::OnControl( ULONG id, ULONG ulNotifyCode,
                            ULONG ulControlSpec )
{
    switch( ulNotifyCode )
    {
        case BN_CLICKED    : return BnClicked( id );
        case BN_DBLCLICKED : return BnDblClicked( id );
        case BN_PAINT      : return BnPaint( id, ulControlSpec );
    }

    return 0;
}

MRESULT KWindow::OnHScroll( ULONG id, LONG lSlider, ULONG ulCmd )
{
    switch( ulCmd )
    {
        case SB_LINELEFT       : return HSbLineLeft( id, lSlider );
        case SB_LINERIGHT      : return HSbLineRight( id, lSlider );
        case SB_PAGELEFT       : return HSbPageLeft( id, lSlider );
        case SB_PAGERIGHT      : return HSbPageRight( id, lSlider );
        case SB_SLIDERPOSITION : return HSbSliderPosition( id, lSlider );
        case SB_SLIDERTRACK    : return HSbSliderTrack( id, lSlider );
        case SB_ENDSCROLL      : return HSbEndScroll( id, lSlider );
    }

    return 0;
}

MRESULT KWindow::OnVScroll( ULONG id, LONG lSlider, ULONG ulCmd )
{
    switch( ulCmd )
    {
        case SB_LINEUP         : return VSbLineUp( id, lSlider );
        case SB_LINEDOWN       : return VSbLineDown( id, lSlider );
        case SB_PAGEUP         : return VSbPageUp( id, lSlider );
        case SB_PAGEDOWN       : return VSbPageDown( id, lSlider );
        case SB_SLIDERPOSITION : return VSbSliderPosition( id, lSlider );
        case SB_SLIDERTRACK    : return VSbSliderTrack( id, lSlider );
        case SB_ENDSCROLL      : return VSbEndScroll( id, lSlider );
    }

    return 0;
}

MRESULT KWindow::OnSysCommand( ULONG ulCmd, ULONG ulSource, bool fPointer )
{
    switch( ulSource )
    {
        case CMDSRC_PUSHBUTTON  :
            return SysCmdSrcPushButton( ulCmd, fPointer );

        case CMDSRC_MENU        :
            return SysCmdSrcMenu( ulCmd, fPointer );

        case CMDSRC_ACCELERATOR :
            return SysCmdSrcAccelerator( ulCmd, fPointer );

        case CMDSRC_FONTDLG     :
            return SysCmdSrcFontDlg( ulCmd, fPointer );

        case CMDSRC_FILEDLG     :
            return SysCmdSrcFileDlg( ulCmd, fPointer );

        case CMDSRC_OTHER       :
            return SysCmdSrcOther( ulCmd, fPointer );
    }

    return SysCmdSrcUser( ulCmd, fPointer );
}

MRESULT KWindow::OnHelp( ULONG ulCmd, ULONG ulSource, bool fPointer )
{
    switch( ulSource )
    {
        case CMDSRC_PUSHBUTTON  :
            return HelpCmdSrcPushButton( ulCmd, fPointer );

        case CMDSRC_MENU        :
            return HelpCmdSrcMenu( ulCmd, fPointer );

        case CMDSRC_ACCELERATOR :
            return HelpCmdSrcAccelerator( ulCmd, fPointer );

        case CMDSRC_FONTDLG     :
            return HelpCmdSrcFontDlg( ulCmd, fPointer );

        case CMDSRC_FILEDLG     :
            return HelpCmdSrcFileDlg( ulCmd, fPointer );

        case CMDSRC_OTHER       :
            return HelpCmdSrcOther( ulCmd, fPointer );
    }

    return HelpCmdSrcUser( ulCmd, fPointer );
}

