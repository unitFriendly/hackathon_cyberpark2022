import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id: root
    width: app_width
    height: app_height

    Rectangle{
        anchors.fill: parent
        width: parent.width
        height: parent.height
        color: "black"

        Image {
            id: mainPhone
            anchors.fill: parent
            source: "qrc:/picture/phone.jpg"
            opacity: 0.6
        }
    }

    Rectangle{
        id: header
        width: parent.width
        height: 70
        color: "#3FAE51"

        Rectangle {
            id: header1
            width: parent.width
            height: 60
            color: "#3fae51"
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
                        id: arrow
                        x: 30
                        y: 13
                        width: 39
                        height: 35
                        source: "qrc:/picture/ri_tochki.tif"
                        fillMode: Image.PreserveAspectFit
                        MouseArea {
                            anchors.fill: parent

                           onClicked: {
                               burgermenu.showNavDrawer()
                           }
                        }
                    }
                }

                Rectangle {
                    id: rectangle2
                    x: 195
                    y: 0
                    width: 117
                    height: 60
                    color: "#00000000"
                    Text {
                        id: text2
                        x: 0
                        y: 0
                        width: 117
                        height: 60
                        color: "#ffffff"
                        text: "Добавить грядку"
                        font.pixelSize: 20
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }
    }



    ScrollView{
        anchors.top: header.bottom
        width: root.width
        height: root.height - header.height
        clip: true
        contentHeight: first.height > second.height? first.height : second.height
        Row{
            Item{
                width: 5
                height: 10
            }
            anchors.horizontalCenter: root.horizontalCenter
            spacing: 10
            Column{
                width: header.width
                id: first
                spacing: 7


                Item{
                    width: 1
                    height: 10
                }
                Image {
                    width: parent.width
                    fillMode:Image.PreserveAspectFit
                    source: "qrc:/picture/weather.png"
                }
                Image {
                    width: parent.width
                    fillMode:Image.PreserveAspectFit
                    source: "qrc:/picture/flowers.png"
                }
                Image {
                    width: parent.width
                    fillMode:Image.PreserveAspectFit
                    source: "qrc:/picture/berry.png"
                }

                Item{
                    width: 1
                    height: 10
                }

                Item{
                    width: 1
                    height: 10
                }
                Image {
                    width: parent.width
                    fillMode:Image.PreserveAspectFit
                    source: "qrc:/picture/azalia.png"

                    MouseArea{
                        id: azalia
                        x: 13
                        y: 329
                        width: 209
                        height: 20
                        onClicked: {
                            print("prikol")
                        }
                    }
                }
                Image {
                    width: parent.width
                    fillMode:Image.PreserveAspectFit
                    source: "qrc:/picture/design.png"
                }
                Image {
                    width: parent.width
                    fillMode:Image.PreserveAspectFit
                    source: "qrc:/picture/wet.png"
                }

                Item{
                    width: 1
                    height: 10
                }


            }
        }
    }
}
