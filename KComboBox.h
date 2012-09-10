#ifndef KCOMBO_BOX_H
#define KCOMBO_BOX_H

#define INCL_WIN
#include <os2.h>

#include "KWindow.h"

class KComboBox : public KWindow
{
public :
    KComboBox() : KWindow() {};
    virtual ~KComboBox() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    virtual bool Hilite( bool fHilite )
    { return SendMsg( CBM_HILITE, MPFROMLONG( fHilite )); }

    virtual bool IsLitShowing() { return SendMsg( CBM_ISLISTSHOWING ); }
    virtual bool ShowList( bool fShow )
    { return SendMsg( CBM_SHOWLIST, MPFROMLONG( fShow )); }

    // member-functions for ListBox control
    virtual bool LmDeleteAll() { return SendMsg( LM_DELETEALL ); }

    virtual SHORT LmDeleteItem( SHORT sItemIndex )
    {
        return SHORT1FROMMR( SendMsg( LM_DELETEITEM,
                                      MPFROMSHORT( sItemIndex )));
    }

    virtual SHORT LmInsertItem( SHORT sItemIndex, PCSZ pcszItemText )
    {
        return SHORT1FROMMR( SendMsg( LM_INSERTITEM,
                                      MPFROMSHORT( sItemIndex ),
                                      MPFROMP( pcszItemText )));
    }

    virtual SHORT LmQueryItemCount()
    { return SHORT1FROMMR( SendMsg( LM_QUERYITEMCOUNT )); }

    virtual SHORT LMQueryItemText( SHORT sItemIndex, SHORT sMaxCount,
                                   PSZ pszItemText )
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYITEMTEXT,
                                      MPFROM2SHORT( sItemIndex, sMaxCount ),
                                      MPFROMP( pszItemText )));
    }

    virtual SHORT LmQueryItemTextLength( SHORT sItemIndex )
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYITEMTEXTLENGTH,
                                      MPFROMSHORT( sItemIndex )));
    }

    virtual SHORT LmQuerySelection( SHORT sItemStart )
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYSELECTION,
                                      MPFROMSHORT( sItemStart )));
    }

    virtual SHORT LmQueryTopIndex()
    { return SHORT1FROMMR( SendMsg( LM_QUERYTOPINDEX )); }

    virtual SHORT LmSearchString( USHORT usCmd, SHORT sItemStart,
                                PCSZ pcszSearchString )
    {
        return SHORT1FROMMR( SendMsg( LM_SEARCHSTRING,
                                      MPFROM2SHORT( usCmd, sItemStart ),
                                      MPFROMP( pcszSearchString )));
    }

    virtual bool LmSelectItem( SHORT sItemIndex, bool fSelect )
    {
        return SendMsg( LM_SELECTITEM, MPFROMSHORT( sItemIndex ),
                        MPFROMLONG( fSelect ));
    }

    virtual bool LmSetItemText( SHORT sItemIndex, PCSZ pcszItemText )
    {
        return SendMsg( LM_SETITEMTEXT, MPFROMSHORT( sItemIndex ),
                        MPFROMP( pcszItemText ));
    }

    virtual bool LmSetTopIndex( SHORT sItemIndex )
    { return SendMsg( LM_SETTOPINDEX, MPFROMSHORT( sItemIndex )); }

    // member-functions for EntryField control
    virtual bool EmClear() { return SendMsg( EM_CLEAR ); }
    virtual bool EmCopy() { return SendMsg( EM_COPY ); }
    virtual bool EmCut() { return SendMsg( EM_CUT ); }
    virtual bool EmPaste() { return SendMsg( EM_PASTE ); }
    virtual bool EmQueryChanged() { return SendMsg( EM_QUERYCHANGED ); }
    virtual SHORT EmQueryFirstChar()
    { return SHORT1FROMMR( SendMsg( EM_QUERYFIRSTCHAR )); }

    virtual void EmQuerySel( SHORT& sMinSel, SHORT& sMaxSel )
    {
        MRESULT mr = SendMsg( EM_QUERYSEL );

        sMinSel = LOUSHORT( mr );
        sMaxSel = HIUSHORT( mr );
    }

    virtual bool EmSetFirstChar( SHORT sOffset )
    { return SendMsg( EM_SETFIRSTCHAR, MPFROMSHORT( sOffset )); }

    virtual bool EmSetSel( USHORT usMinSel, USHORT usMaxSel )
    { return SendMsg( EM_SETSEL, MPFROM2SHORT( usMinSel, usMaxSel )); }

    virtual bool EmSetTextLimit( SHORT sTextLimit )
    { return SendMsg( EM_SETTEXTLIMIT, MPFROMSHORT( sTextLimit )); }
};
#endif
