#ifndef KLIST_BOX_H
#define KLIST_BOX_H

#include "KWindow.h"

class KListBox : public KWindow
{
public :
    KListBox() : KWindow() {};
    virtual ~KListBox() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    virtual bool DeleteAll() { return SendMsg( LM_DELETEALL ); }

    virtual SHORT DeleteItem( SHORT sItemIndex )
    {
        return SHORT1FROMMR( SendMsg( LM_DELETEITEM,
                                      MPFROMSHORT( sItemIndex )));
    }

    virtual SHORT InsertItem( SHORT sItemIndex, PCSZ pcszItemText )
    {
        return SHORT1FROMMR( SendMsg( LM_INSERTITEM,
                                      MPFROMSHORT( sItemIndex ),
                                      MPFROMP( pcszItemText )));
    }

    virtual LONG InsertMultiItems( PLBOXINFO plbi, PCSZ* papcszText )
    {
        return LONGFROMMR( SendMsg( LM_INSERTMULTITEMS,
                                    MPFROMP( plbi ), MPFROMP( papcszText )));
    }

    virtual SHORT QueryItemCount()
    { return SHORT1FROMMR( SendMsg( LM_QUERYITEMCOUNT )); }

    virtual ULONG QueryItemHandle( SHORT sItemIndex )
    {
        return LONGFROMMR( SendMsg( LM_QUERYITEMHANDLE,
                                    MPFROMSHORT( sItemIndex )));
    }

    virtual SHORT QueryItemText( SHORT sItemIndex, SHORT sMaxCount,
                                 PSZ pszItemText )
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYITEMTEXT,
                                      MPFROM2SHORT( sItemIndex, sMaxCount ),
                                      MPFROMP( pszItemText )));
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
    { return SHORT1FROMMR( SendMsg( LM_QUERYTOPINDEX )); }

    virtual SHORT SearchString( USHORT usCmd, SHORT sItemStart,
                                PCSZ pcszSearchString )
    {
        return SHORT1FROMMR( SendMsg( LM_SEARCHSTRING,
                                      MPFROM2SHORT( usCmd, sItemStart ),
                                      MPFROMP( pcszSearchString )));
    }

    virtual bool SelectItem( SHORT sItemIndex, bool fSelect )
    {
        return SendMsg( LM_SELECTITEM, MPFROMSHORT( sItemIndex ),
                        MPFROMLONG( fSelect ));
    }

    virtual bool SetItemHandle( SHORT sItemIndex, ULONG ulItemHandle )
    {
        return SendMsg( LM_SETITEMHANDLE, MPFROMSHORT( sItemIndex ),
                        MPFROMLONG( ulItemHandle ));
    }

    virtual bool SetItemHeight( ULONG ulNewHeight )
    { return SendMsg( LM_SETITEMHEIGHT, MPFROMLONG( ulNewHeight )); }

    virtual bool SetItemText( SHORT sItemIndex, PCSZ pcszItemText )
    {
        return SendMsg( LM_SETITEMTEXT, MPFROMSHORT( sItemIndex ),
                        MPFROMP( pcszItemText ));
    }

    virtual bool SetItemWidth( ULONG ulNewWidth )
    { return SendMsg( LM_SETITEMWIDTH, MPFROMLONG( ulNewWidth )); }

    virtual bool SetTopIndex( SHORT sItemIndex )
    { return SendMsg( LM_SETTOPINDEX, MPFROMSHORT( sItemIndex )); }
};
#endif
