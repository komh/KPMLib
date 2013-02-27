/*
    KPMLib, C++ encapsulation class library for OS/2 PM
    Copyright (C) 2012-2013 by KO Myung-Hun <komh@chollian.net>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software Foundation,
    Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
*/

#define INCL_WIN
#include <os2.h>

#include <string>

#include <cstdlib>

#include "KPMLib.h"

#include "kpmw.h"

#define IDB_MYPUSH          100
#define IDB_MYRADIO         101
#define IDB_MYCHECKBOX      102
#define IDB_MY3STATE        103
#define IDB_MYOPEN          104

#define IDSB_MYHORZ 200
#define IDSB_MYVERT 201

#define IDST_MYSTATIC   300

#define IDTB_MYTITLE    400

#define IDM_MYMENU1 500
#define IDM_MYMENU2 501

#define IDEF_MYEF 600

#define IDLB_MYLB 700

#define IDCB_MYCB 800

#define IDCNR_MYCNR 900

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
    _kstStatus.SetWindowText("I'm fine");

    WindowFromID( IDT_KPMW_SPEED, _kstSpeed );
    _kstSpeed.SetWindowText("Very fast");

    WindowFromID( DID_CANCEL, _kbtCancel );
    _kbtCancel.SetWindowText("Exit");

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
    virtual MRESULT EnChange( USHORT id );
    virtual MRESULT LnEnter( USHORT Id );
    virtual MRESULT CbnEfChange( USHORT id );
    virtual MRESULT CnEnter( USHORT id, PNOTIFYRECORDENTER pnre );
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
    KWindowPS kwps;

    RECTL rcl;

    kwps.BeginPaint( this, 0, &rcl);

    kwps.FillRect( &rcl, SYSCLR_WINDOW );

    QueryWindowRect( &rcl );

    kwps.DrawText( -1, "This is KPMApp test program !!!",
                   &rcl, SYSCLR_WINDOWTEXT, SYSCLR_WINDOW,
                   DT_CENTER | DT_VCENTER );

    kwps.EndPaint();

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
            break;
        }

        case IDB_MYOPEN :
        {
            KFileDlg kfd;

            kfd.Clear();
            kfd.FileDlg( KWND_DESKTOP, this );
            if( kfd.GetReturn() == DID_OK )
            {
                MessageBox( kfd.GetFullFile(),
                            "Your selected file", MB_OK );
            }
            break;
        }
    }

    return 0;
}

MRESULT KMyClientWindow::CmdSrcMenu( USHORT usCmd, bool fPointer )
{
    if( usCmd == IDM_MYMENU2 )
    {
        MessageBox( "My menu item 2 selected",
                    "Client:CmdSrcMenu()", MB_OK );

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

        case IDEF_MYEF :
            if ( usNotifyCode == EN_CHANGE )
                return EnChange( id );
            break;

        case IDLB_MYLB :
            if( usNotifyCode == LN_ENTER )
                return LnEnter( id );
            break;

        case IDCB_MYCB :
            if( usNotifyCode == CBN_EFCHANGE )
                return CbnEfChange( id );
            break;

        case IDCNR_MYCNR :
            if( usNotifyCode == CN_ENTER )
                return CnEnter( id, reinterpret_cast< PNOTIFYRECORDENTER >
                                        ( ulControlSpec ));
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
            MessageBox("My Radio button clicked",
                       "BnClicked()", MB_OK );

            KButton kbtnRadio;
            WindowFromID( id, kbtnRadio );
            kbtnRadio.SetCheck( !kbtnRadio.QueryCheck());
            break;
        }

        case IDB_MYCHECKBOX :
            MessageBox("My CheckBox button clicked",
                       "BnClicked()", MB_OK );
            break;

        case IDB_MY3STATE :
            MessageBox("My 3State CheckBox button clicked",
                       "BnClicked()", MB_OK );
            break;
    }

    return 0;
}

MRESULT KMyClientWindow::EnChange( USHORT id )
{
    switch( id )
    {
        case IDEF_MYEF :
        {
            string strBuf;

            KEntryField kef;

            WindowFromID( id, kef );
            kef.QueryWindowText( strBuf );

            KStaticText kst;
            WindowFromID( IDST_MYSTATIC, kst );
            kst.SetWindowText( strBuf );
            break;
        }
    }

    return 0;
}

MRESULT KMyClientWindow::LnEnter( USHORT id )
{
    switch( id )
    {
        case IDLB_MYLB :
        {
            string strBuf;

            KListBox klb;

            WindowFromID( id, klb );
            klb.QueryItemText( klb.QuerySelection( LIT_FIRST ), strBuf );

            KStaticText kst;
            WindowFromID( IDST_MYSTATIC, kst );
            kst.SetWindowText( strBuf );
            break;
        }
    }

    return 0;
}

