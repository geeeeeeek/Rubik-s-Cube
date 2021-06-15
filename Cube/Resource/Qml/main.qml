import QtQuick 2.12
import QtQuick.Window 2.12
import OpenGLUnderQML 1.0

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello OpenGL")
    // color: "black"

    // Rectangle {
    //     anchors.fill: parent
    //     color: "red"
    // }
   
    OpenGLWindow {
        
    }

    Rectangle {
        x: 200
        y: 300

        width: 400
        height: 300

        color: "green"
    }

}