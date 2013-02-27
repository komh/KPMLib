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

#ifndef KCOMBO_BOX_H
#define KCOMBO_BOX_H

#define INCL_WIN
#include <os2.h>

#include <string>

#include "KWindow.h"

class KComboBox : public KWindow
{
public :
    KComboBox() : KWindow() {};
    virtual ~KComboBox() {};

    virtual bool CreateWindow( const KWindow* pkwndP, const string& strName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    virtual bool Hilite( bool fHilite )
    {
        return SendMsg( CBM_HILITE, MPFROMLONG( fHilite ));
    }

    virtual bool HiliteP( bool fHilite )
    {
        return PostMsg( CBM_HILITE, MPFROMLONG( fHilite ));
    }

    virtual bool IsLitShowing() { return SendMsg( CBM_ISLISTSHOWING ); }

    virtual bool ShowList( bool fShow )
    {
        return SendMsg( CBM_SHOWLIST, MPFROMLONG( fShow ));
    }

    virtual bool ShowListP( bool fShow )
    {
        return PostMsg( CBM_SHOWLIST, MPFROMLONG( fShow ));
    }

    // member-functions for ListBox control
    virtual bool LmDeleteAll() { return SendMsg( LM_DELETEALL ); }
    virtual bool LmDeleteAllP() { return PostMsg( LM_DELETEALL ); }

    virtual SHORT LmDeleteItem( SHORT sItemIndex )
    {
        return SHORT1FROMMR( SendMsg( LM_DELETEITEM,
                                      MPFROMSHORT( sItemIndex )));
    }

    virtual bool LmDeleteItemP( SHORT sItemIndex )
    {
        return PostMsg( LM_DELETEITEM, MPFROMSHORT( sItemIndex ));
    }

    virtual SHORT LmInsertItem( SHORT sItemIndex, const string& strItemText )
    {
        return SHORT1FROMMR( SendMsg( LM_INSERTITEM,
                                      MPFROMSHORT( sItemIndex ),
                                      MPFROMP( strItemText.c_str())));
    }

    virtual bool LmInsertItemP( SHORT sItemIndex, const string& strItemText )
    {
        return PostMsg( LM_INSERTITEM, MPFROMSHORT( sItemIndex ),
                        MPFROMP( strItemText.c_str()));
    }

    virtual SHORT LmQueryItemCount()
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYITEMCOUNT ));
    }

    virtual SHORT LMQueryItemText( SHORT sItemIndex, string& strItemText )
    {
        SHORT sMaxCount   = LmQueryItemTextLength( sItemIndex ) + 1;
        PSZ   pszItemText = new CHAR[ sMaxCount ];;
        SHORT rc;

        rc = SHORT1FROMMR( SendMsg( LM_QUERYITEMTEXT,
                                    MPFROM2SHORT( sItemIndex, sMaxCount ),
                                    MPFROMP( pszItemText )));

        strItemText = pszItemText;

        delete[] pszItemText;

        return rc;
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
    {
        return SHORT1FROMMR( SendMsg( LM_QUERYTOPINDEX ));
    }

    virtual SHORT LmSearchString( USHORT usCmd, SHORT sItemStart,
                                  const string& strSearchString )
    {
        return SHORT1FROMMR( SendMsg( LM_SEARCHSTRING,
                                      MPFROM2SHORT( usCmd, sItemStart ),
                                      MPFROMP( strSearchString.c_str())));
    }

    virtual bool LmSelectItem( SHORT sItemIndex, bool fSelect )
    {
        return SendMsg( LM_SELECTITEM, MPFROMSHORT( sItemIndex ),
                        MPFROMLONG( fSelect ));
    }

    virtual bool LmSelectItemP( SHORT sItemIndex, bool fSelect )
    {
        return PostMsg( LM_SELECTITEM, MPFROMSHORT( sItemIndex ),
                        MPFROMLONG( fSelect ));
    }

    virtual bool LmSetItemText( SHORT sItemIndex, const string& strItemText )
    {
        return SendMsg( LM_SETITEMTEXT, MPFROMSHORT( sItemIndex ),
                        MPFROMP( strItemText.c_str()));
    }

    virtual bool LmSetItemTextP( SHORT sItemIndex, const string& strItemText )
    {
        return PostMsg( LM_SETITEMTEXT, MPFROMSHORT( sItemIndex ),
                        MPFROMP( strItemText.c_str()));
    }

    virtual bool LmSetTopIndex( SHORT sItemIndex )
    {
        return SendMsg( LM_SETTOPINDEX, MPFROMSHORT( sItemIndex ));
    }

    virtual bool LmSetTopIndexP( SHORT sItemIndex )
    {
        return PostMsg( LM_SETTOPINDEX, MPFROMSHORT( sItemIndex ));
    }

    // member-functions for EntryField control
    virtual bool EmClear() { return SendMsg( EM_CLEAR ); }
    virtual bool EmClearP() { return PostMsg( EM_CLEAR ); }
    virtual bool EmCopy() { return SendMsg( EM_COPY ); }
    virtual bool EmCopyP() { return PostMsg( EM_COPY ); }
    virtual bool EmCut() { return SendMsg( EM_CUT ); }
    virtual bool EmCutP() { return PostMsg( EM_CUT ); }
    virtual bool EmPaste() { return SendMsg( EM_PASTE ); }
    virtual bool EmPasteP() { return PostMsg( EM_PASTE ); }
    virtual bool EmQueryChanged() { return SendMsg( EM_QUERYCHANGED ); }

    virtual SHORT EmQueryFirstChar()
    {
        return SHORT1FROMMR( SendMsg( EM_QUERYFIRSTCHAR ));
    }

    virtual void EmQuerySel( SHORT& sMinSel, SHORT& sMaxSel )
    {
        MRESULT mr = SendMsg( EM_QUERYSEL );

        sMinSel = LOUSHORT( mr );
        sMaxSel = HIUSHORT( mr );
    }

    virtual bool EmSetFirstChar( SHORT sOffset )
    {
        return SendMsg( EM_SETFIRSTCHAR, MPFROMSHORT( sOffset ));
    }

    virtual bool EmSetFirstCharP( SHORT sOffset )
    {
        return PostMsg( EM_SETFIRSTCHAR, MPFROMSHORT( sOffset ));
    }

    virtual bool EmSetSel( USHORT usMinSel, USHORT usMaxSel )
    {
        return SendMsg( EM_SETSEL, MPFROM2SHORT( usMinSel, usMaxSel ));
    }

    virtual bool EmSetSelP( USHORT usMinSel, USHORT usMaxSel )
    {
        return PostMsg( EM_SETSEL, MPFROM2SHORT( usMinSel, usMaxSel ));
    }

    virtual bool EmSetTextLimit( SHORT sTextLimit )
    {
        return SendMsg( EM_SETTEXTLIMIT, MPFROMSHORT( sTextLimit ));
    }

    virtual bool EmSetTextLimitP( SHORT sTextLimit )
    {
        return PostMsg( EM_SETTEXTLIMIT, MPFROMSHORT( sTextLimit ));
    }
};
#endif