MRESULT KMyClientWindow::CbnEfChange( USHORT id )
{
    switch( id )
    {
        case IDCB_MYCB :
        {
            string strBuf;

            KComboBox kcb;

            WindowFromID( id, kcb );
            kcb.QueryWindowText( strBuf );

            KStaticText kst;
            WindowFromID( IDST_MYSTATIC, kst );
            kst.SetWindowText( strBuf );
            break;
        }
    }

    return 0;
}

MRESULT KMyClientWindow::CnEnter( USHORT id, PNOTIFYRECORDENTER pnre )
{

    if( !pnre->pRecord )
        return 0;

    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText( pnre->pRecord->pszIcon );

    return 0;

}

MRESULT KMyClientWindow::HSbLineLeft( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText("SB_LINELEFT by OnHScroll()");

    return 0;
}

MRESULT KMyClientWindow::HSbLineRight( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText("SB_LINERIGHT by OnHScroll()");

    return 0;
}

MRESULT KMyClientWindow::HSbPageLeft( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText("SB_PAGELEFT by OnHScroll()");

    return 0;
}

MRESULT KMyClientWindow::HSbPageRight( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText("SB_PAGERIGHT by OnHScroll()");

    return 0;
}

MRESULT KMyClientWindow::VSbLineUp( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText("SB_LINEUP by OnVScroll()");

    return 0;
}

MRESULT KMyClientWindow::VSbLineDown( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText("SB_LINEDOWN by OnVScroll()");

    return 0;
}

MRESULT KMyClientWindow::VSbPageUp( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText("SB_PAGEUP by OnVScroll()");

    return 0;
}

MRESULT KMyClientWindow::VSbPageDown( USHORT id, SHORT sSlider )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText("SB_PAGEDOWN by OnVScroll()");

    return 0;
}

MRESULT KMyClientWindow::OnTrackFrame( USHORT usTrackFlags )
{
    KStaticText kst;

    WindowFromID( IDST_MYSTATIC, kst );
    kst.SetWindowText("Client: OnTrackFrame() called");

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
        MessageBox("My menu item 1 selected",
                   "Frame: SysCmdSrcMenu()", MB_OK );

        return 0;
    }

    // Must call this, otherwise other SYSCOMMANDs do not work
    return KFrameWindow::SysCmdSrcMenu( usCmd, fPointer );
}

class KMyPMApp : public KPMApp
{
public :
    virtual int Run();
};

