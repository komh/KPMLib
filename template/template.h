/*
    @PROG_NAME@
    Copyright (C) 2013 by KO Myung-Hun <komh@chollian.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef @PROG_UPPER_NAME@_H
#define @PROG_UPPER_NAME@_H

#include "KPMLib.h"

#define @PROG_UPPER_NAME@_VERSION "1.0.0"

#define ID_@PROG_UPPER_NAME@ 1

#define WC_@PROG_UPPER_NAME@ "@PROG_UPPER_NAME@ CLASS"

#define @PROG_UPPER_NAME@_TITLE  "@PROG_NAME@"

class @PROG_NAME@ : public KPMApp
{
public :
    @PROG_NAME@();
    virtual ~@PROG_NAME@();

    virtual int Run();
};
#endif

