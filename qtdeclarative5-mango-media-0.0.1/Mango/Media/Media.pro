TEMPLATE = lib
TARGET = Mango.Media
QT += qml quick multimedia
CONFIG += qt plugin


TARGET = $$qtLibraryTarget($$TARGET)
uri = Mango.Media


macx:SOURCES += \
    soundrecorder.cpp \
    mediaplugin.cpp

unix:SOURCES += \
    soundrecorder.cpp \
    mediaplugin.cpp

macx:HEADERS += \
    soundrecorder.h \
    mediaplugin.h

unix:HEADERS += \
    soundrecorder.h \
    mediaplugin.h
	
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
