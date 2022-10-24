import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id: root
    width: app_width
    height: app_height
    Image {
        id: mainPhone
        opacity: 0.6
        anchors.fill: parent
        source: "qrc:/picture/phone.jpg"
    }

    Rectangle{
        id: header
        width: parent.width
        height: 70
        color: "#3FAE51"
        Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: app_width
        height: 60
        color: "#3fae51"

        Rectangle {
            id: rectangle1
            x: 0
            y: 0
            width: 117
            height: 60
            color: "#00000000"
            Image {
                id: image
                x: 40
                y: 14
                width: 38
                height: 32
                source: "qrc:/picture/arrow.tif"
                fillMode: Image.PreserveAspectFit
                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        loader.sourceComponent = myGryadkiComponent
                    }
                }
            }
        }

        Text {
            id: text1
            x: 191
            y: 8
            width: 125
            height: 44
            color: "#ffffff"
            text: client.getNamePlantFarmer(selectedIdPlantFarmer)
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: text2
            x: 191
            y: 51
            width: 125
            height: 19
            color: "#ffffff"
            text: client.getTypeGroundPlantFarmer(selectedIdPlantFarmer) == 0 ? "Открытый грунт":"Закрытый грунт"
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle {
            id: rectangle2
            x: 336
            y: 8
            width: 162
            height: 52
            color: "#00000000"

            Text {
                id: text3
                anchors.fill: parent
                color: "#ffffff"
                text: qsTr("В Глоссарий")
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent

                    onClicked: {
                        loader.sourceComponent = plantsListComponent
                        console.log("In Glossariu")
                    }
                }
            }
        }
        }
    }
    Rectangle{
        id: background
        anchors.fill: parent
        anchors.topMargin: 70
        color: "#D9D9D9"
        opacity: .9
    }
    ScrollView{
        clip: true
        anchors.top: header.bottom
        width: root.width
        height: root.height - header.height

        contentHeight: columnmain.height +200

        Column{
            id: columnmain
//            spacing: 10
            PlantInfo{

            }
            PlantControl{

            }
            PlantStage{

            }
            PlantPhotos{
                //anchors.horizontalCenter: root.horizontalCenter
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
