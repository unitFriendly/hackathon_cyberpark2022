import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle{
    width: app_width
    height: app_height
    color: "#00000000"

    property var listPrice: ["qrc:/picture/price1700.png", "qrc:/picture/price2149.png", "qrc:/picture/price2490.png"]

    Rectangle{
        anchors.fill: parent
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        width: parent.width
        height: parent.height
        color: "black"

        Image {
            id: mainPhone
            anchors.fill: parent
            source: "qrc:/picture/phone.jpg"
//            opacity: 0.6

            Image {
                id: price1700
                x: 13
                y: 49
                width: 480
                height: 221
                source: "qrc:/picture/price1700.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: price2149
                x: 13
                y: 243
                width: 480
                height: 221
                source: "qrc:/picture/price2149.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: price2490
                x: 13
                y: 436
                width: 480
                height: 221
                source: "qrc:/picture/price2490.png"
                fillMode: Image.PreserveAspectFit
            }
        }
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


                    MouseArea{
                        anchors.fill: parent

                        onClicked: {
                            loader.sourceComponent = plannerComponent
                        }
                    }
                }
            }

            Text {
                id: text1
                x: 193
                y: 8
                width: 125
                height: 44
                color: "#ffffff"
                text: qsTr("Cyber-магазин")
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
