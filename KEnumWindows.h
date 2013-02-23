#ifndef K_ENUM_WINDOWS_H
#define K_ENUM_WINDOWS_H

#define INCL_WIN
#include <os2.h>

#include "KWindow.h"

class KEnumWindows
{
public :
    KEnumWindows() { _henum = NULLHANDLE; }
    KEnumWindows( const KWindow* pkwnd )
    {
        _henum = WinBeginEnumWindows( pkwnd2hwnd( pkwnd ));
    }

    virtual ~KEnumWindows()
    {
        if( _henum != NULLHANDLE )
            WinEndEnumWindows( _henum );
    }

    virtual HENUM BeginEnumWindows( const KWindow* pkwnd )
    {
        _henum = WinBeginEnumWindows( pkwnd2hwnd( pkwnd ));

        return _henum;
    }

    virtual bool GetNextWindow( KWindow& kwndNext )
    {
        HWND hwndNext = WinGetNextWindow( _henum );
        kwndNext.SetHWND( hwndNext );

        return hwndNext;
    }

    virtual bool EndEnumWindows()
    {
        return WinEndEnumWindows( _henum );
    }

protected :
    HENUM _henum;
};
#endif
