import QtQuick
import QtQuick.Controls
// Window {
//     width: 640
//     height: 480
//     visible: true
//     title: qsTr("Hello World")



Rectangle{
    id: rect
    width: 100; height: 100
    color: "blue"
    border.width: 1


    GridView{
        id: gridView
        anchors.fill: rect
        anchors.centerIn: rect
        cellWidth: 40
        cellHeight: 40


        model: Caro.matrix


        delegate:
            Rectangle{

                width: 40
                height: 40
                border.width:1
                color: "orange"
                property int row_ : (index -index%10)/10;
                property int column_ : index%10;
                Text{
                    id:cellText
                    text: (modelData ===0)? " ":(modelData===1)?"x":"o"
                    anchors.centerIn: parent
                    font.pixelSize: 20

                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        var index1 = (index -index%10)/10;
                        var index2 =  index%10;
                        console.log(index1,index2)
                         console.log("showWinScreen in QML", Caro.showWinScreen) //oke
                        if (cellText.text ===" " &&Caro.showWinScreen === 0){
                                //console.log(Caro);
                                Caro.move(index);
                               // Caro.playWithBot(index);
                            //win_file.visible =true;/// Các dòng lệnh này thực hiện rất nhanh và conflict trên cùng giao diện

                        } else if (Caro.showWinScreen ===1){ // phải click lần nữa
                               // win_file.visible =true;
                                with_human_file.source = "win.qml"

                        } else if (Caro.showWinScreen ===2){ // phải click lần nữa
                            // win_file.visible =true;
                             with_human_file.source = "win.qml"

                     }

                    }
                }
            }
    }


}

/*
    How it will send to C++ when click to item?

    How to access array in QML?
    index = index1*10+index2
*
/
   with_human_file.rect1.winPlayerText.text = "player 2 win" // why can not access




