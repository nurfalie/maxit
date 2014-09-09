cache()
purge.commands = rm -f *~ && rm -f Include/*~ && rm -f UI/*~

CONFIG          += app_bundle qt release thread warn_on
ICON            = Images/maxit.icns
LANGUAGE	= C++
QT		+= opengl widgets
TEMPLATE	= app

QMAKE_CLEAN	+= Maxit
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3 -Wall -Werror -Wextra \
			  -Wpointer-arith -Wstack-protector \
			  -Wstrict-overflow=3 \
			  -fPIE -fstack-protector-all
QMAKE_DISTCLEAN	+= .qmake.cache .qmake.stash
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

macdeployqt.path  = Maxit.app
macdeployqt.extra = $$[QT_INSTALL_BINS]/macdeployqt ./Maxit.app

INSTALLS	= macdeployqt
