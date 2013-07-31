purge.commands = del *~ && del include.d\\*~ && del ui.d\\*~

TEMPLATE	= app
LANGUAGE	= C++
CONFIG		+= qt thread release warn_on
QT		+= opengl
QMAKE_CLEAN	+= Maxit
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3 -Wall -Werror -Wextra -pie
QMAKE_EXTRA_TARGETS = purge
ICON            = images.d\\maxit.png
INCLUDEPATH	+= include.d
RC_FILE		= maxit.win.rc

FORMS           = ui.d\\maxit.ui

HEADERS		= include.d\\maxit.h \
		  include.d\\glpiece.h \
		  include.d\\computer.h

SOURCES		= maxit.cc \
		  glpiece.cc \
		  computer.cc \
		  maxit_main.cc

TARGET		= Maxit
PROJECTNAME	= Maxit
