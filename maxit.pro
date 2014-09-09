purge.commands = rm -f *~ && rm -f Include/*~ && rm -f UI/*~

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

INCLUDEPATH	+= Include

FORMS           = UI/maxit.ui

HEADERS		= Include/computer.h \
		  Include/glpiece.h \
		  Include/maxit.h

SOURCES		= Source/computer.cc \
		  Source/glpiece.cc \
                  Source/maxit.cc \
                  Source/maxit_main.cc

PROJECTNAME	= Maxit
TARGET		= Maxit
