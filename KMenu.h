/*
    KPMLib, C++ encapsulation class library for OS/2 PM
    Copyright (C) 2012-2013 by KO Myung-Hun <komh@chollian.net>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software Foundation,
    Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
*/

#ifndef KMENU_H
#define KMENU_H

#include <string>

#include "KWindow.h"

class KMenu : public KWindow
{
public :
    KMenu() : KWindow() {};
    virtual ~KMenu() {};

    virtual bool CreateWindow( const KWindow* pkwndP, const string& strName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    virtual bool LoadMenu( const KWindow* pkwndO, HMODULE hmod, ULONG idMenu )
    {
        HWND hwnd = WinLoadMenu( pkwnd2hwnd( pkwndO ), hmod, idMenu );
        SetHWND( hwnd );

        return hwnd;
    }

    virtual bool PopupMenu( const KWindow* pkwndP, const KWindow* pkwndO,
                            LONG x, LONG y, LONG idItem, ULONG fs )
    {
        return WinPopupMenu( pkwnd2hwnd( pkwndP ), pkwnd2hwnd( pkwndO ),
                             _hwnd, x, y, idItem, fs );
    }

    virtual SHORT DeleteItem( USHORT usItem, bool fIncSub )
    {
        return SHORT1FROMMR( SendMsg( MM_DELETEITEM,
                                      MPFROM2SHORT( usItem, fIncSub )));
    }

    virtual bool DeleteItemP( USHORT usItem, bool fIncSub )
    {
        return PostMsg( MM_DELETEITEM, MPFROM2SHORT( usItem, fIncSub ));
    }

    virtual void EndMenuMode( bool fDismiss )
    {
        SendMsg( MM_ENDMENUMODE, MPFROMLONG( fDismiss ));
    }

    virtual bool EndMenuModeP( bool fDismiss )
    {
        return PostMsg( MM_ENDMENUMODE, MPFROMLONG( fDismiss ));
    }

    virtual SHORT InsertItem( PMENUITEM pmi, const string& strText )
    {
        return SHORT1FROMMR( SendMsg( MM_INSERTITEM, MPFROMP( pmi ),
                                      MPFROMP( strText.c_str())));
    }

    virtual bool IsItemValid( USHORT usItem, BOOL fIncSub )
    {
        return SendMsg( MM_ISITEMVALID, MPFROM2SHORT( usItem, fIncSub ));
    }

    virtual SHORT ItemIDFromPosition( SHORT sItemIndex )
    {
        return SHORT1FROMMR( SendMsg( MM_ITEMIDFROMPOSITION,
                                      MPFROMSHORT( sItemIndex )));
    }

    virtual SHORT ItemPositionFromID( USHORT usItem, bool fIncSub )
    {
        return SHORT1FROMMR( SendMsg( MM_ITEMPOSITIONFROMID,
                                      MPFROM2SHORT( usItem, fIncSub )));
    }

    virtual ULONG QueryDefaultItemID()
    {
        return LONGFROMMR( SendMsg( MM_QUERYDEFAULTITEMID ));
    }

    virtual bool QueryItem( USHORT usItem, bool fIncSub, PMENUITEM pmi )
    {
        return SendMsg( MM_QUERYITEM, MPFROM2SHORT( usItem, fIncSub ),
                        MPFROMP( pmi ));
    }

    virtual USHORT QueryItemAttr( USHORT usItem, bool fIncSub, USHORT usMask )
    {
        return SHORT1FROMMR( SendMsg( MM_QUERYITEMATTR,
                                      MPFROM2SHORT( usItem, fIncSub ),
                                      MPFROMSHORT( usMask )));
    }

    virtual SHORT QueryItemCount()
    {
        return SHORT1FROMMR( SendMsg( MM_QUERYITEMCOUNT ));
    }

    virtual bool QueryItemRect( USHORT usItem, bool fIncSub, PRECTL prcl )
    {
        return SendMsg( MM_QUERYITEMRECT, MPFROM2SHORT( usItem, fIncSub ),
                        MPFROMP( prcl ));
    }

    virtual SHORT QueryItemText( USHORT usItem, string& strText )
    {
        SHORT sMaxCount = QueryItemTextLength( usItem ) + 1;
        PSZ   pszText   = new CHAR[ sMaxCount ];
        SHORT rc;

        rc = SHORT1FROMMR( SendMsg( MM_QUERYITEMTEXT,
                                    MPFROM2SHORT( usItem, sMaxCount ),
                                    MPFROMP( pszText )));

        strText = pszText;

        delete[] pszText;

        return rc;
    }

    virtual SHORT QueryItemTextLength( USHORT usItem )
    {
        return SHORT1FROMMR( SendMsg( MM_QUERYITEMTEXTLENGTH,
                                      MPFROMSHORT( usItem )));
    }

    virtual SHORT QuerySelItemID( bool fIncSub )
    {
        return SHORT1FROMMR( SendMsg( MM_QUERYSELITEMID,
                                      MPFROM2SHORT( 0, fIncSub )));
    }

    virtual SHORT RemoveItem( USHORT usItem, bool fIncSub )
    {
        return SHORT1FROMMR( SendMsg( MM_REMOVEITEM,
                                      MPFROM2SHORT( usItem, fIncSub )));
    }

    virtual bool RemoveItemP( USHORT usItem, bool fIncSub )
    {
        return PostMsg( MM_REMOVEITEM, MPFROM2SHORT( usItem, fIncSub ));
    }

    virtual bool SelectItem( SHORT sItem, bool fIncSub, bool fDismiss )
    {
        return SendMsg( MM_SELECTITEM, MPFROM2SHORT( sItem, fIncSub ),
                        MPFROM2SHORT( 0, fDismiss ));
    }

    virtual bool SelectItemP( SHORT sItem, bool fIncSub, bool fDismiss )
    {
        return PostMsg( MM_SELECTITEM, MPFROM2SHORT( sItem, fIncSub ),
                        MPFROM2SHORT( 0, fDismiss ));
    }

    virtual bool SetDefaultItemID( ULONG ulId )
    {
        return SendMsg( MM_SETDEFAULTITEMID, MPFROMLONG( ulId ));
    }

    virtual bool SetDefaultItemIDP( ULONG ulId )
    {
        return PostMsg( MM_SETDEFAULTITEMID, MPFROMLONG( ulId ));
    }

    virtual bool SetItem( bool fIncSub, PMENUITEM pmi )
    {
        return SendMsg( MM_SETITEM, MPFROM2SHORT( 0, fIncSub ),
                        MPFROMP( pmi ));
    }

    virtual bool SetItemAttr( USHORT usItem, bool fIncSub,
                              USHORT usMask, USHORT usData )
    {
        return SendMsg( MM_SETITEMATTR, MPFROM2SHORT( usItem, fIncSub ),
                        MPFROM2SHORT( usMask, usData ));
    }

    virtual bool SetItemAttrP( USHORT usItem, bool fIncSub,
                               USHORT usMask, USHORT usData )
    {
        return PostMsg( MM_SETITEMATTR, MPFROM2SHORT( usItem, fIncSub ),
                        MPFROM2SHORT( usMask, usData ));
    }

    virtual bool SetItemHandle( USHORT usItem, ULONG ulHandle )
    {
        return SendMsg( MM_SETITEMHANDLE, MPFROMSHORT( usItem ),
                        MPFROMLONG( ulHandle ));
    }

    virtual bool SetItemHandleP( USHORT usItem, ULONG ulHandle )
    {
        return PostMsg( MM_SETITEMHANDLE, MPFROMSHORT( usItem ),
                        MPFROMLONG( ulHandle ));
    }

    virtual bool SetItemText( USHORT usItem, const string& strText )
    {
        return SendMsg( MM_SETITEMTEXT, MPFROMSHORT( usItem ),
                        MPFROMP( strText.c_str()));
    }

    virtual bool StartMenuMode( bool fShowSub, bool fResume )
    {
        return SendMsg( MM_STARTMENUMODE, MPFROM2SHORT( fShowSub, fResume ));
    }

    virtual bool StartMenuModeP( bool fShowSub, bool fResume )
    {
        return PostMsg( MM_STARTMENUMODE, MPFROM2SHORT( fShowSub, fResume ));
    }
};
#endif
