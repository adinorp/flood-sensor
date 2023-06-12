import QtQuick
import Felgo
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

NavigationStack{
    id: consoleControl

    function printToOutput(txt) {
        console.log(txt)
        consoleReceive.append(txt)
    }

    function printToInput(txt) {
        console.log(txt)
        consoleTransmit.text = txt
    }

    function clearConsoleInput()
    {
        consoleTransmit.clear()
    }


    AppPage {
        navigationBarTranslucency: 1
        backgroundColor: "white"

        Item{
            id: consoleItem
            anchors.fill:parent
            anchors.leftMargin: 5

            ColumnLayout{
                width: parent.width
                height: parent.height

                AppText {
                    text: "Console Receive"
                    height: 20
                    font.bold: true
                    fontSize: 14
                }

                //Console Output
                Rectangle {
                    color: "lightgrey"
                    Layout.preferredWidth: consoleItem.width-5
                    Layout.fillHeight: true
                    border.color: "black"
                    border.width: 1

                    // Flickable for scrolling, with text field inside
                    AppFlickable {
                        id: flick
                        anchors.fill: parent
                        contentWidth: width
                        contentHeight: consoleReceive.height
                        desktopScrollEnabled: true


                        AppTextEdit{
                            id: consoleReceive
                            anchors{
                                fill: parent
                                margins: 5
                            }

                            // This enables the text field to automatically scroll if cursor moves outside while typing
                            cursorInView: true
                            cursorInViewBottomPadding: dp(25)
                            cursorInViewTopPadding: dp(25)
                            flickable: flick
                            fontSize: 12
                            text:"Console Output"
                            wrapMode: TextEdit.WordWrap
                        }

                        AppScrollIndicator {
                            flickable: flick
                        }
                    }
                }

                Row
                {
                    AppButton{
                        id: btnConsoleTrash
                        text:"Clear Console Receive"
                        iconRight: IconType.trash
                        onClicked: {
                            consoleReceive.clear();
                        }
                    }
                }

                AppText{
                    text: "Console Transmit"
                    height: 20
                    font.bold: true
                    fontSize: 14
                }

                Rectangle {
                    color: "lightgrey"
                    border.color: "black"
                    Layout.preferredWidth: consoleItem.width-5
                    height: 80
                    border.width: 1
                    AppFlickable {
                        id: flickInput
                        anchors.fill: parent
                        contentWidth: width
                        contentHeight: consoleTransmit.height
                        desktopScrollEnabled: true

                        AppTextEdit{
                            id: consoleTransmit
                            anchors{
                                fill: parent
                                margins: 5
                            }
                            // This enables the text field to automatically scroll if cursor moves outside while typing
                            cursorInView: true
                            cursorInViewBottomPadding: dp(25)
                            cursorInViewTopPadding: dp(25)
                            flickable: flick
                            fontSize: 12
                            wrapMode: TextEdit.WordWrap
                        }

                        AppScrollIndicator {
                            flickable: flickInput
                        }
                    }
                }

                AppButton{
                    id: btnConsoleTransmitTrash
                    text:"Clear Console Transmit"
                    iconRight: IconType.trash
                    onClicked: {
                        consoleTransmit.clear();
                        cliCommands = "";
                    }
                }
            }
        }

    }
}
