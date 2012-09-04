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

class KMyDialog : public KDialog
{
protected :
    virtual MRESULT OnInitDlg( HWND hwndFocus, PVOID pCreate );
    virtual MRESULT CmdSrcPushButton( USHORT usCmd, bool fPointer );

private :
    KStaticText _kstStatus;
    KStaticText _kstSpeed;
    KButton     _kbtCancel;
};

MRESULT KMyDialog::OnInitDlg( HWND hwndFocus, PVOID pCreate )
{
    WindowFromID( IDT_KPMW_STATUS, _kstStatus );
    _kstStatus.SetWindowText( PMLITERAL("I'm fine"));

    WindowFromID( IDT_KPMW_SPEED, _kstSpeed );
    _kstSpeed.SetWindowText( PMLITERAL("Very fast"));

    WindowFromID( DID_CANCEL, _kbtCancel );
    _kbtCancel.SetWindowText( PMLITERAL("Exit"));

    return FALSE;
}

MRESULT KMyDialog::CmdSrcPushButton( USHORT usCmd, bool fPointer )
{
    if( usCmd == DID_CANCEL )
        DismissDlg( DID_CANCEL );

    return 0;
}

class KMyClientWindow : public KWindow
{
protected :
    virtual MRESULT OnPaint();
    virtual MRESULT CmdSrcPushButton( USHORT usCmd, bool fPointer );
    virtual MRESULT CmdSrcMenu( USHORT usCmd, bool fPointer );
    virtual MRESULT OnControl( USHORT id, USHORT usNotifyCode,
                               ULONG ulControlSpec );
    virtual MRESULT BnClicked( USHORT id );
    virtual MRESULT HSbLineLeft( USHORT id, SHORT sSlider );
    virtual MRESULT HSbLineRight( USHORT id, SHORT sSlider );
    virtual MRESULT HSbPageLeft( USHORT id, SHORT sSlider );
    virtual MRESULT HSbPageRight( USHORT id, SHORT sSlider );
    virtual MRESULT VSbLineUp( USHORT id, SHORT sSlider );
    virtual MRESULT VSbLineDown( USHORT id, SHORT sSlider );
    virtual MRESULT VSbPageUp( USHORT id, SHORT sSlider );
    virtual MRESULT VSbPageDown( USHORT id, SHORT sSlider );
    virtual MRESULT OnTrackFrame( USHORT flTrackFlags );
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

MRESULT KMyClientWindow::CmdSrcPushButton( USHORT usCmd,
                                           bool fPointer )
{
    switch( usCmd )
    {
        case IDB_MYPUSH :
        {
            KMyDialog kdlg;
            kdlg.LoadDlg( KWND_DESKTOP, this, 0, ID_KPMW );
            kdlg.ProcessDlg();
            kdlg.DestroyWindow();
        }
    }

    return 0;
}

MRESULT KMyClientWindow::CmdSrcMenu( USHORT usCmd, bool fPointer )
{
    if( usCmd == IDM_MYMENU2 )
    {
        MessageBox( PMLITERAL("My menu item 2 selected"),
                    PMLITERAL("Client:CmdSrcMenu()"), MB_OK );

        return 0;
    }

    return KWindow::CmdSrcMenu( usCmd, fPointer );
}

MRESULT KMyClientWindow::OnControl( USHORT id, USHORT usNotifyCode,
                                    ULONG ulControlSpec )
{
    switch( id )
    {
        case IDB_MYRADIO :
        case IDB_MYCHECKBOX :
        case IDB_MY3STATE :
            if( usNotifyCode == BN_CLICKED )
                return BnClicked( id );
            break;
    }

    return 0;
}

MRESULT KMyClientWindow::BnClicked( USHORT id )
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

MRESULT KMyClientWindow::HSbLineLeft( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText( PMLITERAL("SB_LINELEFT by OnHScroll()"));

    return 0;
}

MRESULT KMyClientWindow::HSbLineRight( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText( PMLITERAL("SB_LINERIGHT by OnHScroll()"));

    return 0;
}

MRESULT KMyClientWindow::HSbPageLeft( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText( PMLITERAL("SB_PAGELEFT by OnHScroll()"));

    return 0;
}

MRESULT KMyClientWindow::HSbPageRight( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText( PMLITERAL("SB_PAGERIGHT by OnHScroll()"));

    return 0;
}

MRESULT KMyClientWindow::VSbLineUp( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText( PMLITERAL("SB_LINEUP by OnVScroll()"));

    return 0;
}

MRESULT KMyClientWindow::VSbLineDown( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText( PMLITERAL("SB_LINEDOWN by OnVScroll()"));

    return 0;
}

MRESULT KMyClientWindow::VSbPageUp( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText( PMLITERAL("SB_PAGEUP by OnVScroll()"));

    return 0;
}

MRESULT KMyClientWindow::VSbPageDown( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText( PMLITERAL("SB_PAGEDOWN by OnVScroll()"));

    return 0;
}

MRESULT KMyClientWindow::OnTrackFrame( USHORT usTrackFlags )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText( PMLITERAL("Client: OnTrackFrame() called"));

    return KWindow::OnTrackFrame( usTrackFlags );
}

class KMyFrameWindow : public KFrameWindow
{
protected :
    virtual MRESULT SysCmdSrcMenu( USHORT usCmd, bool fPointer );
};

MRESULT KMyFrameWindow::SysCmdSrcMenu( USHORT usCmd, bool fPointer )
{
    if( usCmd == IDM_MYMENU1 )
    {
        MessageBox( PMLITERAL("My menu item 1 selected"),
                    PMLITERAL("Frame: SysCmdSrcMenu()"), MB_OK );

        return 0;
    }

    // Must call this, otherwise other SYSCOMMANDs do not work
    return KFrameWindow::SysCmdSrcMenu( usCmd, fPointer );
}

class KMyPMApp : public KPMApp
{
public :
    virtual void Run();
};

void KMyPMApp::Run()
{
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
}

int main()
{
    KMyPMApp app;

    app.Run();

    return 0;
}

