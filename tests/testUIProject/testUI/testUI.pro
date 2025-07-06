QT += testlib
QT += testlib widgets
QT += gui

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_testvamsui.cpp \
    ../numbers/mainwindow.cpp

HEADERS += \
    ../numbers/mainwindow.h \


INCLUDEPATH += ../numbers
INCLUDEPATH += ../build/numbers_autogen/include
