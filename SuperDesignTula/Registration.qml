import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    id: autorization
    width: app_width
    height: app_height


    property real customOpacity: 0.7
    property int fontSize: 18

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#000000"
        anchors.fill: parent
        Image {
            id: mainPhone
            opacity: 0.6
            anchors.fill: parent
            source: "qrc:/picture/phone.jpg"
        }

        Rectangle {
            id: rectangle
            x: 156
            y: 268
            width: 195
            height: 60
            color: "#00000000"
            Text {
                id: text1
                x: 0
                y: 0
                width: 195
                height: 60
                color: "#ffffff"
                text: qsTr("Регистрация")
                font.pixelSize: fontSize + 8
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                styleColor: "#000000"
            }
        }

        Rectangle {
            id: rectangle1
            x: 55
            y: 334
            width: 164
            height: 51
            color: "#00000000"
            Image {
                id: image
                width: 164
                height: 51
//                opacity: customOpacity
                source: "qrc:/picture/backgroundLabel.png"
            }

            Text {
                id: text2
                x: 0
                y: 0
                width: 164
                height: 51
                color: "#000000"
                text: qsTr("E-mail")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle {
            id: rectangle2
            x: 204
            y: 334
            width: 231
            height: 51
            color: "#00000000"
            radius: 0
            TextField {
                id: email
                anchors.fill: parent
                width: 231
                height: 51
                color: "#ffffff"
                text: "igor"
                hoverEnabled: false
                focus: true
                placeholderTextColor: "#404040"

                background: Image {
                    anchors.fill: parent
                    source: "qrc:/picture/backgroundTextField.png"
                }
            }
        }

        Rectangle {
            id: rectangle3
            x: 55
            y: 400
            width: 164
            height: 51
            color: "#00000000"
            Image {
                id: image1
                width: 164
                height: 51
//                opacity: customOpacity
                source: "qrc:/picture/backgroundLabel.png"
            }

            Text {
                id: text3
                x: 0
                y: 0
                width: 164
                height: 51
                color: "#000000"
                text: qsTr("Логин")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle {
            id: login
            x: 204
            y: 400
            width: 231
            height: 51
            color: "#00000000"
            radius: 0

            TextField {
                id: loginTextField
                x: 0
                y: 0
                width: 231
                height: 51

                hoverEnabled: false
                placeholderText: "IgorPrikol"
                selectByMouse: true

                placeholderTextColor: "#404040"

                background: Image {
                    anchors.fill: parent
                    source: "qrc:/picture/backgroundTextField.png"
                }
            }
        }

        Rectangle {
            id: rectangle5
            x: 55
            y: 540
            width: 164
            height: 51
            color: "#00000000"
            Image {
                id: image2
                width: 164
                height: 51
                source: "qrc:/picture/backgroundLabel.png"
            }

            Text {
                id: text4
                x: 0
                y: 0
                width: 164
                height: 51
                color: "#000000"
                text: qsTr("Еще раз")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle {
            id: rectangle6
            x: 204
            y: 540
            width: 231
            height: 51
            color: "#00000000"
            radius: 0
            TextField {
                id: password1
                x: 0
                y: 0
                width: 231
                height: 51
                text: "123"
                hoverEnabled: false
                placeholderText: "********"
                background: Image {
                    anchors.fill: parent
                    source: "qrc:/picture/backgroundTextField.png"
                }
                selectByMouse: true
                echoMode: TextInput.Password
                placeholderTextColor: "#404040"
            }
        }

        Rectangle {
            id: rectangle7
            x: 55
            y: 472
            width: 164
            height: 51
            color: "#00000000"
            Image {
                id: image3
                width: 164
                height: 51
                source: "qrc:/picture/backgroundLabel.png"
            }

            Text {
                id: text5
                x: 0
                y: 0
                width: 164
                height: 51
                color: "#000000"
                text: qsTr("Пароль")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle {
            id: rectangle8
            x: 204
            y: 472
            width: 231
            height: 51
            color: "#00000000"
            radius: 0
            TextField {
                id: password2
                x: 0
                y: 0
                width: 231
                height: 51
                text: "123"
                hoverEnabled: false
                placeholderText: "********"
                background: Image {
                    anchors.fill: parent
                    source: "qrc:/picture/backgroundTextField.png"
                }
                selectByMouse: true
                echoMode: TextInput.Password
                placeholderTextColor: "#404040"
            }
        }
    }

    Rectangle {
        id: input
        x: 141
        y: 620
        width: 224
        height: 40
        color: "#3fae51"
        radius: input.height / 4
        opacity: customOpacity
        Text {
            color: "#ffffff"
            text: "Зарегистрироваться"
            font.pixelSize: fontSize
            font.bold: true
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                client.sendRegistration(login.text,password1.text, email.text)
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:1.33}
}
##^##*/
