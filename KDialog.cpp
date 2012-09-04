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
    if( msg == WM_INITDLG )
    {
        CreateParams* pcp = reinterpret_cast< CreateParams* >( mp2 );

        mp2 = pcp->pCreate;

        KDialog* pkdlg = pcp->pkdlg;

        // Subclass to KWindow::WndProc()
        pkdlg->SetHWND( hwndDlg );

        // Pass the control to KWindow::WndProc()
        return pkdlg->KWndProc( msg, mp1, mp2 );
    }

    return WinDefDlgProc( hwndDlg, msg, mp1, mp2 );
}

