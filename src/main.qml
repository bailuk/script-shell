
import QtQuick 2.9
import org.asteroid.controls 1.0
import org.asteroid.utils 1.0

import QtQuick 2.9
import org.asteroid.controls 1.0
import org.asteroid.utils 1.0

Application {
    id: app

    centerColor: "#7997be"
    outerColor:  "#10386c"

    Component {
        id: scriptDetailComponent
        Item {
            id: labelItem
            Flickable {
                anchors.fill: parent
                anchors.topMargin: Dims.l(10)
                contentHeight: contentColumn.implicitHeight
    
                Column {
                    id: contentColumn
                    anchors.fill: parent

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
                        id: scriptNameLabel
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
                        id: scriptFirstLineLabel
                        width: parent.width
                        height: Dims.l(12)
                        text: controller.selectedScriptLine1()
                        verticalAlignment: Text.AlignBottom
                        horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.Wrap
                    }

                    Label {
                        id: scriptSecondLineLabel
                        width: parent.width
                        height: Dims.l(12)
                        text: controller.selectedScriptLine2()
                        verticalAlignment: Text.AlignBottom
                        horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.Wrap
                    }
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
            function updateLabels() {
                scriptStateLabel.text = controller.selectedScriptState()
                scriptFirstLineLabel.text = controller.selectedScriptLine1()
                scriptSecondLineLabel.text = controller.selectedScriptLine2()
            }
            Connections {
                target: controller
                function onModelUpdated() {
                    updateLabels()
                    console.log("Model has been updated")
                }
            }
        }
    }

    LayerStack {
        id: layerStack
        firstPage: firstPageComponent
    }

    Component {
        id: firstPageComponent

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
}
