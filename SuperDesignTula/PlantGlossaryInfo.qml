import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    id: plantGlossaryInfo

    width: app_width
    height: app_height

    property var namePlant
    property var imagePlant



    ScrollView {
        id: scrollView
        contentWidth: parent.width
        anchors.fill: parent
        clip: true
        //ScrollBar.vertical: ScrollBar{}

        Image {
            id: image
            width: parent.width
            anchors.fill: parent
            /*height: 184
            verticalAlignment: Image.AlignTop*/
            source: client.getDescriptPlant(selectedIdPlant)
//            sourceSize.width: 1
//            fillMode: Image.PreserveAspectFit
        }
    }

    Rectangle {
        id: header
        x: 0
        y: 0
        width: app_width
        height: 70
        color: "transparent"

        Rectangle {
            id: rectangle
            x: 17
            y: 0
            width: 70
            height: 70
            color: "#3fae51"

            Image {
                id: arrow
                x: 13
                y: 20
                width: 44
                height: 31
                source: "qrc:/picture/arrow.tif"
                fillMode: Image.PreserveAspectFit

                MouseArea{
                    anchors.fill: parent

                    onClicked: {
                        loader.sourceComponent = plannerComponent
                    }
                }
            }
        }

        Text {
            id: textNamePlant
            x: 162
            y: 0
            width: 182
            height: 70
            color: "#ffffff"
            text: client.getNamePlant(selectedIdPlant)
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

}
