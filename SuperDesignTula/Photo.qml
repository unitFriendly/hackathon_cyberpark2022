import QtQuick 2.0

Item {
    id: root
    width: app_width - 20
    height: photo.height + 70
    property string description_text
    property string pathFile
    property string dateTime
    property int id

    Rectangle{
        id: background

        width: parent.width
        color: "#3FAE51"
        radius: 20
        height: photo.height + 70

        Column{
            id: column
            anchors.fill: parent


            Image {
                anchors.top: parent.top
                anchors.topMargin: 30
                id: photo
                width: root.width - 20
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
                source: pathFile
            }

            Text{
                id: dateTime
                x: 10
                y: 10
                color: "#ffffff"
                text: dateTime
                font.pointSize: 12
            }
            Text{
                id: time_text
                anchors.right: parent.right
                anchors.rightMargin: 10
                y: 10
                width: 40
                color: "#ffffff"
                text: dateTime
                font.pointSize: 12
            }

            Text{
                id: description
                color: "#ffffff"
                text: description_text
                font.preferShaping: none.none
                anchors.bottom: column.bottom
                font.pointSize: 12
                anchors.bottomMargin: 20
                x: 10
            }
        }
    }
}
