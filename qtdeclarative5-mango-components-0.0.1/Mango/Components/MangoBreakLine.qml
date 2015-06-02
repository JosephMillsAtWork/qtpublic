import QtQuick 2.0

/*!
 \qmltype MangoBreakLine
 \inqmlmodule Mango.Components 0.1
 \inherits Item
 \since 5.3
 Qml Breakline that uses gradient to set the color.
 \code
        MangoBreakLine{
            width: parent.width
            height: Math.round(parent.height / 15)
        }
 \endcode

 Or if you wish to set the colors yourself  you can do it like this

 \code
        MangoBreakLine{
            width: parent.width
            height: Math.round(parent.height / 15)
            postionOne: "#000"
            postionTwo: "transparent"
            postionThree: "#30000000"
        }

 \endcode
    also see postionOne postionTwo and postionThree
 \b{ WARNING this Element is under heavey development }
*/

Rectangle{
    width: parent.width
    height: parent.height

    /*!
      \qmlproperty color MangoBreakLine::postionOne
      This is the first color of the three.  It is at the bottom of the Rectangle.
      default color is \b{#b95f00}
    */
    property color postionOne: "#b95f00"
    /*!
      \qmlproperty color MangoBreakLine::postionTwo
      This is the second color of the three.  It is at the middle of the Rectangle.
      default color is \b{#e67700}
    */
    property color postionTwo: "#e67700"
    /*!
      \qmlproperty color MangoBreakLine::postionThree
      This is the thrid color of the three.  It is at the top of the Rectangle.
      default color is \b{#b95f00}
    */
    property color postionThree: "#b95f00"
    gradient: Gradient{
        GradientStop{position: 0.1;color: postionOne}
        GradientStop{position: 0.5;color: postionTwo}
        GradientStop{position: 1;color:  postionThree}
    }
}
