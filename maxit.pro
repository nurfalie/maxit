purge.commands = rm -f *~ && rm -f include.d/*~

TEMPLATE	= app
LANGUAGE	= C++
CONFIG		+= qt release warn_on
QT		+= network opengl
QMAKE_CXXFLAGS	+= -Wall -Werror
QMAKE_CLEAN	+= Maxit
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -Werror
QMAKE_CXXFLAGS_RELEASE += -Werror
QMAKE_EXTRA_UNIX_TARGETS = purge
INCPATH		+= /usr/local/include

FORMS           += maxit.ui

HEADERS		= maxit.h \
		  gui_board.h

SOURCES		= maxit.cc \
		  gui_board.cc \
		  maxit_main.cc

TARGET		= Maxit
PROJECTNAME	= Maxit
