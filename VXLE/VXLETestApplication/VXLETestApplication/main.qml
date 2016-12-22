import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import QtQuick.Window 2.0

import com.vxle.testapplication 1.0

import "qml_components"

ApplicationWindow {
    id: mainWindow
    objectName: "mainWindow"
    visible: false
    width: 1024
    height: 768
    color: "#00000000"
    minimumWidth: -1
    title: qsTr("VXLE Test application")
    flags: Qt.FramelessWindowHint /* | Qt.WindowActive | Qt.WindowStaysOnTopHint */

    property var isMaximized: true

    signal resized();

    ApplicationSettings {
        id: appSettings
        settingsFile: "settings.ini"
    }

    Component.onCompleted: {
        if(mainWindow.isMaximized) {
            content.anchors.rightMargin = 0
            content.anchors.leftMargin = 0
            content.anchors.bottomMargin = 0
            content.anchors.topMargin = 0

            mainWindow.showMaximized()
            mainWindow.isMaximized = true
        } else {
            content.anchors.rightMargin = 10
            content.anchors.leftMargin = 10
            content.anchors.bottomMargin = 10
            content.anchors.topMargin = 10

            mainWindow.showNormal()
            mainWindow.isMaximized = false
        }

        resized()
        mainWindow.visible = true
        console.log(applicationPath)
    }

    Item {
        id: content
        anchors.rightMargin: 9
        anchors.leftMargin: 11
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.fill: parent

        Rectangle {
            id: windowMenu
            height: 60
            color: "#3E4F63"
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top

            MouseArea {
                id: doubleClicker
                enabled: true
                anchors.fill: parent


                onDoubleClicked: {
                    if(!mainWindow.isMaximized) {
                        content.anchors.rightMargin = 0
                        content.anchors.leftMargin = 0
                        content.anchors.bottomMargin = 0
                        content.anchors.topMargin = 0

                        mainWindow.showMaximized()
                        mainWindow.isMaximized = true
                    } else {
                        content.anchors.rightMargin = 10
                        content.anchors.leftMargin = 10
                        content.anchors.bottomMargin = 10
                        content.anchors.topMargin = 10

                        mainWindow.showNormal()
                        mainWindow.isMaximized = false
                    }
                }


                property variant previousPosition
                height: 20
                onPressed: {
                    if(!mainWindow.isMaximized) previousPosition = Qt.point(mouseX, mouseY)
                }
                onPositionChanged: {
                    if (pressedButtons == Qt.LeftButton && !mainWindow.isMaximized) {

                        cursorShape = Qt.SizeAllCursor

                        var dx = mouseX - previousPosition.x
                        var dy = mouseY - previousPosition.y

                        mainWindow.setX(mainWindow.x + dx)
                        mainWindow.setY(mainWindow.y + dy)
                    }
                }
                onReleased: {
                    cursorShape = Qt.ArrowCursor
                }

            }

            Button {
                id: close
                x: 697
                y: 0
                width: 18
                height: 18
                text: qsTr("")
                anchors.verticalCenter: parent.verticalCenter
                z: 2
                anchors.right: parent.right
                anchors.rightMargin: 7

                Image {
                    id: closeIcon
                    width: 18
                    height: 18
                    anchors.fill: parent
                    source: "images/close.png"

                }

                style: ButtonStyle {
                    background: Rectangle {
                        color: "transparent"
                    }
                }

                Component.onCompleted: __behavior.cursorShape = Qt.PointingHandCursor
                onClicked: Qt.quit()
            }

            Button {
                id: maximize
                x: 697
                y: 1
                width: close.width
                height: close.height
                text: qsTr("")
                anchors.right: close.left
                anchors.rightMargin: 15
                style: ButtonStyle {
                    background: Rectangle {
                        color: "#00000000"
                    }
                }
                anchors.verticalCenter: parent.verticalCenter
                Image {
                    id: maximizeIcon
                    width: 18
                    height: 18
                    anchors.fill: parent
                    source: "images/maximize.png"
                }
                z: 2

                Component.onCompleted: __behavior.cursorShape = Qt.PointingHandCursor
                onClicked: {
                    if(!mainWindow.isMaximized) {
                        content.anchors.rightMargin = 0
                        content.anchors.leftMargin = 0
                        content.anchors.bottomMargin = 0
                        content.anchors.topMargin = 0

                        mainWindow.showMaximized()
                        mainWindow.isMaximized = true
                    } else {
                        content.anchors.rightMargin = 10
                        content.anchors.leftMargin = 10
                        content.anchors.bottomMargin = 10
                        content.anchors.topMargin = 10

                        mainWindow.showNormal()
                        mainWindow.isMaximized = false
                    }

                    resized()
                }
            }

            Button {
                id: minimize
                x: 696
                y: -8
                width: close.width
                height: close.height
                text: qsTr("")
                style: ButtonStyle {
                    background: Rectangle {
                        color: "#00000000"
                    }
                }
                anchors.verticalCenter: parent.verticalCenter
                Image {
                    id: minimizeIcon
                    width: 18
                    height: 18
                    anchors.fill: parent
                    source: "images/minimize.png"
                }
                anchors.right: maximize.left
                anchors.rightMargin: 15
                z: 2


                Component.onCompleted: __behavior.cursorShape = Qt.PointingHandCursor
                onClicked: mainWindow.showMinimized()
            }

            MenuController {
                id: menu
            }

            Button {
                id: openFolder
                width: height
                height: parent.height - 5
                text: qsTr("Button")
                anchors.verticalCenterOffset: 5
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter

                Rectangle {
                    id: openFolderBackground
                    anchors.fill: parent
                    color: "#3e4f63"
                }

                Image {
                    id: openFolderIcon
                    x: 6
                    y: 6
                    width: 36
                    height: 36
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    source: "images/folder.png"
                }

                Component.onCompleted: __behavior.cursorShape = Qt.PointingHandCursor

                MenuItem {
                    id: openFolderMenuItem
                    button: openFolder
                    background: openFolderBackground
                    icon: openFolderIcon
                    selected: false
                    enabled: true

                    Component.onCompleted: {
                        menu.registerMenuItem(openFolderMenuItem)
                        enable()
                        menu.itemSelected(openFolderMenuItem)
                    }

                    onEnabled: {
                        openFolderIcon.opacity = 1
                    }

                    onDisabled: {
                        openFolderIcon.opacity = 0.25
                    }

                    onSelected: {
                        openFolderBackground.color = "#46aae0"
                        openFolderContent.visible = true;
                    }

                    onDeselected: {
                        openFolderBackground.color = "#3e4f63"
                        openFolderContent.visible = false;
                    }
                }

                onClicked: function(){
                    menu.itemSelected(openFolderMenuItem)
                }

            }

            Button {
                id: resultMap
                width: height
                height: parent.height - 5
                text: qsTr("Button")
                anchors.verticalCenterOffset: 5
                anchors.left: openFolder.right
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter

                Rectangle {
                    id: resultMapBackground
                    color: "#3e4f63"
                    anchors.fill: parent
                }

                Image {
                    id: resultMapIcon
                    x: 6
                    y: 6
                    width: 36
                    height: 36
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    source: "images/orientation.png"
                }

                Component.onCompleted: __behavior.cursorShape = Qt.PointingHandCursor

                MenuItem {
                    id: resultMapMenuItem
                    button: resultMap
                    background: resultMapBackground
                    icon: resultMapIcon
                    selected: false
                    enabled: true

                    Component.onCompleted: {
                        menu.registerMenuItem(resultMapMenuItem)
                        disable()
                    }

                    onEnabled: {
                        resultMapIcon.opacity = 1
                    }

                    onDisabled: {
                        resultMapIcon.opacity = 0.25
                    }

                    onSelected: {
                        resultMapBackground.color = "#46aae0"
                        resultMapContent.visible = true;
                       // resultMapContent.setMap(resultMapContent.lastWidth, resultMapContent.lastHeight, resultMapContent.lastSource)

                    }

                    onDeselected: {
                        resultMapBackground.color = "#3e4f63"
                        resultMapContent.visible = false;
                    }
                }

                onClicked: function(){
                    menu.itemSelected(resultMapMenuItem)
                }

            }

            Button {
                id: engine
                width: height
                height: parent.height - 5
                text: qsTr("Button")
                anchors.verticalCenterOffset: 5
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: resultMap.right
                anchors.leftMargin: 20

                Rectangle {
                    id: engineBackground
                    color: "#3e4f63"
                    anchors.fill: parent
                }

                Image {
                    id: engineIcon
                    x: 6
                    y: 6
                    width: 36
                    height: 36
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    source: "images/shape.png"
                }

                MenuItem {
                    id: engineMenuItem
                    button: engine
                    background: engineBackground
                    icon: engineIcon
                    selected: false
                    enabled: true

                    Component.onCompleted: {
                        menu.registerMenuItem(engineMenuItem)
                        disable()
                    }

                    onEnabled: function() {
                        engineIcon.opacity = 1
                    }

                    onDisabled: function() {
                        engineIcon.opacity = 0.25
                    }

                    onSelected: {
                        engineBackground.color = "#46aae0"

                    }

                    onDeselected: {
                        engineBackground.color = "#3e4f63"
                    }


                }

                onClicked: function(){
                    menu.itemSelected(engineMenuItem)
                }

                Component.onCompleted: __behavior.cursorShape = Qt.PointingHandCursor
            }
        }

        Rectangle {
            id: contentBackground
            color: "#EFF3F6"
            border.color: "#e2e2e2"
            anchors.fill: parent
            z: -1
        }

        Rectangle {
            id: windowMenuSeparator
            height: 5
            color: "#46AAE0"

            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: windowMenu.bottom
            anchors.topMargin: 0
        }

        EngineContent {
            anchors.top: windowMenuSeparator.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.topMargin: 0
        }

        OpenFolderContent {

            id:openFolderContent

            applicationSettings: appSettings

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: windowMenuSeparator.bottom
            anchors.topMargin: 0

            onLoadedImage: {
                resultMapMenuItem.enable()
                resultMapContent.setMap(sourceWidth, sourceHeight, source)
            }
        }

        ResultMapContent {
            id: resultMapContent

            visible: false

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: windowMenuSeparator.bottom
            anchors.topMargin: 0
        }
    }

    DropShadow {
        id: shadowEf
        anchors.fill: content
        source: content
        horizontalOffset: 1
        verticalOffset: 1
        radius: 4
        anchors.rightMargin: -1
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        z: -1
        samples: 8
        color: "#353C46"
        transparentBorder: true
    }

}


