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

    return pkdlg->KWndProc( msg, mp1, mp2 );
}

