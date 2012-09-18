#ifndef KFILE_DLG_H
#define KFILE_DLG_H

#define INCL_WIN
#include <os2.h>

#include <cstring>

#include "KDialog.h"

class KFileDlg : public KDialog
{
public :
    KFileDlg();
    virtual ~KFileDlg();

    virtual bool FileDlg( const KWindow* pkwndP, const KWindow* pkwndO );

    virtual void Clear()
    {
        memset( &_fild, 0, sizeof( _fild ));

        _fild.cbSize = sizeof( FILEDLG );
    }

    virtual void SetFl( ULONG fl ) { _fild.fl = fl; }
    virtual void SetUser( ULONG ulUser ) { _fild.ulUser = ulUser; }
    virtual void SetTitle( PSZ pszTitle ) { _fild.pszTitle = pszTitle; }
    virtual void SetOkButton( PSZ pszOKButton )
    { _fild.pszOKButton = pszOKButton; }

    virtual void SetIType( PSZ pszIType ) { _fild.pszIType = pszIType; }
    virtual void SetITypeList( PAPSZ papszITypeList )
    { _fild.papszITypeList = papszITypeList; }

    virtual void SetIDrive( PSZ pszIDrive ) { _fild.pszIDrive = pszIDrive; }
    virtual void SetIDriveList( PAPSZ papszIDriveList )
    { _fild.papszIDriveList = papszIDriveList; }

    virtual void SetMod( HMODULE hMod ) { _fild.hMod = hMod; }
    virtual void SetFullFile( PCSZ pcszFullFile )
    {
        strncpy( _fild.szFullFile,
                 reinterpret_cast< const char* >( pcszFullFile ),
                 sizeof( _fild.szFullFile ) -1 );

        _fild.szFullFile[ sizeof( _fild.szFullFile ) - 1 ] = '\0';
    }

    virtual void SetDlgID( USHORT usDlgId ) { _fild.usDlgId = usDlgId; }
    virtual void SetXY( SHORT x, SHORT y ) { _fild.x = x; _fild.y = y; }

    LONG GetReturn() const { return _fild.lReturn; }
    LONG GetSrc() const { return _fild.lSRC; }
    PCSZ GetFullFile() const
    { return reinterpret_cast< PCSZ >( _fild.szFullFile ); }

    PAPSZ GetFQFilename() const { return _fild.papszFQFilename; }
    ULONG GetFQFCount() const { return _fild.ulFQFCount; }
    SHORT GetEAType() const { return _fild.sEAType; }

protected :
    FILEDLG _fild;

    static MRESULT EXPENTRY FileDlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1,
                                         MPARAM mp2 );

    virtual MRESULT KDefWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
    { return WinDefFileDlgProc( _hwnd, msg, mp1, mp2 ); }
};
#endif
