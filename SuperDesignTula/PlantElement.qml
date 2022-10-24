import QtQuick 2.0


Item {
    id: root

    width: app_height
    height: 210

    property string stage_textfield: "I"
    property string username: "Клава"
    property string name: "Клубника (Земляника)"

    property string icon_path: "qrc:/picture/strawberry.png"

    property string water_data_text: "39%"
    property string temperature_data_text: "22 ⁰С"
    property string light_data_text: "--"


    property int inst_id;
    property int plant_id;
    property string created_date;
    property int type_id;
    property int status;


    Rectangle{
        id: background
        anchors.fill: root
        radius: 25

        color: "#ccf5f5f5"



        Column{
            id: element_column
            anchors.fill: background

            Row{
                id: header
                width: background.width
                height: 40
                anchors.top: element_column.top
                anchors.topMargin: 10
                Text{
                    id: plant_username
                    font.pixelSize: 30
                    text: username
                    font.family: "Calibri Light"
                    width: 250
                    height: header.height
                    anchors.verticalCenter: header.verticalCenter
                    anchors.left: header.left
                    anchors.leftMargin: 10
                }

                Text{
                    id: plant_name
                    font.pixelSize: 20
                    text: name
                    font.family: "Calibri Light"
                    color: "#7F7F7F"
                    anchors.right: header.right
                    anchors.rightMargin: 25
                    anchors.verticalCenter: header.verticalCenter
                }
            }

            Row{
                id: control_row
                spacing: 20
                anchors.left: element_column.left
                anchors.leftMargin: 13
                anchors.bottom: element_column.bottom
                anchors.bottomMargin: 13
                Rectangle{
                    id: image_background

                    property int margin: 13

                    height: background.height - margin*2 - 40
                    width: height
                    color: "#f5f5f5"
                    radius: margin*2
//                    anchors.bottom: element_column.bottom
//                    anchors.bottomMargin: margin

//                    anchors.left: element_column.left
//                    anchors.leftMargin: margin

                    Image{
                        id: plant_image
                        width: image_background.width - 60
                        height: width
                        anchors.centerIn: image_background
                        source: icon_path
                        fillMode: Image.PreserveAspectFit
                    }

                    Rectangle{
                        id: stage_background
                        width: image_background.width/3
                        height: width
                        color: "#628395"

                        radius: 10

                        anchors.left: image_background.left
                        anchors.bottom: image_background.bottom

                        Text{
                            id: stage_text
                            color:"#f5f5f5"
                            font.pixelSize: 23
                            text: stage_textfield == "1" ? "I" : stage_textfield == "2" ? "II" : stage_textfield == "3" ? "III" :"IV"
                            font.family: "Times New Roman"
                            anchors.centerIn: stage_background
                        }
                    }
                }

                Column{
                    id: table
                    height: image_background.height


                    Row{
                        id: water_row
                        height: table.height/3
                        width: background.width - image_background.height/3

                        spacing: 20

                        Image{
                            id: water_icon
                            source: "qrc:/picture/water.png"
                            height: image_background.height/3-10
                            width: height
                            fillMode: Image.PreserveAspectFit
                            anchors.verticalCenter: water_row.verticalCenter
                        }

                        Text{
                            id: water_data
                            font.pixelSize: 20
                            font.family: "Calibri Light"
                            text: water_data_text
                            width: 50
                            anchors.verticalCenter: water_row.verticalCenter
                            anchors.horizontalCenter: element_column.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
//                        PlantButton{
//                            is_active: true
//                        }


                        PlantButton{
                            id: water_button
                            mode: "water"
                        }

//                        Rectangle {
//                            id: water_button
//                            width: 150
//                            height: 40
//                            color: mouseArea_water.containsPress ? Qt.darker("#3fae51") : "#3fae51"
//                            radius: water_button.height / 4
//                            opacity: 0.9
//                            anchors.verticalCenter: water_icon.verticalCenter

//                            Text {
//                                color: "#f5f5f5"
//                                text: "Полить"
//                                font.pixelSize: 20
//                                anchors.fill: parent
//                                horizontalAlignment: Text.AlignHCenter
//                                verticalAlignment: Text.AlignVCenter
//                            }

//                            MouseArea {
//                                id: mouseArea_water
//                                anchors.fill: water_button
//                                //hoverEnabled: true
//                            }
//                        }
                    }


                    Row{
                        id: temperature_row
                        height: table.height/3
                        width: background.width - image_background.height/3

                        spacing: 20

                        Image{
                            id: temperature_icon
                            source: "qrc:/picture/temperature.png"
                            height: image_background.height/3-10
                            width: height
                            fillMode: Image.PreserveAspectFit
                            anchors.verticalCenter: temperature_row.verticalCenter
                        }

                        Text{
                            id: temperature_data
                            font.pixelSize: 20
                            font.family: "Calibri Light"
                            text: temperature_data_text
                            width: 50
                            anchors.verticalCenter: temperature_row.verticalCenter
                            anchors.horizontalCenter: element_column.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }


                        PlantButton{
                            id: temperature_button
                            mode: "temperature"
                            is_active: false
                            button_text: "Через 9 ч."
                        }

//                        Rectangle {
//                            id: temperature_button
//                            width: 150
//                            height: 40
//                            color: mouseArea_temperature.containsPress ? Qt.darker("#3fae51") : "#3fae51"
//                            radius: temperature_button.height / 4
//                            opacity: 0.9
//                            anchors.verticalCenter: temperature_icon.verticalCenter

//                            Text {
//                                color: "#f5f5f5"
//                                text: "Через 9 ч."
//                                font.pixelSize: 20
//                                anchors.fill: parent
//                                horizontalAlignment: Text.AlignHCenter
//                                verticalAlignment: Text.AlignVCenter
//                            }

//                            MouseArea {
//                                id: mouseArea_temperature
//                                anchors.fill: temperature_button
//                                //hoverEnabled: true
//                            }
//                        }
                    }

                    Row{
                        id: light_row
                        height: table.height/3
                        width: background.width - image_background.height/3

                        spacing: 20

                        Image{
                            id: light_icon
                            source: "qrc:/picture/light.png"
                            height: image_background.height/3-10
                            width: height
                            fillMode: Image.PreserveAspectFit
                            anchors.verticalCenter: light_row.verticalCenter
                        }

                        Text{
                            id: light_data
                            font.pixelSize: 20
                            font.family: "Calibri Light"
                            text: light_data_text
                            width: 50
                            anchors.verticalCenter: light_row.verticalCenter
                            anchors.horizontalCenter: element_column.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }


                        PlantButton{
                            id: light_button
                            button_text: "Включить"
                            is_overdue: true
                        }

//                        Rectangle {
//                            id: light_button
//                            width: 150
//                            height: 40
//                            color: mouseArea_light.containsPress ? Qt.darker("#3fae51") : "#3fae51"
//                            radius: light_button.height / 4
//                            opacity: 0.9
//                            anchors.verticalCenter: light_icon.verticalCenter

//                            Text {
//                                color: "#f5f5f5"
//                                text: "Включить"
//                                font.pixelSize: 20
//                                anchors.fill: parent
//                                horizontalAlignment: Text.AlignHCenter
//                                verticalAlignment: Text.AlignVCenter
//                            }

//                            MouseArea {
//                                id: mouseArea_light
//                                anchors.fill: light_button
//                                //hoverEnabled: true
//                            }
//                        }
                    }


                    //                    Image {
                    //                        id: temperature_icon
                    //                        source: "qrc:/picture/temperature.png"
                    //                        height: image_background.height/3
                    //                        width: height
                    //                    }
                    //                    Image {
                    //                        id: light_icon
                    //                        source: "qrc:/picture/light.png"
                    //                        height: image_background.height/3
                    //                        width: height
                    //                    }
                }
            }
        }

    MouseArea{
        id: mouseArea_rect
        anchors.fill: parent

        onClicked: {
            selectedIdPlantFarmer = inst_id
            loader.sourceComponent = pageComponent
        }
    }
    }
}

