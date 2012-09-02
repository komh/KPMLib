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

bool KWindow::CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                            ULONG flStyle, LONG x, LONG y, LONG cx, LONG cy,
                            const KWindow* pkwndO, const KWindow* pkwndS,
                            ULONG id, PVOID pCtlData, PVOID pPresParams )
{
    HWND hwndP = pkwnd2hwnd( pkwndP );
    HWND hwndO = pkwnd2hwnd( pkwndO );
    HWND hwndS = pkwnd2hwnd( pkwndS );
    HWND hwnd;

    CreateParams cp = { pPresParams, this };

    hwnd = WinCreateWindow( hwndP, _pcszClassName, pcszName,flStyle,
                            x, y, cx, cy, hwndO, hwndS,
                            id, pCtlData, &cp );

    SetHWND( hwnd );

    return hwnd;
}

bool KWindow::DestroyWindow()
{
    if( WinDestroyWindow( _hwnd ))
    {
        _hwnd = 0;

        if( HIUSHORT( _pcszClassName ) != 0xFFFF )
            free( reinterpret_cast< void * >( const_cast< PSZ >
                                                ( _pcszClassName )));
        _pcszClassName = 0;
        _pfnwpOldProc  = 0;

        return true;
    }

    return false;
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

bool KWindow::WindowFromID( ULONG id, KWindow& kwnd )
{
    HWND     hwnd;

    hwnd = WinWindowFromID( _hwnd, id );
    if( !hwnd )
        return false;

    kwnd.SetHWND( hwnd );

    return true;
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

    // Already allocated ?
    if( _pcszClassName )
        return;

    UCHAR szClassName[ 512 ];
    WinQueryClassName( hwnd, sizeof( szClassName ), szClassName );
    _pcszClassName = reinterpret_cast< PCSZ >
                            ( strdup( reinterpret_cast< const char * >
                                        ( szClassName )));
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
        case WM_CHAR :
            return OnChar( SHORT1FROMMP( mp1 ), CHAR3FROMMP( mp1 ),
                           CHAR4FROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                           SHORT2FROMMP( mp2 ));

        case WM_CLOSE :
            return OnClose();

        case WM_COMMAND :
            return OnCommand( SHORT1FROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                              SHORT2FROMMP( mp2 ));

        case WM_CONTROL :
            return OnControl( SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ),
                              LONGFROMMP( mp2 ));

        case WM_CREATE :
            return OnCreate( PVOIDFROMMP( mp1 ),
                             reinterpret_cast< PCREATESTRUCT >
                                 ( PVOIDFROMMP( mp2 )));

        case WM_DESTROY :
            return OnDestroy();

        case WM_DRAWITEM :
            return OnDrawItem( SHORT1FROMMP( mp1 ), LONGFROMMP( mp2 ));

        case WM_HELP :
            return OnHelp( SHORT1FROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                           SHORT2FROMMP( mp2 ));

        case WM_HSCROLL :
            return OnHScroll( SHORT1FROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                              SHORT2FROMMP( mp2 ));

        case WM_INITDLG :
            return OnInitDlg( HWNDFROMMP( mp1 ), PVOIDFROMMP( mp2 ));

        case WM_INITMENU :
            return OnInitMenu( SHORT1FROMMP( mp1 ), HWNDFROMMP( mp2 ));

        case WM_MATCHMNEMONIC :
            return OnMatchMnemonic( SHORT1FROMMP( mp1 ));

        case WM_MEASUREITEM :
            return OnMeasureItem( SHORT1FROMMP( mp1 ), LONGFROMMP( mp2 ));

        case WM_MENUEND :
            return OnMenuEnd( SHORT1FROMMP( mp1 ), HWNDFROMMP( mp2 ));

        case WM_MENUSELECT :
            return OnMenuSelect( SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ),
                                 HWNDFROMMP( mp2 ));

        case WM_NEXTMENU :
            return OnNextMenu( HWNDFROMMP( mp1 ), SHORT1FROMMP( mp2 ));

        case WM_PAINT :
            return OnPaint();

        case WM_QUERYDLGCODE :
            return OnQueryDlgCode( reinterpret_cast< PQMSG >( mp1 ));

        case WM_SYSCOMMAND :
            return OnSysCommand( SHORT1FROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                                 SHORT2FROMMP( mp2 ));

        case WM_TRACKFRAME :
            return OnTrackFrame( SHORT1FROMMP( mp1 ));

        case WM_VSCROLL :
            return OnVScroll( SHORT1FROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                              SHORT2FROMMP( mp2 ));
    }

    return KDefWndProc( msg, mp1, mp2 );
}

