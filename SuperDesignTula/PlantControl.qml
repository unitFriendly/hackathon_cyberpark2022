import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id: root
    width: app_width
    height: width/3+20

        Rectangle {
            id: hatAccountMask
            width: dfltWidth
            height: 50
            color: "#00000000"


            property var nameText: "Устройство контроля"
            x: 0
            y: 0
            Text {
                id: text1
                x: 191
                y: 0
                width: 125
                height: 50
                text: "Устройство контроля"
                font.pixelSize: 18
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Rectangle {
                id: rectangle1
                x: 8
                y: 24
                width: 148
                height: 2
                color: "black"
            }

            Rectangle {
                id: rectangle2
                x: 355
                y: 24
                width: 144
                height: 2
                color: "black"
            }
        }


        Column{
            anchors.fill: parent
            Item{
                anchors.fill: parent

                Text{
                    id: control_name
                    text: "OJ24 RealTime"
                    color: "#7F7F7F"
                    font.pixelSize: 21
                    anchors.left: parent.left
                    anchors.leftMargin: 10

                    anchors.top: parent.top
                    anchors.topMargin: 70
                }
                Rectangle {
                    id: button
                    visible: is_active
                    width: 150
                    height: 40
                    color:mouseArea.containsPress ? Qt.darker("#628395") : "#628395"
                    radius: button.height / 4
                    opacity: 0.9
                    anchors.verticalCenter: control_name.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                    //anchors.verticalCenter: light_icon.verticalCenter

                    Text {
                        color: "#f5f5f5"
                        text: "Отвязать"
                        font.pixelSize: 20
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    MouseArea {
                        id: mouseArea
                        anchors.fill: button

                        //hoverEnabled: true
                    }
                }
            }

            Image{
                source: "qrc:/picture/aaaaaaaaaa.png"
                width: root.width - 140
                x: 10
                fillMode: Image.PreserveAspectFit
                y: 140
                Text {
                    id: water_text
                    x: 49
                    y: 8
                    text: qsTr("39%")
                    font.pointSize: 16
                    minimumPixelSize: 21
                }

                Text {
                    id: temperature_text
                    x: 185
                    y: 8
                    text: qsTr("--")
                    font.pointSize: 16
                    minimumPixelSize: 21
                }

                Text {
                    id: light_text
                    x: 372
                    y: 8
                    text: qsTr("86%")
                    font.pointSize: 16
                    minimumPixelSize: 21
                }
            }
        }


}
