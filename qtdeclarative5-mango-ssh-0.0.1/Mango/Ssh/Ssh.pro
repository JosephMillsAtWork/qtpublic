TEMPLATE = lib
TARGET = Mango.Ssh
QT += qml quick gui network widgets
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = Mango.Ssh

LIBS += "-L$$[QT_INSTALL_LIBS]/" -lBotan
LIBS += "-L$$[QT_INSTALL_LIBS]/" -lQSsh

INCLUDEPATH += "QSsh/src/libs/ssh/"
INCLUDEPATH += "QSsh/src/libs/3rdParty/botan/"

# Input
SOURCES += \
    mangosshremoteprocess.cpp \
    mango_ssh_plugin.cpp \
    sftpupload.cpp \
    generatekeys.cpp \
    remotefilemodel.cpp

HEADERS += \
    mangosshremoteprocess.h \
    mango_ssh_plugin.h \
    sftpupload.h \
    generatekeys.h \
    remotefilemodel.h



!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

