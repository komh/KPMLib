#ifndef KMENU_H
#define KMENU_H

#include "KWindow.h"

class KMenu : public KWindow
{
public :
    KMenu() : KWindow() {};
    virtual ~KMenu() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    virtual LONG DeleteItem( ULONG ulItem, bool fIncSub )
    {
        return LONGFROMMR( SendMsg( MM_DELETEITEM,
                                    MPFROM2SHORT( ulItem, fIncSub )));
    }

    virtual void EndMenuMode( bool fDismiss )
    { SendMsg( MM_ENDMENUMODE, MPFROMLONG( fDismiss )); }

    virtual LONG InsertItem( PMENUITEM pmi, PCSZ pcszText )
    {
        return LONGFROMMR( SendMsg( MM_INSERTITEM, MPFROMP( pmi ),
                                    MPFROMP( pcszText )));
    }

    virtual bool IsItemValid( ULONG ulItem, BOOL fIncSub )
    { return SendMsg( MM_ISITEMVALID, MPFROM2SHORT( ulItem, fIncSub )); }

    virtual LONG ItemIDFromPosition( LONG lItemIndex )
    {
        return LONGFROMMR( SendMsg( MM_ITEMIDFROMPOSITION,
                                    MPFROMLONG( lItemIndex )));
    }

    virtual LONG ItemPositionFromID( ULONG ulItem, bool fIncSub )
    {
        return LONGFROMMR( SendMsg( MM_ITEMPOSITIONFROMID,
                                    MPFROM2SHORT( ulItem, fIncSub )));
    }

    virtual ULONG QueryDefaultItemID()
    { return LONGFROMMR( SendMsg( MM_QUERYDEFAULTITEMID )); }

    virtual bool QueryItem( ULONG ulItem, bool fIncSub, PMENUITEM pmi )
    {
        return SendMsg( MM_QUERYITEM, MPFROM2SHORT( ulItem, fIncSub ),
                        MPFROMP( pmi ));
    }

    virtual ULONG QueryItemAttr( ULONG ulItem, bool fIncSub, ULONG ulMask )
    {
        return LONGFROMMR( SendMsg( MM_QUERYITEMATTR,
                                    MPFROM2SHORT( ulItem, fIncSub ),
                                    MPFROMLONG( ulMask )));
    }

    virtual LONG QueryItemCount()
    { return LONGFROMMR( SendMsg( MM_QUERYITEMCOUNT )); }

    virtual bool QueryItemRect( ULONG ulItem, bool fIncSub, PRECTL prcl )
    {
        return SendMsg( MM_QUERYITEMRECT, MPFROM2SHORT( ulItem, fIncSub ),
                        MPFROMP( prcl ));
    }

    virtual LONG QueryItemText( ULONG ulItem, LONG lMaxCount, PCSZ pcszText )
    {
        return LONGFROMMR( SendMsg( MM_QUERYITEMTEXT,
                                    MPFROM2SHORT( ulItem, lMaxCount ),
                                    MPFROMP( pcszText )));
    }

    virtual LONG QueryItemTextLength( ULONG ulItem )
    {
        return LONGFROMMR( SendMsg( MM_QUERYITEMTEXTLENGTH,
                                    MPFROMLONG( ulItem )));
    }

    virtual LONG QuerySelItemID( bool fIncSub )
    {
        return LONGFROMMR( SendMsg( MM_QUERYSELITEMID,
                                    MPFROM2SHORT( 0, fIncSub )));
    }

    virtual LONG RemoveItem( ULONG ulItem, bool fIncSub )
    {
        return LONGFROMMR( SendMsg( MM_REMOVEITEM,
                                    MPFROM2SHORT( ulItem, fIncSub )));
    }

    virtual bool SelectItem( LONG lItem, bool fIncSub, bool fDismiss )
    {
        return SendMsg( MM_SELECTITEM, MPFROM2SHORT( lItem, fIncSub ),
                        MPFROM2SHORT( 0, fDismiss ));
    }

    virtual bool SetDefaultItemID( ULONG ulId )
    { return SendMsg( MM_SETDEFAULTITEMID, MPFROMLONG( ulId )); }

    virtual bool SetItem( bool fIncSub, PMENUITEM pmi )
    {
        return SendMsg( MM_SETITEM, MPFROM2SHORT( 0, fIncSub ),
                        MPFROMP( pmi ));
    }

    virtual bool SetItemAttr( ULONG ulItem, bool fIncSub,
                              ULONG ulMask, ULONG ulData )
    {
        return SendMsg( MM_SETITEMATTR, MPFROM2SHORT( ulItem, fIncSub ),
                        MPFROM2SHORT( ulMask, ulData ));
    }

    virtual bool SetItemHandle( ULONG ulItem, ULONG ulHandle )
    {
        return SendMsg( MM_SETITEMHANDLE, MPFROMLONG( ulItem ),
                        MPFROMLONG( ulHandle ));
    }

    virtual bool SetItemText( ULONG ulItem, PCSZ pcszText )
    {
        return SendMsg( MM_SETITEMTEXT, MPFROMLONG( ulItem ),
                        MPFROMP( pcszText ));
    }

    virtual bool StartMenuMode( bool fShowSub, bool fResume )
    { return SendMsg( MM_STARTMENUMODE, MPFROM2SHORT( fShowSub, fResume )); }
};
#endif
