import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: root
    visible: true
    width: 480
    height: 360

    property string dice_text: "";
    function rollDice(text) {
        if(text == "clear") {
            dice_text = ""
        } else {
            dice_text += "\n\n"
            dice_text += "----------\n"
            dice_text += text+"\n"
            dice_text += Dice.interpret_text(text)
        }
    }

    Rectangle {
        id: wind_background
        anchors.fill: parent
        color: "white"

        Rectangle {
            id: text_background
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                topMargin: 20
                leftMargin: 20
                rightMargin: 20
            }
            z: 1
            height: 45
            radius: 10.0

            color: "#cacdd1"

            TextInput {
                id: user_input
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                    topMargin: 5
                }

                verticalAlignment: TextInput.AlignVCenter
                horizontalAlignment: TextInput.AlignHCenter
                color: "black"
                property string example_text: "#d#+|-#r# or clear (to reset results)"
                //font.bold: true
                font.family: "Dyuthi"
                font.pixelSize: 25
                validator: RegExpValidator { regExp: /(clear)|([0-9]*d([2468]|10|12|20|100)((\+[0-9]+)|(\-[0-9]+))?(r[0-9]+)?)/ }

                onActiveFocusChanged: {
                    if(activeFocus == true) {
                        clear();
                    } else {
                        text = example_text;
                    }
                }

                Component.onCompleted: {
                    text = example_text;
                }

                onAccepted: {
                    root.rollDice(text)
                }
            }
        }

        Flickable {
            id: dice_results_container
            anchors {
                top: text_background.bottom
                left: parent.left
                right: parent.horizontalCenter
                bottom: parent.bottom
                topMargin: 10
                leftMargin: 20
                bottomMargin: 20
            }
            clip: true
            flickableDirection: Flickable.VerticalFlick
            height: dice_results.height
            contentWidth: dice_results.width
            contentHeight: dice_results.height

            Text {
                id: dice_results
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                text: root.dice_text
                font.family: "Dyuthi"
                font.pixelSize: 25
            }

            onContentHeightChanged: {
                contentY = contentHeight - height;
            }
        }

        Image {
            id: dice_image
            anchors {
                bottom: parent.bottom
                right: parent.right
            }
            width: 260

            fillMode: Image.PreserveAspectFit
            source: "img/d20_3.png"
        }
    }
}
