#define INCL_WIN
#include <os2.h>

// kLIBC 0.6.5 does not have BM_AUTOSIZE
#ifndef BM_AUTOSIZE
#define BM_AUTOSIZE 0x128
#endif

#include "KButton.h"

KButton::KButton()
{
}

KButton::~KButton()
{
}

bool KButton::CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                            ULONG flStyle, LONG x, LONG y, LONG cx, LONG cy,
                            const KWindow* pkwndO, const KWindow* pkwndS,
                            ULONG id, PVOID pCtlData, PVOID pPresParams )
{
    SetClassName( PMLITERAL( WC_BUTTON ));

    return KWindow::CreateWindow( pkwndP, pcszName, flStyle, x, y, cx, cy,
                                  pkwndO, pkwndS, id, pCtlData, pPresParams );
}

bool KButton::AutoSize()
{
    return SendMsg( BM_AUTOSIZE, 0, 0 );
}

void KButton::Click( bool fUp )
{
    SendMsg( BM_CLICK, MPFROMLONG( fUp ), 0 );
}

KButton::CheckState KButton::QueryCheck()
{
    return static_cast< CheckState >
                ( LONGFROMMR( SendMsg( BM_QUERYCHECK, 0, 0 )));
}

int KButton::QueryCheckIndex()
{
    return LONGFROMMR( SendMsg( BM_QUERYCHECKINDEX, 0, 0 ));
}

bool KButton::QueryHilite()
{
    return SendMsg( BM_QUERYHILITE, 0, 0 );
}

KButton::CheckState KButton::SetCheck( CheckState bcsNew )
{
    return static_cast< CheckState >
                ( LONGFROMMR( SendMsg( BM_SETCHECK,
                                          MPFROMLONG( bcsNew ), 0 )));
}

bool KButton::SetDefault( bool fDefault )
{
    return SendMsg( BM_SETDEFAULT, MPFROMLONG( fDefault ), 0 );
}

bool KButton::SetHilite( bool fHilite )
{
    return SendMsg( BM_SETHILITE, MPFROMLONG( fHilite ), 0 );
}


