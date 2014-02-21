purge.commands = rm -f *~ && rm -f include.d/*~ && rm -f ui.d/*~

CONFIG          += app_bundle qt release thread warn_on
ICON            = images.d/maxit.icns
LANGUAGE	= C++
QT		+= opengl
TEMPLATE	= app

QMAKE_CLEAN	+= Maxit
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3 -Wall -Werror -Wextra -Wstack-protector \
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

macdeployqt.path  = Maxit.app
macdeployqt.extra = $$[QT_INSTALL_BINS]/macdeployqt ./Maxit.app

INSTALLS	= macdeployqt
