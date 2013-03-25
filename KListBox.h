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

#ifndef KLIST_BOX_H
#define KLIST_BOX_H

#include <string>

#include <vector>

#include "KWindow.h"

typedef vector< string > KLBVECSTR;

class KListBox : public KWindow
{
public :
    KListBox() : KWindow() {};
    virtual ~KListBox() {};

    virtual bool CreateWindow( const KWindow* pkwndP, const string& strName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    virtual LONG DeleteLboxItem( LONG index ) const
    {
        return WinDeleteLboxItem( _hwnd, index );
    }

    virtual LONG InsertLboxItem( LONG index, const string& str ) const
    {
        return WinInsertLboxItem( _hwnd, index, str.c_str());
    }

    virtual LONG QueryLboxSelectedItem() const
    {
        return WinQueryLboxSelectedItem( _hwnd );
    }

    virtual bool SetLboxItemText( LONG index, const string& str ) const
    {
        return WinSetLboxItemText( _hwnd, index, str.c_str());
    }

    virtual bool DeleteAll()  const { return SendMsg( LM_DELETEALL ); }
    virtual bool DeleteAllP()  const { return PostMsg( LM_DELETEALL ); }

    virtual SHORT DeleteItem( SHORT sItemIndex ) const
    {
        return SHORT1FROMMR( SendMsg( LM_DELETEITEM,
                                      MPFROMSHORT( sItemIndex )));
    }

    virtual bool DeleteItemP( SHORT sItemIndex ) const
    {
        return PostMsg( LM_DELETEITEM, MPFROMSHORT( sItemIndex ));
    }

    virtual SHORT InsertItem( SHORT sItemIndex,
                              const string& strItemText ) const
    {
        return SHORT1FROMMR( SendMsg( LM_INSERTITEM,
                                      MPFROMSHORT( sItemIndex ),
                                      MPFROMP( strItemText.c_str())));
    }

    virtual LONG InsertMultiItems( PLBOXINFO plbi, PCSZ* papcszText ) const
    {
        return LONGFROMMR( SendMsg( LM_INSERTMULTITEMS,
                                    MPFROMP( plbi ), MPFROMP( papcszText )));
    }

    virtual LONG InsertMultiItems( PLBOXINFO plbi,
                                   const KLBVECSTR& vsText ) const
    {
        PCSZ* papcszText;
        LONG  rc;

        papcszText = new PCSZ[ plbi->ulItemCount ];

        for( size_t i = 0; i < vsText.size(); i++ )
            papcszText[ i ] = vsText[ i ].c_str();

        rc = LONGFROMMR( SendMsg( LM_INSERTMULTITEMS,
                                  MPFROMP( plbi ), MPFROMP( papcszText )));

        delete[] papcszText;

        return rc;
    }

    virtual SHORT QueryItemCount() const
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYITEMCOUNT ));
    }

    virtual ULONG QueryItemHandle( SHORT sItemIndex ) const
    {
        return LONGFROMMR( SendMsg( LM_QUERYITEMHANDLE,
                                    MPFROMSHORT( sItemIndex )));
    }

    virtual SHORT QueryItemText( SHORT sItemIndex,
                                 string& strItemText ) const
    {
        SHORT sMaxCount = QueryItemTextLength( sItemIndex ) + 1;
        PSZ   pszItemText = new CHAR[ sMaxCount ];
        SHORT rc;

        rc = SHORT1FROMMR( SendMsg( LM_QUERYITEMTEXT,
                                    MPFROM2SHORT( sItemIndex, sMaxCount ),
                                    MPFROMP( pszItemText )));

        strItemText = pszItemText;

        delete[] pszItemText;

        return rc;
    }

    virtual SHORT QueryItemTextLength( SHORT sItemIndex ) const
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYITEMTEXTLENGTH,
                                      MPFROMSHORT( sItemIndex )));
    }

    virtual SHORT QuerySelection( SHORT sItemStart ) const
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYSELECTION,
                                      MPFROMSHORT( sItemStart )));
    }

    virtual SHORT QueryTopIndex() const
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYTOPINDEX ));
    }

    virtual SHORT SearchString( USHORT usCmd, SHORT sItemStart,
                                const string& strSearchString ) const
    {
        return SHORT1FROMMR( SendMsg( LM_SEARCHSTRING,
                                      MPFROM2SHORT( usCmd, sItemStart ),
                                      MPFROMP( strSearchString.c_str())));
    }

    virtual bool SelectItem( SHORT sItemIndex, bool fSelect ) const
    {
        return SendMsg( LM_SELECTITEM, MPFROMSHORT( sItemIndex ),
                        MPFROMLONG( fSelect ));
    }

    virtual bool SelectItemP( SHORT sItemIndex, bool fSelect ) const
    {
        return PostMsg( LM_SELECTITEM, MPFROMSHORT( sItemIndex ),
                        MPFROMLONG( fSelect ));
    }

    virtual bool SetItemHandle( SHORT sItemIndex, ULONG ulItemHandle ) const
    {
        return SendMsg( LM_SETITEMHANDLE, MPFROMSHORT( sItemIndex ),
                        MPFROMLONG( ulItemHandle ));
    }

    virtual bool SetItemHandleP( SHORT sItemIndex, ULONG ulItemHandle ) const
    {
        return PostMsg( LM_SETITEMHANDLE, MPFROMSHORT( sItemIndex ),
                        MPFROMLONG( ulItemHandle ));
    }

    virtual bool SetItemHeight( ULONG ulNewHeight ) const
    {
        return SendMsg( LM_SETITEMHEIGHT, MPFROMLONG( ulNewHeight ));
    }

    virtual bool SetItemHeightP( ULONG ulNewHeight ) const
    {
        return PostMsg( LM_SETITEMHEIGHT, MPFROMLONG( ulNewHeight ));
    }

    virtual bool SetItemText( SHORT sItemIndex,
                              const string& strItemText ) const
    {
        return SendMsg( LM_SETITEMTEXT, MPFROMSHORT( sItemIndex ),
                        MPFROMP( strItemText.c_str()));
    }

    virtual bool SetItemWidth( ULONG ulNewWidth ) const
    {
        return SendMsg( LM_SETITEMWIDTH, MPFROMLONG( ulNewWidth ));
    }

    virtual bool SetItemWidthP( ULONG ulNewWidth ) const
    {
        return PostMsg( LM_SETITEMWIDTH, MPFROMLONG( ulNewWidth ));
    }

    virtual bool SetTopIndex( SHORT sItemIndex ) const
    {
        return SendMsg( LM_SETTOPINDEX, MPFROMSHORT( sItemIndex ));
    }

    virtual bool SetTopIndexP( SHORT sItemIndex ) const
    {
        return PostMsg( LM_SETTOPINDEX, MPFROMSHORT( sItemIndex ));
    }
};
#endif
