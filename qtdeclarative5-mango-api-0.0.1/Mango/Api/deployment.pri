uri = Mango.Api
installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)

# Components
QML_FILES = BaseModel.qml \
PutModel.qml \
PostModel.qml \
LoopModel.qml\
Login.qml \
Logout.qml \
GetAllPoints.qml \
GetPointByXid.qml \
GetPointStats.qml \
GetPointValue.qml \
WebSocketPoints.qml \
ModifyPoint.qml \
RealTimeValue.qml \
RuningPointsAll.qml \
GetHierarchy.qml \
GetFolderByName.qml \
GetFolderById.qml \
FormateLocalDate.qml \
PutDataPoint.qml \
CreatePoint.qml

# qmldir
QMLDIR_FILE = qmldir

# make found deployables visible in Qt Creator
OTHER_FILES += $$QML_FILES

# define deployment for found deployables
qmldir_file.path = $$installPath
qmldir_file.files = $$QMLDIR_FILE

qml_files.path = $$installPath
qml_files.files = $$QML_FILES

plugins_qmltypes.path = $$installPath
plugins_qmltypes.files = plugins.qmltypes
#lugins_qmltypes.extra = $$[QT_INSTALL_BINS]/qmlplugindump -notrelocatable Mango.Api 0.1 ../../ 2>/dev/null > $(INSTALL_ROOT)/$$installPath/plugins.qmltypes

INSTALLS += qmldir_file qml_files plugins_qmltypes


