/*
* Joseph Mills 
* a custom image button
*/

import QtQuick 2.0
import QtQuick.Controls.Styles 1.0
    /*!
    \qmltype ImageButton
    \inqmlmodule Mango.Components 0.1
     \inherits Item
     \since 5.3
     Qml Button that has a image in the center of it
     \b{ WARNING this Element is under heavey development }
	*/

Item{
    id:buttonRoot
    width: parent.width
    height: parent.height
    /*!
     \qmlproperty bool ImageButton::isImage
        used to tell the Image Button if it in fact does have a image default value is false
	*/
	property bool isImage: false
    /*!
     \qmlproperty bool ImageButton::hasBorder
     tells the Button if there is a border by default this is set to false
	*/
	property bool  hasBorder: false
    
	/*!
     \qmlproperty string ImageButton::string
      The text that is inside the button
	*/
	
	property string text: ""
    
	/*!
     \qmlproperty string ImageButton::fontFamily
     the tye of font for the text that is in the button
	*/
	property string fontFamily: "Sans"
    
	/*!
     \qmlproperty string ImageButton::image
     The Image that is in the button can be from a url or a local file. Or a resources file
	*/
	property string image

    /*!
    \qmlproperty int ImageButton::imageHeight
     the hight of the image that is in the button. Be carful with this
	*/
	property int imageHeight
    /*!
     \qmlproperty int ImageButton::imageWidth
     the width of the image that is in the button.  Be Carefull with this.
	*/
	property int imageWidth
    /*!
     \qmlproperty bool ImageButton::hoverEnabled
      Sets the Button to allow or disallow hovering on the buttons Mouse area.  Also see  onEntered and onExited
	*/
	property bool hoverEnabled: false
    /*!
     \qmlproperty int ImageButton::radius
     the over all radius of the button. by default this is set to 0
	*/
	property int radius: 0
    /*!
     \qmlproperty string ImageButton::color
     The Background color of the button that will be used. Default is set to white
	*/
	property string color: "white"
    /*!
     \qmlproperty color ImageButton::textColor
     The color of the text if there is any
	*/
	property color textColor:  "black"
    /*!
    \qmlproperty int ImageButton::fontSize
     the size of the font for the text that is in the button if any.  default is set to 22 px
	*/
	property int fontSize: 22
    /*!
     \qmlproperty int ImageButton::borderSize
     the overall size of the border line that gets drawed around the button
	*/
	property int borderSize: 0
    /*!
     \qmlproperty string ImageButton::borderColor
     the color of the line that get drawed around the edge of the button.
	*/
	property string borderColor: "transparent"
    /*!
     \qmlsignal ImageButton::clicked()
     a signal that is sent when the button is clicked
	*/
	signal clicked
    /*!
     \qmlsignal ImageButton::entered()
     a signal that is sent when the mouse area of the button has been entered \b{NOTE: hoverEnabled must be set to true}
	*/
	signal entered
    /*!
     \qmlsignal ImageButton::exited()
     a signal that is sent when the mouse area of the button is not in focus. In other words if one enters the mouse area of the button with te mouse then leaves it signals that it has left the button.
     \b{NOTE hoverEnabled must be set to true}
	*/
	signal exited
    /*!
    \qmlsignal ImageButton::pressAndHold()
    A signal that is sent when the button is press and held down for more then a second
	*/
	signal pressAndHold
    /*!
     \qmlmethod ImageButton::onEnterPressed
     a keyboard signal that sends a clicked method to the button when the enter key is pressed
	*/
	Keys.onEnterPressed: clicked()
    /*!
     \qmlmethod ImageButton::onEnterPressed
     a keyboard signal that sends a clicked method to the button when the enter key is pressed this is also a work around for different OS systems
	*/  
	Keys.onReturnPressed: clicked()
    
	Rectangle{
        width: parent.width
        height: parent.height
        radius: buttonRoot.radius
        color: buttonRoot.color
        border.width: buttonRoot.borderSize
        border.color: buttonRoot.borderColor
    }
    MouseArea{
        anchors.fill: parent
        onClicked: buttonRoot.clicked();
        hoverEnabled: buttonRoot.hoverEnabled
        onEntered: buttonRoot.entered()
        onExited: buttonRoot.exited()
        onPressAndHold: buttonRoot.pressAndHold();
    } 
    Image{
        //fixme make more dynamic in the anchors
        anchors.centerIn: parent
        source: buttonRoot.image
        visible: buttonRoot.isImage
        width: buttonRoot.imageWidth
        height: buttonRoot.imageHeight
    }
    Text {
        text: buttonRoot.text 
        color: buttonRoot.textColor
        font.pixelSize: buttonRoot.fontSize
        font.family: buttonRoot.fontFamily
        anchors.centerIn: parent
    }
}
