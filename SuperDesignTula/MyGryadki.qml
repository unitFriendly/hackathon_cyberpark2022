import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: addContact

    property int dfltWidth: app_width
    property int dfltHeight: app_height
    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#3fae51"

    property int sizeHeightRectName: 84

    property int fontSize: 14
    property var tmpContactsChar
    property string chat_title: "Контакты"

    property var patternPlantElement


    property int counter: 0
    property var logins: []


//    ConfidenceWidget{
//        id: confidence
//        onClicked: {
//            confidence.show()
//        }
//    }

    width: dfltWidth
    height: dfltHeight
    color: noColor


    function loadContacts(){
//        for(var i = 0; i < columnContact.data.length;i++)
//        {
//            columnContact.data[i].destroy()
//        }

//        var countD = clientData.getCountMapContacts();

//        var tmp;

//        for(var i=0;i<countD;i++){
//            tmp = tmpContactsChar.createObject(columnContact,
//                                               {
//                                                   indexRepeaterChar: i,
//                                                   textRepeaterChar: clientData.getCharMapContacts(i),
//                                                   //dfltHeight: clientData.getCountContactsInMap(clientData.getCharMapContacts(i)) * sizeHeightRectName
//                                                   //                                                   textRepeaterContactsName: contactsss.getName(i)
//                                               });
//        }

////        if(createChatType == "just_chat")
////            chat_title = "Создать чат"
////        else if(createChatType == "group_chat")
////            chat_title = "Создать группу"
////        else if(createChatType == "private_chat")
////            chat_title = "Создать приватный чат"
////        else if(createChatType == "non_chat")
////            chat_title = "Контакты"

//        scrollContacts.contentHeight= clientData.getc * sizeHeightRectName
    }


    function clearAll(){
        if(columnContact.data!=null)
        for(var i = 0; i < columnContact.data.length;i++)
        {
            columnContact.data[i].destroy()
        }
    }

    function addPlantFarmer(id, namePlant, _plant_id, stage, createdDate, tipe_id, _status, name, pathAvatar){
        this_tmp = patternPlantElement.createObject(columnContact,
                                           {
                                               //horizontalCenter: parent.horizontalCenter,
                                               stage_textfield: stage,
                                               username: name,
                                               name: namePlant,
                                               icon_path: pathAvatar,
                                               inst_id: id,
                                               plant_id: _plant_id ,
                                               created_date: createdDate,
                                               type_id: tipe_id,
                                               status: _status

                                           });
    }

    onCounterChanged: {
        if(counter > 0)
            chat_title = "Выбрано: " + counter
        else chat_title = "Создать группу"
    }

    Rectangle{
        anchors.fill: parent
        width: parent.width
        height: parent.height
        color: "black"

        Image {
            id: mainPhone
            anchors.fill: parent
            source: "qrc:/picture/phone.jpg"
            opacity: customOpacity
        }
        Rectangle {
            z: 1
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
                    x: 8
                    y: 0
                    width: 40
                    height: 60
                    source: "qrc:/picture/ri_tochki.tif"
                    fillMode: Image.PreserveAspectFit
                }

                MouseArea{
                    anchors.fill: parent

                    onClicked: {
                        burgermenu.showNavDrawer()
//                        loader.sourceComponent = burgermenuComponent
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
                    text: "Мои грядки"
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle {
                id: rectangle3
                x: 389
                y: 0
                width: 117
                height: 60
                color: "#00000000"

                Image {
                    id: image1
                    x: 44
                    y: 8
                    width: 65
                    height: 44
                    source: "qrc:/picture/luppa.tif"
                    fillMode: Image.PreserveAspectFit
                }
                MouseArea{
                    anchors.fill: parent

                    onClicked: {
                        console.log("Здесь будет фильтр")
                    }
                }
            }
        }

        Rectangle {
            id: rectangle4
            x: 0
            y: 59
            width: app_width
            height: 841
            color: "#00000000"

            ScrollView{
                id: scrollContacts
                anchors.fill: parent
//                width: parent.width
//                anchors.topMargin: header.height
//                height: app_height*5
                contentWidth: parent.width

                anchors.top: header.bottom
                width: app_width
                height: app_height
                clip: false


               // clip: true

                Column{
                    id: columnContact
                    anchors.fill: parent
                    width: parent.width
                    height: parent.height
                    spacing: 10

//                    Repeater{
//                        model: 5

//                        PlantElement{
//                            anchors.horizontalCenter: parent.horizontalCenter
//                        }
//                    }

                }
            }
        }
    }

    Rectangle {
        id: addNewDialogMask
        x: 434
        y: 828
//        visible: createChatType == "group_chat" && counter > 0
        color: "#00000000"
        width: 72
        height: 72

        anchors.right: addContact.right
        anchors.rightMargin: 15

        anchors.bottom: addContact.bottom
        anchors.bottomMargin: 15

        radius: addNewDialogMask.width / 7

        opacity: customOpacity


        Image {
            id: addNewPlant
            x: 0
            y: 0
            width: 72
            height: 72
            source: "qrc:/picture/addNewPlant.png"
            fillMode: Image.PreserveAspectFit
        }

        MouseArea{
            id: addNewDialogMouse
            anchors.fill: parent

            onClicked: {
                dateLeft.setIsFromGoto(true);
                loader.sourceComponent = plantsListComponent




//                //                    loader.sourceComponent = contactsList
//                if(createChatType == "group_chat"){
//                    client.createChat(logins, "Групповой чат", "", true)
//                }

//                client.getMyDialogs()
//                loader.sourceComponent = listDialog
//                //var str = "123213"
//                //testMap.createNewDialog(str)


//                console.log("loader.source = contactsList")
            }
        }
    }


    Component.onCompleted: {
        patternPlantElement = Qt.createComponent("PlantElement.qml");
        //loadContacts()
        client.onAnswerPlantsUser.connect(clearAll);
        client.onAddPlantFarmer.connect(addPlantFarmer);
        client.sendGetPlantsUser();
        client.emitPlantsFarmer();
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
