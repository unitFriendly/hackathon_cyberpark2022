import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    id: autorization
    width: app_width
    height: app_height


    property real customOpacity: 0.7
    property int fontSize: 18

    function onAutorization(flag)
    {
        if (flag){
            loader.sourceComponent = plannerComponent
            client.sendGetAchivementsUser()
            client.sendGetAllDataFromGlossary()
            client.sendGetPlantsUser()

        }
        else
            console.log("Error autorization")
    }

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
                text: qsTr("Авторизация")
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
                text: qsTr("Логин")
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
                id: login
                anchors.fill: parent
                width: 231
                height: 51
                color: "#ffffff"
                text: "maksim"
                hoverEnabled: false
                focus: true
                placeholderTextColor: "#404040"

                background: Image {
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
                text: qsTr("Пароль")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle {
            id: rectangle4
            x: 204
            y: 400
            width: 231
            height: 51
            color: "#00000000"
            radius: 0

            TextField {
                id: password
                x: 0
                y: 0
                width: 231
                height: 51
                text: "123"
                hoverEnabled: false
                placeholderText: "********"
                selectByMouse: true
                echoMode: TextInput.Password
                placeholderTextColor: "#404040"

                background: Image {
                    source: "qrc:/picture/backgroundTextField.png"
                }
            }
        }

        Label {
            id: forgotPassword
            x: 55
            y: 477
            width: 149
            height: 37
            color: "#ffffff"
            text: qsTr("Забыли пароль?")
            font.underline: true
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            MouseArea {
                id: mouseArea2
                x: 0
                y: 0
                width: 149
                height: 37
            }
        }

        Label {
            id: registration
            x: 307
            y: 477
            font.underline: true
            width: 128
            height: 37
            color: "#ffffff"
            font.pixelSize: fontSize
            text: qsTr("Регистрация")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            MouseArea {
                id: mouseArea1
                anchors.fill: parent

                onClicked: {

                    loader.sourceComponent = registrationComponent;
                    console.log("Регистрация загружена")
                }
            }
        }
    }

    Rectangle {
        id: input
        x: 204
        y: 474
        width: 103
        height: 40
        color: mouseArea.containsPress ? "#3fae51" : "pink"
        radius: input.height / 4
        opacity: customOpacity

        Text {
            color: "#000000"
            text: "Вход"
            font.pixelSize: fontSize
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            //hoverEnabled: true
            onClicked: {
                client.sendAuthorization(login.text, password.text)
            }
        }
    }

    Component.onCompleted: {
        client.onAnswerAuthorization.connect(onAutorization);
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.1}D{i:19}
}
##^##*/
