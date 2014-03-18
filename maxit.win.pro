purge.commands = del *~ && del include.d\\*~ && del ui.d\\*~

CONFIG		+= qt release thread warn_on
ICON            = images.d\\maxit.png
LANGUAGE	= C++
QT		+= opengl
RC_FILE		= maxit.win.rc
TEMPLATE	= app

QMAKE_CLEAN	+= Maxit
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -Os -Wall -Werror -Wextra -pie
QMAKE_EXTRA_TARGETS = purge

INCLUDEPATH	+= include.d

FORMS           = ui.d\\maxit.ui

HEADERS		= include.d\\computer.h \
		  include.d\\glpiece.h \
		  include.d\\maxit.h

SOURCES		= computer.cc \
		  glpiece.cc \
		  maxit.cc \
		  maxit_main.cc

PROJECTNAME	= Maxit
TARGET		= Maxit
