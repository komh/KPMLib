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

#ifndef KENTRY_FIELD_H
#define KENTRY_FIELD_H

#include <string>

#include "KWindow.h"

class KEntryField : public KWindow
{
public :
    KEntryField() : KWindow() {};
    virtual ~KEntryField() {};

    virtual bool CreateWindow( const KWindow* pkwndP, const string& strName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 );

    virtual bool Clear() { return SendMsg( EM_CLEAR ); }
    virtual bool ClearP() { return PostMsg( EM_CLEAR ); }
    virtual bool Copy() { return SendMsg( EM_COPY ); }
    virtual bool CopyP() { return PostMsg( EM_COPY ); }
    virtual bool Cut() { return SendMsg( EM_CUT ); }
    virtual bool CutP() { return PostMsg( EM_CUT ); }
    virtual bool Paste() { return SendMsg( EM_PASTE ); }
    virtual bool PasteP() { return PostMsg( EM_PASTE ); }
    virtual bool QueryChanged() { return SendMsg( EM_QUERYCHANGED ); }

    virtual SHORT QueryFirstChar()
    {
        return SHORT1FROMMR( SendMsg( EM_QUERYFIRSTCHAR ));
    }

    virtual bool QueryReadOnly() { return SendMsg( EM_QUERYREADONLY ); }

    virtual void QuerySel( SHORT& sMinSel, SHORT& sMaxSel )
    {
        MRESULT mr = SendMsg( EM_QUERYSEL );

        sMinSel = LOUSHORT( mr );
        sMaxSel = HIUSHORT( mr );
    }

    virtual bool SetFirstChar( SHORT sOffset )
    {
        return SendMsg( EM_SETFIRSTCHAR, MPFROMSHORT( sOffset ));
    }

    virtual bool SetFirstCharP( SHORT sOffset )
    {
        return PostMsg( EM_SETFIRSTCHAR, MPFROMSHORT( sOffset ));
    }

    virtual bool SetInsertMode( bool fInsert )
    {
        return SendMsg( EM_SETINSERTMODE, MPFROMLONG( fInsert ));
    }

    virtual bool SetInsertModeP( bool fInsert )
    {
        return PostMsg( EM_SETINSERTMODE, MPFROMLONG( fInsert ));
    }

    virtual bool SetReadOnly( bool fReadOnly )
    {
        return SendMsg( EM_SETREADONLY, MPFROMLONG( fReadOnly ));
    }

    virtual bool SetReadOnlyP( bool fReadOnly )
    {
        return PostMsg( EM_SETREADONLY, MPFROMLONG( fReadOnly ));
    }

    virtual bool SetSel( USHORT usMinSel, USHORT usMaxSel )
    {
        return SendMsg( EM_SETSEL, MPFROM2SHORT( usMinSel, usMaxSel ));
    }

    virtual bool SetSelP( USHORT usMinSel, USHORT usMaxSel )
    {
        return PostMsg( EM_SETSEL, MPFROM2SHORT( usMinSel, usMaxSel ));
    }

    virtual bool SetTextLimit( SHORT sTextLimit )
    {
        return SendMsg( EM_SETTEXTLIMIT, MPFROMSHORT( sTextLimit ));
    }

    virtual bool SetTextLimitP( SHORT sTextLimit )
    {
        return PostMsg( EM_SETTEXTLIMIT, MPFROMSHORT( sTextLimit ));
    }
};
#endif
