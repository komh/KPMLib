#include <string.h>

#include "KDialog.h"

struct CreateParams
{
    USHORT   cb;
    PVOID    pCreate;
    KDialog* pkdlg;
};

KDialog::KDialog() : KFrameWindow()
{
    _ulResult = 0;
}

KDialog::~KDialog()
{
}

void KDialog::DlgBox( KWindow* pkwndP, KWindow* pkwndO, HMODULE hmod,
                      ULONG idDlg, PVOID pCreateParams )
{
    HWND hwndP = pkwnd2hwnd( pkwndP );
    HWND hwndO = pkwnd2hwnd( pkwndO );

    CreateParams cp = { sizeof( cp ), pCreateParams, this };

    _ulResult = WinDlgBox( hwndP, hwndO, DlgProc, hmod, idDlg, &cp );
}

bool KDialog::LoadDlg( KWindow* pkwndP, KWindow* pkwndO, HMODULE hmod,
                       ULONG idDlg, PVOID pCreateParams )
{
    HWND hwndP = pkwnd2hwnd( pkwndP );
    HWND hwndO = pkwnd2hwnd( pkwndO );

    CreateParams cp = { sizeof( cp ), pCreateParams, this };

    _hwnd = WinLoadDlg( hwndP, hwndO, DlgProc, hmod, idDlg, &cp );

    return _hwnd;
}

void KDialog::SetHWND( HWND hwndDlg )
{
    KWindow::SetHWND( hwndDlg );

    if( WinQueryWindowPtr( hwndDlg, 0 ) &&
        WinQueryWindowPtr( hwndDlg, QWP_PFNWP ) == WndProc )
        // Set a window procture to DlgProc instead of WndProc
        WinSubclassWindow( hwndDlg, DlgProc );
}

MRESULT EXPENTRY KDialog::DlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1,
                                   MPARAM mp2 )
{
    KDialog* pkdlg = reinterpret_cast< KDialog* >
                        ( WinQueryWindowPtr( hwndDlg, 0 ));

    if( msg == WM_INITDLG )
    {
        CreateParams* pcp = reinterpret_cast< CreateParams* >( mp2 );

        pkdlg = pcp->pkdlg;
        pkdlg->SetHWND( hwndDlg );

        mp2 = pcp->pCreate;
    }

    if( !pkdlg )
        return WinDefDlgProc( hwndDlg, msg, mp1, mp2 );

    return pkdlg->KDlgProc( msg, mp1, mp2 );
}

MRESULT KDialog::KDlgProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    switch( msg )
    {
        case WM_CHAR :
            return OnChar( SHORT1FROMMP( mp1 ), CHAR3FROMMP( mp1 ),
                           CHAR4FROMMP( mp1 ), SHORT1FROMMP( mp2 ),
                           SHORT2FROMMP( mp2 ));

        case WM_CLOSE :
            return OnClose();

        case WM_COMMAND :
            return OnCommand( SHORT1FROMMP( mp1 ), SHORT1FROMMP( mp2),
                              SHORT2FROMMP( mp2 ));

        case WM_CONTROL :
            return OnControl( SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ),
                              LONGFROMMP( mp2 ));

        case WM_DESTROY :
            return OnDestroy();

        case WM_INITDLG :
            return OnInitDlg( HWNDFROMMP( mp1 ), PVOIDFROMMP( mp2 ));

        case WM_MATCHMNEMONIC :
            return OnMatchMnemonic( SHORT1FROMMP( mp1 ));

        case WM_QUERYDLGCODE :
            return OnQueryDlgCode( reinterpret_cast< PQMSG >( mp1 ));
    }

    return KDefDlgProc( msg, mp1, mp2 );
}

MRESULT KDialog::OnCommand( USHORT usCmd, USHORT usSource, bool fPointer )
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

