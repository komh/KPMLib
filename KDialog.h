#ifndef KDIALOG_H
#define KDIALOG_H

#define INCL_WIN
#include <os2.h>

#include "KFrameWindow.h"

class KDialog : public KFrameWindow
{
public :
    KDialog();
    virtual ~KDialog();

    virtual void SetHWND( HWND hwndDlg );
    virtual bool LoadDlg( KWindow* pkwndP, KWindow* pkwndO, HMODULE hmod,
                          ULONG idDlg, PVOID pCreateParams );
    virtual void DlgBox( KWindow* pkwndP, KWindow* pkwndO, HMODULE hmod,
                         ULONG idDlg, PVOID pCreateParams );
    virtual void ProcessDlg() { _ulResult = WinProcessDlg( _hwnd ); }
    virtual bool DismissDlg( ULONG ulResult )
    { return WinDismissDlg( _hwnd, ulResult ); }

    ULONG GetResult() const { return _ulResult; }

protected :
    ULONG _ulResult;

    static MRESULT EXPENTRY DlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1,
                                     MPARAM mp2 );

    virtual MRESULT KDlgProc( ULONG msg, MPARAM mp1, MPARAM mp2 );
    virtual MRESULT OnInitDlg( HWND hwndFocus, PVOID pCreate )
    {
        return KDefDlgProc( WM_INITDLG, MPFROMHWND( hwndFocus ),
                            MPFROMP( pCreate ));
    }

private :
    MRESULT KDefDlgProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
    { return WinDefDlgProc( _hwnd, msg, mp1, mp2 ); }
};
#endif
