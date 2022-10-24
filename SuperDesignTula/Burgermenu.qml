import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: navigationDrawer
    property int dfltWidth: app_width
    property int dfltHeight: app_height
    width: dfltWidth//Math.min(dfltWidth, dfltHeight) / 3 * 2
    height: dfltHeight

    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"
    property int fontSize: 20

    function closeNavDrawer()
    {
        closeNavDrower.start()
    }

    function showNavDrawer()
    {
        openNavDrawer.start()
        console.log("showNavDrawer()")

        imgAvatar.source=client.getMyAvatar()
        tbName.text=client.getMyName();
        tbLogin.text=client.getMyLogin();
    }


    color: noColor
    //    opacity: 0.3

    MouseArea{
        anchors.fill: parent
    }

    NumberAnimation {
        id: openNavDrawer
        target: navigationDrawer
        property: "x"
        from: -dfltWidth
        to: 0
        loops: 1
        duration: 300
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        id: closeNavDrower
        target: navigationDrawer
        property: "x"
        from: 0
        to: -dfltWidth
        loops: 1
        duration: 300
        easing.type: Easing.InOutQuad
    }

    Rectangle{
        id: burgerMenu
        width: Math.min(dfltWidth, dfltHeight) / 3 * 2
        height: parent.height
        color: "#3fae51"


        Rectangle {
            id: rectangle
            width: Math.min(dfltWidth, dfltHeight) / 3 * 2
            height: 60
            color: noColor

            Rectangle {
                id: rectangle1
                width: 60
                height: 60
                color: noColor
                //            radius: 30


                Rectangle {
                    id: rectangle5
                    x: 8
                    y: 8
                    width: 44
                    height: 44
                    color: "#ffffff"
                    radius: rectangle5.width / 2

                    Image {
                        id: imgAvatar
                        x: 8
                        y: 8
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectCrop
                        source: client.getMyAvatar()
                        anchors.rightMargin: 0
                        anchors.bottomMargin: 0
                        anchors.leftMargin: 0
                        anchors.topMargin: 0

                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: parent
                        }
                    }
                }

                MouseArea {
                    id: mouseArea
                    x: 0
                    y: 0
                    width: 263
                    height: 60

                    onClicked: {
                        loader.sourceComponent = profileAchivmentComponent
                        burgermenu.closeNavDrawer()
                    }
                }
            }

            Rectangle {
                id: buttonSettings
                x: 277
                y: 0
                width: 60
                height: 60
                color: noColor
                z: 10
                Image {
                    x: 17
                    y: 18
                    width: 26
                    height: 25

                    source: "qrc:/picture/settings.png"
                    //                fillMode: Image.PreserveAspectFit
                }

                MouseArea{
                    anchors.fill: parent

                    onClicked: {
                        loader.sourceComponent = settingsComponent
                        burgermenu.closeNavDrawer()
                    }
                }
            }

            Rectangle {
                id: rectangle3
                x: 60
                y: 0
                width: 218
                height: 30
                color: noColor

                Text {
                    id: tbName
                    anchors.leftMargin: 10
                    anchors.fill: parent
                    color: "#ffffff"
                    text: client.getMyName()
                    font.pixelSize: fontSize
                    verticalAlignment: Text.AlignVCenter
                    Component.onCompleted: {
                        text: client.getMyName()
                    }
                }


            }

            Rectangle {
                id: rectangle4
                x: 60
                y: 30
                width: 218
                height: 30
                color: noColor

                Text {
                    id: tbLogin
                    anchors.leftMargin: 10
                    anchors.fill: parent
                    color: "#ffffff"
                    text: client.getMyLogin()
                    font.pixelSize: 12
                    verticalAlignment: Text.AlignVCenter
                }

            }
        }

        Rectangle {
            id: lineCuka
            x: 35
            y: 66
            width: 267
            height: 1
            color: "#ffffff"
        }

        Column {
            id: columnMenu
            anchors.top: lineCuka.bottom
            anchors.topMargin: 15
            anchors.right: parent.right
            anchors.left: parent.left
            width: parent.width
            height: 4 * (columnMenu.spacing * repMenu.height)
            spacing: 5


            Repeater{
                id: repMenu
                anchors.fill: parent

                model: 6

                property int sizeHeightMenuElement: 60
                MenuElement {


                }
            }
        }

        Rectangle {
            id: lineCuka1
            x: 35
            y: 477
            width: 267
            height: 1
            color: "#ffffff"
        }

        Rectangle {
            id: lineCuka2
            x: 35
            y: 693
            width: 267
            height: 1
            color: "#ffffff"
        }

        Column {
            id: helpColumn
            anchors.top: lineCuka2.bottom
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left

            spacing: 10
            width: parent.width
            height: repHelp.model * (helpColumn.spacing + repHelp.height)

            Repeater{
                id: repHelp
                anchors.fill: parent
                model: 3

                property int sizeHelpHeight: 60

                HelpMenu{

                }
            }
        }
    }

    Rectangle {
        id: rectangle7
        width: 169
        height: parent.height
        anchors.right: parent.right
        anchors.left: burgerMenu.right
        color: "black" // black
        opacity: 0.3

        MouseArea{
            anchors.fill: parent

            onClicked: {
                closeNavDrower.start()
            }
        }
    }

    //    Component.onCompleted: {
    //        openNavDrawer.start()
    //    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:1.75}
}
##^##*/
