import QtQuick 2.0
Item{
    id:imgButton

    SystemPalette{id: palette}
//    img
    property string img
//    text
    property string text
    property color textColor: palette.buttonText
    property double textFontSize: 12
    property bool textBold: false
//    mouse
    signal clicked()
Image {
    id: img
    source: imgButton.img
    width: parent.width
    height: parent.height
    MouseArea{
        id: burnMouseArea
        anchors.fill: img
        onClicked:{
         clicked()
        }
    }
    Text {
        id: modelTXT
        font.bold: imgButton.textBold
        font.pixelSize: imgButton.textFontSize
        color: imgButton.textColor
        wrapMode: Text.WordWrap
        width: img.paintedWidth
        height: paintedHeight
        anchors{
            horizontalCenter: burnMouseArea.horizontalCenter
            top: burnMouseArea.bottom
            topMargin: img.paintedHeight / 8
        }
        text: imgButton.text
    }
}
}
