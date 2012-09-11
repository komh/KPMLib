#ifndef KCONTAINER_H
#define KCONTAINER_H

#define INCL_WIN
#include <os2.h>

#include "KWindow.h"

template< typename T, bool MiniRecord = false >
class KContainer : public KWindow
{
public :
    KContainer() : KWindow() {};
    virtual ~KContainer() {};

    virtual bool CreateWindow( const KWindow* pkwndP, PCSZ pcszName,
                               ULONG flStyle, LONG x, LONG y,
                               LONG cx, LONG cy, const KWindow* pkwndO,
                               const KWindow* pkwndS, ULONG id,
                               PVOID pCtlData = 0, PVOID pPresParams = 0 )
    {
        SetClassName( PMLITERAL( WC_CONTAINER ));

        flStyle &= ~CCS_MINIRECORDCORE;
        if( MiniRecord )
            flStyle |= CCS_MINIRECORDCORE;

        return KWindow::CreateWindow( pkwndP, pcszName, flStyle, x, y,
                                      cx, cy, pkwndO, pkwndS, id,
                                      pCtlData, pPresParams );
    }

    virtual PFIELDINFO AllocDetailFieldInfo( USHORT nFieldInfo )
    {
        return reinterpret_cast< PFIELDINFO >
                    ( SendMsg( CM_ALLOCDETAILFIELDINFO,
                               MPFROMSHORT( nFieldInfo )));
    }

    virtual T* AllocRecord( USHORT nRecords )
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

    virtual bool Arrange( ULONG ulType, ULONG ulFlags )
    {
        return SendMsg( CM_ARRANGE, MPFROMLONG( ulType ),
                        MPFROMLONG( ulFlags ));
    }

    virtual bool CloseEdit() { return SendMsg( CM_CLOSEEDIT ); }
    virtual bool CollapseTree( T* pRecord )
    { return SendMsg( CM_COLLAPSETREE, MPFROMP( pRecord )); }

    virtual bool EraseRecord( T* pRecord )
    { return SendMsg( CM_ERASERECORD, MPFROMP( pRecord )); }

    virtual bool ExpandTree( T* pRecord )
    { return SendMsg( CM_EXPANDTREE, MPFROMP( pRecord )); }

    virtual bool Filter( PFN pfnFilter, PVOID pStorage )
    { return SendMsg( CM_FILTER, MPFROMP( pfnFilter ), MPFROMP( pStorage )); }

    virtual bool FreeDetailFieldInfo( PVOID pFieldInfoArray,
                                      USHORT cNumFieldInfo )
    {
        return SendMsg( CM_FREEDETAILFIELDINFO, MPFROMP( pFieldInfoArray ),
                        MPFROMSHORT( cNumFieldInfo ));
    }

    virtual bool FreeRecord( PVOID pRecordArray, USHORT cNumRecord )
    {
        return SendMsg( CM_FREERECORD, MPFROMP( pRecordArray ),
                        MPFROMSHORT( cNumRecord ));
    }

    virtual bool HorzScrollSplitWindow( USHORT usWindow, LONG lScrollInc )
    {
        return SendMsg( CM_HORZSCROLLSPLITWINDOW, MPFROMSHORT( usWindow ),
                        MPFROMLONG( lScrollInc ));
    }

    virtual USHORT InsertDetailFieldInfo( PFIELDINFO pfi,
                                          PFIELDINFOINSERT pfii )
    {
        return SHORT1FROMMR( SendMsg( CM_INSERTDETAILFIELDINFO,
                                      MPFROMP( pfi ), MPFROMP( pfii )));
    }

    virtual ULONG InsertRecord( T* pRecord, PRECORDINSERT pri )
    {
        return LONGFROMMR( SendMsg( CM_INSERTRECORD, MPFROMP( pRecord ),
                                    MPFROMP( pri )));
    }

    virtual ULONG InsertRecordArray( PVOID pRecordArray, PRECORDINSERT pri )
    {
        return LONGFROMMR( SendMsg( CM_INSERTRECORDARRAY,
                                    MPFROMP( pRecordArray ), MPFROMP( pri )));
    }

    virtual bool InvalidateDetailFieldInfo()
    { return SendMsg( CM_INVALIDATEDETAILFIELDINFO ); }

    virtual bool InvalidateRecord( PVOID pRecordArray, USHORT cNumRecord,
                                   USHORT fsInvalidateRecord )
    {
        return SendMsg( CM_INVALIDATERECORD, MPFROMP( pRecordArray ),
                        MPFROM2SHORT( cNumRecord, fsInvalidateRecord ));
    }

    virtual bool MoveTree( PTREEMOVE ptm )
    { return SendMsg( CM_MOVETREE, MPFROMP( ptm )); }

    virtual bool OpenEdit( PCNREDITDATA pced )
    { return SendMsg( CM_OPENEDIT, MPFROMP( pced )); }

    virtual bool PaintBackground( POWNERBACKGROUND pobg )
    { return SendMsg( CM_PAINTBACKGROUND, MPFROMP( pobg )); }

    virtual USHORT QueryCnrInfo( PCNRINFO pci, USHORT cbBuffer )
    {
        return SHORT1FROMMR( SendMsg( CM_QUERYCNRINFO, MPFROMP( pci ),
                                      MPFROMSHORT( cbBuffer )));
    }

