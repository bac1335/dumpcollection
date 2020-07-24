import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Window {
    id: root
    visible: true
    width: 960
    height: 640
    title: qsTr("数据LOG模拟器")
    color: "#242424"
    property int  btnTypeConnect: 0
    property int  btnTypeDisconnect: 0
    signal sigBtnClicked(int type)


    ScrollView{
        id: textBody
        width:  root.width
        height: root.height

        TextArea{
            id: textArea
            width: root.width
            height: root.height * 3/4
            wrapMode : TextEdit.WrapAnywhere
            font.pixelSize:20
            style: TextAreaStyle{
                textColor: "white"
                selectionColor: "steelblue"
                selectedTextColor: "#eee"
                backgroundColor: root.color
            }
        }

        Rectangle{

            anchors.fill: parent
        }
    }

    Item{
        width: 260
        height: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        Row{
            spacing: 100
            Loader{
                sourceComponent: btnCom
            }
            Loader{
                sourceComponent: btnCom
            }
        }
    }


    Component{
        id: btnCom
        Button{
            id: btn
            property int  btnType: -1
            width: 80
            height: 60
            text: "test"
            onClicked: {
                sigBtnClickedd(btnType)
            }

            function setBtnType(text,type){
                btn.btnType = type
                btn.text = text
            }

        }
    }


    function textAreaAdd(text){
        var str = text + "\n"
        textArea.insert(0,str)
    }

    Connections{
        target: EmulatorManager
        onSigSendQmlWorld: {
            textAreaAdd(array)
        }

    }

}
