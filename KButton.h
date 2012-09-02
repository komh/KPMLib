#ifndef KBUTTON_H
#define KBUTTON_H

#define INCL_WIN
#include <os2.h>

#include "KWindow.h"

// kLIBC 0.6.5 does not have BM_AUTOSIZE
#ifndef BM_AUTOSIZE
#define BM_AUTOSIZE 0x128
#endif

class KButton : public KWindow
{
public :
    KButton() : KWindow() {};
    virtual ~KButton() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    enum CheckState { kUncheck = 0, kCheck, kIndeterminate };

    virtual bool AutoSize() { return SendMsg( BM_AUTOSIZE ); }
    virtual void Click( bool fUp ) { SendMsg( BM_CLICK, MPFROMLONG( fUp )); }

    virtual ULONG QueryCheck()
    { return LONGFROMMR( SendMsg( BM_QUERYCHECK )); }

    virtual LONG QueryCheckIndex()
    { return LONGFROMMR( SendMsg( BM_QUERYCHECKINDEX )); }

    virtual bool QueryHilite() { return SendMsg( BM_QUERYHILITE ); }
    virtual ULONG SetCheck( ULONG ulCheck )
    { return LONGFROMMR( SendMsg( BM_SETCHECK, MPFROMLONG( ulCheck ))); }

    virtual bool SetDefault( bool fDefault )
    { return SendMsg( BM_SETDEFAULT, MPFROMLONG( fDefault )); }

    virtual bool SetHilite( bool fHilite )
    { return SendMsg( BM_SETHILITE, MPFROMLONG( fHilite )); }
};
#endif
