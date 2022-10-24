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
    property color biruzoviu: "#3FAe51"

    property int sizeHeightRectName: 84

    property int fontSize: 14
    property var tmpContactsChar
    property string chat_title: "Глоссарий"

    property int counter: 0
    property var logins: []

    property var testChar: ["a", "g", "w"]

    property var testW: ["wew", "wq"]

    property var testA: ["aofof"]
    property var testG: ["gad", "gbd"]

    property var testAG: [testA, testG, testW]


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
        for(var i = 0; i < columnContact.data.length;i++)
        {
            columnContact.data[i].destroy()
        }

        var countD = client.getCountCharPlants();

        var tmp;

        var sum=0;
        for(var i=0;i<countD;i++){
            tmp = tmpContactsChar.createObject(columnContact,
                                               {
                                                   indexRepeaterChar: i,
                                                   textRepeaterChar: client.getCharPlantsForIndex(i),
                                                   //dfltHeight: client.getCountPlantsinChar(i) * sizeHeightRectName
                                                   //                                                   textRepeaterContactsName: contactsss.getName(i)
                                               });
            sum+=client.getCountPlantsinChar(i);
        }

//        if(createChatType == "just_chat")
//            chat_title = "Создать чат"
//        else if(createChatType == "group_chat")
//            chat_title = "Создать группу"
//        else if(createChatType == "private_chat")
//            chat_title = "Создать приватный чат"
//        else if(createChatType == "non_chat")
//            chat_title = "Контакты"

        scrollContacts.contentHeight= sum * sizeHeightRectName
    }


    onCounterChanged: {
        if(counter > 0)
            chat_title = "Выбрано: " + counter
        else chat_title = "Создать группу"
    }

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
                    text: chat_title
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

            Image {
                id: camera
                x: 347
                y: 4
                width: 64
                height: 52
                source: "picture/camera.png"
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent

                    onClicked: {
                        loader.sourceComponent = cameraNeuronComponent
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
                width: parent.width
                anchors.topMargin: header.height
                height: app_height - header.height
                contentWidth: parent.width


                clip: false

                Column{
                    id: columnContact
                    //                    anchors.fill: parent
                    //                    width: parent.width
                    //                    height: parent.height
                    spacing: 10

//                    Repeater{
//                        model: testChar.length
//                        PlantsChar{
//                            //                            border.color: "red"

//                            textRepeaterChar: testChar[index]
//                            indexRepeaterChar: index
//                            testList: testAG[index]
//                        }
//                    }
                }
            }
        }
    }

//    Rectangle {
//        id: addNewDialogMask
//        x: 434
//        y: 828
//        visible: createChatType == "group_chat" && counter > 0
//        width: 72
//        height: 72

//        anchors.right: addContact.right
//        anchors.rightMargin: 15

//        anchors.bottom: addContact.bottom
//        anchors.bottomMargin: 15

//        radius: addNewDialogMask.width / 7

////        opacity: customOpacity
//        color: "#ff3fae51"
////        color: addNewDialogMouse.containsPress ? Qt.lighter(biruzoviu) : biruzoviu

////        Image {
////            id: addNewDialog
////            x: 11
////            y: 11
////            width: 50
////            height: 50
////            source: "qrc:/resourses/create chat_2.tif"
////            fillMode: Image.PreserveAspectFit
////        }

//        MouseArea{
//            id: addNewDialogMouse
//            anchors.fill: parent

//            onClicked: {
//                //                    loader.sourceComponent = contactsList
//                if(createChatType == "group_chat"){
//                    client.createChat(logins, "Групповой чат", "", true)
//                }

//                client.getMyDialogs()
//                loader.sourceComponent = listDialog
//                //var str = "123213"
//                //testMap.createNewDialog(str)


//                console.log("loader.source = contactsList")
//            }
//        }
//    }


    Component.onCompleted: {
        tmpContactsChar = Qt.createComponent("PlantsChar.qml");
        loadContacts()
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/