MRESULT KWindow::OnCommand( USHORT usCmd, USHORT usSource, bool fPointer )
{
    switch( usSource )
    {
        case CMDSRC_PUSHBUTTON  : return CmdSrcPushButton( usCmd, fPointer );
        case CMDSRC_MENU        : return CmdSrcMenu( usCmd, fPointer );
        case CMDSRC_ACCELERATOR : return CmdSrcAccelerator( usCmd, fPointer );
        case CMDSRC_FONTDLG     : return CmdSrcFontDlg( usCmd, fPointer );
        case CMDSRC_FILEDLG     : return CmdSrcFileDlg( usCmd, fPointer );
        case CMDSRC_OTHER       : return CmdSrcOther( usCmd, fPointer );
    }

    return CmdSrcUser( usCmd, usSource, fPointer );
}

MRESULT KWindow::OnHelp( USHORT usCmd, USHORT usSource, bool fPointer )
{
    switch( usSource )
    {
        case CMDSRC_PUSHBUTTON  :
            return HelpCmdSrcPushButton( usCmd, fPointer );

        case CMDSRC_MENU        :
            return HelpCmdSrcMenu( usCmd, fPointer );

        case CMDSRC_ACCELERATOR :
            return HelpCmdSrcAccelerator( usCmd, fPointer );

        case CMDSRC_FONTDLG     :
            return HelpCmdSrcFontDlg( usCmd, fPointer );

        case CMDSRC_FILEDLG     :
            return HelpCmdSrcFileDlg( usCmd, fPointer );

        case CMDSRC_OTHER       :
            return HelpCmdSrcOther( usCmd, fPointer );
    }

    return HelpCmdSrcUser( usCmd, usSource, fPointer );
}

MRESULT KWindow::OnHScroll( USHORT id, SHORT sSlider, USHORT usCmd )
{
    switch( usCmd )
    {
        case SB_LINELEFT       : return HSbLineLeft( id, sSlider );
        case SB_LINERIGHT      : return HSbLineRight( id, sSlider );
        case SB_PAGELEFT       : return HSbPageLeft( id, sSlider );
        case SB_PAGERIGHT      : return HSbPageRight( id, sSlider );
        case SB_SLIDERPOSITION : return HSbSliderPosition( id, sSlider );
        case SB_SLIDERTRACK    : return HSbSliderTrack( id, sSlider );
        case SB_ENDSCROLL      : return HSbEndScroll( id, sSlider );
    }

    return 0;
}

MRESULT KWindow::OnSysCommand( USHORT usCmd, USHORT usSource, bool fPointer )
{
    switch( usSource )
    {
        case CMDSRC_PUSHBUTTON  :
            return SysCmdSrcPushButton( usCmd, fPointer );

        case CMDSRC_MENU        :
            return SysCmdSrcMenu( usCmd, fPointer );

        case CMDSRC_ACCELERATOR :
            return SysCmdSrcAccelerator( usCmd, fPointer );

        case CMDSRC_FONTDLG     :
            return SysCmdSrcFontDlg( usCmd, fPointer );

        case CMDSRC_FILEDLG     :
            return SysCmdSrcFileDlg( usCmd, fPointer );

        case CMDSRC_OTHER       :
            return SysCmdSrcOther( usCmd, fPointer );
    }

    return SysCmdSrcUser( usCmd, usSource, fPointer );
}

MRESULT KWindow::OnVScroll( USHORT id, SHORT sSlider, USHORT usCmd )
{
    switch( usCmd )
    {
        case SB_LINEUP         : return VSbLineUp( id, sSlider );
        case SB_LINEDOWN       : return VSbLineDown( id, sSlider );
        case SB_PAGEUP         : return VSbPageUp( id, sSlider );
        case SB_PAGEDOWN       : return VSbPageDown( id, sSlider );
        case SB_SLIDERPOSITION : return VSbSliderPosition( id, sSlider );
        case SB_SLIDERTRACK    : return VSbSliderTrack( id, sSlider );
        case SB_ENDSCROLL      : return VSbEndScroll( id, sSlider );
    }

    return 0;
}

