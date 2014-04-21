purge.commands = rm -f *~ && rm -f include.d/*~ && rm -f ui.d/*~

CONFIG		+= qt release thread warn_on
LANGUAGE	= C++
QT		+= opengl
TEMPLATE	= app

QMAKE_CLEAN	+= Maxit
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -Os -Wall -Werror -Wextra \
			  -Wpointer-arith -Wstack-protector \
			  -Wstrict-overflow=3 \
			  -fPIE -fstack-protector-all -pie
QMAKE_EXTRA_TARGETS = purge

INCLUDEPATH	+= include.d

FORMS           = ui.d/maxit.ui

HEADERS		= include.d/computer.h \
		  include.d/glpiece.h \
		  include.d/maxit.h

SOURCES		= computer.cc \
		  glpiece.cc \
		  maxit.cc \
		  maxit_main.cc

PROJECTNAME	= Maxit
TARGET		= Maxit
