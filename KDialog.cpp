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

void KDialog::SetHWND( HWND hwndDlg )
{
    KWindow::SetHWND( hwndDlg );

    if( WinQueryWindowPtr( hwndDlg, 0 ) &&
        WinQueryWindowPtr( hwndDlg, QWP_PFNWP ) == WndProc )
        // Set a window procture to DlgProc instead of WndProc
        WinSubclassWindow( hwndDlg, DlgProc );
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

void KDialog::DlgBox( KWindow* pkwndP, KWindow* pkwndO, HMODULE hmod,
                      ULONG idDlg, PVOID pCreateParams )
{
    HWND hwndP = pkwnd2hwnd( pkwndP );
    HWND hwndO = pkwnd2hwnd( pkwndO );

    CreateParams cp = { sizeof( cp ), pCreateParams, this };

    _ulResult = WinDlgBox( hwndP, hwndO, DlgProc, hmod, idDlg, &cp );
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
        case WM_INITDLG : return OnInitDlg( HWNDFROMMP( mp1 ),
                                            PVOIDFROMMP( mp2 ));
        case WM_DESTROY : return OnDestroy();
        case WM_COMMAND : return OnCommand( SHORT1FROMMP( mp1 ),
                                            SHORT1FROMMP( mp2),
                                            SHORT2FROMMP( mp2 ));
        case WM_CONTROL : return OnControl( SHORT1FROMMP( mp1 ),
                                            SHORT2FROMMP( mp1 ),
                                            LONGFROMMP( mp2 ));
    }

    return KDefDlgProc( msg, mp1, mp2 );
}

