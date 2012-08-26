#ifndef KFRAMEWINDOW_H
#define KFRAMEWINDOW_H

#define INCL_WIN
#include <os2.h>

#include "KWindow.h"

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

protected :
    KWindow _kwndClient;
};
#endif
