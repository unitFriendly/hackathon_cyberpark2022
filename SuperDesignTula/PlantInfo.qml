import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id: root
    width: app_width
    height: parent.width/2.1
    property string icon_path: "qrc:/picture/strawberry.png"

    Rectangle{
        id: image_background

        anchors.top: parent.top
        anchors.topMargin: 15

        anchors.left: parent.left
        anchors.leftMargin: 15

        property int margin: 13

        height: parent.width/2.3
        width: height
        color: "#f5f5f5"
        radius: margin*2
        //                    anchors.bottom: element_column.bottom
        //                    anchors.bottomMargin: margin

        //                    anchors.left: element_column.left
        //                    anchors.leftMargin: margin

        Image{
            id: plant_image
            width: image_background.width - 60
            height: width
            anchors.centerIn: image_background
            source: client.getAvatarPlantFarmer(selectedIdPlantFarmer)
        }
    }


    TextField{
        id: plant_name
        placeholderText: client.getNamePlantFarmer(selectedIdPlantFarmer)
        font.pixelSize: 29


        anchors.left: image_background.right
        anchors.leftMargin: 15

        anchors.top: parent.top
        anchors.topMargin: 15

        background: Rectangle{
            opacity: 0
        }
    }


    Image{
        id: icon_edit
        width: 25
        height: width
        fillMode: Image.PreserveAspectFit

        source: "qrc:/picture/edit.png"
        anchors.top: parent.top
        anchors.topMargin: 25

        anchors.right: parent.right
        anchors.rightMargin: 20
    }

    Text{
        id: label1
        text: "Посадка:"
        color: "#7F7F7F"
        font.pixelSize: 21
        anchors.left: plant_name.left
        anchors.leftMargin: 10

        anchors.top: plant_name.bottom
        anchors.topMargin: 20
    }
    Text{
        id: date1
        anchors.left: label1.left

        anchors.top: label1.bottom
        anchors.topMargin: 5
        text: client.getCreateTimePlantFarmer(selectedIdPlantFarmer)
        font.pixelSize: 21
    }


    Text{
        id: label2
        text: "Окончание ухода:"
        color: "#7F7F7F"
        font.pixelSize: 21
        anchors.left: plant_name.left
        anchors.leftMargin: 10

        anchors.top: date1.bottom
        anchors.topMargin: 20
    }

    Rectangle {
        id: button
        visible: is_active
        width: 150
        height: 40
        color:mouseArea.containsPress ? Qt.darker("#628395") : "#628395"
        radius: button.height / 4
        opacity: 0.9
        anchors.bottom: image_background.bottom
        anchors.right: parent.right
        anchors.rightMargin: 15
        //anchors.verticalCenter: light_icon.verticalCenter

        Text {
            color: "#f5f5f5"
            text: "Отметить"
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

