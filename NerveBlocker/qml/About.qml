import QtQuick 2.3

Rectangle {
    id: topRec
    signal backButtonClicked()
    color: backgroundGrey

    Text {
        id: title
        text: "ABOUT Version 1.3"
        horizontalAlignment: Text.AlignHCenter
        color: "white"
        font.family: ubuntu.name
        font.pixelSize: parent.width/18

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.height/20
    }


    Text{
        id: introText
        text: "This app is the result of a two master student\
        \nprojects at the Norwegian University of Science\
        \nand Technology (NTNU)in collaboration \
        \nwith SINTEF and St. Olav's Hospital. \
        \nIt is provided free of charge\
        \nfor the purpose of education."
        horizontalAlignment: Text.AlignHCenter
        color: "white"
        font.family: ubuntu.name
        font.pixelSize: parent.width/25

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: qtLicense.top
        anchors.bottomMargin: topRec.height/20
    }
    Text{
        id: qtLicense
        text: "This software was developed using Qt\n under the LGPLv3 license"
        horizontalAlignment: Text.AlignHCenter
        color: "white"
        font.family: ubuntu.name
        font.pixelSize: parent.width/25

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: icons.top
        anchors.bottomMargin: topRec.height/20
    }
    Text{
        id: icons
        text: "The instructional video is provided by \
        \nThe New York School of Regional Anesthesia\
        \nwww.nysora.com\
        \n\nThe icons used come from www.icons8.com"
        horizontalAlignment: Text.AlignHCenter
        color: "white"
        font.family: ubuntu.name
        font.pixelSize: parent.width/30

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: parent.width/30

    }
    Text{
        id: github
        text: "The source code can be found at \
        \nwww.github.com/blackCheetah/RegAnesthAppMSc"
        horizontalAlignment: Text.AlignHCenter
        color: "white"
        font.family: ubuntu.name
        font.pixelSize: parent.width/30

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: icons.bottom
        anchors.topMargin: topRec.height/20
    }

    Text{
        id: sincerely
        text: "Sincerely,\
        \n Master students: Solveig Hellan,\
        \nHanna Holler Kamperud and\
        \nMartin S. Tønnessen\
        \nSuperviser: Frank Lindseth\
        \nPhysician: Kaj F. Johansen"
        horizontalAlignment: Text.AlignHCenter
        color: "white"
        font.family: ubuntu.name
        font.pixelSize: parent.width/35

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: github.bottom
        anchors.topMargin: topRec.height/20
    }

    MenuButton {
        id: menuButton
        width:parent.width*11/12
        anchors.horizontalCenter: parent.horizontalCenter

        onMenuClicked: {
            backButtonClicked();;
        }
    }
}

