#define INCL_WIN
#include <os2.h>

#include <stdlib.h>
#include <string.h>

#include "KPMLib.h"

#include "kpmw.h"

class KMyClientWindow : public KWindow
{
public :
    virtual MRESULT OnPaint();
};

MRESULT KMyClientWindow::OnPaint()
{
    HPS   hps;
    RECTL rcl;

    hps = WinBeginPaint( _hwnd, 0, &rcl);

    WinFillRect( hps, &rcl, SYSCLR_WINDOW );

    WinQueryWindowRect( _hwnd, &rcl );

    WinDrawText(
        hps,
        -1,
        PMLITERAL("This is KPMApp test program !!!"),
        &rcl,
        SYSCLR_WINDOWTEXT,
        SYSCLR_WINDOW,
        DT_CENTER | DT_VCENTER
    );

    WinEndPaint( hps );

    return 0;
}

class KMyDialog : public KDialog
{
public :
    MRESULT OnInitDlg( HWND hwndFocus, PVOID pCreate );

private :
    KStaticText _kstStatus;
    KButton     _kbtCancel;
};

MRESULT KMyDialog::OnInitDlg( HWND hwndFocus, PVOID pCreate )
{
    WindowFromID( IDT_KPMW_STATUS, _kstStatus );
    _kstStatus.SetWindowText( PMLITERAL("I'm fine"));

    WindowFromID( DID_CANCEL, _kbtCancel );
    _kbtCancel.SetWindowText( PMLITERAL("Exit"));

    return FALSE;
}

class KMyPMApp : public KPMApp
{
public :
    virtual void Run();
};

void KMyPMApp::Run()
{
#if 1
    KFrameWindow    kframe;
    KMyClientWindow kclient;

    kclient.RegisterClass( _hab, PMLITERAL( WC_KPMW ), CS_SIZEREDRAW,
                           sizeof( PVOID ));

    ULONG flFrameFlags = FCF_SYSMENU | FCF_TITLEBAR | FCF_MINMAX |
                         FCF_SIZEBORDER | FCF_SHELLPOSITION | FCF_TASKLIST;

    kframe.CreateStdWindow( KWND_DESKTOP,           // parent window handle
                            WS_VISIBLE,             // frame window style
                            &flFrameFlags,          // window style
                            PMLITERAL("KPMApp"),    // window title
                            0,                      // default client style
                            0,                      // resource in exe file
                            ID_KPMW,                // frame window id
                            kclient                 // client window handle
                          );

    KPMApp::Run();

    kframe.DestroyWindow();
#else
    KMyDialog kdlg;

    kdlg.LoadDlg( KWND_DESKTOP, 0, 0, ID_KPMW, 0 );

    kdlg.ProcessDlg();

    kdlg.DestroyWindow();
#endif
}

int main()
{
    KMyPMApp app;

    app.Run();

    return 0;
}

