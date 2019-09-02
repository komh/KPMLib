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

#ifndef KCONTAINER_H
#define KCONTAINER_H

#define INCL_WIN
#include <os2.h>

#include <string>
#include <list>

#include "KWindow.h"

#define TOPRECC( x ) ( reinterpret_cast< PRECORDCORE >( x ))
#define TOPFI( x )   ( reinterpret_cast< PFIELDINFO >( x ))

template< typename T, bool MiniRecord = false >
class KContainer : public KWindow
{
public :
    struct StorageParam
    {
        PVOID pStorage;
        const KContainer< T, MiniRecord >* pkcnr;
    };

    KContainer() : KWindow() { _fDoSort = false; }

    virtual ~KContainer()
    {
        typename std::list< StorageParam* >::iterator it;

        for( it = _StorageParamList.begin(); it != _StorageParamList.end();
             ++it )
            delete *it;
    }

    virtual bool CreateWindow( const KWindow* pkwndP, 
                               const std::string& strName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 )
    {
        SetClassName( WC_CONTAINER );

        flStyle &= ~CCS_MINIRECORDCORE;
        if( MiniRecord )
            flStyle |= CCS_MINIRECORDCORE;

        return KWindow::CreateWindow( pkwndP, strName, flStyle, x, y,
                                      cx, cy, pkwndO, pkwndS, id,
                                      pCtlData, pPresParams );
    }

    virtual PFIELDINFO AllocDetailFieldInfo( USHORT nFieldInfo ) const
    {
        return reinterpret_cast< PFIELDINFO >
                    ( SendMsg( CM_ALLOCDETAILFIELDINFO,
                               MPFROMSHORT( nFieldInfo )));
    }

    virtual T* AllocRecord( USHORT nRecords ) const
    {
        ULONG cbRecordData = sizeof( T );

        if( MiniRecord )
            cbRecordData -= sizeof( MINIRECORDCORE );
        else
            cbRecordData -= sizeof( RECORDCORE );

        return reinterpret_cast< T* >
                    ( SendMsg( CM_ALLOCRECORD, MPFROMLONG( cbRecordData ),
                               MPFROMSHORT( nRecords )));
    }

    virtual bool Arrange( ULONG ulType, ULONG ulFlags ) const
    {
        return SendMsg( CM_ARRANGE, MPFROMLONG( ulType ),
                        MPFROMLONG( ulFlags ));
    }

    virtual bool ArrangeP( ULONG ulType, ULONG ulFlags ) const
    {
        return PostMsg( CM_ARRANGE, MPFROMLONG( ulType ),
                        MPFROMLONG( ulFlags ));
    }

    virtual bool CloseEdit() const { return SendMsg( CM_CLOSEEDIT ); }
    virtual bool CloseEditP() const { return PostMsg( CM_CLOSEEDIT ); }

    virtual bool CollapseTree( T* pRecord ) const
    {
        return SendMsg( CM_COLLAPSETREE, MPFROMP( pRecord ));
    }

    virtual bool EraseRecord( T* pRecord ) const
    {
        return SendMsg( CM_ERASERECORD, MPFROMP( pRecord ));
    }

    virtual bool ExpandTree( T* pRecord ) const
    {
        return SendMsg( CM_EXPANDTREE, MPFROMP( pRecord ));
    }

    virtual bool Filter( PVOID pStorage = 0 ) const
    {
        StorageParam sp = { pStorage, this };

        return SendMsg( CM_FILTER, MPFROMP( FilterFunc ), MPFROMP( &sp ));
    }

    virtual bool FreeDetailFieldInfo( PFIELDINFO* pFieldInfoArray,
                                      USHORT cNumFieldInfo ) const
    {
        return SendMsg( CM_FREEDETAILFIELDINFO, MPFROMP( pFieldInfoArray ),
                        MPFROMSHORT( cNumFieldInfo ));
    }

    virtual bool FreeRecord( T** pRecordArray, USHORT cNumRecord ) const
    {
        return SendMsg( CM_FREERECORD, MPFROMP( pRecordArray ),
                        MPFROMSHORT( cNumRecord ));
    }

    virtual bool HorzScrollSplitWindow( USHORT usWindow,
                                        LONG lScrollInc ) const
    {
        return SendMsg( CM_HORZSCROLLSPLITWINDOW, MPFROMSHORT( usWindow ),
                        MPFROMLONG( lScrollInc ));
    }

    virtual bool HorzScrollSplitWindowP( USHORT usWindow,
                                         LONG lScrollInc ) const
    {
        return PostMsg( CM_HORZSCROLLSPLITWINDOW, MPFROMSHORT( usWindow ),
                        MPFROMLONG( lScrollInc ));
    }

    virtual USHORT InsertDetailFieldInfo( PFIELDINFO pfi,
                                          PFIELDINFOINSERT pfii ) const
    {
        return SHORT1FROMMR( SendMsg( CM_INSERTDETAILFIELDINFO,
                                      MPFROMP( pfi ), MPFROMP( pfii )));
    }

