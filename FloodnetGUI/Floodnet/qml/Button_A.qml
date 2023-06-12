import QtQuick
import Felgo

AppButton{
    property int buttonRadius:5
    property int buttonTextSize: 16
    property int buttonWidth: 150

    minimumWidth: buttonWidth
    radius: buttonRadius
    textSize: buttonTextSize
}
