######################################################################
# Automatically generated by qmake (2.00a) dim fév 26 23:27:19 2006
######################################################################

# libtorrent compilation

libtorrent.commands = cd src/3rd_party/libtorrent-0.9.1 ; \
                      ./configure ; \
                      make ;
libtorrent.target = src/3rd_party/libtorrent-0.9.1/src/libtorrent.la
PRE_TARGETDEPS += $${libtorrent.target}
QMAKE_EXTRA_TARGETS += libtorrent

TEMPLATE = app
TARGET = tlclient
QT += xml sql

DEPENDPATH += . \
              src \
              src/qalf/core \
              src/qalf/gui \
              src/qalf/image \
              src/3rd_party/libtorrent-0.9.1

INCLUDEPATH += . \
               src/qalf/core \
               src/qalf/gui \
               src/qalf/image \
               src/3rd_party/libtorrent-0.9.1

DESTDIR += bin
OBJECTS_DIR = obj
MOC_DIR = $${OBJECTS_DIR}
RESOURCES = tlclient.qrc

# Input
HEADERS += qalfmainwindow.h \
           qalfdb.h \
           qalfconfig.h \
           qalfsearchwidget.h \
           qalfimagewidget.h \
           qalftreemodel.h \
           treeitem.h \
           qalfimagetreemodel.h \
           qalfimagefile.h \
           qalffile.h \
           qalfmoderatordialog.h

SOURCES += tlclient.cpp \
           qalfmainwindow.cpp \
           qalfdb.cpp \
           qalfconfig.cpp \
           qalfsearchwidget.cpp \
           qalfimagewidget.cpp \
           qalftreemodel.cpp \
           treeitem.cpp \
           qalfimagetreemodel.cpp \
           qalfimagefile.cpp \
           qalffile.cpp \
           qalfmoderatordialog.cpp
