#
#   KPMLib, C++ encapsulation class library for OS/2 PM
#   Copyright (C) 2012-2013 by KO Myung-Hun <komh@chollian.net>
#
#   This program is free software; you can redistribute it and/or modify it
#   under the terms of the GNU Lesser General Public License as published by
#   the Free Software Foundation; either version 2.1 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public License
#   along with this program; if not, write to the Free Software Foundation,
#   Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
#

##### Configuration parts that you can modify
CC       = gcc
CFLAGS   = -Wall
CXX      = g++
CXXFLAGS = -Wall -DOS2EMX_PLAIN_CHAR=1
LD       = g++
LDFLAGS  =
LIBS     =

ifdef RELEASE
CFLAGS   += -O3
CXXFLAGS += -O3
STRIP     = lxlite /B- /L- /CS
else
CFLAGS   += -O0 -g -DDEBUG
CXXFLAGS += -O0 -g -DDEBUG
LDFLAGS  += -g
STRIP     = echo
endif

RC      = rc
RCFLAGS = -n

RM = rm -f

PROGRAM     = kpmw
PROGRAM_EXT = .exe

OBJ_EXT = .o

CSRCS   =
CXXSRCS = kpmw.cpp \
          KPMMainThread.cpp \
          KPMSubThread.cpp \
          KPMApp.cpp \
          KWindow.cpp \
          KFrameWindow.cpp \
          KDialog.cpp \
          KStaticText.cpp \
          KButton.cpp \
          KScrollBar.cpp \
          KMenu.cpp \
          KTitleBar.cpp \
          KEntryField.cpp \
          KListBox.cpp \
          KComboBox.cpp \
          KFileDlg.cpp \
          KDirDlg.cpp \
          KWindowPS.cpp

include Makefile.common

.PHONY : lib

AR      = ar
ARFLAGS = crv

LIB_NAME = KPMLib

%.lib : %.a
	emxomf -o $@ $<

all : lib

lib : $(LIB_NAME).a $(LIB_NAME).lib

LIB_OBJS = $(filter-out kpmw$(OBJ_EXT), $(CXXSRCS:.cpp=$(OBJ_EXT)))

$(LIB_NAME).a : $(LIB_OBJS)
	$(if $(QUIET), @echo [AR] $@)
	$(QUIET)$(AR) $(ARFLAGS) $@ $^

clean : cleanlib

cleanlib:
	$(RM) $(LIB_NAME).a $(LIB_NAME).lib
