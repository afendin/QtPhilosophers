import QtQuick 2.12
import QtQuick.Controls 2.5

Repeater {
    id: philosopherRepeater
    
    model: resourceManager.threadCount
    
    Item {
        anchors.centerIn: parent
        width: parent.width * .7
        height: parent.height *.7
        rotation: (360 / philosopherRepeater.count) * index
        
        Rectangle {
            id: philosopherRect

            width: 30
            height: 30
            radius: height
            border.width: 1
            anchors.horizontalCenter: parent.right
            anchors.verticalCenter: parent.top

            Connections {
                target: application
//                onWaitingForks: console.log("waiting: " + threadIndex + " index: " + index)
//                onStartEating: console.log("eating: " + threadIndex + " index: " + index)
//                onDoneEating: console.log("done: " + threadIndex + " index: " + index)
                onWaitingForks: threadIndex === index ? philosopherRect.color = "red" : null
                onStartEating: threadIndex === index ? philosopherRect.color = "green" : null
                onDoneEating: threadIndex === index ? philosopherRect.color = "white" : null
            }
        }
    }
}
