TEMPLATE = lib
TARGET = Mango.System
QT += qml quick network multimedia core widgets
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = Mango.System

macx:SOURCES += \
iorequestworker.cpp \
mangosharedmemory.cpp \
mangoclipboard.cpp \
iconprovider.cpp \
mangodevice.cpp \
menumodels.cpp \
placesmodel.cpp \
mangoiodevice.cpp \
mangomimetype.cpp \
mangounits.cpp \
iorequest.cpp \
desktopfileModel.cpp \
ioworkerthread.cpp \
mangomime.cpp \
mdesktopentry.cpp \
applicationlauncher.cpp \
systemplugin.cpp

# Input
unix:SOURCES += \
iorequestworker.cpp \ 
mangosharedmemory.cpp \
mangoclipboard.cpp \
iconprovider.cpp \
mangodevice.cpp \
menumodels.cpp \
placesmodel.cpp \
mangoiodevice.cpp \
mangomimetype.cpp \
mangounits.cpp \
iorequest.cpp \
desktopfileModel.cpp \
ioworkerthread.cpp \
mangomime.cpp \  
mdesktopentry.cpp \
applicationlauncher.cpp \
systemplugin.cpp


macx:HEADERS += \
mdesktopentry.h \
mangodevice.h \
applicationlauncher.h \
mdesktopentry_p.h \
mangomime.h \
mlite-global.h \
iorequestworker.h \
mangosharedmemory.h \
desktopfileModel.h \
mangounits.h \
ioworkerthread.h \
placesmodel.h \
mangoiodevice.h \
mangoclipboard.h \
qsysteminfocommon_p.h \
iorequest.h \
menumodels.h \
iconprovider.h \
mangomimetype.h \
systemplugin.h

unix:HEADERS += \ 
mdesktopentry.h \
mangodevice.h \
applicationlauncher.h \
mdesktopentry_p.h \
mangomime.h \
mlite-global.h \
iorequestworker.h \
mangosharedmemory.h \
desktopfileModel.h \
mangounits.h \
ioworkerthread.h \
placesmodel.h \
mangoiodevice.h \
mangoclipboard.h \
qsysteminfocommon_p.h \
iorequest.h \
menumodels.h \
iconprovider.h \
mangomimetype.h \
systemplugin.h

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
