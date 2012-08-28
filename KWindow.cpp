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
    _hab           = 0;
    _pkwndP        = 0;
    _pkwndO        = 0;
    _hwnd          = 0;
    _pcszClassName = 0;
    _pfnwpOldProc  = 0;
}

KWindow::~KWindow()
{
    if( _pfnwpOldProc )
    {
        WinSubclassWindow( _hwnd, _pfnwpOldProc );

        delete _pkwndP;
        delete _pkwndO;
    }

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

    _hab = WinQueryAnchorBlock( hwnd );

    _pkwndP = new KWindow;
    _pkwndP->SetHWND( WinQueryWindow( hwnd, QW_PARENT ));

    _pkwndO = new KWindow;
    _pkwndO->SetHWND( WinQueryWindow( hwnd, QW_OWNER ));

    UCHAR szClassName[ 512 ];
    WinQueryClassName( hwnd, sizeof( szClassName ), szClassName );
    _pcszClassName = reinterpret_cast< PCSZ >
                            ( strdup( reinterpret_cast< const char * >
                                        ( szClassName )));
}

bool KWindow::RegisterClass( HAB hab, PCSZ pcszClassName, ULONG flStyle,
                             ULONG cbWindowData )
{
    _hab           = hab;
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
    _pkwndP = const_cast< KWindow* >( pkwndP );
    _pkwndO = const_cast< KWindow* >( pkwndO );

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
        case WM_PAINT : return OnPaint();
    }

    return KDefWndProc( msg, mp1, mp2 );
}

MRESULT KWindow::OnPaint()
{
    return KDefWndProc( WM_PAINT, 0, 0 );
}

