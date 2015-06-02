import QtQuick 2.0
import QtGraphicalEffects 1.0
/*!
 \qmltype MangoButton
 \inqmlmodule Mango.Components 0.1
 \inherits Item
 \since 5.3
  A real simple button that has text and a radius and background color and more.

  \b{ WARNING this Element is under heavey development }

 \b{EXAMPLE: }

 \code
    MangoButton{
        buttonRadius: 20
        width: parent.width / 3
        height: 20
        text: "Button Text"
        onClicked:{
            console.log("The button was clicked")
        }
    }
  \endcode

*/

Item {
    id:button
    width: parent.width
    height: parent.height
    /*!
      \qmlproperty color MangoButton::buttonColor
      The background color of the button. For text color please see color .
      The default value of this property is set to \b{#e67700}
    */
    property color  buttonColor: "#e67700"
    /*!
      \qmlproperty int MangoButton::buttonRadius
      The radius of the Rectangle that will be used.  if set to higher then one.
      \b{default is set to 0}
    */
    property int  buttonRadius: 0
    /*!
      \qmlproperty string MangoButton::text
      The text of the button that is anchored into the center of the button.
    */
    property string  text: ""
    /*!
      \qmlproperty int MangoButton::buttonWidth
      the over all width of the button.  By default this is set to \b{20}px
    */
    property int buttonWidth: 20
    /*!
      \qmlproperty int MangoButton::buttonHeight
      The over all height of the button. by default this is set to \b{20}px
    */
    property int buttonHeight: 20
    /*!
      \qmlproperty color MangoButton::color
      The text color of the text that is centerIn to the MangoButton. for background color of the button see buttonColor
      deafult color is set to \b{whitesmoke}
    */
    property color color: "whitesmoke"
    /*!
      \qmlproperty string MangoButton::borderWidth
      The width of the border that will be drawn around the rectangle of the button
      by default the color of the text is set tpo \b{1}px
    */
    property int borderWidth: 1
    /*!
      \qmlproperty color MangoButton::borderColor
      The color of the border of the rectangle if the borderWidth is set to anything bigger then 1
      by default color is set to \b{#D35400}
    */
    property color borderColor: "#D35400"
    /*!
      \qmlproperty bool MangoButton::hoverEnabled
      This is used to set tyhe button to be responsive when hovered over and or exited.
      see also entered and exit
      */
    property bool hoverEnabled: false

    /*!
    \qmlproperty bool MangoButton::multiMouse
    Set this to true if you would like to use rightClicked or middleClicked
    by default this is set to \b{false}
    */
    property bool multiMouse: false

    /*!
    \qmlproperty bool MangoButton::dragEnabled
    Set this to true if you wish to be able to drag and drop the button.
    by default this is set to \b{false}
    */
    property bool dragEnabled: false


    /*!
    \qmlproperty bool MangoButton::dragXOnly
    Set this to true if you would like to be able to drag the button around the screen \b{only on its X axis}.
    dragEnabled must be set to \b{true} for this property to work
    */
    property bool dragXOnly: false

    /*!
    \qmlproperty bool MangoButton::dragYOnly
    Set this to true if you would like to be able to drag the button around the screen \b{only on its Y axis}.
    dragEnabled must be set to \b{true} for this property to work
   */
    property bool dragYOnly: false

    /*!
    \qmlproperty bool MangoButton::dragXAndY
    Set this to true if you would like to be able to drag the button around the screen \b{on both the X and Y axis}.
    dragEnabled must be set to \b{true} for this property to work
    */
    property bool dragXAndY: false

    /*!
      \qmlsignal MangoButton::entered()
    A signal that is used for when the mouse enters the MangoButton.
    hoverEnabled \b{must be set to true}
    */
    signal entered

    /*!
      \qmlsignal MangoButton::exit()
    A signal that is used for when the mouse leaves the MangoButton.
    hoverEnabled \b{must be set to true}
    */
    signal exit

    /*!
      \qmlsignal MangoButton::clicked()
      A signal that is sent when the Button is clicked.
    */
    signal clicked

    /*!
      \qmlsignal MangoButton::doubleClicked()
      signal that is sent when the button is double clicked by the mouses left button
    */
    signal doubleClicked

    /*!
    \qmlsignal MangoButton::middleClicked()
    A signal that is sent when the middle mouse button is clicked. \b{NOTE:} multiMouse must be set to \b{true} for this to work
    */
    signal middleClicked

    /*!
    \qmlsignal MangoButton::rightClicked()
    A signal that is sent when the button has been clicked with the right mouse button.
    \b{NOTE:} for this to work multiMouse must be set to \b{true}
    */
    signal rightClicked

    /*!
    \qmlsignal MangoButton::pressAndHold()
    A signal that is sent when the left mouse button is pressed and held down.
    */
    signal pressAndHold

    /*!
    \qmlsignal MangoButton::pressed()
    a signal that is sent for when the mouse button is pressed fast.  For other pressure points of the mouse please see.
    pressAndHold
    */
    signal pressed

    /*!
    \qmlsignal MangoButton::released()
    a signal that is sent when the left mouse button is released after it has just been pressed .  Also see pressAndHold
    */
    signal released
// /*!
//    \qmlproperty MangoButton::effect
//    a string that is used to set the effect of the button.  by default there is none.
//    */

    property color effectColor: "#77000000"
    property int  effectGlowRadius: 10
    property double effectSpread: 0.2
    property int  effectConerRadius: rootTangle.radius + effectGlowRadius
    RectangularGlow {
          id: effect
          anchors.fill: rootTangle
          glowRadius: effectGlowRadius
          spread: effectSpread
          color: effectColor
          cornerRadius: effectConerRadius // rootTangle.radius + glowRadius
      }
    Rectangle {
        id: rootTangle
        width: parent.width
        height: parent.height
        color:  buttonColor
        radius: buttonRadius
        border.width: button.borderWidth
        border.color: button.borderColor

        MouseArea{
            anchors.fill: parent
            hoverEnabled: button.hoverEnabled
            onPressAndHold: {
             button.pressAndHold()
            }
            onPressed: {
             button.pressed()
            }
            onReleased: {
             button.released()
            }
            onEntered: {
             button.entered()
            }
            onExited: {
             button.exit()
            }
            acceptedButtons: button.multiMouse ? Qt.LeftButton | Qt.RightButton | Qt.MiddleButton : Qt.LeftButton
            onClicked:{
                if(mouse.button === Qt.RightButton){
                 button.rightClicked()
                }else if (mouse.button === Qt.MiddleButton){
                 button.middleClciked()
                }else{
                button.clicked()
                }
            }
            drag.target:button.dragEnabled === true ? NULL : rootTangle
//            drag.active: button.dragEnabled === true ? true : false
            drag.axis:{
                if(button.dragXOnly === true){
                    Drag.XAxis
                }else if(button.dragYOnly === true){
                    Drag.YAxis
                }else if (button.dragXAndY === true ){
                    Drag.XandYAxis
                }else if (button.dragEnabled === false){
                    Drag.None
                }
            }

             onDoubleClicked: {
             button.doubleClicked()
            }

        }
        Text {
            text: button.text
            color: button.color
            anchors.centerIn:  parent
        }
    }
}