    virtual ULONG InsertRecord( T* pRecord, PRECORDINSERT pri ) const
    {
        LONG rc = LONGFROMMR( SendMsg( CM_INSERTRECORD, MPFROMP( pRecord ),
                              MPFROMP( pri )));

        if( _fDoSort )
            SortRecord();

        return rc;
    }

    virtual ULONG InsertRecordArray( T** pRecordArray,
                                     PRECORDINSERT pri ) const
    {
        ULONG rc = LONGFROMMR( SendMsg( CM_INSERTRECORDARRAY,
                               MPFROMP( pRecordArray ), MPFROMP( pri )));

        if( _fDoSort )
            SortRecord();

        return rc;
    }

    virtual bool InvalidateDetailFieldInfo() const
    {
        return SendMsg( CM_INVALIDATEDETAILFIELDINFO );
    }

    virtual bool InvalidateDetailFieldInfoP() const
    {
        return PostMsg( CM_INVALIDATEDETAILFIELDINFO );
    }

    virtual bool InvalidateRecord( T** pRecordArray, USHORT cNumRecord,
                                   USHORT fsInvalidateRecord ) const
    {
        return SendMsg( CM_INVALIDATERECORD, MPFROMP( pRecordArray ),
                        MPFROM2SHORT( cNumRecord, fsInvalidateRecord ));
    }

    virtual bool MoveTree( PTREEMOVE ptm ) const
    {
        return SendMsg( CM_MOVETREE, MPFROMP( ptm ));
    }

    virtual bool OpenEdit( PCNREDITDATA pced ) const
    {
        return SendMsg( CM_OPENEDIT, MPFROMP( pced ));
    }

    virtual bool PaintBackground( POWNERBACKGROUND pobg ) const
    {
        return SendMsg( CM_PAINTBACKGROUND, MPFROMP( pobg ));
    }

    virtual USHORT QueryCnrInfo( PCNRINFO pci, USHORT cbBuffer ) const
    {
        return SHORT1FROMMR( SendMsg( CM_QUERYCNRINFO, MPFROMP( pci ),
                                      MPFROMSHORT( cbBuffer )));
    }

    virtual PFIELDINFO QueryDetailFieldInfo( PFIELDINFO pfiBase,
                                             USHORT cmd ) const
    {
        return reinterpret_cast< PFIELDINFO >
                    ( SendMsg( CM_QUERYDETAILFIELDINFO, MPFROMP( pfiBase ),
                               MPFROMSHORT( cmd )));
    }

    virtual LHANDLE QueryDragImage( T* pRecord ) const
    {
        return LONGFROMMR( SendMsg( CM_QUERYDRAGIMAGE, MPFROMP( pRecord )));
    }

    virtual bool QueryGridInfo( PGRIDINFO pgi ) const
    {
        return SendMsg( CM_QUERYGRIDINFO, MPFROMP( pgi ));
    }

    virtual T* QueryRecord( T* pRecord, USHORT cmd, USHORT fsSearch ) const
    {
        return reinterpret_cast< T* >
                    ( SendMsg( CM_QUERYRECORD, MPFROMP( pRecord ),
                               MPFROM2SHORT( cmd, fsSearch )));
    }

    virtual T* QueryRecordEmphasis( T* pSearchAfter, USHORT fsMask ) const
    {
        return reinterpret_cast< T* >
                    ( SendMsg( CM_QUERYRECORDEMPHASIS,
                               MPFROMP( pSearchAfter ),
                               MPFROMSHORT( fsMask )));
    }

    virtual T* QueryRecordFromRect( T* pSearchAfter,
                                    PQUERYRECFROMRECT pqrfr ) const
    {
        return reinterpret_cast< T* >
                    ( SendMsg( CM_QUERYRECORDFROMRECT,
                               MPFROMP( pSearchAfter ), MPFROMP( pqrfr )));
    }

    virtual bool QueryRecordInfo( T** pRecordArray, USHORT cNumRecord ) const
    {
        return SendMsg( CM_QUERYRECORDINFO, MPFROMP( pRecordArray ),
                        MPFROMSHORT( cNumRecord ));
    }

    virtual bool QueryRecordRect( PRECTL prcl, PQUERYRECORDRECT pqrr ) const
    {
        return SendMsg( CM_QUERYRECORDRECT, MPFROMP( prcl ),
                        MPFROMP( pqrr ));
    }

    virtual bool QueryViewportRect( PRECTL prcl, USHORT usIndicator,
                                    bool fRightSplitWindow ) const
    {
        return SendMsg( CM_QUERYVIEWPORTRECT, MPFROMP( prcl ),
                        MPFROM2SHORT( usIndicator, fRightSplitWindow ));
    }

