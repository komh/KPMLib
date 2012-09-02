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

#define IDSB_MYHORZ 200
#define IDSB_MYVERT 201

#define IDST_MYSTATIC   300

#define IDTB_MYTITLE    400

#define IDM_MYMENU1 500
#define IDM_MYMENU2 501

class KMyClientWindow : public KWindow
{
public :
    virtual MRESULT OnPaint();
    virtual MRESULT CmdSrcPushButton( ULONG ulCmd, bool fPointer );
    virtual MRESULT CmdSrcMenu( ULONG ulCmd, bool fPointer );
    virtual MRESULT BnClicked( ULONG id );
    virtual MRESULT HSbLineLeft( ULONG id, LONG lSlider );
    virtual MRESULT HSbLineRight( ULONG id, LONG lSlider );
    virtual MRESULT HSbPageLeft( ULONG id, LONG lSlider );
    virtual MRESULT HSbPageRight( ULONG id, LONG lSlider );
    virtual MRESULT VSbLineUp( ULONG id, LONG lSlider );
    virtual MRESULT VSbLineDown( ULONG id, LONG lSlider );
    virtual MRESULT VSbPageUp( ULONG id, LONG lSlider );
    virtual MRESULT VSbPageDown( ULONG id, LONG lSlider );
    virtual MRESULT OnTrackFrame( ULONG flTrackFlags );
};

MRESULT KMyClientWindow::OnPaint()
{
    HPS   hps;
    RECTL rcl;

    hps = BeginPaint( 0, &rcl);

    FillRect( hps, &rcl, SYSCLR_WINDOW );

    QueryWindowRect( &rcl );

    DrawText( hps, -1, PMLITERAL("This is KPMApp test program !!!"),
              &rcl, SYSCLR_WINDOWTEXT, SYSCLR_WINDOW,
              DT_CENTER | DT_VCENTER );

    EndPaint( hps );

    return 0;
}

MRESULT KMyClientWindow::CmdSrcPushButton( ULONG ulCmd,
                                           bool fPointer )
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

MRESULT KMyClientWindow::CmdSrcMenu( ULONG ulCmd, bool fPointer )
{
    if( ulCmd == IDM_MYMENU2 )
    {
        MessageBox( PMLITERAL("My menu item 2 selected"),
                    PMLITERAL("Client:CmdSrcMenu()"), MB_OK );

        return 0;
    }

    return KWindow::CmdSrcMenu( ulCmd, fPointer );
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
            kbtnRadio.SetCheck( !kbtnRadio.QueryCheck());
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

MRESULT KMyClientWindow::HSbLineLeft( ULONG id, LONG lSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText( PMLITERAL("SB_LINELEFT by OnHScroll()"));

    return 0;
}

MRESULT KMyClientWindow::HSbLineRight( ULONG id, LONG lSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText( PMLITERAL("SB_LINERIGHT by OnHScroll()"));

    return 0;
}

MRESULT KMyClientWindow::HSbPageLeft( ULONG id, LONG lSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText(PMLITERAL("SB_PAGELEFT by OnHScroll()"));

    return 0;
}

MRESULT KMyClientWindow::HSbPageRight( ULONG id, LONG lSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText(PMLITERAL("SB_PAGERIGHT by OnHScroll()"));

    return 0;
}

MRESULT KMyClientWindow::VSbLineUp( ULONG id, LONG lSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText(PMLITERAL("SB_LINEUP by OnVScroll()"));

    return 0;
}

MRESULT KMyClientWindow::VSbLineDown( ULONG id, LONG lSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText(PMLITERAL("SB_LINEDOWN by OnVScroll()"));

    return 0;
}

MRESULT KMyClientWindow::VSbPageUp( ULONG id, LONG lSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText(PMLITERAL("SB_PAGEUP by OnVScroll()"));

    return 0;
}

MRESULT KMyClientWindow::VSbPageDown( ULONG id, LONG lSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText(PMLITERAL("SB_PAGEDOWN by OnVScroll()"));

    return 0;
}

MRESULT KMyClientWindow::OnTrackFrame( ULONG ulTrackFlags )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText( PMLITERAL("Client: OnTrackFrame() called"));

    return KWindow::OnTrackFrame( ulTrackFlags );
}

class KMyFrameWindow : public KFrameWindow
{
public :
    virtual MRESULT SysCmdSrcMenu( ULONG ulCmd, bool fPointer );
};

MRESULT KMyFrameWindow::SysCmdSrcMenu( ULONG ulCmd, bool fPointer )
{
    if( ulCmd == IDM_MYMENU1 )
    {
        MessageBox( PMLITERAL("My menu item 1 selected"),
                    PMLITERAL("Frame: SysCmdSrcMenu()"), MB_OK );

        return 0;
    }

    // Must call this, otherwise other SYSCOMMANDs do not work
    return KFrameWindow::SysCmdSrcMenu( ulCmd, fPointer );
}

