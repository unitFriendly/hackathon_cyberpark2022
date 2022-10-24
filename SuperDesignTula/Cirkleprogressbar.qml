import QtQuick 2.9

Rectangle {
    id: root

    property int size: 70
    property int lineWidth: 5
    property real value: 0

    property color primaryColor: "#e0e0e0"
    property color secondaryColor: "#628395"

    property int animationDuration: 1000

    property string namePlant: "namePlant"

    property string valueProgress: "valueProgress"

    property string sourceImg: "qrc:/achivments/Неизвестное.png"
    width: 120
    height: 120

    color: "#00000000"

    onValueChanged: {
        canvas.degree = value * 360;
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: size
        height: size
        color: "#00000000"
        clip: false

        Canvas {
            id: canvas

            property real degree: 76


            anchors.fill: parent
            anchors.rightMargin: -50
            anchors.bottomMargin: -29
            anchors.leftMargin: 0
            anchors.topMargin: 0
            antialiasing: true

            onDegreeChanged: {
                requestPaint();
            }

            onPaint: {
                var ctx = getContext("2d");

                var x = root.width/2;
                var y = root.height/2;

                var radius = root.size/2 - root.lineWidth
                var startAngle = (Math.PI/180) * 270;
                var fullAngle = (Math.PI/180) * (270 + 360);
                var progressAngle = (Math.PI/180) * (270 + degree);

                ctx.reset()

                ctx.lineCap = 'round';
                ctx.lineWidth = root.lineWidth;

                ctx.beginPath();
                ctx.arc(x, y, radius, startAngle, fullAngle);
                ctx.strokeStyle = root.secondaryColor;
                ctx.stroke();

                ctx.beginPath();
                ctx.arc(x, y, radius, startAngle, progressAngle);
                ctx.strokeStyle = root.primaryColor;
                ctx.stroke();
            }

//            Image {
//                width: 82
//                height: 74
//                anchors.centerIn: parent
//                source: sourceImg
//                anchors.verticalCenterOffset: 10
//                anchors.horizontalCenterOffset: 0
//            }

            Behavior on degree {
                NumberAnimation {
                    duration: root.animationDuration
                }
            }
        }
    }

    Text {
        id: text1
        x: 0
        y: 0
        width: 120
        height: 26
        text: namePlant
        color: "#ffffff"
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: text2
        x: 0
        y: 98
        width: 120
        height: 22
        color: "#ffffff"
        text: valueProgress
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}

