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

    virtual LONG DeleteLboxItem( LONG index )
    {
        return WinDeleteLboxItem( _hwnd, index );
    }

    virtual LONG InsertLboxItem( LONG index, const string& str )
    {
        return WinInsertLboxItem( _hwnd, index, str.c_str());
    }

    virtual LONG QueryLboxSelectedItem()
    {
        return WinQueryLboxSelectedItem( _hwnd );
    }

    virtual bool SetLboxItemText( LONG index, const string& str )
    {
        return WinSetLboxItemText( _hwnd, index, str.c_str());
    }

    virtual bool DeleteAll() { return SendMsg( LM_DELETEALL ); }
    virtual bool DeleteAllP() { return PostMsg( LM_DELETEALL ); }

    virtual SHORT DeleteItem( SHORT sItemIndex )
    {
        return SHORT1FROMMR( SendMsg( LM_DELETEITEM,
                                      MPFROMSHORT( sItemIndex )));
    }

    virtual bool DeleteItemP( SHORT sItemIndex )
    {
        return PostMsg( LM_DELETEITEM, MPFROMSHORT( sItemIndex ));
    }

    virtual SHORT InsertItem( SHORT sItemIndex, const string& strItemText )
    {
        return SHORT1FROMMR( SendMsg( LM_INSERTITEM,
                                      MPFROMSHORT( sItemIndex ),
                                      MPFROMP( strItemText.c_str())));
    }

    virtual bool InsertItemP( SHORT sItemIndex, const string& strItemText )
    {
        return PostMsg( LM_INSERTITEM, MPFROMSHORT( sItemIndex ),
                        MPFROMP( strItemText.c_str()));
    }

    virtual LONG InsertMultiItems( PLBOXINFO plbi, const KLBVECSTR& vsText )
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

#if 0
    virtual bool InsertMultiItemsP( PLBOXINFO plbi, const KLBVECSTR& vsText )
    {
        PCSZ* papcszText;
        LONG  rc;

        papcszText = new PCSZ[ plbi->ulItemCount ];

        for( size_t i = 0; i < vsText.size(); i++ )
            papcszText[ i ] = vsText[ i ].c_str();

        rc = PostMsg( LM_INSERTMULTITEMS, MPFROMP( plbi ),
                      MPFROMP( papcszText ));

        // FIXME :
        // this causes to crash because memory can be freed
        // before it is passed to PM
        delete[] papcszText;

        return rc;
    }
#endif

    virtual SHORT QueryItemCount()
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYITEMCOUNT ));
    }

    virtual ULONG QueryItemHandle( SHORT sItemIndex )
    {
        return LONGFROMMR( SendMsg( LM_QUERYITEMHANDLE,
                                    MPFROMSHORT( sItemIndex )));
    }

    virtual SHORT QueryItemText( SHORT sItemIndex, string& strItemText )
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

    virtual SHORT QueryItemTextLength( SHORT sItemIndex )
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYITEMTEXTLENGTH,
                                      MPFROMSHORT( sItemIndex )));
    }

    virtual SHORT QuerySelection( SHORT sItemStart )
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYSELECTION,
                                      MPFROMSHORT( sItemStart )));
    }

    virtual SHORT QueryTopIndex()
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYTOPINDEX ));
    }

    virtual SHORT SearchString( USHORT usCmd, SHORT sItemStart,
                                const string& strSearchString )
    {
        return SHORT1FROMMR( SendMsg( LM_SEARCHSTRING,
                                      MPFROM2SHORT( usCmd, sItemStart ),
                                      MPFROMP( strSearchString.c_str())));
    }

    virtual bool SelectItem( SHORT sItemIndex, bool fSelect )
    {
        return SendMsg( LM_SELECTITEM, MPFROMSHORT( sItemIndex ),
                        MPFROMLONG( fSelect ));
    }

    virtual bool SelectItemP( SHORT sItemIndex, bool fSelect )
    {
        return PostMsg( LM_SELECTITEM, MPFROMSHORT( sItemIndex ),
                        MPFROMLONG( fSelect ));
    }

    virtual bool SetItemHandle( SHORT sItemIndex, ULONG ulItemHandle )
    {
        return SendMsg( LM_SETITEMHANDLE, MPFROMSHORT( sItemIndex ),
                        MPFROMLONG( ulItemHandle ));
    }

    virtual bool SetItemHandleP( SHORT sItemIndex, ULONG ulItemHandle )
    {
        return PostMsg( LM_SETITEMHANDLE, MPFROMSHORT( sItemIndex ),
                        MPFROMLONG( ulItemHandle ));
    }

    virtual bool SetItemHeight( ULONG ulNewHeight )
    {
        return SendMsg( LM_SETITEMHEIGHT, MPFROMLONG( ulNewHeight ));
    }

    virtual bool SetItemHeightP( ULONG ulNewHeight )
    {
        return PostMsg( LM_SETITEMHEIGHT, MPFROMLONG( ulNewHeight ));
    }

    virtual bool SetItemText( SHORT sItemIndex, const string& strItemText )
    {
        return SendMsg( LM_SETITEMTEXT, MPFROMSHORT( sItemIndex ),
                        MPFROMP( strItemText.c_str()));
    }

    virtual bool SetItemTextP( SHORT sItemIndex, const string& strItemText )
    {
        return PostMsg( LM_SETITEMTEXT, MPFROMSHORT( sItemIndex ),
                        MPFROMP( strItemText.c_str()));
    }

    virtual bool SetItemWidth( ULONG ulNewWidth )
    {
        return SendMsg( LM_SETITEMWIDTH, MPFROMLONG( ulNewWidth ));
    }

    virtual bool SetItemWidthP( ULONG ulNewWidth )
    {
        return PostMsg( LM_SETITEMWIDTH, MPFROMLONG( ulNewWidth ));
    }

    virtual bool SetTopIndex( SHORT sItemIndex )
    {
        return SendMsg( LM_SETTOPINDEX, MPFROMSHORT( sItemIndex ));
    }

    virtual bool SetTopIndexP( SHORT sItemIndex )
    {
        return PostMsg( LM_SETTOPINDEX, MPFROMSHORT( sItemIndex ));
    }
};
#endif
