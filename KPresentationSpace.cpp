#include "KPresentationSpace.h"

HPS pkps2hps( const KPresentationSpace* pkps )
{
    return pkps ? pkps->_hps : 0;
}

