#ifndef KSTATIC_TEXT_H
#define KSTATIC_TEXT_H

#define INCL_WIN
#include <os2.h>

#include <string>

#include "KWindow.h"

class KStaticText : public KWindow
{
public :
    KStaticText() : KWindow() {};
    virtual ~KStaticText() {};

    virtual bool CreateWindow( const KWindow* pkwndP, const string& strName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    virtual HBITMAP QueryHandle()
    {
        return LONGFROMMR( SendMsg( SM_QUERYHANDLE ));
    }

    virtual HBITMAP SetHandle( HBITMAP hbmHandle )
    {
        return LONGFROMMR( SendMsg( SM_SETHANDLE, MPFROMLONG( hbmHandle )));
    }

    virtual bool SetHandleP( HBITMAP hbmHandle )
    {
        return PostMsg( SM_SETHANDLE, MPFROMLONG( hbmHandle ));
    }
};
#endif
