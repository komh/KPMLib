#ifndef KFRAMEWINDOW_H
#define KFRAMEWINDOW_H

#define INCL_WIN
#include <os2.h>

#include "KWindow.h"
#include "KScrollBar.h"
#include "KMenu.h"
#include "KTitleBar.h"

class KFrameWindow : public KWindow
{
public :
    KFrameWindow();
    virtual ~KFrameWindow();

    virtual bool CreateStdWindow( KWindow* pkwndP, ULONG flStyle,
                                  PULONG pflCreateFlags,
                                  PCSZ pcszTitle, ULONG flClientStyle,
                                  HMODULE hmodResources, ULONG ulId,
                                  KWindow& kwndClient );

    KWindow& GetClient() { return _kwndClient; }
    KScrollBar& GetHorzScroll() { return _kwndHorzScroll; }
    KMenu& GetMenu() { return _kwndMenu; }
    KMenu& GetMinMax() { return _kwndMinMax; }
    KMenu& GetSysMenu() { return _kwndSysMenu; }
    KTitleBar& GetTitleBar() { return _kwndTitleBar; }
    KScrollBar& GetVertScroll() { return _kwndVertScroll; }

protected :
    KWindow    _kwndClient;
    KScrollBar _kwndHorzScroll;
    KMenu      _kwndMenu;
    KMenu      _kwndMinMax;
    KMenu      _kwndSysMenu;
    KTitleBar  _kwndTitleBar;
    KScrollBar _kwndVertScroll;
};
#endif
