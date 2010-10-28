purge.commands = rm -f *~ && rm -f include.d/*~ && rm -f ui.d/*~

TEMPLATE	= app
LANGUAGE	= C++
CONFIG         += qt thread release warn_on app_bundle
QT		+= opengl
ICON            = images.d/maxit.icns
QMAKE_LFLAGS_RELEASE =
QMAKE_LFLAGS_RPATH =
QMAKE_CXXFLAGS	+= -Wall
QMAKE_CLEAN	+= Maxit
QMAKE_CFLAGS_RELEASE +=
QMAKE_CXXFLAGS_RELEASE +=
QMAKE_EXTRA_TARGETS = purge
INCLUDEPATH	+= include.d

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
