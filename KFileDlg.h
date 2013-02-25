#ifndef KFILE_DLG_H
#define KFILE_DLG_H

#define INCL_WIN
#include <os2.h>

#include <string>

#include <vector>

#include "KDialog.h"

typedef vector< string > KFDVECSTR;

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
    virtual void SetTitle( const string& strTitle )
    {
        _strTitle      = strTitle;
        _fild.pszTitle = const_cast< char* >( _strTitle.c_str());
    }

    virtual void SetOkButton( const string& strOKButton )
    {
        _strOKButton      = strOKButton;
        _fild.pszOKButton = const_cast< char* >( _strOKButton.c_str());
    }

    virtual void SetIType( const string& strIType )
    {
        _strIType      = strIType;
        _fild.pszIType = const_cast< char* >( _strIType.c_str());
    }

    virtual void SetITypeList( const KFDVECSTR& vsITypeList )
    {
        _vsITypeList = vsITypeList;

        delete[] _ppszITypeList;

        _ppszITypeList = new PSZ[ _vsITypeList.size() + 1 ];

        for( size_t i = 0; i < _vsITypeList.size(); i++ )
            _ppszITypeList[ i ] = const_cast< char* >
                                    ( _vsITypeList[ i ].c_str());
        _ppszITypeList[ _vsITypeList.size()] = 0;

        _fild.papszITypeList = reinterpret_cast< PAPSZ >( &_ppszITypeList );
    }

    virtual void SetIDrive( const string& strIDrive )
    {
        _strIDrive      = strIDrive;
        _fild.pszIDrive = const_cast< char* >( _strIDrive.c_str());
    }

    virtual void SetIDriveList( const KFDVECSTR& vsIDriveList )
    {
        _vsIDriveList = vsIDriveList;

        delete[] _ppszIDriveList;

        _ppszIDriveList = new PSZ[ _vsIDriveList.size() + 1 ];

        for( size_t i = 0; i < vsIDriveList.size(); i++ )
            _ppszIDriveList[ i ] = const_cast< char* >
                                        ( _vsIDriveList[ i ].c_str());
        _ppszIDriveList[ vsIDriveList.size()] = 0;

        _fild.papszIDriveList = reinterpret_cast< PAPSZ >( &_ppszIDriveList );
    }

    virtual void SetMod( HMODULE hMod ) { _fild.hMod = hMod; }

    virtual void SetFullFile( const string& strFullFile )
    {
        strncpy( _fild.szFullFile, strFullFile.c_str(),
                 sizeof( _fild.szFullFile ) - 1 );

        _fild.szFullFile[ sizeof( _fild.szFullFile ) - 1 ] = '\0';
    }

    virtual void SetDlgID( USHORT usDlgId ) { _fild.usDlgId = usDlgId; }
    virtual void SetXY( SHORT x, SHORT y ) { _fild.x = x; _fild.y = y; }

    LONG GetReturn() const { return _fild.lReturn; }
    LONG GetSrc() const { return _fild.lSRC; }

    const string& GetFullFile()
    {
        _strFullFile = _fild.szFullFile;

        return _strFullFile;
    }

    const KFDVECSTR& GetFQFilename()
    {
        _vsFQFilename.clear();

        for( ULONG i = 0; i < _fild.ulFQFCount; i++ )
            _vsFQFilename.push_back(( *_fild.papszFQFilename )[ i ]);

        return _vsFQFilename;
    }

    ULONG GetFQFCount() const { return _fild.ulFQFCount; }
    SHORT GetEAType() const { return _fild.sEAType; }

protected :
    FILEDLG   _fild;
    string    _strTitle;
    string    _strOKButton;
    string    _strIType;
    string    _strIDrive;
    string    _strFullFile;
    PSZ*      _ppszITypeList;
    KFDVECSTR _vsITypeList;
    PSZ*      _ppszIDriveList;
    KFDVECSTR _vsIDriveList;
    KFDVECSTR _vsFQFilename;

    static MRESULT EXPENTRY FileDlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1,
                                         MPARAM mp2 );

    virtual MRESULT KDefWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
    {
        return WinDefFileDlgProc( _hwnd, msg, mp1, mp2 );
    }
};
#endif
