import QtQuick 2.0
import UllApp 1.0


Rectangle {
    property var game: gamehandler.game
    property bool taskXSet: false
    property bool taskConfirmed: false


    property var startTime
    property var answerTime
    property real bonusTime: 0.15
    property int maxTime: 15000

    property var unscaledX
    property var unscaledY
    signal gameMenuClicked()
    signal gameSummaryClicked()

    color: backgroundGrey

    onTaskXSetChanged: {
        if(gamehandler.game.mode === Mode.TIMED){
            botNext.nextClicked();
            delay(1000, function() {
                 botNext.nextClicked();

            })
        }

    }

    Timer{
        id: timer
        interval: maxTime
        running: true
        onTriggered: {
            if(gamehandler.game.mode === Mode.TIMED){
                gamehandler.game.finishedChanged(true);
                gameSummaryClicked();
            }
        }
    }

    function startTimer(){
        timer.running = true;
        task.progressBarWidth = task.progressBarStarterWidth;
        task.progressBarRunning = true;
        startTime = new Date();
    }


    function addTime(){
        // Calculate new time with added bonus time
        answerTime = new Date();
        var timeDiff = answerTime.getTime() - startTime.getTime();
        timeDiff = timer.interval - timeDiff;
        timer.interval = timeDiff + maxTime*bonusTime;

        // Calculate new animation bar width
        task.progressBarWidth += task.progressBarStarterWidth*bonusTime;

        // Make sure new time doesnt surpass maximum time
        if(timer.interval>maxTime) {
            timer.interval = maxTime;
            task.progressBarWidth = task.progressBarStarterWidth;
        }

        // Restart animation and timer with new values
        task.seqAnimation.restart();
        timer.restart();

        startTime = new Date();
    }


    //todo move to a service
    function getOrganName(organ){
        switch(organ){
        case Organ.FEMUR:
            return "Femur";
        case Organ.ARTERY:
            return "Femoral Artery";
        case Organ.ILIACA:
            return "Fascia Iliaca";
        case Organ.LATA:
            return "Vascular Sheeth";
        case Organ.NERVE:
            return "Femoral Nerve";
        default:
            return "Unknown";
        }
    }


    function timer2() {
        return Qt.createQmlObject("import QtQuick 2.0; Timer {}", root);
    }

    Timer {
            id: timer2
        }

        function delay(delayTime, cb) {
            timer2.interval = delayTime;
            timer2.repeat = false;
            timer2.triggered.connect(cb);
            timer2.start();
        }

        Rectangle {
            id: rectangle
            color: "yellow"
            anchors.fill: parent
            anchors.margins: 100
            opacity: 0

            Behavior on opacity {
                NumberAnimation {
                    duration: 500
                }
            }
        }

    //POINTS box
    GamePointsBox {
        id: topPoints
        contentText: gamehandler.game.points
        width: parent.width*4.5/12
        height: main.height/main.width<1.5 ? parent.height/13 : parent.height/10
        anchors.left: parent.left
        anchors.leftMargin: parent.width/12
        anchors.top: parent.top
        anchors.topMargin: parent.width/20
    }

    //MULTIPLIER box
    GamePointsBox {
        id: topMulti
        contentText: "x" + gamehandler.game.multiplier
        labelText: qsTr("MULTIPLIER")
        width: parent.width*4.5/12
        height: main.height/main.width<1.5 ? parent.height/13 : parent.height/10
        anchors.top: parent.top
        anchors.topMargin: parent.width/20
        anchors.right: parent.right
        anchors.rightMargin: parent.width/12
    }

    //TASK
    GameTask {
        id: task
        task: game.currentTask
        progressBarInterval:timer.interval
        anchors.top: topPoints.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: botMenu.top


    }

    //MENU button
    MenuButton {
        id: botMenu
        onMenuClicked: {
            gameMenuClicked();
        }
    }

    NextButton {
        id: botNext
        arrowVisible: taskConfirmed && gamehandler.game.mode !== Mode.TIMED && !game.currentTask.correct

        onNextClicked: {
            //Game done
            if(game.finished && gamehandler.game.mode !== Mode.TIMED){
                 gameSummaryClicked();
            }


            //CONFIRM (vis annoret bilde)
        if(taskXSet && !taskConfirmed){
                taskConfirmed = true;
                if(gamehandler.game.currentTask.answerTask(unscaledX, unscaledY) && gamehandler.game.mode === Mode.TIMED){
                    addTime();
                }else
                if(game.currentTask.correct){
                    delay(1000, function() {
                         botNext.nextClicked();

                    })
                }

            }

            //NEXT
            else if(game.currentTask.answered){
                taskConfirmed = false;
                taskXSet = false;
                task.croXvisible = false;
                game.newTask();
            }

        }
    }
}