    virtual SHORT RemoveDetailFieldInfo( PFIELDINFO* pFieldInfoArray,
                                         USHORT cNumFieldInfo,
                                         USHORT fsRemoveFieldInfo ) const
    {
        return SHORT1FROMMR( SendMsg( CM_REMOVEDETAILFIELDINFO,
                                      MPFROMP( pFieldInfoArray ),
                                      MPFROM2SHORT( cNumFieldInfo,
                                                    fsRemoveFieldInfo )));
    }

    virtual LONG RemoveRecord( T** pRecordArray, USHORT cNumRecord,
                               USHORT fsRemoveRecord ) const
    {
        return LONGFROMMR( SendMsg( CM_REMOVERECORD, MPFROMP( pRecordArray ),
                                    MPFROM2SHORT( cNumRecord,
                                                  fsRemoveRecord )));
    }

    virtual bool ScrollWindow( USHORT fsScrollDirection,
                               LONG lScrollInc ) const
    {
        return SendMsg( CM_SCROLLWINDOW, MPFROMSHORT( fsScrollDirection ),
                        MPFROMLONG( lScrollInc ));
    }

    virtual bool ScrollWindowP( USHORT fsScrollDirection,
                                LONG lScrollInc ) const
    {
        return PostMsg( CM_SCROLLWINDOW, MPFROMSHORT( fsScrollDirection ),
                        MPFROMLONG( lScrollInc ));
    }

    virtual T* SearchString( PSEARCHSTRING pss, int iAfter ) const
    {
        return reinterpret_cast< T* >
                    ( SendMsg( CM_SEARCHSTRING, MPFROMP( pss ),
                               MPFROMP( iAfter )));
    }

    virtual T* SearchString( PSEARCHSTRING pss, T* pAfter ) const
    {
        return reinterpret_cast< T* >
                    ( SendMsg( CM_SEARCHSTRING, MPFROMP( pss ),
                               MPFROMP( pAfter )));
    }

    virtual bool SetCnrInfo( PCNRINFO pCnrInfo, ULONG ulCnrInfoFl ) const
    {
        bool rc;

        if( ulCnrInfoFl & CMA_PSORTRECORD )
        {
            ulCnrInfoFl          &= ~CMA_PSORTRECORD;
            pCnrInfo->pSortRecord = 0;
            _fDoSort              = true;
        }
        else
            _fDoSort = false;

        rc = SendMsg( CM_SETCNRINFO, MPFROMP( pCnrInfo ),
                      MPFROMLONG( ulCnrInfoFl ));

        if( _fDoSort )
            SortRecord();

        return rc;
    }

    virtual bool SetGridInfo( PGRIDINFO pGridInfo, bool fRepaint ) const
    {
        return SendMsg( CM_SETGRIDINFO, MPFROMP( pGridInfo ),
                        MPFROMLONG( fRepaint ));
    }

    virtual bool SetRecordEmphasis( T* pRecord,
                                    USHORT usChangeEmphasis,
                                    USHORT fsEmphasisAttr ) const
    {
        return SendMsg( CM_SETRECORDEMPHASIS, MPFROMP( pRecord ),
                        MPFROM2SHORT( usChangeEmphasis, fsEmphasisAttr ));
    }

    virtual bool SetTextVisibility( bool fVisible ) const
    {
        return SendMsg( CM_SETTEXTVISIBILITY, MPFROMLONG( fVisible ));
    }

    virtual bool SetTextVisibilityP( bool fVisible ) const
    {
        return PostMsg( CM_SETTEXTVISIBILITY, MPFROMLONG( fVisible ));
    }

    virtual bool SnapToGrid( T* pRecord, SHORT xDrop, SHORT yDrop ) const
    {
        return SendMsg( CM_SNAPTOGRID, MPFROMP( pRecord ),
                        MPFROM2SHORT( xDrop, yDrop ));
    }

    virtual bool SortRecord( PVOID pStorage = 0 ) const
    {
        StorageParam sp = { pStorage, this };

        return SendMsg( CM_SORTRECORD, MPFROMP( SortCompare ),
                        MPFROMP( &sp ));
    }

    virtual T* I2PT( int i ) { return reinterpret_cast< T* >( i ); }

protected :

    virtual BOOL  KFilter( T* p, PVOID pStorage ) const { return TRUE; }

    virtual SHORT KSortCompare( T* p1, T* p2, PVOID pStorage ) const
    {
        return 0;
    }

private :
    mutable bool _fDoSort;

    std::list< StorageParam* > _StorageParamList;

    static BOOL EXPENTRY FilterFunc( T* p, PVOID pStorage )
    {
        StorageParam* psp = reinterpret_cast< StorageParam* >( pStorage );

        return psp->pkcnr->KFilter( p, psp->pStorage );
    }

    static SHORT EXPENTRY SortCompare( T* p1, T* p2, PVOID pStorage )
    {
        StorageParam* psp = reinterpret_cast< StorageParam* >( pStorage );

        return psp->pkcnr->KSortCompare( p1, p2, psp->pStorage );
    }
};
#endif
