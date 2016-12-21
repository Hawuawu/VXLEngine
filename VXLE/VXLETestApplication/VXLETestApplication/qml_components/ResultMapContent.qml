import QtQuick 2.0

Item {

    function setMap(image) {
        resultMap.so = image
    }

    Flickable {
        id: flickable
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        GridView {
            id: gridView1
            anchors.fill: parent
            delegate: Rectangle {
                width: 1201
                height: 1201
                color: colorCode
            }
            cellHeight: 1201
            cellWidth: 1201
            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
        }


    }

}
