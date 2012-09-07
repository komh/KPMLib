#define INCL_WIN
#include <os2.h>

#include <cstdlib>
#include <cstring>

#include "KWindow.h"

struct CreateParams
{
    PVOID    pPresParams;
    KWindow* pkwnd;
};

HWND pkwnd2hwnd( const KWindow* kwnd )
{
    if( kwnd == 0 )           return NULLHANDLE;
    if( kwnd == KWND_DESKTOP) return HWND_DESKTOP;
    if( kwnd == KWND_OBJECT)  return HWND_OBJECT;
    if( kwnd == KWND_TOP )    return HWND_TOP;
    if( kwnd == KWND_BOTTOM ) return HWND_BOTTOM;

    return kwnd->_hwnd;
}

KWindow::KWindow()
{
    _hwnd          = 0;
    _pcszClassName = 0;
    _pfnwpOldProc  = 0;
    _fRegistered   = false;
}

KWindow::~KWindow()
{
    if( HIUSHORT( _pcszClassName ) != 0xFFFF )
        free( reinterpret_cast< void * >( const_cast< PSZ >
                                            ( _pcszClassName )));

    if( _pfnwpOldProc )
        WinSubclassWindow( _hwnd, _pfnwpOldProc );

    if( WinQueryWindowPtr( _hwnd, 0 ) == this )
        WinSetWindowPtr( _hwnd, 0, 0 );
}

bool KWindow::CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                            ULONG flStyle, LONG x, LONG y, LONG cx, LONG cy,
                            const KWindow* pkwndO, const KWindow* pkwndS,
                            ULONG id, PVOID pCtlData, PVOID pPresParams )
{
    HWND hwndP = pkwnd2hwnd( pkwndP );
    HWND hwndO = pkwnd2hwnd( pkwndO );
    HWND hwndS = pkwnd2hwnd( pkwndS );
    HWND hwnd;

    CreateParams cp = { pPresParams, this };

    hwnd = WinCreateWindow( hwndP, _pcszClassName, pcszName,flStyle,
                            x, y, cx, cy, hwndO, hwndS,
                            id, pCtlData, &cp );

    // for the pre-defined class
    SetHWND( hwnd );

    return hwnd;
}

bool KWindow::DestroyWindow()
{
    if( WinDestroyWindow( _hwnd ))
    {
        _hwnd = 0;

        if( HIUSHORT( _pcszClassName ) != 0xFFFF )
            free( reinterpret_cast< void * >( const_cast< PSZ >
                                                ( _pcszClassName )));
        _pcszClassName = 0;
        _pfnwpOldProc  = 0;

        return true;
    }

    return false;
}

bool KWindow::RegisterClass( HAB hab, PCSZ pcszClassName, ULONG flStyle,
                             ULONG cbWindowData )
{
    _pcszClassName = reinterpret_cast< PCSZ >(
                        strdup( reinterpret_cast< const char * >
                                    ( pcszClassName )));

    _fRegistered = true;

    return WinRegisterClass( hab, pcszClassName, WndProc, flStyle,
                             sizeof( PVOID ) + cbWindowData );
}

bool KWindow::WindowFromID( ULONG id, KWindow& kwnd )
{
    HWND     hwnd;

    hwnd = WinWindowFromID( _hwnd, id );
    if( !hwnd )
        return false;

    kwnd.SetHWND( hwnd );

    return true;
}

void KWindow::SetHWND( HWND hwnd )
{
    _hwnd = hwnd;

    if( !hwnd )
        return;

    if( !WinQueryWindowPtr( hwnd, 0 ))
    {
        WinSetWindowPtr( hwnd, 0, this );

        if( !_fRegistered )
            _pfnwpOldProc = WinSubclassWindow( hwnd, WndProc );
    }

    // Already allocated ?
    if( _pcszClassName )
        return;

    UCHAR szClassName[ 512 ];
    WinQueryClassName( hwnd, sizeof( szClassName ), szClassName );
    _pcszClassName = reinterpret_cast< PCSZ >
                            ( strdup( reinterpret_cast< const char * >
                                        ( szClassName )));
}

