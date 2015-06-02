TEMPLATE = lib
TARGET = Mango.Api
QT += qml quick
CONFIG += qt plugin


TARGET = $$qtLibraryTarget($$TARGET)
uri = Mango.Api

OTHER_FILES += \
BaseModel.qml \
LoopModel.qml \
PostModel.qml \
PutModel.qml \
Login.qml \
Logout.qml \
GetAllPoints.qml \
GetPointByXid.qml \
GetPointStats.qml \
GetPointValue.qml \
WebSocketPoiints.qml \
ModifyPoint.qml \
RealTimeValue.qml \
RuningPointsAll.qml \
GetHierarchy.qml \
GetFolderByName.qml \
GetFolderById.qml \
FormateLocalDate.qml \
PutDataPoint.qml \
CreatePoint.qml



qmlFiles.files = BaseModel.qml \
LoopModel.qml \
PostModel.qml \
PutModel.qml \
Login.qml \
Logout.qml \
GetAllPoints.qml \
GetPointByXid.qml \
GetPointStats.qml \
GetPointValue.qml \
WebSocketPoiints.qml \
ModifyPoint.qml \
RealTimeValue.qml \
RuningPointsAll.qml \
GetHierarchy.qml \
GetFolderByName.qml \
GetFolderById.qml \
FormateLocalDate.qml \
PutDataPoint.qml \
CreatePoint.qml

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
    qmlFiles.path = $$installPath
    INSTALLS += target qmldir qmlFiles
}

