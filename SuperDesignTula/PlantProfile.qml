import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: contactPageMain

    property string namePlant
    property int idPlant
    property string pathAvatar

    x: 50
    y: 8
    width: 448
    height: 84
    color: noColor
    //                opacity: 0.7
    //    border.color: mouseContacts.containsPress ? "white" : noColor
    //    border.width: 1

    Rectangle {
        id: contactPageAvatar
        x: 0
        y: 0
        width: 84
        height: parent.height
        color: noColor

        Rectangle {
            id: contactPageAvatarMask
            x: 10
            y: 10
            width: 64
            height: 65
            color: "#ffffff"
            radius: contactPageAvatarMask.width / 2


            Image {
                id: image1
                anchors.fill: parent
                fillMode: Image.PreserveAspectCrop
                source: pathAvatar
                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: parent
                }
            }
        }

        Rectangle {
            x: 80
            y: 0
            width: 367
            height: 84
            color: noColor

            Text {
                property int fontSize: 20
                id: textName
                anchors.fill: parent
                text: namePlant
                font.pixelSize: textName.fontSize
                color: "white"
                verticalAlignment: Text.AlignVCenter
                leftPadding: 10
            }
        }
    }

    MouseArea {
        id: mouseContacts
//        enabled: createChatType != "group_chat"
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {

            if (dateLeft.getIsFromGoto())
            {
                selectedIdPlant = idPlant
                loader.sourceComponent = plantcreatorComponent
            }
            else
            {
                selectedIdPlant = idPlant
                loader.sourceComponent = plantGlossaryInfoComponent
                console.log("loader.sourceComponent = articles")
            }






            //            if (createChatType == "non_chat")
            //            {
            //                currentContactOpen = indexContact
            //                currentCharContactOpen = textRepeaterChar
            //                loader.sourceComponent = profileMember
            //            }
            //            if(createChatType == "just_chat")
            //            {
            //                if(clientData.isExistDialogWithUser(clientData.getLoginContact(textRepeaterChar, indexContact)))
            //                {
            //                    console.log("Dialog is exist")
            //                }
            //                else
            //                {
            //                    client.createChat([clientData.getLoginContact(textRepeaterChar, indexContact)],"","",false)
            //                    client.getMyDialogs()
            //                    loader.sourceComponent = listDialog
            //                }
            //            }
            //            if(createChatType == "private_chat"){
            //                client.createPrivateChat(clientData.getLoginContact(textRepeaterChar, indexContact))
            //            }


            //        }
        }
    }
}
