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

    virtual MRESULT OnChar( ULONG flFlags, ULONG ulRepeat, ULONG ulScanCode,
                            ULONG ulCh, ULONG ulVk )
    {
        return KDefDlgProc( WM_CHAR,
                            MPFROMSH2CH( flFlags, ulRepeat, ulScanCode ),
                            MPFROM2SHORT( ulCh, ulVk ));
    }

    virtual MRESULT OnClose() { return KDefDlgProc( WM_CLOSE, 0, 0 ); }

private :
    MRESULT KDefDlgProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
    { return WinDefDlgProc( _hwnd, msg, mp1, mp2 ); }
};
#endif
