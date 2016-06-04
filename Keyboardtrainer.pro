#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T21:32:28
#
#-------------------------------------------------

QT    += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = Keyboardtrainer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \    
    keyboard1.cpp \
    listOfUser.cpp

HEADERS  += mainwindow.h \    
    keyboard1.h

FORMS    += mainwindow.ui  

RESOURCES += \
    Images.qrc
