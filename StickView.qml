import QtQuick 2.12
import QtQuick.Controls 2.5

Repeater {
    id: stickRepeater
    
    model: resourceManager.available
    
    Item {
        anchors.centerIn: parent
        rotation: (360 / stickRepeater.count) * index
        
        Rectangle {
            
            anchors.right: parent.right
            anchors.bottom: parent.top
            height: table.height / 7
            width: 1
            color: "black"
            
        }
    }
}
