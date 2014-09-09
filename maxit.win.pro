purge.commands = del *~ && del Include\\*~ && del UI\\*~

CONFIG		+= qt release thread warn_on
ICON            = Images\\maxit.png
LANGUAGE	= C++
QT		+= opengl
RC_FILE		= maxit.win.rc
TEMPLATE	= app

QMAKE_CLEAN	+= Maxit
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -Os -Wall -Werror -Wextra \
			  -Wpointer-arith \
			  -Wstrict-overflow=3 -pie
QMAKE_EXTRA_TARGETS = purge

INCLUDEPATH	+= Include

FORMS           = UI\\maxit.ui

HEADERS		= Include\\computer.h \
		  Include\\glpiece.h \
		  Include\\maxit.h

SOURCES		= Source\\computer.cc \
		  Source\\glpiece.cc \
                  Source\\maxit.cc \
                  Source\\maxit_main.cc

PROJECTNAME	= Maxit
TARGET		= Maxit
