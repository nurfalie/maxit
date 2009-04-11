purge.commands = rm -f *~ && rm -f include.d/*~ && rm -f ui.d/*~

TEMPLATE	= app
LANGUAGE	= C++
CONFIG		+= qt thread release warn_on
QT		+= opengl
ICON            = images.d/maxit.icns
QMAKE_CXXFLAGS	+= -Wall -Werror
QMAKE_CLEAN	+= Maxit
QMAKE_CFLAGS_RELEASE += -Werror
QMAKE_CXXFLAGS_RELEASE += -Werror
QMAKE_EXTRA_UNIX_TARGETS = purge
INCPATH		+= include.d

FORMS           = ui.d/maxit.ui

HEADERS		= include.d/maxit.h \
		  include.d/glpiece.h \
		  include.d/computer.h

SOURCES		= maxit.cc \
		  glpiece.cc \
		  computer.cc \
		  maxit_main.cc

TARGET		= Maxit
PROJECTNAME	= Maxit