int KMyPMApp::Run()
{
    KMyClientWindow kclient;
    kclient.RegisterClass( _hab, WC_KPMW, CS_SIZEREDRAW,
                           sizeof( PVOID ));

    ULONG flFrameFlags = FCF_SYSMENU | FCF_TITLEBAR | FCF_MINMAX |
                         FCF_SIZEBORDER | FCF_SHELLPOSITION | FCF_TASKLIST;

    KMyFrameWindow kframe;
    kframe.CreateStdWindow( KWND_DESKTOP,           // parent window handle
                            WS_VISIBLE,             // frame window style
                            &flFrameFlags,          // window style
                            "KPMApp",               // window title
                            0,                      // default client style
                            0,                      // resource in exe file
                            ID_KPMW,                // frame window id
                            kclient                 // client window handle
                          );

    KButton kbtnPush;
    kbtnPush.CreateWindow( &kclient, "My Push",
                           WS_VISIBLE | BS_PUSHBUTTON,
                           10, 10, 100, 100, &kclient, KWND_TOP,
                           IDB_MYPUSH );

    KButton kbtnRadio;
    kbtnRadio.CreateWindow( &kclient, "My Radio",
                            WS_VISIBLE | BS_RADIOBUTTON,
                            110, 10, 100, 100, &kclient, KWND_TOP,
                            IDB_MYRADIO );

    KButton kbtnCheckBox;
    kbtnCheckBox.CreateWindow( &kclient, "My CheckBox",
                               WS_VISIBLE | BS_CHECKBOX,
                               210, 10, 100, 100, &kclient, KWND_TOP,
                               IDB_MYCHECKBOX );

    KButton kbtn3State;
    kbtn3State.CreateWindow( &kclient, "My 3-State",
                             WS_VISIBLE | BS_3STATE,
                             310, 10, 100, 100, &kclient, KWND_TOP,
                             IDB_MY3STATE );

    KButton kbtnOpen;
    kbtnOpen.CreateWindow( &kclient, "My Open",
                           WS_VISIBLE | BS_PUSHBUTTON,
                           410, 10, 100, 100, &kclient, KWND_TOP,
                           IDB_MYOPEN );

    KScrollBar ksbHScroll;
    ksbHScroll.CreateWindow( &kclient, "HScrollBar",
                             WS_VISIBLE | SBS_HORZ,
                             100, 150, 200, 30, &kclient, KWND_TOP,
                             IDSB_MYHORZ );
    ksbHScroll.SetScrollBar( 50, 0, 100 );

    KScrollBar ksbVScroll;
    ksbVScroll.CreateWindow( &kclient, "VScrollBar",
                             WS_VISIBLE | SBS_VERT,
                             400, 150, 30, 200, &kclient, KWND_TOP,
                             IDSB_MYVERT );
    ksbVScroll.SetScrollBar( 50, 0, 100 );

    KStaticText kst;
    kst.CreateWindow( &kclient, "My Static Text",
                      WS_VISIBLE | SS_TEXT | SS_AUTOSIZE,
                      0, 300, 400, -1, &kclient, KWND_TOP, IDST_MYSTATIC );

    KTitleBar ktb;
    ktb.CreateWindow( &kclient, "My Title Bar",
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
    kmSys.InsertItem( &mi, "My item1");

    mi.iPosition++;
    mi.afStyle     = MIS_TEXT;
    mi.afAttribute = 0;
    mi.id          = IDM_MYMENU2;
    mi.hwndSubMenu = 0;
    mi.hItem       = 0;
    kmSys.InsertItem( &mi, "My item2");

    mi.iPosition++;
    mi.afStyle = MIS_SEPARATOR;
    mi.afAttribute = 0;
    mi.id = 0;
    mi.hwndSubMenu = NULLHANDLE;
    mi.hItem = 0;
    kmSys.InsertItem( &mi, "");

    KEntryField kef;
    kef.CreateWindow( &kclient, "My Entry Field",
                      WS_VISIBLE | ES_CENTER | ES_MARGIN,
                      500, 150, 100, 30, &kclient, KWND_TOP,
                      IDEF_MYEF );

    KListBox klb;
    klb.CreateWindow( &kclient, "My List Box",
                      WS_VISIBLE,
                      500, 200, 100, 150, &kclient, KWND_TOP,
                      IDLB_MYLB );

#if 0
    klb.InsertItem( LIT_END, "Item 1");
    klb.InsertItem( LIT_END, "Item 2");
#else
    LBOXINFO lbi;

    lbi.lItemIndex  = LIT_END;
    lbi.ulItemCount = 2;

    vector< string > vsItem;

    vsItem.push_back("Item 1");
    vsItem.push_back("Item 2");
    klb.InsertMultiItems( &lbi, vsItem );
#endif

    KComboBox kcb;
    kcb.CreateWindow( &kclient, "My Combox Box",
                      WS_VISIBLE | CBS_DROPDOWN,
                      100, 300, 200, 100, &kclient, KWND_TOP,
                      IDCB_MYCB );
    kcb.LmInsertItem( LIT_END, "CB Item 1");
    kcb.LmInsertItem( LIT_END, "CB Item 2");

    KContainer< MINIRECORDCORE, true > kcnr;
    kcnr.CreateWindow( &kclient, "My Container",
                       WS_VISIBLE | CCS_AUTOPOSITION | CCS_READONLY,
                       510, 10, 150, 100, &kclient, KWND_TOP,
                       IDCNR_MYCNR );

    CNRINFO ci;
    ci.flWindowAttr = CV_ICON;
    kcnr.SetCnrInfo( &ci, CMA_FLWINDOWATTR );

    PMINIRECORDCORE prec;
    RECORDINSERT ri;

    prec = kcnr.AllocRecord( 1 );
    prec->hptrIcon = WinQuerySysPointer( HWND_DESKTOP, SPTR_APPICON, FALSE );
    prec->pszIcon = CSTR2PSZ("Item1");

    ri.cb                = sizeof( RECORDINSERT );
    ri.pRecordOrder      = TOPRECC( CMA_END );
    ri.pRecordParent     = 0;
    ri.zOrder            = static_cast< USHORT >( CMA_TOP );
    ri.fInvalidateRecord = FALSE;
    ri.cRecordsInsert    = 1;
    kcnr.InsertRecord( prec, &ri );

    prec = kcnr.AllocRecord( 1 );
    prec->hptrIcon = WinQuerySysPointer( HWND_DESKTOP, SPTR_APPICON, FALSE );
    prec->pszIcon = CSTR2PSZ("Item2");

    ri.cb                = sizeof( RECORDINSERT );
    ri.pRecordOrder      = TOPRECC( CMA_END );
    ri.pRecordParent     = 0;
    ri.zOrder            = static_cast< USHORT >( CMA_TOP );
    ri.fInvalidateRecord = FALSE;
    ri.cRecordsInsert    = 1;
    kcnr.InsertRecord( prec, &ri );

    KPMApp::Run();

    PMINIRECORDCORE prc, prcNext;

    prc = kcnr.QueryRecord( 0, CMA_FIRST, CMA_ITEMORDER );
    for(; prc; prc = prcNext )
    {
        prcNext = kcnr.QueryRecord( prc, CMA_NEXT, CMA_ITEMORDER );

        kcnr.RemoveRecord( &prc, 1, CMA_FREE );
    }

    kframe.DestroyWindow();

    return 0;
}

int main()
{
    KMyPMApp app;

    return app.Run();
}

