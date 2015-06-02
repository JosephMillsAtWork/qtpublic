TEMPLATE = lib
TARGET = Mango.Networking
QT += qml quick network core
CONFIG += qt plugin

# get the Libs for avahi/bonjour/zeroconf
unix:!android: LIBS += -ldns_sd
!contains(CONFIG,NO_AVAHI): unix:!macx:LIBS +=  -lavahi-client -lavahi-common
win32:LIBS += -L"c:\\PROGRA~1\\BONJOU~1\\lib\\win32" -ldnssd
win32:INCLUDEPATH += "c:\\program files\\bonjour sdk\\include"

TARGET = $$qtLibraryTarget($$TARGET)
uri = Mango.Networking

macx:SOURCES += \
    mangossl.cpp \
    mangocurl.cpp \
    oauth2.cpp \
    macaddressgenerator.cpp \
    mangomodbusregistermodel.cpp \
    qmlnetworkinfo.cpp \
    bonjour.cpp \
    dnslookup.cpp \
    hostinfo.cpp \
    mangosslsocket.cpp \
    mangodownloader.cpp \
    networkingplugin.cpp

unix:SOURCES += \
    mangossl.cpp \
    mangocurl.cpp \
    oauth2.cpp \
    macaddressgenerator.cpp \
    mangomodbusregistermodel.cpp \
    qmlnetworkinfo.cpp \
    bonjour.cpp \
    dnslookup.cpp \
    hostinfo.cpp \
    mangosslsocket.cpp \
    mangodownloader.cpp \
    bonjourservicebrowser.cpp \
    bonjourregister.cpp \
    bonjourserviceresolver.cpp \
    networkingplugin.cpp


macx:HEADERS += \
    mangossl.h \
    mangocurl.h \
    oauth2.h \
    macaddressgenerator.h \
    mangomodbusregistermodel.h \
    qmlnetworkinfo.h \
    bonjour.h \
    dnslookup.h \
    hostinfo.h \
    mangosslsocket.h \
    mangodownloader.h \
    networkingplugin.h



unix:HEADERS += \
    mangossl.h \
    mangocurl.h \
    oauth2.h \
    macaddressgenerator.h \
    mangomodbusregistermodel.h \
    qmlnetworkinfo.h \
    bonjour.h \
    dnslookup.h \
    hostinfo.h \
    mangosslsocket.h \
    mangodownloader.h \
    bonjourservicebrowser.h \
    bonjourregister.h \
    bonjourserviceresolver.h \
    networkingplugin.h

	
!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir

unix:*-g++* {
    QMAKE_CFLAGS += -fPIC -fpermissive -finline-functions -Wno-long-long
    ## adding c++ 11
    QMAKE_CXXFLAGS += -fPIC -fpermissive -finline-functions -Wno-long-long -std=c++0x -Wall -Wextra -pedantic
    QMAKE_CXXFLAGS_HIDESYMS -= -fvisibility-inlines-hidden # for ubuntu 7.04
}



unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

macx {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}
win32 {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}
