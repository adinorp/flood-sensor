import QtQuick
import Felgo
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

NavigationStack{
    id: deviceControlPage
    anchors.fill:parent
    width: parent.width
    property int textSize: 16
    property bool periodicSend: false
    property int delayInterval: 100
    property variant stringlist
    property int count: 0
    property int gpioSwitchWidth: 170
    property int gpioSwitchHeight: 30


    AppPage {
        navigationBarTranslucency: 1
        backgroundColor: "blue"
        anchors.fill: parent


        Rectangle {
            anchors.fill: parent
            TabControl {
                id: engineeringTabControl
                currentIndex:0
                NavigationItem{
                    title: "Device"
                    iconType: IconType.info
                    ColumnLayout{
                        width: engineeringTabControl.width
                        AppText {
                            text: "ST"
                            font.bold: true
                            leftPadding: 5
                            fontSize: 14
                        }

                        Row{
                            Button_A{
                                text: "STDEVICEID"
                                onClicked:backend.writeData("STDEVICEID" + "\r");
                            }
                        }

                        Rectangle{
                            width: engineeringTabControl.width
                            height: 3
                            color: "darkgrey"
                        }

                        AppText {
                            text: "RTC"
                            font.bold: true
                            leftPadding: 5
                            fontSize: 14
                        }


                        Row{
                            Button_A {
                                text: qsTr("Get Date")
                                onClicked:backend.writeData("GETDATE" + "\r");
                            }

                            Button_A{
                                text: "Get Time"
                                onClicked:backend.writeData("GETTIME" + "\r");
                            }

                        }
                        Row
                        {
                            leftPadding: 10

                            AppText {
                                text: pickerModal.pickerDate.toLocaleString()
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            Button_A {
                                text: qsTr("Pick Date and Time")
                                onClicked: pickerModal.open()
                            }

                            Button_A{
                                text: "Set RTC"
                                onClicked:backend.writeData("" + "\r");
                            }

                            AppModal {
                                id: pickerModal
                                fullscreen: false
                                modalHeight: doneButton.height + datePicker.height + NativeUtils.safeAreaInsets.bottom
                                property date pickerDate: new Date()

                                // reset the picker when the modal is closed
                                onClosed: datePicker.setDate(pickerModal.pickerDate)

                                AppButton {
                                    text: qsTr("Cancel")
                                    anchors.left: parent.left
                                    flat: true
                                    fontBold: false
                                    onClicked: pickerModal.close()
                                }

                                AppButton {
                                    id: doneButton
                                    text: qsTr("Done")
                                    anchors.right: parent.right
                                    flat: true
                                    fontBold: true
                                    onClicked: {
                                        pickerModal.pickerDate = datePicker.selectedDate
                                        console.log(datePicker.selectedDate.toLocaleString())
                                        pickerModal.close()
                                    }
                                }

                                DatePicker {
                                    id: datePicker
                                    datePickerMode: dateTimeMode
                                    useCombinedDate: false
                                    use24HourFormat: false
                                    anchors.top: doneButton.bottom
                                    selectedDate: pickerModal.pickerDate
                                }
                            }
                        }

                        Item
                        {
                            Layout.fillHeight: true
                        }


                    }

                }


                NavigationItem {

                    title: "Engineering"
                    iconType: IconType.gears


                    ColumnLayout{
                        width: engineeringTabControl.width

                        AppText {
                            text: "ADC Read"
                            font.bold: true
                            leftPadding: 5
                            fontSize: 14
                        }
                        Row{
                            Button_A{
                                text: "BATTREAD"//"ADC_IN"
                                onClicked:backend.writeData("BATTREAD" + "\r");
                            }
                            Button_A{
                                text: "ADC_SW"
                                onClicked:backend.writeData("" + "\r");
                            }
                        }

                        Rectangle{
                            width: engineeringTabControl.width
                            height: 3
                            color: "darkgrey"
                        }

                        AppText {
                            text: "Ultrasonic Sensor"
                            font.bold: true
                            leftPadding: 5
                            fontSize: 14
                        }

                        Row{

                            Button_A{
                                text: "Read"
                                onClicked:backend.writeData("QCELLIDGET" + "\r");
                            }
                        }

                        Rectangle{
                            width: engineeringTabControl.width
                            height: 3
                            color: "darkgrey"
                        }

                        AppText {
                            text: "GPIO Controls"
                            font.bold: true
                            leftPadding: 5
                            fontSize: 14
                        }

                        Row{
                            width: parent.width
                            leftPadding: 10

                            ColumnLayout{
                                spacing: 10

                                Item{
                                    width: gpioSwitchWidth + 40
                                    height: gpioSwitchHeight

                                    AppSwitch {
                                        id: switchGpioMbOC
                                        anchors.verticalCenter: parent.verticalCenter
                                        onToggled: {
                                            if (switchGpioMbOC.checked)
                                            {
                                                //set the gpio high
                                                console.log("MB OC High")
                                            }
                                            else
                                            {
                                                //set the gpio low
                                                console.log("MB OC Low")
                                            }
                                        }
                                    }

                                    AppText {
                                        anchors{
                                            verticalCenter: parent.verticalCenter
                                            left: parent.left
                                            leftMargin: 65
                                        }
                                        text: switchGpioMbOC.checked ? "MB OC HIGH" : "MB OC LOW"
                                    }
                                }

                                Item{
                                    width: gpioSwitchWidth + 40
                                    height: gpioSwitchHeight

                                    AppSwitch {
                                        id: switchGpioMbCtl
                                        anchors.verticalCenter: parent.verticalCenter
                                        onToggled: {
                                            if (switchGpioMbCtl.checked)
                                            {
                                                //set the gpio high
                                                console.log("MB CTL High")
                                            }
                                            else
                                            {
                                                //set the gpio low
                                                console.log("MB CTL Low")
                                            }
                                        }
                                    }

                                    AppText {
                                        anchors{
                                            verticalCenter: parent.verticalCenter
                                            left: parent.left
                                            leftMargin: 65
                                        }
                                        text: switchGpioMbCtl.checked ? "MB CTL HIGH" : "MB CTL LOW"
                                    }
                                }

                                Item{
                                    width: gpioSwitchWidth + 40
                                    height: gpioSwitchHeight
                                    AppSwitch {
                                        id: switchGpioRx
                                        anchors.verticalCenter: parent.verticalCenter
                                        onToggled: {
                                            if (switchGpioRx.checked)
                                            {
                                                //set the gpio high
                                                console.log("MB RX High")
                                            }
                                            else
                                            {
                                                //set the gpio low
                                                console.log("MB RX Low")
                                            }
                                        }
                                    }

                                    AppText {
                                        anchors{
                                            verticalCenter: parent.verticalCenter
                                            left: parent.left
                                            leftMargin: 65
                                        }
                                        text: switchGpioRx.checked ? "MB RX HIGH" : "MB RX LOW"
                                    }
                                }

                                Item{
                                    width: gpioSwitchWidth + 40
                                    height: gpioSwitchHeight
                                    AppSwitch {
                                        id: switchGpioMbPwr
                                        anchors.verticalCenter: parent.verticalCenter
                                        onToggled: {
                                            if (switchGpioMbPwr.checked)
                                            {
                                                //set the gpio high
                                                console.log("MB PWR High")
                                            }
                                            else
                                            {
                                                //set the gpio low
                                                console.log("MB PWR Low")
                                            }
                                        }
                                    }

                                    AppText {
                                        anchors{
                                            verticalCenter: parent.verticalCenter
                                            left: parent.left
                                            leftMargin: 65
                                        }
                                        text: switchGpioMbPwr.checked ? "MB PWR HIGH" : "MB PWR LOW"
                                    }
                                }
                            }

                            ColumnLayout{
                                spacing: 10
                                Item{
                                    width: gpioSwitchWidth
                                    height: gpioSwitchHeight
                                    AppSwitch {
                                        id: switchGpioPg
                                        anchors.verticalCenter: parent.verticalCenter
                                        onToggled: {
                                            if (switchGpioPg.checked)
                                            {
                                                //set the gpio high
                                                console.log("PG High")
                                            }
                                            else
                                            {
                                                //set the gpio low
                                                console.log("PG Low")
                                            }
                                        }
                                    }

                                    AppText {
                                        anchors{
                                            verticalCenter: parent.verticalCenter
                                            left: parent.left
                                            leftMargin: 65
                                        }

                                        text: switchGpioPg.checked ? "PG HIGH" : "PG LOW"
                                    }
                                }

                                Item{
                                    width: gpioSwitchWidth
                                    height: gpioSwitchHeight
                                    AppSwitch {
                                        id: switchGpioLed
                                        anchors.verticalCenter: parent.verticalCenter
                                        onToggled: {
                                            if (switchGpioLed.checked)
                                            {
                                                //set the gpio high
                                                console.log("LED High")
                                            }
                                            else
                                            {
                                                //set the gpio low
                                                console.log("LED Low")
                                            }
                                        }
                                    }

                                    AppText {
                                        anchors{
                                            verticalCenter: parent.verticalCenter
                                            left: parent.left
                                            leftMargin: 65
                                        }
                                        text: switchGpioLed.checked ? "LED HIGH" : "LED LOW"
                                    }
                                }

                            }


                            ColumnLayout{
                                spacing: 10
                                Item{
                                    width: gpioSwitchWidth
                                    height: gpioSwitchHeight
                                    AppSwitch {
                                        id: switchGpioExtPwr
                                        anchors.verticalCenter: parent.verticalCenter
                                        onToggled: {
                                            if (switchGpioExtPwr.checked)
                                            {
                                                //set the gpio high
                                                console.log("EXT PWR High")
                                            }
                                            else
                                            {
                                                //set the gpio low
                                                console.log("EXT PWR Low")
                                            }
                                        }
                                    }

                                    AppText {
                                        anchors{
                                            verticalCenter: parent.verticalCenter
                                            left: parent.left
                                            leftMargin: 65
                                        }
                                        text: switchGpioExtPwr.checked ? "EXT PWR HIGH" : "EXT PWR LOW"
                                    }
                                }

                                Item{
                                    width: gpioSwitchWidth
                                    height: gpioSwitchHeight
                                    AppSwitch {
                                        id: switchGpioExtOc
                                        anchors.verticalCenter: parent.verticalCenter
                                        onToggled: {
                                            if (switchGpioExtOc.checked)
                                            {
                                                //set the gpio high
                                                console.log("EXT OC High")
                                            }
                                            else
                                            {
                                                //set the gpio low
                                                console.log("EXT OC Low")
                                            }
                                        }
                                    }

                                    AppText {
                                        anchors{
                                            verticalCenter: parent.verticalCenter
                                            left: parent.left
                                            leftMargin: 65
                                        }
                                        text: switchGpioExtOc.checked ? "EXT OC HIGH" : "EXT OC LOW"
                                    }
                                }
                            }

                        }

                        Rectangle{
                            width: engineeringTabControl.width
                            height: 3
                            color: "darkgrey"
                        }


                        AppText {
                            text: "BME280"
                            font.bold: true
                            leftPadding: 5
                            fontSize: 14

                        }

                        Row
                        {
                            Button_A{
                                text: "Read"
                                onClicked:backend.writeData("" + "\r");
                            }
                        }


                        Item{
                            Layout.fillHeight: true
                        }

                    }


                }


                NavigationItem {
                    title: "LoRa"
                    iconType: IconType.gears

                    Item
                    {
                        ColumnLayout{
                            AppText {
                                id: labelQueries
                                text: "Queries"
                                font.bold: true
                                leftPadding: 5
                                fontSize: 14
                            }

                            ColumnLayout{
                                height: parent.height
                                width: parent.width
                                Layout.fillHeight: false

                                RowLayout{
                                    AppButton{
                                        id: btnConsoleSend
                                        text:"Send Once"
                                        iconRight: IconType.send
                                        onClicked: {
                                            console.log("Send once")
                                            var newCliCommands = cliCommands.replace(/\s/g,"")
                                            var stringList = newCliCommands.split(",")

                                            for(count = 0; count < stringList.length-1; count++)
                                            {
                                                backend.writeData(stringList[count] + "\r");
                                                console.log(stringList[count] + "\r")
                                            }
                                        }
                                    }

                                    Rectangle{
                                        height: parent.height
                                        width: 2
                                        color: "darkgrey"
                                    }
                                }



                                RowLayout
                                {
                                    AppText {
                                        text: "Send"
                                        font.bold: true
                                        font.pointSize: sp(textSize)
                                        leftPadding: 5
                                        topPadding: 10
                                        fontSize: 14
                                    }

                                    SpinBox{
                                        id: repeatFor
                                        value: 1
                                        from: 1
                                        to: 100
                                        editable: true
                                    }
                                    AppText {
                                        text: "Times"
                                        font.bold: true
                                        font.pointSize: sp(textSize)
                                        leftPadding: 5
                                        topPadding: 10
                                        fontSize: 14

                                    }

                                    AppButton{
                                        id: btnConsoleSendForRepetitions
                                        text:"Repeat Send"
                                        iconRight: IconType.send
                                        onClicked: {
                                            var repeatCount = 0;
                                            var newCliCommands = cliCommands.replace(/\s/g,"")
                                            var stringList = newCliCommands.split(",")
                                            var count = 0;

                                            console.log("Repeat " + repeatFor.value + " times" + "\r")
                                            for(repeatCount = 0; repeatCount < repeatFor.value; repeatCount++)
                                            {
                                                for(count = 0; count < stringList.length-1; count++)
                                                {
                                                    backend.writeData(stringList[stringListCount] + "\r");
                                                    console.log(stringList[count] + "\r")
                                                }
                                            }
                                        }
                                    }

                                }


                                RowLayout
                                {

                                    AppText {
                                        text: "Send Every"
                                        font.bold: true
                                        font.pointSize: sp(textSize)
                                        leftPadding: 5
                                        topPadding: 10
                                        fontSize: 14

                                    }

                                    SpinBox{
                                        id: repeatPeriodic
                                        value: 1000
                                        from: 1
                                        to: 1000000
                                        editable: true

                                    }
                                    AppText {
                                        text: "ms"
                                        font.bold: true
                                        font.pointSize: sp(textSize)
                                        leftPadding: 5
                                        topPadding: 10
                                        fontSize: 14

                                    }

                                    AppButton{
                                        id: btnConsoleSendPeriodicRepetitions
                                        text:"Periodic Start"
                                        iconRight: IconType.send
                                        onClicked: {
                                            console.log("Periodic Start");
                                            delayInterval = repeatPeriodic.value;
                                            console.log(delayInterval + "ms");
                                            periodicSend = true;
                                            periodicTimer.start();
                                        }
                                    }
                                    AppButton{
                                        id: btnConsoleStopPeriodicRepetitions
                                        text:"Periodic Stop"
                                        iconRight: IconType.send
                                        onClicked: {
                                            console.log("Periodic Stop");
                                            periodicSend = false
                                            periodicTimer.stop();
                                        }
                                    }


                                    Timer
                                    {
                                        id: periodicTimer
                                        interval: delayInterval
                                        running: periodicSend
                                        repeat: true
                                        onTriggered:
                                        {
                                            var newCliCommands = cliCommands.replace(/\s/g,"")
                                            var stringList = newCliCommands.split(",")
                                            for(count = 0; count < stringList.length-1; count++)
                                            {
                                                backend.writeData(stringList[count] + "\r");
                                                console.log(stringList[count] + "\r")
                                            }
                                        }
                                    }
                                }

                                Item{
                                    Layout.fillHeight: true
                                }
                            }
                        }
                    }


                }
            }
        }
    }
}
