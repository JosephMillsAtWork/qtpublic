TEMPLATE = lib
TARGET = Mango.Files
QT += qml quick network sql multimedia core widgets serialport
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = Mango.Files

#macx:SOURCES += \
#    mangofileinfo.cpp \
#    mangosavefile.cpp \
#    mangotemporaryfile.cpp \
#    dirreader.cpp \
#    mangofilesystemwatcher.cpp \
#    mangodir.cpp \
#    filereader.cpp \
#    dirmodel.cpp \
#    mangofile.cpp \
#    filemove.cpp \
#    filewriter.cpp \
#    filesplugin.cpp

# Input
#unix:
SOURCES += \
    mangofileinfo.cpp \
    mangosavefile.cpp \
    mangotemporaryfile.cpp \
    dirreader.cpp \
    mangofilesystemwatcher.cpp \
    mangodir.cpp \
    filereader.cpp \
    dirmodel.cpp \
    mangofile.cpp \
    filemove.cpp \
    filewriter.cpp \
    filesplugin.cpp \
    iorequest.cpp \
    iorequestworker.cpp



#macx:HEADERS += \
#    mangofileinfo.h \
#    mangosavefile.h \
#    mangotemporaryfile.h \
#    dirreader.h \
#    mangofilesystemwatcher.h \
#    mangodir.h \
#    filereader.h \
#    dirmodel.h \
#    mangofile.h \
#    filemove.h \
#    filewriter.h \
#    filesplugin.h

#unix:
HEADERS += \
    mangofileinfo.h \
    mangosavefile.h \
    mangotemporaryfile.h \
    dirreader.h \
    mangofilesystemwatcher.h \
    mangodir.h \
    filereader.h \
    dirmodel.h \
    mangofile.h \
    filemove.h \
    filewriter.h \
    filesplugin.h \
    iorequest.h \
    iorequestworker.h

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