    virtual PFIELDINFO QueryDetailFieldInfo( PFIELDINFO pfiBase, USHORT cmd )
    {
        return reinterpret_cast< PFIELDINFO >
                    ( SendMsg( CM_QUERYDETAILFIELDINFO, MPFROMP( pfiBase ),
                               MPFROMSHORT( cmd )));
    }

    virtual LHANDLE QueryDragImage( T* pRecord )
    { return LONGFROMMR( SendMsg( CM_QUERYDRAGIMAGE, MPFROMP( pRecord ))); }

    virtual bool QueryGridInfo( PGRIDINFO pgi )
    { return SendMsg( CM_QUERYGRIDINFO, MPFROMP( pgi )); }

    virtual T* QueryRecord( T* pRecord, USHORT cmd, USHORT fsSearch )
    {
        return reinterpret_cast< T* >
                    ( SendMsg( CM_QUERYRECORD, MPFROMP( pRecord ),
                               MPFROM2SHORT( cmd, fsSearch )));
    }

    virtual T* QueryRecordEmphasis( T* pSearchAfter, USHORT fsMask )
    {
        return reinterpret_cast< T* >
                    ( SendMsg( CM_QUERYRECORDEMPHASIS,
                               MPFROMP( pSearchAfter ),
                               MPFROMSHORT( fsMask )));
    }

    virtual T* QueryRecordFromRect( T* pSearchAfter, PQUERYRECFROMRECT pqrfr )
    {
        return reinterpret_cast< T* >
                    ( SendMsg( CM_QUERYRECORDFROMRECT,
                               MPFROMP( pSearchAfter ), MPFROMP( pqrfr )));
    }

    virtual bool QueryRecordInfo( PVOID pRecordArray, USHORT cNumRecord )
    {
        return SendMsg( CM_QUERYRECORDINFO, MPFROMP( pRecordArray ),
                        MPFROMSHORT( cNumRecord ));
    }

    virtual bool QueryRecordRect( PRECTL prcl, PQUERYRECORDRECT pqrr )
    {
        return SendMsg( CM_QUERYRECORDRECT, MPFROMP( prcl ),
                        MPFROMP( pqrr ));
    }

    virtual bool QueryViewportRect( PRECTL prcl, USHORT usIndicator,
                                    bool fRightSplitWindow )
    {
        return SendMsg( CM_QUERYVIEWPORTRECT, MPFROMP( prcl ),
                        MPFROM2SHORT( usIndicator, fRightSplitWindow ));
    }

    virtual SHORT RemoveDetailFieldInfo( PVOID pFieldInfoArray,
                                         USHORT cNumFieldInfo,
                                         USHORT fsRemoveFieldInfo )
    {
        return SHORT1FROMMR( SendMsg( CM_REMOVEDETAILFIELDINFO,
                                      MPFROMP( pFieldInfoArray ),
                                      MPFROM2SHORT( cNumFieldInfo,
                                                    fsRemoveFieldInfo )));
    }

    virtual LONG RemoveRecord( PVOID pRecordArray, USHORT cNumRecord,
                               USHORT fsRemoveRecord )
    {
        return LONGFROMMR( SendMsg( CM_REMOVERECORD, MPFROMP( pRecordArray ),
                                    MPFROM2SHORT( cNumRecord,
                                                  fsRemoveRecord )));
    }

    virtual bool ScrollWindow( USHORT fsScrollDirection, LONG lScrollInc )
    {
        return SendMsg( CM_SCROLLWINDOW, MPFROMSHORT( fsScrollDirection ),
                        MPFROMLONG( lScrollInc ));
    }

    virtual T* SearchString( PSEARCHSTRING pss, T* pAfter )
    {
        return reinterpret_cast< T* >
                    ( SendMsg( CM_SEARCHSTRING, MPFROMP( pss ),
                               MPFROMP( pAfter )));
    }

    virtual bool SetCnrInfo( PCNRINFO pCnrInfo, ULONG ulCnrInfoFl )
    {
        return SendMsg( CM_SETCNRINFO, MPFROMP( pCnrInfo ),
                        MPFROMLONG( ulCnrInfoFl ));
    }

    virtual bool SetGridInfo( PGRIDINFO pGridInfo, bool fRepaint )
    {
        return SendMsg( CM_SETGRIDINFO, MPFROMP( pGridInfo ),
                        MPFROMLONG( fRepaint ));
    }

    virtual bool SetRecordEmphasis( T* pRecord,
                                    USHORT usChangeEmphasis,
                                    USHORT fsEmphasisAttr )
    {
        return SendMsg( CM_SETRECORDEMPHASIS, MPFROMP( pRecord ),
                        MPFROM2SHORT( usChangeEmphasis, fsEmphasisAttr ));
    }

    virtual bool SetTextVisibility( bool fVisible )
    { return SendMsg( CM_SETTEXTVISIBILITY, MPFROMLONG( fVisible )); }

    virtual bool SnapToGrid( T* pRecord, SHORT xDrop, SHORT yDrop )
    {
        return SendMsg( CM_SNAPTOGRID, MPFROMP( pRecord ),
                        MPFROM2SHORT( xDrop, yDrop ));
    }

    virtual bool SortRecord( PFN pfnCompare, PVOID pStorage )
    {
        return SendMsg( CM_SORTRECORD, MPFROMP( pfnCompare ),
                        MPFROMP( pStorage ));
    }
};
#endif
