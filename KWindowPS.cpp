#include "KWindowPS.h"

HPS pkwps2hps( const KWindowPS* pkwps )
{
    return pkwps ? pkwps->_hps : 0;
}

