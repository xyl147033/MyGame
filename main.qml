import QtQuick
import QtQuick.Controls
import QtQuick.Window

Window {
    visible: true
    width: 600
    height: 850
    title: qsTr("Hello World")

    Rectangle{
        id: scoreAreaID
        width: 580
        height: 250
        x: 10
        y:10
        color: "lightgrey"
        border.color: "black"
        border.width: 1

        Label{
            x:320;y:80
            width: 200
            height: 40
            text: "Score: " + "0"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Label{
            x:20;y:80
            width: 200
            height: 40
            text: "Level: "+ "1"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    Rectangle{
        id : operationRectID
        x:20;y:270;
        width: 560
        height: 560
        color: "#666666"

        property var posX: [10,120,230,340,450]
        property var posY: [10,120,230,340,450]

        Repeater{
            id : repeaterID
            model: 25

            Rectangle{
                id: rectID
                width: 100
                height: 100
                x: operationRectID.posX[index%5]
                y: operationRectID.posY[Math.floor(index/5)]
                Image {
                    id: imgID
                    anchors.fill: parent
                    anchors.margins: 2
                    source: "qrc:/ghost/" + manager.levelItems[index] + ".png"
                }

                MouseArea{
                    anchors.fill: parent
                    property bool isPressed: false
                    property real preX: 0.0
                    property real preY: 0.0
                    property real pressedX: 0.0
                    property real pressedY: 0.0
                    hoverEnabled: true
                    onPressed: {
                        isPressed = true
                        preX = rectID.x
                        preY = rectID.y
                        pressedX = mouseX
                        pressedY = mouseY
                        rectID.z = 5
                        rectID.border.color = "red"
                        rectID.border.width = 2
                    }
                    onReleased: {
                        isPressed = false

                        rectID.z = 0
                        rectID.border.color = "white"
                        rectID.border.width = 2
                        // 若是在得分区域内:拖拽
                        if(isInScoreArea(rectID.x + operationRectID.x,rectID.y + operationRectID.y,rectID.width,rectID.height)){
                            // 先设为不可见
                            rectID.visible = false
                            // 请求拖拽计算
                            manager.dragEvent(index)
                        }
                        // 点击或拖拽未在得分区内
                        else{
                            if(Math.abs(rectID.x-preX)>=5&&Math.abs(rectID.y-preY)>=5){
                                backPositionXAnimationID.from = rectID.x
                                backPositionXAnimationID.to = preX
                                backPositionYAnimationID.from = rectID.y
                                backPositionYAnimationID.to = preY
                                backPositionAnimationID.start()
                            }
                        }
                    }
                    onPositionChanged: {
                        if(isPressed){
                            rectID.x += mouseX - pressedX
                            rectID.y += mouseY - pressedY
                            if(isInScoreArea(rectID.x + operationRectID.x,rectID.y + operationRectID.y,rectID.width,rectID.height)){
                                rectID.border.color = "lightgreen"
                            }
                            else{
                                rectID.border.color = "red"
                            }
                        }
                    }
                    onEntered: {
                        rectID.border.color = "yellow"
                        rectID.border.width = 2
                    }
                    onExited: {
                        rectID.border.color = "white"
                        rectID.border.width = 2
                    }
                }

                // 回位动画
                ParallelAnimation{
                    id: backPositionAnimationID
                    SpringAnimation{
                        id: backPositionXAnimationID
                        target: rectID
                        property: "x"
                        spring: 5
                        damping: 0.1
                        epsilon: 0.25
                    }
                    SpringAnimation{
                        id: backPositionYAnimationID
                        target: rectID
                        property: "y"
                        spring: 5
                        damping: 0.1
                        epsilon: 0.25
                    }
                }
                // 下落动画


            }

        }
    }

    function isInScoreArea(x,y,w,h){
        if(x>=scoreAreaID.x && x+w<=scoreAreaID.x + scoreAreaID.width && y +h <= scoreAreaID.y + scoreAreaID.height){
            return true
        }
        return false
    }
}
