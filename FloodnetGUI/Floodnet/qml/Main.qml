import Felgo
import QtQuick
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs



App {
    id: app
    property double tabWidth:0.7
    property double consoleWidth : 0.3
    property double consoleOutputHeight: 0.7
    property double consoleInputHeight : 0.3
    property int verticalLineThickness: 2
    property int engineeringDataSetHeight: 90
    property int buttonRadius:5
    property int buttonTextSize: 16

    property string cliCommands: ""


    width: 1200
    height: 800

    minimumWidth: 1200
    minimumHeight: 800

    NavigationStack {
        id: mainApp

        AppPage {
            title: "FLOODNET - ENGINEERING GUI"

            Connections{
                target:backend
                onUartnotice:{
                    consoleTab.printToOutput(data)
                }
            }

            RowLayout{
                id: comPortControl
                AppText {
                    text: "COM Ports"
                    font.bold: true
                    leftPadding: 5
                }
                ComboBox {
                    id: comboBox_COM_Ports
                    model:backend.comboList
                }

                AppButton
                {
                    id:comPortConnectButton
                    text: "Connect"
                    radius: buttonRadius
                    textSize: buttonTextSize
                    iconRight: IconType.chain
                    onClicked: {
                        backend.openSerialPort(comboBox_COM_Ports.currentText.toString());
                        comPortConnectButton.enabled = false;
                        comPortDisconnectButton.enabled = true;
                        consoleTab.printToOutput("COM Connected: " + comboBox_COM_Ports.currentText.toString() + "\n");
                    }
                }
                AppButton
                {
                    id:comPortDisconnectButton
                    text: "Disconnect"
                    radius: buttonRadius
                    textSize: buttonTextSize
                    iconRight: IconType.chainbroken
                    onClicked:{
                        backend.closeSerialPort();
                        comPortConnectButton.enabled = true;
                        comPortDisconnectButton.enabled = false;
                        consoleTab.printToOutput("COM Disconnected: " + comboBox_COM_Ports.currentText.toString() + "\n");
                    }
                }
                AppButton
                {
                    text: "Scan Ports"
                    radius: buttonRadius
                    textSize: buttonTextSize
                    iconRight: IconType.chainbroken
                }

                AppButton
                {
                    text: "Firmware Update"
                    radius: buttonRadius
                    textSize: buttonTextSize
                    iconRight: IconType.download
                    onClicked: firmwareUpdateDialog.open()
                }

                FileDialog {
                    id: firmwareUpdateDialog;
                    title: "Select firmware file";
                    nameFilters: ["Firmware files (*.hex)"]
                    onAccepted: {
                        var output = backend.processCommand(firmwareUpdateDialog.selectedFile)
                        console.log(output);
                        consoleTab.printToOutput(output)
                    }
                    onRejected: { console.log("Rejected") }
                }
            }


            Rectangle{
                id: dividingLine
                height: 5
                width: parent.width
                color: "lightgrey"

                anchors{
                    top: comPortControl.bottom
                    topMargin: -2
                }

            }

            SplitView
            {
                anchors.fill: parent
                anchors{
                    top: comPortControl.bottom
                    topMargin: 60
                }


                Rectangle{
                    SplitView.minimumWidth: parent.width * 0.6
                    SplitView.preferredWidth: parent.width * 0.6
                    SplitView.maximumWidth: parent.width * 0.7
                    color: "blue"
                    DeviceControl{}
                }


                Rectangle{
                    SplitView.minimumWidth: parent.width * 0.3
                    SplitView.maximumWidth: parent.width * 0.4
                    color: "red"
                    ConsoleTab{
                        id: consoleTab
                    }
                }
            }

        }
    }
}
