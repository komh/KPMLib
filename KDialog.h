#ifndef KDIALOG_H
#define KDIALOG_H

#define INCL_WIN
#include <os2.h>

#include <string>

#include "KFrameWindow.h"

class KDialog : public KFrameWindow
{
public :
    KDialog();
    virtual ~KDialog();

    virtual USHORT CheckButton( USHORT usID, USHORT usChkState )
    {
        return WinCheckButton( _hwnd, usID, usChkState );
    }

    virtual bool DismissDlg( ULONG ulResult )
    {
        return WinDismissDlg( _hwnd, ulResult );
    }

    virtual void DlgBox( KWindow* pkwndP, KWindow* pkwndO, HMODULE hmod,
                         ULONG idDlg, PVOID pCreateParams = 0 );
    virtual bool LoadDlg( KWindow* pkwndP, KWindow* pkwndO, HMODULE hmod,
                          ULONG idDlg, PVOID pCreateParams = 0 );
    virtual void ProcessDlg() { _ulResult = WinProcessDlg( _hwnd ); }

    virtual USHORT QueryButtonCheckstate( USHORT usID )
    {
        return WinQueryButtonCheckstate( _hwnd, usID );
    }

    virtual ULONG QueryDlgItemText( ULONG idItem, string& strText )
    {
        LONG  lMaxText = QueryDlgItemTextLength( idItem ) + 1;
        PSZ   pszText  = new CHAR[ lMaxText ];
        ULONG rc;

        rc = WinQueryDlgItemText( _hwnd, idItem, lMaxText, pszText );

        strText = pszText;

        delete[] pszText;

        return rc;
    }

    virtual LONG QueryDlgItemTextLength( ULONG idItem )
    {
        return WinQueryDlgItemTextLength( _hwnd, idItem );
    }

    virtual MRESULT SendDlgItemMsg( ULONG idItem, ULONG msg, MPARAM mp1,
                                    MPARAM mp2 )
    {
        return WinSendDlgItemMsg( _hwnd, idItem, msg, mp1, mp2 );
    }

    virtual bool SetDlgItemText( ULONG idItem, const string& strText )
    {
        return WinSetDlgItemText( _hwnd, idItem, strText.c_str());
    }

    ULONG GetResult() const { return _ulResult; }

protected :
    static MRESULT EXPENTRY DlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1,
                                     MPARAM mp2 );

    virtual MRESULT KDefWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
    {
        return WinDefDlgProc( _hwnd, msg, mp1, mp2 );
    }

private :
    ULONG _ulResult;
};
#endif
