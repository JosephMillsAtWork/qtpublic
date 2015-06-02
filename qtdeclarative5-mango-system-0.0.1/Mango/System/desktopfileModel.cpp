/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#include "desktopfileModel.h"

    /*!
     \qmltype DesktopFile
     \inqmlmodule Mango.System 0.1
     \ingroup Mango.System
     \inherits Item
     \since 5.3
     \brief Used to parse out linux desktop files.

\b{Code for C++ side example: main.cpp}
\code
#include <QQmlApplicationEngine>
#include <QQmlExtensionPlugin>
#include <QQmlContext>
#include "desktopfilemodel.h"
....
.......
............

    // Add the Model to the Mix
    DesktopFileModel allModel;
    DesktopFileModel accessoriesModel;
    DesktopFileModel developmentModel;
    DesktopFileModel gamesModel;
    DesktopFileModel graphicsModel;
    DesktopFileModel internetModel;
    DesktopFileModel multimediaModel;
    DesktopFileModel officeModel;
    DesktopFileModel scienceModel;
    DesktopFileModel systemModel;
    DesktopFileModel universalModel;
    DesktopFileModel unknownModel;
    DesktopFileModel educationModel;

// I have to make a model for each of the categories//


    // for each desktop file use QSettings to get the info then add it to the Model
    foreach (QString str, desktopFiles) {
        MDesktopEntry desktopFileValue(str);
        QString n = desktopFileValue.name();
        QString c = desktopFileValue.comment();
        QString e = desktopFileValue.exec();
        QString ty = desktopFileValue.type();
        bool te = desktopFileValue.terminal();
        QString ic = "image://theme/" + desktopFileValue.icon();
        QStringList categories = desktopFileValue.categories();
        allModel.addDesktopFile(DesktopFile(n,c,e,ty,te,ic));
        if (categories.contains("System", Qt::CaseInsensitive) ){
            systemModel.addDesktopFile(DesktopFile(n,c,e,ty,te,ic));
        }

        else if (categories.contains("Internet", Qt::CaseInsensitive) ||
                 categories.contains("Network", Qt::CaseInsensitive) ||
                 categories.contains("Browser", Qt::CaseInsensitive)){
            internetModel.addDesktopFile(DesktopFile(n,c,e,ty,te,ic));

        }

        else if (categories.contains("Graphics", Qt::CaseInsensitive) == true){
            graphicsModel.addDesktopFile(DesktopFile(n,c,e,ty,te,ic));

        }

        else if (categories.contains("Office", Qt::CaseInsensitive) == true){
            officeModel.addDesktopFile(DesktopFile(n,c,e,ty,te,ic));
        }

        else if (categories.contains("AudioVideo", Qt::CaseInsensitive) ||
                 categories.contains("Video",Qt::CaseInsensitive) ||
                 categories.contains("Audio",Qt::CaseInsensitive)){
            multimediaModel.addDesktopFile(DesktopFile(n,c,e,ty,te,ic));
        }

        else if (categories.contains("Accessibility", Qt::CaseInsensitive)){
            universalModel.addDesktopFile(DesktopFile(n,c,e,ty,te,ic));
        }

        else if (categories.contains("Education", Qt::CaseInsensitive) == true){
            educationModel.addDesktopFile(DesktopFile(n,c,e,ty,te,ic));
        }
        else if (categories.contains("Science", Qt::CaseInsensitive) == true){
            scienceModel.addDesktopFile(DesktopFile(n,c,e,ty,te,ic));
        }

        else if (categories.contains("Game", Qt::CaseInsensitive)){
            gamesModel.addDesktopFile(DesktopFile(n,c,e,ty,te,ic));
        }
        else if (categories.contains("Development", Qt::CaseInsensitive))
        {
            developmentModel.addDesktopFile(DesktopFile(n,c,e,ty,te,ic));
        }

        else if (categories.contains("Utility", Qt::CaseInsensitive)){
            accessoriesModel.addDesktopFile(DesktopFile(n,c,e,ty,te,ic));
        }
        else{
           unknownModel.addDesktopFile(DesktopFile(n,c,e,ty,te,ic));
        }
    }

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("ChannelModel", &channelModel);
    ctxt->setContextProperty("UserModel", &usersModel);

    // models for apps that are installed
    ctxt->setContextProperty("allAppsModel", &allModel);
    ctxt->setContextProperty("developerAppsModel", &developmentModel);
    ctxt->setContextProperty("accessoriesAppsModel", &accessoriesModel);
    ctxt->setContextProperty("gamesAppsModel", &gamesModel);
    ctxt->setContextProperty("grapicsAppsModel", &graphicsModel);
    ctxt->setContextProperty("internetAppsModel", &internetModel);
    ctxt->setContextProperty("multimediaAppsModel", &multimediaModel);
    ctxt->setContextProperty("officeAppsModel", &officeModel);
    ctxt->setContextProperty("scienceAppsModel", &scienceModel);
    ctxt->setContextProperty("systemAppsModel", &systemModel);
    ctxt->setContextProperty("universalAppsModel", &universalModel);
    ctxt->setContextProperty("educationAppsModel", &educationModel);
    ctxt->setContextProperty("unknownAppsModel", &unknownModel);

...............
.........................
..........................................


\endcode



\b{Code in QML example: AllApps.qml}

One would need to make sure that the icon set Faenza is installed on there host machine for this example.

But the There have been updates to Mango::iconprovider and this plugin should be used instead of hard coding in the icons path,  due to fragmentation in OS icon provider meta types,



\code
import QtQuick 2.0
import Mango 0.1

Rectangle {
    id: appsRootViewer
    width: root.loaderWidth
    height: root.loaderHeight
    color:palete.window
    property string currentModel: "All"
    SystemPalette{id:palete}

    // A Qprocess plugin see Mango::Application class for more info
    Application{
        id: runner
        isApp: false
        startDetached: true
    }
    ListView{
        id: installedViewer
        width: appsRootViewer.width / 1.3
        height:appsRootViewer.height - header.height
        anchors.bottom: parent.bottom
        spacing: 1
        model: allAppsModel
        anchors.right:  parent.right
        delegate: FileManagerButton{
            text: model.name
            color: "#999"//palete.dark
            width: appsRootViewer.width / 1.3
            height: appsRootViewer.height / 12
            textColor: palete.buttonText
            subTextColor: palete.text
            textVisable: true
            hoverEnabled: false
            onClicked:{
            /// look to see if the application needs to be launched with a termianl emulator
            /// FIXME add preferences that looks to see if there is defalut terminal application
            /// example:  gnome-terminal vs knosole vs xterm ect may store this in sqlight
            /// Or just see that OS and what device and have better things for that to push to qtSerial and many other classes that should be exposed in QML
            ///1/2 FIXME the QtSerialPort port to qml is done,
            ///
            ///Still need to fix database stuff in Js
            ///
                if(model.terminal === "true"){
                    runner.appName = model.exec
                    runner.startDetached = false
                    runner.isApp = false;
                    runner.start();
                }else{
                    runner.appName = model.exec
                    runner.start();
                }
            }
            image: "file://" + model.icon
            subText: model.comment
        }
    }


    ListView{
        id: categories
        width: appsRootViewer.width  - installedViewer.width
        height:appsRootViewer.height -header.height
        anchors.bottom: parent.bottom
        spacing: 1
        // the category model that we passed in via C++
        model: catModels
        delegate: FileManagerButton{
            width: appsRootViewer.width  - installedViewer.width
            height:appsRootViewer.height / 14.04
            hoverEnabled: false
            color: palete.dark
            text: model.name
            textColor: palete.buttonText
            image:"file://"+ model.icon
            subText: model.text
            subTextColor: palete.text
            onClicked: {
                if (text === "Games"){
                    installedViewer.model = gamesAppsModel;
                    currentModel = text
                }
                else if (text === "Development"){
                    installedViewer.model = developerAppsModel;
                    currentModel = text

                }
                else if (text === "Accessories"){
                    installedViewer.model = accessoriesAppsModel;
                    currentModel = text

                }
                else if (text === "Games"){
                    installedViewer.model = gamesAppsModel;
                    currentModel = text

                }
                else if (text === "Graphics"){
                    currentModel = text
                    installedViewer.model = grapicsAppsModel;
                }
                else if (text === "Internet"){
                    currentModel = text
                    installedViewer.model = internetAppsModel;
                }
                else if (text === "Office"){
                    currentModel = text
                    installedViewer.model = officeAppsModel;
                }
                else if (text === "Science"){
                    currentModel = text
                    installedViewer.model = scienceAppsModel;
                }
                else if (text === "Multimedia"){
                    currentModel = text
                    installedViewer.model = multimediaAppsModel;
                }
                else if (text === "Universal"){
                    currentModel = text
                    installedViewer.model = universalAppsModel;
                }
                else if (text === "System"){
                    currentModel = text
                    installedViewer.model = systemAppsModel;
                }
                else if (text === "Unknown"){
                    currentModel = text
                    installedViewer.model = unknownAppsModel;
                }
                else if (text === "All"){
                    currentModel = text
                    installedViewer.model = allAppsModel;
                }
            }
        }
    }

    DesktopFileCategoriesModel{
        id:catModels
    }

    Rectangle{
        id: header
        width:     parent.width
        height: parent.height   / 10
        color: palete.mid
        border.width: 1
        border.color: palete.text
        Text {
            anchors{
                left: parent.left
                leftMargin: 10
                verticalCenter: parent.verticalCenter
            }
            text: currentModel
            color: palete.text
            font.pixelSize: header.height - 4
            font.bold: true
        }
    }
}
\endcode


\b{DesktopFileCategoriesModel}



\code
import QtQuick 2.0

ListModel{
 ListElement{
  name: "Accessories"
  icon: "/usr/share/icons/Faenza/categories/96/applications-accessories.png"
  text: "Accessories applications"
 }
 ListElement{
  name: "Development"
  icon: "/usr/share/icons/Faenza/categories/96/applications-development.png"
  text: "Developer applications"
 }
 ListElement{
  name: "Games"
  icon: "/usr/share/icons/Faenza/categories/96/applications-games.png"
  text: "Puzzels,board,card games and much more"
 }
 ListElement{
  name: "Graphics"
  icon: "/usr/share/icons/Faenza/categories/96/applications-graphics.png"
  text: "Painting and image viewers"
 }
 ListElement{
  name: "Internet"
  icon: "/usr/share/icons/Faenza/categories/96/applications-internet.png"
  text: "Browsers,chat applications and much more"
 }
 ListElement{
  name: "Office"
  icon: "/usr/share/icons/Faenza/categories/96/applications-office.png"
  text: "Writer Cal and other Office applications"

 }
 ListElement{
  name: "Science"
  icon: "/usr/share/icons/Faenza/categories/96/applications-science.png"
  text: "Science and engineering applications"

 }
 ListElement{
  name: "Multimedia"
  icon: "/usr/share/icons/Faenza/categories/96/applications-multimedia.png"
  text: "video and audio appplications"

 }
 ListElement{
  name: "Universal"
  icon: "/usr/share/icons/Faenza/apps/96/preferences-desktop-accessibility.png"
  text: "Screen readers and other access items"
 }
 ListElement{
  name: "System"
  icon: "/usr/share/icons/Faenza/categories/96/applications-system.png"
  text: "backgrounds fonts and much more"
 }
 ListElement{
  name: "Unknown"
  icon: "/usr/share/icons/Faenza/mimetypes/96/unknown.png"
  text: "Other apps with mal formed desktop files"
 }
 ListElement{
  name: "All"
  icon: "/usr/share/icons/Faenza/apps/96/system-software-installer.png"
  text: "All apps"
 }
}
\endcode





\b{FileManagerButton.qml}


Simple button that has text and subtext maybe should be moved to the Mango.Components.  For file management and also other Button properties



\code

import QtQuick 2.0
Item{
    id: imgButton
    property color color
    property bool textVisable: true
    property string text
    property color textColor: primaryText

    property bool subTextVisable: true
    property string subText
    property color subTextColor: primaryText
    property int subTextFontSize: 12
    property bool subTextFontBold: false
    property bool subTextFontItalic: false
    property string subTextFont: "Tahoma"
    property bool subTextFontUnderline: false


    property url image
    property color hoverColor: secondaryColor
    property bool hoverEnabled: true
    property int fontSize: 22
    property bool fontBold: false
    property bool fontItalic: false
    property string font: "Tahoma"
    property bool fontUnderline: false
    signal clicked()
    signal doubleClicked()
    width: parent.width
    height: parent.height

    Rectangle{
        id: hoverRec
        color: imgButton.color
        width: parent.width
        height: parent.height
    }
    MouseArea{
        anchors.fill: hoverRec
        onClicked:{
            imgButton.clicked()
        }
        onDoubleClicked: {
            imgButton.doubleClicked()
        }
    }
    Image {
        id: img
        source: imgButton.image === "" ? "file:///usr/share/icons/Faenza/mimetypes/96/unknown.png" : imgButton.image
        width: height
        height: parent.height
        anchors.left: parent.left
    }

    Text {
        id: mainText
        visible: textVisable
        text: imgButton.text
        color: imgButton.textColor
        font.pixelSize: imgButton.fontSize
        font.bold: imgButton.fontBold
        font.italic: imgButton.fontItalic
        font.family: imgButton.font
        font.underline: imgButton.fontUnderline
        height: paintedHeight
        wrapMode: Text.WordWrap
        anchors{
            top: parent.top
            left: img.right
            leftMargin: 12
        }
    }
    Text {
        visible: textVisable
        text: imgButton.subText
        color: imgButton.subTextColor
        font.pixelSize: imgButton.subTextFontSize
        font.bold: imgButton.subTextFontBold
        font.italic: imgButton.subTextFontItalic
        font.family: imgButton.subTextFont
        font.underline: imgButton.subTextFontUnderline
        wrapMode: Text.WordWrap
        anchors{
            top: mainText.bottom
            left: parent.left
            leftMargin: img.width + 12
        }
    }
}

\endcode

Kinda cunfusing but does the job.



	*/
	
