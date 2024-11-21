import QtQuick



Rectangle{
        id: winStateRoot
        anchors.centerIn: parent
        width: 400
        height: 400
        border.width: 1
        color:"grey"
        Text{
            x: 180
            text: "CARO"
            color: "red"
            font.bold: true

        }

    Rectangle{
        border.width: 1
        anchors.centerIn: parent
        width: 350; height: 350
        id: winState
        color:"white"

        Text{
            id: winPlayerText
            anchors.centerIn: winState
            text: "Player " + Caro.showWinScreen + " win"
            font.pixelSize: 40
            font.bold: true
            color:"green"
        }

        Row{
            spacing: 40
            width: 150; height: 100
            x: 25; y: 220
            Rectangle{
                width: 130
                height: 50
                id: replayButton
                color: "blue"
                border.width:1
                Text{
                    anchors.centerIn: replayButton
                    text: "Replay"
                    color:"white"
                    font.pixelSize: 25
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        with_human_file.source = "with_human.qml";
                        with_human_file.visible = true
                        win_file.visible =false
                        Caro.replayLastMatch();

                    }
                }

            }

            Rectangle{
                width: 130
                height: 50
                id: quitButton
                color: "blue"
                border.width:1

                Text{
                    anchors.centerIn: quitButton
                    text: "Quit match"
                    color:"white"
                    font.pixelSize: 25

                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        //with_human_file.source = "main.qml"
                        mainColumn.visible = true
                        with_human_file.visible = false
                        console.log("click button!")
                    }


                }

            }
        }
    }

}
