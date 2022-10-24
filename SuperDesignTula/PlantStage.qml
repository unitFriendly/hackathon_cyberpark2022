import QtQuick 2.0

Rectangle {
    id: root
    width: app_width
    height: 300
    Rectangle {
        id: hatAccountMask
        width: dfltWidth
        height: 50
        color: "#00000000"


        property var nameText: "Стадия роста"
        x: 0
        y: 0
        Text {
            id: text1
            x: 191
            y: 0
            width: 125
            height: 50
            text: "Стадия роста"
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

    Image {
        id: stage_img
        y: 25
        source: client.getStagePlantFarmer(selectedIdPlant) == 0 ? "qrc:/picture/stage1.png" : client.getStagePlantFarmer(selectedIdPlant) == 1? "qrc:/picture/stage2.png": client.getStagePlantFarmer(selectedIdPlant) == 2? "qrc:/picture/stage3.png":"qrc:/picture/stage4.png"
        fillMode: Image.PreserveAspectFit
        width: root.width-100
        anchors.horizontalCenter: root.horizontalCenter
    }

    MouseArea{
        id: first
        x: 86
        y: 44
        width: 50
        height: 50
        onClicked: {
            stage_img.source = "qrc:/picture/stage1.png"
        }
    }
    MouseArea{
        id: second
        x: 86
        y: 107
        width: 50
        height: 50
        onClicked: {
            stage_img.source = "qrc:/picture/stage2.png"
        }
    }
    MouseArea{
        id: third
        x: 88
        y: 169
        width: 47
        height: 50
        onClicked: {
            stage_img.source = "qrc:/picture/stage3.png"
        }
    }
    MouseArea{
        id: fourth
        x: 89
        y: 241
        width: 44
        height: 50
        onClicked: {
            stage_img.source = "qrc:/picture/stage4.png"
        }
    }
}
