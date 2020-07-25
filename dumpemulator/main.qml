import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Qt.labs.platform 1.1

Window {
    id: root
    visible: true
    width: 960
    height: 640
    property bool isConnectChanged: false
    title: qsTr("数据LOG模拟器")
    Image {
        id: bg
        anchors.fill: parent
        opacity: 0.8
        Component.onCompleted: {
            bg.source = "qrc:/skin/bg.png"
        }
    }
    property int  btnTypeConnect: 0
    property int  btnTypeDisconnect: 1
    property int  btnTypeClear: 2
    property int  btnTypeSave: 3

    TextArea{
        id: textArea
        property string savePath: ""
        width: root.width
        height: root.height * 4/5
        anchors.top: parent.top
        anchors.topMargin: 5
//        wrapMode : TextEdit.WordWrap
        backgroundVisible: false
        tabChangesFocus: true
        readOnly: true
        font.pixelSize:22
        font.family: "微软雅黑"
        style: TextAreaStyle{
            textColor: "black"
            selectionColor: "steelblue"
            selectedTextColor: "#eee"
            frame: Item{}
//            transientScrollBars: true
        }

    }

    Item{
        width: 700
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        Row{
            spacing: 10
            //TextFiled用Loader加载会出现异常，显示不了
            TextField{
                id: ipInput
                anchors.verticalCenter: parent.verticalCenter
                width: 200
                height: 20
                style: TextFieldStyle{
                    background: Rectangle{
                        color: control.hovered?"#87CEEB":"#87CEFA";
                        radius: 10
                    }
                    padding.bottom: 10
                    padding.left: 10
                    padding.top: 10
                    padding.right: 10
                }
                placeholderText: "127.0.0.1"
                anchors.bottom: parent.bottom
            }

            TextField{
                id: portInput
                anchors.verticalCenter: parent.verticalCenter
                style: TextFieldStyle{
                    background: Rectangle{
                        color: control.hovered?"#87CEEB":"#87CEFA";
                        radius: 10
                    }
                    padding.bottom: 10
                    padding.left: 10
                    padding.top: 10
                    padding.right: 10
                }
                width: 100
                height: 20
                placeholderText: "10241"
                anchors.bottom: parent.bottom
            }

            Loader{
                id: btnConnent
                sourceComponent: btnCom
                Component.onCompleted: {
                    btnConnent.item.setBtnType("连接",btnTypeConnect);
                }
            }
            Loader{
                id: btnDisconnent
                sourceComponent: btnCom
                Component.onCompleted: {
                    btnDisconnent.item.setBtnType("断开",btnTypeDisconnect);
                    btnDisconnent.item.setBtnEable(false)
                }
            }
            Loader{
                id: btnClear
                sourceComponent: btnCom
                Component.onCompleted: {
                    btnClear.item.setBtnType("清空",btnTypeClear);
                }
            }
            Loader{
                id: btnSave
                sourceComponent: btnCom
                Component.onCompleted: {
                    btnSave.item.setBtnType("保存",btnTypeSave);
                }
            }
        }
    }

    FileDialog {
        id: fileSave
        fileMode: FileDialog.SaveFile
        title: "Please choose a file"
        nameFilters: [ "Text Files (*.txt)"]
        onAccepted: {
            console.log("You chose: " + fileSave.currentFile)
            fileSave.visible = false
            saveFlie(fileSave.currentFile)

        }


    }

    Component{
        id: btnCom
        Button{
            id: btn
            property int  btnType: -1
            width: 80
            height: 45
            text: "test"
            style:ButtonStyle{
                  background: Rectangle{
                      color: control.hovered?"#87CEEB":"#87CEFA";
                      radius: 10
                  }
                  padding.bottom: 10
                  padding.left: 10
                  padding.top: 10
                  padding.right: 10
            }
            onClicked: {
                doBtnClicked(btnType)
            }

            function setBtnType(text,type){
                btn.btnType = type
                btn.text = text
            }

            function setBtnEable(state){
                btn.enabled = state
            }

        }

    }

    function textAreaAdd(text){
        textArea.append(text)
    }

    Connections{
        target: EmulatorManager
        onSigSendQmlWorld: {
            textAreaAdd(array)
        }

    }

    Connections{
        target: EmulatorManager
        onSigSendConnetState :{
            setConnectState(state);
        }
    }

    function doBtnClicked(btnType){
        console.log("============================" + btnType)
        switch(btnType){
        case btnTypeConnect:
            isConnectChanged = true
            var text1,text2
            if(ipInput.text == "") {
                text1 = "127.0.0.1"
            }
            else{
                text1 = ipInput.text
            }

            if(portInput.text == "") {
                text2 = "10241"
            }
            else{
                text2 = portInput.text
            }
            EmulatorManager.startConnect(text1,text2)
            break;
        case btnTypeDisconnect:
            EmulatorManager.disConnect()
            break;
        case btnTypeClear:
            textArea.text = ""
        break;
        case btnTypeSave:
//            textArea.text = ""
            fileSave.visible = true
        break;
        }
    }

    function saveFlie(path){
        if(textArea.text != ""){
            EmulatorManager.saveFile(textArea.text,path)
        }
        else{

        }
    }

    function setConnectState(state){
        btnConnent.item.setBtnEable(!state)
        btnDisconnent.item.setBtnEable(state)
    }

}
