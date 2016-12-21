import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

import com.vxle.testapplication 1.0

Rectangle {
    id: rectangle2
    color: "#e1e1e1"

    property ApplicationSettings applicationSettings;
    signal loadedImage(Image image);
    signal loadedPartImage(int x, int y, Image image)

    Rectangle {
        id: bg
        width: parent.width  * 0.7
        height: 125
        color: "#ffffff"
        border.width: 2
        border.color: "#46aae0"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        SRTMLoader {
            id: srtmLoader

            onLoadStarted: {
                loaderContainer.visible = true;
            }

            onLoadedPercent: {
                loadingBar.setValue(percent)
            }

            onLoadDone: {
                loaderContainer.visible = false;
                loadedImage(srtmLoader.resultImage)
            }

            onLoadedImage: {
                loadedPartImage(x, y, image)
            }
        }

        Text {
            id: selectFolderToImport
            height: 28
            color: "#46aae0"
            text: qsTr("Select folder for import SRTM data:")
            anchors.top: parent.top
            anchors.topMargin: 10
            font.bold: true
            verticalAlignment: Text.AlignBottom
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            font.pixelSize: 12
        }

        Button {
            id: openFolderButton
            x: 396
            width: 24
            height: 24
            text: qsTr("")
            anchors.top: selectFolderToImport.bottom
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10

            Rectangle {
                id: openFolderButtonBg
                color: "#46aae0"
                anchors.fill: parent
            }

            Image {
                id: openFolderButtonIcon
                fillMode: Image.PreserveAspectFit
                anchors.rightMargin: 4
                anchors.leftMargin: 4
                anchors.bottomMargin: 4
                anchors.topMargin: 4
                anchors.fill: parent
                source: "../images/folder.png"
            }

            Component.onCompleted: __behavior.cursorShape = Qt.PointingHandCursor

            onClicked: {
                openFolder.visible = true;
            }
        }

        TextField {
            id: loadDataUrlTextField
            x: 11
            y: 46
            height: 24
            anchors.top: selectFolderToImport.bottom
            anchors.topMargin: 10
            anchors.right: openFolderButton.left
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            placeholderText: qsTr("C:\\path\\to\\srtm\\data")
            text:  applicationSettings.lastPath
        }

        Button {
            id: loadDataButton
            x: 414
            y: 85
            width: 100
            height: 24
            text: qsTr("Load")
            anchors.right: parent.right
            anchors.topMargin: 10
            anchors.rightMargin: 10
            anchors.top: loadDataUrlTextField.bottom

            Rectangle {
                id: loadDataButtonBg
                color: "#46aae0"
                radius: 0
                anchors.fill: parent
            }

            Text {
                id: text1
                color: "#ffffff"
                text: qsTr("Load")
                font.bold: false
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
            }

            Component.onCompleted: __behavior.cursorShape = Qt.PointingHandCursor

            onClicked: {
                var result = srtmLoader.loadSRTMData(loadDataUrlTextField.text)
                if(!result) {
                    errorMessageLabel.text = qsTr("Cannot load SRTM data!")
                } else {
                    errorMessageLabel.text = ""
                }
            }
        }

        Text {
            id: errorMessageLabel
            height: 24
            color: "#e07c46"
            text: qsTr("")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            anchors.top: loadDataUrlTextField.bottom
            anchors.topMargin: 10
            anchors.right: loadDataButton.left
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: loaderContainer
        color: "#ffffff"
        visible: false
        border.color: "#46aae0"
        border.width: 2
        anchors.top: bg.top
        anchors.topMargin: 0
        anchors.bottom: bg.bottom
        anchors.bottomMargin: 0
        anchors.left: bg.left
        anchors.leftMargin: 0
        anchors.right: bg.right
        anchors.rightMargin: 0

        ProgressBar {
            id: loadingBar
            y: 125
            height: 23
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
        }

        Text {
            id: loadingBarLabel
            height: 24
            color: "#46aae0"
            text: qsTr("Loading ...")
            anchors.top: loadingBar.bottom
            anchors.topMargin: 2
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            anchors.left: loadingBar.left
            anchors.leftMargin: 0
            anchors.right: loadingBar.right
            anchors.rightMargin: 0
            font.pixelSize: 12
        }
    }


    FileDialog {
        id: openFolder
        selectFolder: true
        title: "Please choose SRTM data folder"
        folder: "file:///" + applicationSettings.lastPath
        onAccepted: {
            loadDataUrlTextField.text = openFolder.folder.toString().replace(/^(file:\/{3})/,"");
            applicationSettings.lastPath = loadDataUrlTextField.text
        }
        onRejected: {

        }
    }

}
