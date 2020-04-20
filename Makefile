#############################################################################
# Makefile for building: soxmap_dc8x4
# Generated by qmake (1.07a) (Qt 3.3.8b) on: Fri Oct  4 15:08:37 2013
# Project:  soxmap_dc8x4.pro
# Template: app
# Command: $(QMAKE) -o Makefile soxmap_dc8x4.pro
#############################################################################

####### Compiler, tools and options

CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -g -Wall -W -O2 -D_REENTRANT  -DQT_NO_DEBUG -DQT_THREAD_SUPPORT -DQT_SHARED -DQT_TABLET_SUPPORT
CXXFLAGS = -pipe -g -Wall -W -O2 -D_REENTRANT  -DQT_NO_DEBUG -DQT_THREAD_SUPPORT -DQT_SHARED -DQT_TABLET_SUPPORT
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I/usr/share/qt3/mkspecs/default -I. -I. -I/usr/include/qt3
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS) -L/usr/share/qt3/lib -L/usr/X11R6/lib -lqt-mt -lXext -lX11 -lm -lpthread
AR       = ar cqs
RANLIB   = 
MOC      = /usr/share/qt3/bin/moc
UIC      = /usr/share/qt3/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = ./

####### Files

HEADERS = coords_ll.h \
		genericclient.h \
		mapview.h \
		pathdialog.h \
		position.h \
		setupgui.h \
		showstate.h \
		soxgui.h \
		soxmap.h \
		utility.h \
		wp_ll.h
SOURCES = coords_ll.cpp \
		genericclient.cpp \
		main.cpp \
		mapview.cpp \
		options.cpp \
		pathdialog.cpp \
		position.cpp \
		setupgui.cpp \
		showstate.cpp \
		soxgui.cpp \
		utility.cpp \
		wp_ll.cpp
OBJECTS = coords_ll.o \
		genericclient.o \
		main.o \
		mapview.o \
		options.o \
		pathdialog.o \
		position.o \
		setupgui.o \
		showstate.o \
		soxgui.o \
		utility.o \
		wp_ll.o
FORMS = 
UICDECLS = 
UICIMPLS = 
SRCMOC   = moc_genericclient.cpp \
		moc_mapview.cpp \
		moc_pathdialog.cpp \
		moc_setupgui.cpp \
		moc_showstate.cpp \
		moc_soxgui.cpp
OBJMOC = moc_genericclient.o \
		moc_mapview.o \
		moc_pathdialog.o \
		moc_setupgui.o \
		moc_showstate.o \
		moc_soxgui.o
DIST	   = soxmap_dc8x4.pro
QMAKE_TARGET = soxmap_dc8x4
DESTDIR  = 
TARGET   = soxmap_dc8x4

first: all
####### Implicit rules

.SUFFIXES: .c .o .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(OBJCOMP) $(LIBS)

mocables: $(SRCMOC)
uicables: $(UICDECLS) $(UICIMPLS)

$(MOC): 
	( cd $(QTDIR)/src/moc && $(MAKE) )

Makefile: soxmap_dc8x4.pro  /usr/share/qt3/mkspecs/default/qmake.conf /usr/share/qt3/lib/libqt-mt.prl
	$(QMAKE) -o Makefile soxmap_dc8x4.pro
qmake: 
	@$(QMAKE) -o Makefile soxmap_dc8x4.pro

dist: 
	@mkdir -p .tmp/soxmap_dc8x4 && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/soxmap_dc8x4/ && ( cd `dirname .tmp/soxmap_dc8x4` && $(TAR) soxmap_dc8x4.tar soxmap_dc8x4 && $(GZIP) soxmap_dc8x4.tar ) && $(MOVE) `dirname .tmp/soxmap_dc8x4`/soxmap_dc8x4.tar.gz . && $(DEL_FILE) -r .tmp/soxmap_dc8x4

mocclean:
	-$(DEL_FILE) $(OBJMOC)
	-$(DEL_FILE) $(SRCMOC)

uiclean:

yaccclean:
lexclean:
clean: mocclean
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) $(TARGET)


FORCE:

####### Compile

coords_ll.o: coords_ll.cpp coords_ll.h

genericclient.o: genericclient.cpp genericclient.h

main.o: main.cpp soxgui.h \
		soxmap.h \
		genericclient.h \
		coords_ll.h \
		wp_ll.h \
		mapview.h \
		position.h \
		showstate.h

mapview.o: mapview.cpp mapview.h \
		utility.h \
		soxmap.h \
		coords_ll.h \
		wp_ll.h \
		position.h

options.o: options.cpp soxmap.h

pathdialog.o: pathdialog.cpp pathdialog.h

position.o: position.cpp position.h \
		utility.h

setupgui.o: setupgui.cpp setupgui.h \
		soxgui.h \
		genericclient.h \
		coords_ll.h \
		wp_ll.h \
		mapview.h \
		position.h \
		showstate.h

showstate.o: showstate.cpp showstate.h \
		position.h

soxgui.o: soxgui.cpp soxmap.h \
		soxgui.h \
		setupgui.h \
		pathdialog.h \
		utility.h \
		genericclient.h \
		coords_ll.h \
		wp_ll.h \
		mapview.h \
		position.h \
		showstate.h

utility.o: utility.cpp utility.h

wp_ll.o: wp_ll.cpp wp_ll.h

moc_genericclient.o: moc_genericclient.cpp  genericclient.h 

moc_mapview.o: moc_mapview.cpp  mapview.h coords_ll.h \
		wp_ll.h \
		position.h

moc_pathdialog.o: moc_pathdialog.cpp  pathdialog.h 

moc_setupgui.o: moc_setupgui.cpp  setupgui.h 

moc_showstate.o: moc_showstate.cpp  showstate.h position.h

moc_soxgui.o: moc_soxgui.cpp  soxgui.h genericclient.h \
		coords_ll.h \
		wp_ll.h \
		mapview.h \
		position.h \
		showstate.h

moc_genericclient.cpp: $(MOC) genericclient.h
	$(MOC) genericclient.h -o moc_genericclient.cpp

moc_mapview.cpp: $(MOC) mapview.h
	$(MOC) mapview.h -o moc_mapview.cpp

moc_pathdialog.cpp: $(MOC) pathdialog.h
	$(MOC) pathdialog.h -o moc_pathdialog.cpp

moc_setupgui.cpp: $(MOC) setupgui.h
	$(MOC) setupgui.h -o moc_setupgui.cpp

moc_showstate.cpp: $(MOC) showstate.h
	$(MOC) showstate.h -o moc_showstate.cpp

moc_soxgui.cpp: $(MOC) soxgui.h
	$(MOC) soxgui.h -o moc_soxgui.cpp

####### Install

install:  

uninstall:  

