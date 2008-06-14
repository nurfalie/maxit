purge.commands = rm -f *~ && rm -f include.d/*~ && rm -f ui.d/*~

TEMPLATE	= app
LANGUAGE	= C++
CONFIG		+= qt release warn_on
QT		+= network opengl
QMAKE_CXXFLAGS	+= -Wall -Werror
QMAKE_CLEAN	+= Maximus
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -Werror
QMAKE_CXXFLAGS_RELEASE += -Werror
QMAKE_EXTRA_UNIX_TARGETS = purge
INCPATH		+= /usr/local/include include.d

FORMS           += ui.d/maxit.ui

HEADERS		= include.d/maxit.h \
		  include.d/glpiece.h

SOURCES		= maxit.cc \
		  glpiece.cc \
		  maxit_main.cc

TARGET		= Maximus
PROJECTNAME	= Maximus