class KMyDialog : public KDialog
{
public :
    virtual MRESULT OnInitDlg( HWND hwndFocus, PVOID pCreate );
    virtual MRESULT CmdSrcPushButton( ULONG ulCmd, bool fPointer );

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

MRESULT KMyDialog::CmdSrcPushButton( ULONG ulCmd, bool fPointer )
{
    if( ulCmd == DID_CANCEL )
        DismissDlg( DID_CANCEL );

    return 0;
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
    KMyClientWindow kclient;
    kclient.RegisterClass( _hab, PMLITERAL( WC_KPMW ), CS_SIZEREDRAW,
                           sizeof( PVOID ));

    ULONG flFrameFlags = FCF_SYSMENU | FCF_TITLEBAR | FCF_MINMAX |
                         FCF_SIZEBORDER | FCF_SHELLPOSITION | FCF_TASKLIST;

    KMyFrameWindow kframe;
    kframe.CreateStdWindow( KWND_DESKTOP,           // parent window handle
                            WS_VISIBLE,             // frame window style
                            &flFrameFlags,          // window style
                            PMLITERAL("KPMApp"),    // window title
                            0,                      // default client style
                            0,                      // resource in exe file
                            ID_KPMW,                // frame window id
                            kclient                 // client window handle
                          );

    KButton kbtnPush;
    kbtnPush.CreateWindow( &kclient, PMLITERAL("My Push"),
                           WS_VISIBLE | BS_PUSHBUTTON,
                           10, 10, 100, 100, &kclient, KWND_TOP,
                           IDB_MYPUSH );

    KButton kbtnRadio;
    kbtnRadio.CreateWindow( &kclient, PMLITERAL("My Radio"),
                            WS_VISIBLE | BS_RADIOBUTTON,
                            110, 10, 100, 100, &kclient, KWND_TOP,
                            IDB_MYRADIO );

    KButton kbtnCheckBox;
    kbtnCheckBox.CreateWindow( &kclient, PMLITERAL("My CheckBox"),
                               WS_VISIBLE | BS_CHECKBOX,
                               210, 10, 100, 100, &kclient, KWND_TOP,
                               IDB_MYCHECKBOX );

    KButton kbtn3State;
    kbtn3State.CreateWindow( &kclient, PMLITERAL("My 3-State"),
                             WS_VISIBLE | BS_3STATE,
                             310, 10, 100, 100, &kclient, KWND_TOP,
                             IDB_MY3STATE );

    KScrollBar ksbHScroll;
    ksbHScroll.CreateWindow( &kclient, PMLITERAL("HScrollBar"),
                             WS_VISIBLE | SBS_HORZ,
                             100, 150, 200, 30, &kclient, KWND_TOP,
                             IDSB_MYHORZ );
    ksbHScroll.SetScrollBar( 50, 0, 100 );

    KScrollBar ksbVScroll;
    ksbVScroll.CreateWindow( &kclient, PMLITERAL("VScrollBar"),
                             WS_VISIBLE | SBS_VERT,
                             400, 150, 30, 200, &kclient, KWND_TOP,
                             IDSB_MYVERT );
    ksbVScroll.SetScrollBar( 50, 0, 100 );

    KStaticText kst;
    kst.CreateWindow( &kclient, PMLITERAL("My Static Text"),
                      WS_VISIBLE | SS_TEXT | SS_AUTOSIZE,
                      0, 300, 400, -1, &kclient, KWND_TOP, IDST_MYSTATIC );

    KTitleBar ktb;
    ktb.CreateWindow( &kclient, PMLITERAL("My Title Bar"),
                      WS_VISIBLE,
                      100, 200, 200, 20, &kclient, KWND_TOP, IDTB_MYTITLE );
    ktb.SetHilite( true );

    MENUITEM mi;
    kframe.GetSysMenu().QueryItem( SC_SYSMENU, false, &mi );

    KMenu kmSys;
    kmSys.SetHWND( mi.hwndSubMenu );
    kmSys.QueryItem( SC_CLOSE, false, &mi );

    mi.iPosition   += 2;
    mi.afStyle     = MIS_TEXT | MIS_SYSCOMMAND;
    mi.afAttribute = 0;
    mi.id          = IDM_MYMENU1;
    mi.hwndSubMenu = 0;
    mi.hItem       = 0;
    kmSys.InsertItem( &mi, PMLITERAL("My item1"));

    mi.iPosition++;
    mi.afStyle     = MIS_TEXT;
    mi.afAttribute = 0;
    mi.id          = IDM_MYMENU2;
    mi.hwndSubMenu = 0;
    mi.hItem       = 0;
    kmSys.InsertItem( &mi, PMLITERAL("My item2"));

    mi.iPosition++;
    mi.afStyle = MIS_SEPARATOR;
    mi.afAttribute = 0;
    mi.id = 0;
    mi.hwndSubMenu = NULLHANDLE;
    mi.hItem = 0;
    kmSys.InsertItem( &mi, 0 );

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

