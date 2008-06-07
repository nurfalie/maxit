purge.commands = rm -f *~ && rm -f include.d/*~

TEMPLATE	= app
LANGUAGE	= C++
CONFIG		+= qt release warn_on
QMAKE_CXXFLAGS	+= -Wall -Werror
QMAKE_CLEAN	+= Maxit
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -Werror
QMAKE_CXXFLAGS_RELEASE += -Werror
QMAKE_EXTRA_UNIX_TARGETS = purge
INCPATH		+= include.d /usr/local/include

FORMS           += maxit.ui

HEADERS		= maxit.h

SOURCES		= maxit.cc \
		  maxit_main.cc

TARGET		= Maxit
PROJECTNAME	= Maxit