DesktopFile::DesktopFile(const QString &name, const QString &comment, const QString &exec, const QString &type, bool &terminal, const QString &icon)
    : m_name(name),
      m_comment(comment),
      m_exec(exec),
      m_type(type),
      m_terminal(terminal),
      m_icon(icon)
{
}
/*!
 \qmlproperty string DesktopFile::name
 Get back the name of the application that is in the *.desktop file
*/
QString DesktopFile::name() const
{
    return m_name;
}
/*!
 \qmlproperty string DesktopFile::comment
 Get back the comment that is in the .desktop file
*/

QString DesktopFile::comment() const
{
    return m_comment;
}

/*!
 \qmlproperty string DesktopFile::exec
 Get back the argument that is used to launch the application from the selected desktop file
*/

QString DesktopFile::exec() const
{
    return m_exec;
}

/*!
 \qmlproperty string DesktopFile::type
 Get back the type of application that is in the selected desktop file
*/
QString DesktopFile::type() const
{
    return m_type;
}
/*!
\qmlproperty bool DesktopFile::terminal
 Returns true if the application needs to be started with a terminal emulator
*/

bool DesktopFile::terminal() const
{
    return m_terminal;
}

/*! 
 \qmlproperty string DesktopFile::icon
 Returns the icon of the applications that is selected via the desktop file
*/

