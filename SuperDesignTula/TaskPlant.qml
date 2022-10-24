import QtQuick 2.0

Item {
    id: root
    width: 480
    height: 50

    property var day_value: 25
    property string button_text_: "Полить"

    Rectangle{
        id: background
        color: "#f5f5f5"
        opacity: .9
        radius: 10
        anchors.fill: parent

        Row{
            id: row
            spacing: 10
            anchors.fill: parent

            Item {
                width: 1
                height: parent.height
            }

            Column{
                anchors.verticalCenter: row.verticalCenter
                Text{
                    id: dayText
//                    height: 45
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    color: "#7F7F7F"
                    text: day_value
                    //                anchors.verticalCenter: row.verticalCenter
                    //anchors.left: row.left
                    //anchors.leftMargin: 10
                }
                Text{
                    id: dayOfWeekText
//                    height: 45
                    font.pixelSize: 10
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    width: dayText.width
                    color: "#7F7F7F"
                    text: "ПН"
                }
            }
            Rectangle{
                width: 1
                height: parent.height - 20
                anchors.verticalCenter: row.verticalCenter
                color: "#7F7F7F"
            }


            Text {
                id: plant_username
                text: qsTr("Валера")
                font.pixelSize: 23
                height: background.height
                verticalAlignment: Text.AlignVCenter
                font.family: "Calibri"
                anchors.verticalCenter: row.verticalCenter
            }


            Rectangle{
                width: 1
                height: parent.height - 20
                anchors.verticalCenter: row.verticalCenter
                color: "#7F7F7F"
            }

            Text {
                id: plant_name
                text: qsTr("Мандарин")
                font.pixelSize: 16
                horizontalAlignment: Text.AlignLeft
                color: "#7F7F7F"
                height: background.height
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: row.verticalCenter
                font.family: "Calibri"
            }
        }
        PlantButton{
            anchors.right: background.right
            anchors.rightMargin: 5
            anchors.verticalCenter: background.verticalCenter
//            is_active: false
//            is_overdue: false
            button_text: button_text_
            width: 150


        }
    }

}
