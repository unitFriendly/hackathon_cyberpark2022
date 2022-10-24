import QtQuick 2.0

Item {
    id: root
    property string button_text: "Включить"
    property bool is_active: true
    property string mode: "water"
    property bool is_overdue: false
    width: 150
    height: 40



    Rectangle {
        id: button
        visible: is_active
        anchors.fill: parent
        color: !is_overdue && is_active ? (mouseArea.containsPress ? Qt.darker("#3fae51") : "#3fae51") : (mouseArea.containsPress ? Qt.darker("#FF0000") : "#FF0000")
        radius: button.height / 4
        opacity: 0.9
        //anchors.verticalCenter: light_icon.verticalCenter

        Text {
            color: "#f5f5f5"
            text: button_text
            font.pixelSize: 20
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: mouseArea
            anchors.fill: button
            //hoverEnabled: true

            onClicked: {
                console.log("button")
            }
        }
    }

    Rectangle{
        id: inactive_button
        visible: !is_active
        anchors.fill: parent
        radius: inactive_button.height / 4
        color: "#f5f5f5"
        Row{
            anchors.fill: parent
            spacing: 7
            //            anchors.verticalCenter: parent.verticalCenter
            Item{
                width: 5
                height: parent.height
            }

            Image {
                id: icon
                width: parent.height -15
                height: width
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
            }
            Text{
                text: button_text
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                //anchors.fill: parent
                //                horizontalAlignment: Text.AlignHCenter
                //                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    Component.onCompleted: {
        if(mode == "water")
            icon.source = "qrc:/picture/water.png"
        else if(mode == "light")
            icon.source = "qrc:/picture/light.png"
        else if(mode == "temperature")
            icon.source = "qrc:/picture/wind.png"
    }
}
