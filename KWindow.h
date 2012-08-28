#ifndef KWINDOW_H
#define KWINDOW_H

#define INCL_WIN
#include <os2.h>

#define PMLITERAL( s ) ( reinterpret_cast < PCSZ >( s ))

#define KWND_DESKTOP ( reinterpret_cast< KWindow* >( HWND_DESKTOP ))
#define KWND_OBJECT  ( reinterpret_cast< KWindow* >( HWND_OBJECT ))
#define KWND_TOP     ( reinterpret_cast< KWindow* >( HWND_TOP ))
#define KWND_BOTTOM  ( reinterpret_cast< KWindow* >( HWND_BOTTOM ))

class KWindow
{
public :
    KWindow();
    virtual ~KWindow();

    virtual void SetHWND( HWND hwnd );
    virtual bool RegisterClass( HAB hab, PCSZ pcszClassName, ULONG flStyle,
                                ULONG cbWindowData );
    virtual void SetClassName( PCSZ pcszClassName );
    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData, PVOID pPresParams );
    virtual bool DestroyWindow();
    virtual bool SetWindowText( PCSZ pcszString );
    virtual bool WindowFromID( ULONG id, KWindow& kwnd );
    virtual bool ShowWindow( BOOL fNewVisibility );

    HWND GetHWND() const { return _hwnd; }
    PCSZ GetClassName() const { return _pcszClassName; }

protected :
    HAB      _hab;
    KWindow* _pkwndP;
    KWindow* _pkwndO;
    HWND     _hwnd;
    PCSZ     _pcszClassName;

    friend HWND pkwnd2hwnd( const KWindow* kwnd );

    static MRESULT EXPENTRY WndProc( HWND hwnd, ULONG msg, MPARAM mp1,
                                     MPARAM mp2 );

    virtual MRESULT KWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 );
    virtual MRESULT OnPaint();

private :
    PFNWP _pfnwpOldProc;

    MRESULT KDefWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
    { return _pfnwpOldProc ? _pfnwpOldProc( _hwnd, msg, mp1, mp2 ) :
                             WinDefWindowProc( _hwnd, msg, mp1, mp2 ); }
};
#endif

