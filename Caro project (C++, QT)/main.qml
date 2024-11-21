import QtQuick
import QtQuick.Controls


Window {
    id: mainRoot
    width: 640
    height: 480
    visible: true
    title: qsTr("CARO GAME")
    color:"white"

    Rectangle{
        id: rect1
        anchors.centerIn: parent
        width: 400
        height: 400
        border.width: 1
        color:"white"
        Text{
            x: 180
            text: "CARO"
            color: "red"
            font.bold: true

        }
    }


    Rectangle{
        id: guideInfo
        anchors.centerIn: parent
        width: 400
        height: 400
        border.width: 1
        color:"orange"
        Text{
            text: "Luật chơi không chặn 2 đầu"
            //wrapMode: Text.WordWrap
        }
        visible: false

        Rectangle{
            id: menuReturnButton
            x:400; y:400
            height: 40
            width: 130
            color:"orange"
            Text{
                anchors.centerIn: parent
                 text:"Return to menu"
                 color:"black"
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    mainColumn.visible = true
                    guideInfo.visible=false
                }
            }

        }

    }

    Loader{
        id:with_human_file
        source: "with_human.qml"
        anchors.fill: rect1
        anchors.centerIn: rect1
        visible: false // Initially hidden
    }

    Loader{
        id: win_file
        source: "win.qml"
        anchors.fill: rect1
        anchors.centerIn: rect1
        visible: false

    }


    Column{
        id: mainColumn
        anchors.centerIn: parent
        spacing: 5
        Rectangle{
            id:with_human
            width: 200; height:40
            border.width:1
            color:"orange"
            Text{
                text: "Play with other player"
                anchors.centerIn: with_human
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    with_human_file.source = "with_human.qml";

                    mainColumn.visible = false
                    with_human_file.visible = true
                    win_file.visible =false

                    console.log("Caro.showWinScreen: ",Caro.showWinScreen);// oke

                }

            }

        }
        Rectangle{
            id:with_bot
            width: 200; height:40
            border.width:1
            color:"orange"
            Text{
                text: "Play with bot"
                 anchors.centerIn: with_bot
            }

            MouseArea{
                anchors.fill: parent
                onClicked:{
                    with_human_file.source = "with_bot.qml";
                    mainColumn.visible = false
                    with_human_file.visible = true
                    win_file.visible =false

                    console.log("Caro.showWinScreen: ",Caro.showWinScreen);// oke

                }

            }
        }
        Rectangle{
            border.width:1
            color:"orange"
            id:replay
            width: 200; height:40
            Text{
                text: "Replay"
                anchors.centerIn: replay

            }

            MouseArea{
                anchors.fill: parent
                onClicked:{
                    with_human_file.source = "with_human.qml";
                    with_human_file.visible = true
                    win_file.visible =false
                    mainColumn.visible = false
                    Caro.replayLastMatch();

                }

            }



        }
        Rectangle{
            id:players_info
            width: 200; height:40
            border.width:1
            color:"orange"
            Text{
                text: "Player's information"
                anchors.centerIn: players_info
            }

            MouseArea{
                anchors.fill: parent
                onClicked:{

                }

            }
        }
        Rectangle{
            id:guide
            width: 200; height:40
            border.width:1
            color:"orange"
            Text{
                text:"Guide"
                anchors.centerIn: guide

            }

            MouseArea{
                anchors.fill: parent
                onClicked:{
                       with_human_file.source = "guide.qml";
                       mainColumn.visible = false
                       rect1.visible = false
                       guideInfo.visible = true
                }

            }
        }




    }

}
