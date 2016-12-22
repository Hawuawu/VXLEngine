import QtQuick 2.0

import com.vxle.testapplication 1.0

Rectangle {
    color: "#e1e1e1"

    function setMap(w, h, image) {
        console.log("Setting image", w, h);

       // resultMap.width = w
       // resultMap.height = h
       // resultMap.sourceSize.width = w
      //  resultMap.sourceSize.height = h
        flickable.contentWidth = w
        flickable.contentHeight = h

      //  lastSource = image

      //  resultMap.source = ""
      //  resultMap.source = applicationPath + "temp.png"
        srtmMap.width = w
        srtmMap.height = h
        srtmMap.loadImage(image)
    }

    Flickable {
        id: flickable
        clip: true
        anchors.fill: parent
/*
        Image {
            id: resultMap
            cache: false
            fillMode: Image.PreserveAspectFit
            scale: 1
        }*/

        SRTMMap {
            id: srtmMap
        }
    }

}