QString DesktopFile::icon() const
{
    return m_icon;
}

/*!
 Set up a model that can be used wth all the desktop files.  So one can use in a ListView or GridView ect
*/
DesktopFileModel::DesktopFileModel(QObject *parent)
    : QAbstractListModel(parent)
{
}
/*!
 Feed the model the desktop files to parse.
*/ 
void DesktopFileModel::addDesktopFile(const DesktopFile &desktopFile)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_desktopFiles << desktopFile;
    endInsertRows();
}
/*!
 Look at the count of the desktop files for the model.
*/
int DesktopFileModel::rowCount(const QModelIndex &) const {
    return m_desktopFiles.count();
}
/*!
  Make hte model and assign all it roles so that we can use in qml
*/
QVariant DesktopFileModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() > m_desktopFiles.count())
        return QVariant();
    const DesktopFile &desktopFile = m_desktopFiles[index.row()];
    if (role == NameRole)
        return desktopFile.name();
    else if (role == CommentRole)
        return desktopFile.comment();
    else if (role == ExecRole)
        return desktopFile.exec();
    else if (role == TypeRole)
        return desktopFile.type();
    else if (role == TerminalRole)
        return desktopFile.terminal();
    else if (role == IconRole)
        return desktopFile.icon();
    return QVariant();
}
/*!
 Hash helper for the roles in the MVA
*/
QHash<int, QByteArray> DesktopFileModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[CommentRole] = "comment";
    roles[ExecRole] = "exec";
    roles[TypeRole] = "type";
    roles[TerminalRole] = "terminal";
    roles[IconRole] = "icon";
    return roles;
}
