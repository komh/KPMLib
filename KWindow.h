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
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );
    virtual bool DestroyWindow();
    virtual bool SetWindowText( PCSZ pcszString );
    virtual bool WindowFromID( ULONG id, KWindow& kwnd );
    virtual bool ShowWindow( BOOL fNewVisibility );
    virtual ULONG MessageBox( PCSZ pcszText, PCSZ pcszCaption, ULONG flStyle )
    {
        return WinMessageBox( HWND_DESKTOP, _hwnd, pcszText, pcszCaption,
                              0xFFFF, flStyle );
    }
    virtual ULONG MessageBox( PCSZ pcszText, PCSZ pcszCaption, ULONG id,
                              ULONG flStyle )
    {
        return WinMessageBox( HWND_DESKTOP, _hwnd, pcszText, pcszCaption,
                              id, flStyle );
    }
    virtual MRESULT SendMsg( ULONG ulMsg, MPARAM mp1 = 0, MPARAM mp2 = 0 )
    {   return WinSendMsg( _hwnd, ulMsg, mp1, mp2 ); }
    virtual HAB QueryAnchorBlock() { return WinQueryAnchorBlock( _hwnd ); }
    virtual ULONG QueryTaskSizePos( PSWP pswp )
    { return WinQueryTaskSizePos( QueryAnchorBlock(), 0, pswp ); }
    virtual bool SetWindowPos( KWindow* pkwndRel, LONG x, LONG y,
                               LONG cx, LONG cy, ULONG fl )
    { return WinSetWindowPos( _hwnd, pkwnd2hwnd( pkwndRel ),
                              x, y, cx, cy, fl ); }

    HWND GetHWND() const { return _hwnd; }
    PCSZ GetClassName() const { return _pcszClassName; }

protected :
    HWND     _hwnd;
    PCSZ     _pcszClassName;

    friend HWND pkwnd2hwnd( const KWindow* kwnd );

    static MRESULT EXPENTRY WndProc( HWND hwnd, ULONG msg, MPARAM mp1,
                                     MPARAM mp2 );

    virtual MRESULT KWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 );
    virtual MRESULT OnPaint();

    virtual MRESULT OnCommand( USHORT usCmd, USHORT usSource,
                               USHORT usPointer );
    virtual MRESULT CmdSrcPushButton( USHORT usCmd, USHORT usPointer );

    virtual MRESULT OnControl( USHORT id, USHORT usNotifyCode,
                                ULONG ulControlSpec );
    virtual MRESULT BnClicked( USHORT id );
    virtual MRESULT BnDblClicked( USHORT id );
    virtual MRESULT BnPaint( USHORT id, ULONG ulControlSpec );

private :
    PFNWP _pfnwpOldProc;

    MRESULT KDefWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
    { return _pfnwpOldProc ? _pfnwpOldProc( _hwnd, msg, mp1, mp2 ) :
                             WinDefWindowProc( _hwnd, msg, mp1, mp2 ); }
};
#endif

