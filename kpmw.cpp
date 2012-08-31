#define INCL_WIN
#include <os2.h>

#include <stdlib.h>
#include <string.h>

#include "KPMLib.h"

#include "kpmw.h"

#define IDB_MYPUSH          100
#define IDB_MYRADIO         101
#define IDB_MYCHECKBOX      102
#define IDB_MY3STATE        103

class KMyClientWindow : public KWindow
{
public :
    virtual MRESULT OnPaint();
    virtual MRESULT CmdSrcPushButton( ULONG ulCmd, ULONG ulPointer );
    virtual MRESULT BnClicked( ULONG id );
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

MRESULT KMyClientWindow::CmdSrcPushButton( ULONG ulCmd,
                                                  ULONG ulPointer )
{
    switch( ulCmd )
    {
        case IDB_MYPUSH :
            MessageBox( PMLITERAL("My Push button clicked"),
                        PMLITERAL("CmdSrcPushButton()"), MB_OK );
            return 0;

        case IDB_MY3STATE :
            MessageBox( PMLITERAL("My 3State CheckBox clicked"),
                        PMLITERAL("CmdSrcPushButton()"), MB_OK );
            return 0;
    }

    return 0;
}

MRESULT KMyClientWindow::BnClicked( ULONG id )
{
    switch( id )
    {
        case IDB_MYRADIO :
        {
            MessageBox( PMLITERAL("My Radio button clicked"),
                        PMLITERAL("BnClicked()"), MB_OK );

            KButton kbtnRadio;
            WindowFromID( id, kbtnRadio );
            kbtnRadio.SetCheck( static_cast< KButton::CheckState >
                                    ( !kbtnRadio.QueryCheck()));
            break;
        }

        case IDB_MYCHECKBOX :
            MessageBox( PMLITERAL("My CheckBox button clicked"),
                        PMLITERAL("BnClicked()"), MB_OK );
            break;

        case IDB_MY3STATE :
            MessageBox( PMLITERAL("My 3State CheckBox button clicked"),
                        PMLITERAL("BnClicked()"), MB_OK );
            break;
    }

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

#define USE_FRAMEWINDOW

void KMyPMApp::Run()
{
#ifdef USE_FRAMEWINDOW
    KFrameWindow    kframe;
    KMyClientWindow kclient;
    KButton         kbtnPush;
    KButton         kbtnRadio;
    KButton         kbtnCheckBox;
    KButton         kbtn3State;

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

    kbtnPush.CreateWindow( &kclient, PMLITERAL("My Push"),
                           WS_VISIBLE | BS_PUSHBUTTON,
                           10, 10, 100, 100, &kclient, KWND_TOP,
                           IDB_MYPUSH );

    kbtnRadio.CreateWindow( &kclient, PMLITERAL("My Radio"),
                            WS_VISIBLE | BS_RADIOBUTTON,
                            110, 10, 100, 100, &kclient, KWND_TOP,
                            IDB_MYRADIO );

    kbtnCheckBox.CreateWindow( &kclient, PMLITERAL("My CheckBox"),
                            WS_VISIBLE | BS_CHECKBOX,
                            210, 10, 100, 100, &kclient, KWND_TOP,
                            IDB_MYCHECKBOX );

    kbtn3State.CreateWindow( &kclient, PMLITERAL("My 3-State"),
                             WS_VISIBLE | BS_3STATE,
                             310, 10, 100, 100, &kclient, KWND_TOP,
                             IDB_MY3STATE );

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

