import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    visible: true
    width: 800
    height: 480
    title: qsTr("QtPhilosophers")


    Row {
        spacing: 50
        padding: 20

        Column {
            spacing: 20
            Rectangle {
                id: table

                width: 300
                height: 300
                radius: height
                border.width: 1

                StickView {}

                PhilosopherView {}
            }

            Item { width: 1; height: 5 }

            Row {
                spacing: 15
                Rectangle {
                    border.width: 1
                    height: 20
                    width: 20
                    radius: width
                    color: "white"
                }

                Text { text: qsTr("Think") }
            }

            Row {
                spacing: 15
                Rectangle {
                    border.width: 1
                    height: 20
                    width: 20
                    radius: width
                    color: "red"
                }

                Text { text: qsTr("Wait for fork") }
            }

            Row {
                spacing: 15
                Rectangle {
                    border.width: 1
                    height: 20
                    width: 20
                    radius: width
                    color: "green"
                }

                Text { text: qsTr("Eat") }
            }
        }


        Column {
            id: propertiesColumn

            enabled: !application.isRunning
            Row {
                QPText { text: qsTr("Philosophers:") }

                QPSpinBox {
                    id: philosopherSB

                    from: 2
                    to: 20
                    value: resourceManager.threadCount
                    onValueChanged: resourceManager.threadCount = value
                }

            }

            Row {
                QPText { text: qsTr("Chopstick per philosopher:") }

               QPSpinBox {
                    id: chopsticksPerPhilosopherSB

                    from: 2
                    to: from * 100
                    value: resourceManager.resourcePerThread
                    onValueChanged: resourceManager.resourcePerThread = value
                }
            }

            Row {
                QPText { text: qsTr("Chopsticks:") }

               QPSpinBox {
                    id: chopsticksSB

                    from: resourceManager.resourcePerThread
                    to: from * 100
                    value: resourceManager.resourceCount
                    onValueChanged: resourceManager.resourceCount = value
                }
            }

            Row {
                QPText { text: "Eat & think delay (ms):" }

               QPSpinBox {
                    editable: true
                    from: 10
                    to: 2000
                    stepSize: 250
                    value: resourceManager.sleepMseconds
                    onValueChanged:  resourceManager.sleepMseconds = value
                }
            }
        }
    }

    Button {
        anchors {
            bottom: parent.bottom
            bottomMargin: 200
            right: parent.right
            rightMargin: 70
        }

        text: application.isRunning ? qsTr("Stop") : qsTr("Start")
        onPressed: application.isRunning ? text = "..." : null
        onClicked: {
            if (application.isRunning) {
                application.stop()
                text = Qt.binding(() => application.isRunning ? qsTr("Stop") : qsTr("Start"))
                return
            }

            application.start();
        }
    }
}
