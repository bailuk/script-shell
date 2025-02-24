
import QtQuick 2.9
import org.asteroid.controls 1.0
import org.asteroid.utils 1.0

import QtQuick 2.9
import org.asteroid.controls 1.0
import org.asteroid.utils 1.0

Application {
    id: app

    centerColor: "#0f6602"
    outerColor:  "#000000"

    Component {
        id: scriptDetailComponent
        Item {
            Column {
                width: parent.width
                height: parent.height
                anchors.fill: parent
                Item { width: parent.width; height: Dims.h(10) }
                Label {
                    id: scriptStateLabel
                    width: parent.width
                    height: Dims.l(12)
                    text: controller.selectedScriptState()
                    verticalAlignment: Text.AlignBottom
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.Wrap
                }
                Label {
                    width: parent.width
                    font {
                        bold: true
                        pixelSize: Dims.l(9)
                    }
                    text: controller.selectedScriptName()
                    verticalAlignment: Text.AlignBottom
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.NoWrap
                }

                Label {
                    id: scriptLine1Label
                    width: parent.width
                    height: Dims.l(12)
                    text: controller.selectedScriptLine1()
                    verticalAlignment: Text.AlignBottom
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.Wrap
                }

                Label {
                    id: scriptLine2Label
                    width: parent.width
                    height: Dims.l(12)
                    text: controller.selectedScriptLine2()
                    verticalAlignment: Text.AlignBottom
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.Wrap
                }
            }

            IconButton {
                iconName: "ios-checkmark-circle-outline"
                anchors { 
                    bottom: parent.bottom
                    horizontalCenter: parent.horizontalCenter
                    bottomMargin: Dims.l(10)
                }
                onClicked: {
                    controller.executeSelected()
                }
            }

            Connections {
                target: controller
                function onModelUpdated() {
                    scriptStateLabel.text = controller.selectedScriptState()
                    scriptLine1Label.text = controller.selectedScriptLine1()
                    scriptLine2Label.text = controller.selectedScriptLine2()
                }
            }
        }
    }

    Component {
        id: scriptListComponent

        Column {
            width: parent.width
            height: parent.height
            Item { width: parent.width; height: Dims.h(10) }
            ListView {
                id: listView
                width: parent.width
                height: parent.height - Dims.h(20)
                model: scriptListModel
                delegate: Item {
                    width: listView.width
                    height: Dims.h(17)                    
                    
                    HighlightBar {
                        anchors.fill: parent
                        onClicked: {
                            controller.selectScript(index);
                            layerStack.push(scriptDetailComponent)
                        }
                    }
                    Label {
                        text: name
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: Dims.l(9)
                        anchors.centerIn: parent                         
                    }
                }
            }
            Item { width: parent.width; height: Dims.h(10) }
        }
    }

    LayerStack {
        id: layerStack
        firstPage: scriptListComponent
    }

}
