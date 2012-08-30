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

    return _hwnd;
}

bool KWindow::DestroyWindow()
{
    return WinDestroyWindow( _hwnd );
}

bool KWindow::SetWindowText( PCSZ pcszString )
{
    return WinSetWindowText( _hwnd, pcszString );
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

bool KWindow::ShowWindow( BOOL fNewVisibility )
{
    return WinShowWindow( _hwnd, fNewVisibility );
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
        case WM_PAINT   : return OnPaint();
        case WM_COMMAND : return OnCommand( SHORT1FROMMP( mp1 ),
                                            SHORT1FROMMP( mp2 ),
                                            SHORT2FROMMP( mp2 ));
        case WM_CONTROL : return OnControl( SHORT1FROMMP( mp1 ),
                                            SHORT2FROMMP( mp1 ),
                                            LONGFROMMP( mp2 ));
    }

    return KDefWndProc( msg, mp1, mp2 );
}

MRESULT KWindow::OnPaint()
{
    return KDefWndProc( WM_PAINT, 0, 0 );
}

MRESULT KWindow::OnCommand( USHORT usCmd, USHORT usSource, USHORT usPointer )
{
    switch( usSource )
    {
        case CMDSRC_PUSHBUTTON : return CmdSrcPushButton( usCmd, usPointer );
    }

    return 0;
}

MRESULT KWindow::CmdSrcPushButton( USHORT usCmd, USHORT usPointer )
{
    return 0;
}

MRESULT KWindow::OnControl( USHORT id, USHORT usNotifyCode,
                            ULONG ulControlSpec )
{
    switch( usNotifyCode )
    {
        case BN_CLICKED    : return BnClicked( id );
        case BN_DBLCLICKED : return BnDblClicked( id );
        case BN_PAINT      : return BnPaint( id, ulControlSpec );
    }

    return 0;
}

MRESULT KWindow::BnClicked( USHORT id )
{
    return 0;
}

MRESULT KWindow::BnDblClicked( USHORT id )
{
    return 0;
}

MRESULT KWindow::BnPaint( USHORT id, ULONG ulControlSpec )
{
    return 0;
}

