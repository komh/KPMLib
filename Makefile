##### Configuration parts that you can modify
CC       = gcc
CFLAGS   = -Wall
CXX      = g++
CXXFLAGS = -Wall
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
CXXSRCS = kpmw.cpp KPMThread.cpp KPMApp.cpp KWindow.cpp KFrameWindow.cpp \
          KDialog.cpp KStaticText.cpp KButton.cpp KScrollBar.cpp KMenu.cpp \
          KTitleBar.cpp KEntryField.cpp KListBox.cpp KComboBox.cpp \
          KFileDlg.cpp

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