void KWindow::SetClassName( PCSZ pcszClassName )
{
    _fRegistered = false;

    // pre-defined class such as WC_FRAME ?
    if( HIUSHORT( pcszClassName ) == 0xFFFF )
        _pcszClassName = pcszClassName;
    else
        _pcszClassName = reinterpret_cast< PCSZ >(
                            strdup( reinterpret_cast< const char * >
                                        ( pcszClassName )));
}

MRESULT EXPENTRY KWindow::WndProc( HWND hwnd, ULONG msg, MPARAM mp1,
                                   MPARAM mp2 )
{
    KWindow* pkwnd = reinterpret_cast< KWindow* >
                        ( WinQueryWindowPtr( hwnd, 0 ));

    if( msg == WM_CREATE )
    {
        PCREATESTRUCT pcs = reinterpret_cast< PCREATESTRUCT >( mp2 );
        CreateParams* pcp = reinterpret_cast< CreateParams* >
                                ( pcs->pPresParams );

        pcs->pPresParams = pcp->pPresParams;

        pkwnd = pcp->pkwnd;
        pkwnd->SetHWND( hwnd );
    }

    return pkwnd->KWndProc( msg, mp1, mp2 );
}

MRESULT KWindow::KWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch( msg )
    {
        case PL_ALTERED :
            return OnPlAltered( LONGFROMMP( mp1 ), LONGFROMMP( mp2 ));

        case WM_ACTIVATE :
            return OnActivate( SHORT1FROMMP( mp1 ), HWNDFROMMP( mp2 ));

        case WM_APPTERMINATENOTIFY :
            return OnAppTerminateNotify( LONGFROMMP( mp1 ), LONGFROMMP( mp2 ));

        case WM_ADJUSTWINDOWPOS :
            return OnAdjustWindowPos( reinterpret_cast< PSWP >( mp1 ),
                                      LONGFROMMP( mp2 ));

        case WM_BEGINDRAG :
            return OnBeginDrag( *reinterpret_cast< PPOINTS >( &mp1 ),
                                SHORT1FROMMP( mp2 ));

        case WM_BEGINSELECT :
            return OnBeginSelect( *reinterpret_cast< PPOINTS >( &mp1 ),
                                  SHORT1FROMMP( mp2 ));

        case WM_BUTTON1CLICK :
            return OnButton1Click( *reinterpret_cast< PPOINTS >( &mp1 ),
                                   SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_BUTTON1DBLCLK:
            return OnButton1DblClk( *reinterpret_cast< PPOINTS >( &mp1 ),
                                    SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_BUTTON1DOWN :
            return OnButton1Down( *reinterpret_cast< PPOINTS >( &mp1 ),
                                  SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_BUTTON1MOTIONEND :
            return OnButton1MotionEnd( *reinterpret_cast< PPOINTS >( &mp1 ),
                                       SHORT1FROMMP( mp2 ));

        case WM_BUTTON1MOTIONSTART :
            return OnButton1MotionStart( *reinterpret_cast< PPOINTS >( &mp1 ),
                                         SHORT1FROMMP( mp2 ));

        case WM_BUTTON1UP :
            return OnButton1Up( *reinterpret_cast< PPOINTS >( &mp1 ),
                                SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_BUTTON2CLICK :
            return OnButton1Click( *reinterpret_cast< PPOINTS >( &mp1 ),
                                   SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_BUTTON2DBLCLK:
            return OnButton1DblClk( *reinterpret_cast< PPOINTS >( &mp1 ),
                                    SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_BUTTON2DOWN :
            return OnButton1Down( *reinterpret_cast< PPOINTS >( &mp1 ),
                                  SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_BUTTON2MOTIONEND :
            return OnButton1MotionEnd( *reinterpret_cast< PPOINTS >( &mp1 ),
                                       SHORT1FROMMP( mp2 ));

        case WM_BUTTON2MOTIONSTART :
            return OnButton1MotionStart( *reinterpret_cast< PPOINTS >( &mp1 ),
                                         SHORT1FROMMP( mp2 ));

        case WM_BUTTON2UP :
            return OnButton1Up( *reinterpret_cast< PPOINTS >( &mp1 ),
                                SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_BUTTON3CLICK :
            return OnButton1Click( *reinterpret_cast< PPOINTS >( &mp1 ),
                                   SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_BUTTON3DBLCLK:
            return OnButton1DblClk( *reinterpret_cast< PPOINTS >( &mp1 ),
                                    SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_BUTTON3DOWN :
            return OnButton1Down( *reinterpret_cast< PPOINTS >( &mp1 ),
                                  SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_BUTTON3MOTIONEND :
            return OnButton1MotionEnd( *reinterpret_cast< PPOINTS >( &mp1 ),
                                       SHORT1FROMMP( mp2 ));

        case WM_BUTTON3MOTIONSTART :
            return OnButton1MotionStart( *reinterpret_cast< PPOINTS >( &mp1 ),
                                         SHORT1FROMMP( mp2 ));

        case WM_BUTTON3UP :
            return OnButton1Up( *reinterpret_cast< PPOINTS >( &mp1 ),
                                SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_CALCFRAMERECT :
            return OnCalcFrameRect( reinterpret_cast< PRECTL >( mp1 ),
                                    SHORT1FROMMP( mp2 ));

        case WM_CALCVALIDRECTS :
            return OnCalcValidRects( reinterpret_cast< PRECTL >( mp1 ),
                                     reinterpret_cast< PSWP >( mp2 ));


        case WM_CHAR :
            return OnChar( SHORT1FROMMP( mp1 ), CHAR3FROMMP( mp1 ),
                           CHAR4FROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                           SHORT2FROMMP( mp2 ));

        case WM_CHORD :
            return OnChord( SHORT1FROMMP( mp2 ));

        case WM_CLOSE :
            return OnClose();

        case WM_COMMAND :
            return OnCommand( SHORT1FROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                              SHORT2FROMMP( mp2 ));

        case WM_CONTEXTMENU :
            return OnContextMenu( *reinterpret_cast< PPOINTS >( &mp1 ),
                                  SHORT2FROMMP( mp2 ));

        case WM_CONTROL :
            return OnControl( SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ),
                              LONGFROMMP( mp2 ));

        case WM_CONTROLPOINTER :
            return OnControlPointer( SHORT1FROMMP( mp1 ), LONGFROMMP( mp2 ));

        case WM_CREATE :
            return OnCreate( PVOIDFROMMP( mp1 ),
                             reinterpret_cast< PCREATESTRUCT >
                                 ( PVOIDFROMMP( mp2 )));

        case WM_CTLCOLORCHANGE :
            return OnCtlColorChange();

        case WM_DESTROY :
            return OnDestroy();

        case WM_DRAWITEM :
            return OnDrawItem( SHORT1FROMMP( mp1 ), LONGFROMMP( mp2 ));

        case WM_ENABLE :
            return OnEnable( SHORT1FROMMP( mp1 ));

        case WM_ENDDRAG :
            return OnEndDrag( *reinterpret_cast< PPOINTS >( &mp1 ),
                              SHORT1FROMMP( mp2 ));

        case WM_ENDSELECT :
            return OnEndSelect( *reinterpret_cast< PPOINTS >( &mp1 ),
                                SHORT1FROMMP( mp2 ));
        case WM_ERROR :
            return OnError( SHORT1FROMMP( mp1 ));

        case WM_FOCUSCHANGE :
            return OnFocusChange( HWNDFROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                                  SHORT2FROMMP( mp2 ));

        case WM_FORMATFRAME :
            return OnFormatFrame( reinterpret_cast< PSWP >( mp1 ),
                                  reinterpret_cast< PRECTL >( mp2 ));

        case WM_HELP :
            return OnHelp( SHORT1FROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                           SHORT2FROMMP( mp2 ));

        case WM_HITTEST :
            return OnHitTest( *reinterpret_cast< PPOINTS >( &mp1 ));

        case WM_HSCROLL :
            return OnHScroll( SHORT1FROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                              SHORT2FROMMP( mp2 ));

        case WM_INITDLG :
            return OnInitDlg( HWNDFROMMP( mp1 ), PVOIDFROMMP( mp2 ));

        case WM_INITMENU :
            return OnInitMenu( SHORT1FROMMP( mp1 ), HWNDFROMMP( mp2 ));

        case WM_JOURNALNOTIFY :
            return OnJournalNotify( LONGFROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                                    SHORT2FROMMP( mp2 ));

        case WM_MATCHMNEMONIC :
            return OnMatchMnemonic( SHORT1FROMMP( mp1 ));

        case WM_MEASUREITEM :
            return OnMeasureItem( SHORT1FROMMP( mp1 ), LONGFROMMP( mp2 ));

        case WM_MENUEND :
            return OnMenuEnd( SHORT1FROMMP( mp1 ), HWNDFROMMP( mp2 ));

        case WM_MENUSELECT :
            return OnMenuSelect( SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ),
                                 HWNDFROMMP( mp2 ));

        case WM_MINMAXFRAME :
            return OnMinMaxFrame( reinterpret_cast< PSWP >( mp1 ));

        case WM_MOUSEMAP :
            return OnMouseMap( LONGFROMMP( mp1 ), LONGFROMMP( mp2 ));

        case WM_MOUSEMOVE :
            return OnMouseMove( SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ),
                                SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_MOVE :
            return OnMove();

        case WM_MSGBOXDISMISS :
            return OnMsgBoxDismiss( HWNDFROMMP( mp1 ), LONGFROMMP( mp2 ));

        case WM_MSGBOXINIT :
            return OnMsgBoxInit( HWNDFROMMP( mp1 ), LONGFROMMP( mp2 ));

        case WM_NEXTMENU :
            return OnNextMenu( HWNDFROMMP( mp1 ), SHORT1FROMMP( mp2 ));

        case WM_NULL :
            return OnNull();

        case WM_OPEN :
            return OnOpen( SHORT1FROMMP( mp1 ),
                           *reinterpret_cast< PPOINTS >( &mp2 ));

        case WM_PACTIVATE :
            return OnPActivate( SHORT1FROMMP( mp1 ), HWNDFROMMP( mp2 ));

        case WM_PAINT :
            return OnPaint();

        case WM_PCONTROL :
            return OnPControl( SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ),
                               LONGFROMMP( mp2 ));
        case WM_PPAINT :
            return OnPPaint();

        case WM_PRESPARAMCHANGED :
            return OnPresParamChanged( LONGFROMMP( mp1 ));

        case WM_PSETFOCUS :
            return OnPSetFocus( HWNDFROMMP( mp1 ), SHORT1FROMMP( mp2 ));

        case WM_PSIZE :
            return OnPSize( SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ),
                            SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_PSYSCOLORCHANGE :
            return OnPSysColorChange( LONGFROMMP( mp1 ));

        case WM_QUERYACCELTABLE :
            return OnQueryAccelTable();

        case WM_QUERYCONVERTPOS :
            return OnQueryConvertPos( reinterpret_cast< PRECTL >( mp1 ));

        case WM_QUERYCTLTYPE :
            return OnQueryCtlType();

        case WM_QUERYDLGCODE :
            return OnQueryDlgCode( reinterpret_cast< PQMSG >( mp1 ));

        case WM_QUERYHELPINFO :
            return OnQueryHelpInfo();

        case WM_QUERYTRACKINFO :
            return OnQueryTrackInfo( SHORT1FROMMP( mp1 ),
                                     reinterpret_cast< PTRACKINFO >( mp2 ));
        case WM_QUERYWINDOWPARAMS :
            return OnQueryWindowParams( reinterpret_cast< PWNDPARAMS >( mp1 ));

        case WM_QUIT :
            return OnQuit();

        case WM_REALIZEPALETTE :
            return OnRealizePalette();

        case WM_SAVEAPPLICATION :
            return OnSaveApplication();

        case WM_SEM1 :
            return OnSem1( LONGFROMMP( mp1 ));

        case WM_SEM2 :
            return OnSem2( LONGFROMMP( mp1 ));

        case WM_SEM3 :
            return OnSem3( LONGFROMMP( mp1 ));

        case WM_SEM4 :
            return OnSem4( LONGFROMMP( mp1 ));

        case WM_SETACCELTABLE :
            return OnSetAccelTable( LONGFROMMP( mp1 ));

        case WM_SETFOCUS :
            return OnSetFocus( HWNDFROMMP( mp1 ), SHORT1FROMMP( mp2 ));

        case WM_SETHELPINFO :
            return OnSetHelpInfo( LONGFROMMP( mp1 ));

        case WM_SETSELECTION :
            return OnSetSelection( SHORT1FROMMP( mp1 ));

        case WM_SETWINDOWPARAMS :
            return OnSetWindowParams( reinterpret_cast< PWNDPARAMS >( mp1 ));

        case WM_SHOW :
            return OnShow( SHORT1FROMMP( mp1 ));

        case WM_SINGLESELECT :
            return OnSingleSelect( *reinterpret_cast< PPOINTS >( &mp1 ),
                                   SHORT1FROMMP( mp2 ));

        case WM_SIZE :
            return OnSize( SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ),
                           SHORT1FROMMP( mp2 ), SHORT2FROMMP( mp2 ));

        case WM_SUBSTITUTESTRING :
            return OnSubstituteString( SHORT1FROMMP( mp1 ));

        case WM_SYSCOLORCHANGE :
            return OnSysColorChange( LONGFROMMP( mp1 ));

        case WM_SYSCOMMAND :
            return OnSysCommand( SHORT1FROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                                 SHORT2FROMMP( mp2 ));

        case WM_SYSVALUECHANGED :
            return OnSysValueChanged( SHORT1FROMMP( mp1 ),
                                      SHORT1FROMMP( mp2 ));
        case WM_TEXTEDIT :
            return OnTextEdit( SHORT1FROMMP( mp1 ),
                               *reinterpret_cast< PPOINTS >( &mp2 ));

        case WM_TIMER :
            return OnTimer( SHORT1FROMMP( mp1 ));

        case WM_TRACKFRAME :
            return OnTrackFrame( SHORT1FROMMP( mp1 ));

        case WM_TRANSLATEACCEL :
            return OnTranslateAccel( reinterpret_cast< PQMSG >( mp1 ));

#if 0
        case WM_TRANSLATEMNEMONIC :
            return OnTranslateMnemonic( reinterpret_cast< PQMSG >( mp1 ));
#endif

        case WM_UPDATEFRAME :
            return OnUpdateFrame( LONGFROMMP( mp1 ));

        case WM_VRNDISABLED :
            return OnVRNDisabled( PVOIDFROMMP( mp1 ), PVOIDFROMMP( mp2 ));

        case WM_VRNENABLED :
            return OnVRNEnabled( LONGFROMMP( mp1 ), PVOIDFROMMP( mp2 ));

        case WM_VSCROLL :
            return OnVScroll( SHORT1FROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                              SHORT2FROMMP( mp2 ));

        case WM_WINDOWPOSCHANGED :
            return OnWindowPosChanged( reinterpret_cast< PSWP >( mp1 ),
                                       LONGFROMMP( mp2 ));
    }

    return KDefWndProc( msg, mp1, mp2 );
}

MRESULT KWindow::OnCommand( USHORT usCmd, USHORT usSource, bool fPointer )
{
    switch( usSource )
    {
        case CMDSRC_PUSHBUTTON  : return CmdSrcPushButton( usCmd, fPointer );
        case CMDSRC_MENU        : return CmdSrcMenu( usCmd, fPointer );
        case CMDSRC_ACCELERATOR : return CmdSrcAccelerator( usCmd, fPointer );
        case CMDSRC_FONTDLG     : return CmdSrcFontDlg( usCmd, fPointer );
        case CMDSRC_FILEDLG     : return CmdSrcFileDlg( usCmd, fPointer );
        case CMDSRC_OTHER       : return CmdSrcOther( usCmd, fPointer );
    }

    return CmdSrcUser( usCmd, usSource, fPointer );
}

MRESULT KWindow::OnHelp( USHORT usCmd, USHORT usSource, bool fPointer )
{
    switch( usSource )
    {
        case CMDSRC_PUSHBUTTON  :
            return HelpCmdSrcPushButton( usCmd, fPointer );

        case CMDSRC_MENU        :
            return HelpCmdSrcMenu( usCmd, fPointer );

        case CMDSRC_ACCELERATOR :
            return HelpCmdSrcAccelerator( usCmd, fPointer );

        case CMDSRC_FONTDLG     :
            return HelpCmdSrcFontDlg( usCmd, fPointer );

        case CMDSRC_FILEDLG     :
            return HelpCmdSrcFileDlg( usCmd, fPointer );

        case CMDSRC_OTHER       :
            return HelpCmdSrcOther( usCmd, fPointer );
    }

    return HelpCmdSrcUser( usCmd, usSource, fPointer );
}

MRESULT KWindow::OnHScroll( USHORT id, SHORT sSlider, USHORT usCmd )
{
    switch( usCmd )
    {
        case SB_LINELEFT       : return HSbLineLeft( id, sSlider );
        case SB_LINERIGHT      : return HSbLineRight( id, sSlider );
        case SB_PAGELEFT       : return HSbPageLeft( id, sSlider );
        case SB_PAGERIGHT      : return HSbPageRight( id, sSlider );
        case SB_SLIDERPOSITION : return HSbSliderPosition( id, sSlider );
        case SB_SLIDERTRACK    : return HSbSliderTrack( id, sSlider );
        case SB_ENDSCROLL      : return HSbEndScroll( id, sSlider );
    }

    return 0;
}

MRESULT KWindow::OnSysCommand( USHORT usCmd, USHORT usSource, bool fPointer )
{
    switch( usSource )
    {
        case CMDSRC_PUSHBUTTON  :
            return SysCmdSrcPushButton( usCmd, fPointer );

        case CMDSRC_MENU        :
            return SysCmdSrcMenu( usCmd, fPointer );

        case CMDSRC_ACCELERATOR :
            return SysCmdSrcAccelerator( usCmd, fPointer );

        case CMDSRC_FONTDLG     :
            return SysCmdSrcFontDlg( usCmd, fPointer );

        case CMDSRC_FILEDLG     :
            return SysCmdSrcFileDlg( usCmd, fPointer );

        case CMDSRC_OTHER       :
            return SysCmdSrcOther( usCmd, fPointer );
    }

    return SysCmdSrcUser( usCmd, usSource, fPointer );
}

MRESULT KWindow::OnVScroll( USHORT id, SHORT sSlider, USHORT usCmd )
{
    switch( usCmd )
    {
        case SB_LINEUP         : return VSbLineUp( id, sSlider );
        case SB_LINEDOWN       : return VSbLineDown( id, sSlider );
        case SB_PAGEUP         : return VSbPageUp( id, sSlider );
        case SB_PAGEDOWN       : return VSbPageDown( id, sSlider );
        case SB_SLIDERPOSITION : return VSbSliderPosition( id, sSlider );
        case SB_SLIDERTRACK    : return VSbSliderTrack( id, sSlider );
        case SB_ENDSCROLL      : return VSbEndScroll( id, sSlider );
    }

    return 0;
}

