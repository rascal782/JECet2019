/**
 ******************************************************************************
 ** ファイル名 : Runner.cpp
 ** クラス名   : Runner
 **
 ** 概要 : 走行を管理するクラス
 ******************************************************************************
 **/
#include "Runner.h"

/**
 * コンストラクタ
 */
Runner::Runner() {
    cm = new ControlManager();
    inspanel = new InstrumentPanel();

    //databank = new Databank();
}

/**
 * スタート待機処理
 * @param forward    前進
 * @param turn       旋回
 * @param tailAngle  尻尾角度
 * @comment TODO whileで処理を行っているためタスク化を考える
 */
void Runner::start(int forward, int turn, int tailAngle) {
    cm->tailInit();
    while (1) {
        int tailTMP = inspanel->pushTailButton();

        if (tailTMP != 0) {
            tailAngle += tailTMP;
            syslog(LOG_NOTICE, "TAIL: %3d\r", tailAngle);
        }

        cm->running(forward, turn, tailAngle);

        if (inspanel->pushButton()) {
            break;
        }

        cm->setTargetRgb(inspanel->pushColorButton());
    }
    cm->gyroInit();
    cm->wheelInit();
    cm->balancerInit();
    databank->openLogFile();
}

/**
 * 走行処理
 * @param forward    前進
 * @param turn       旋回
 * @param tailAngle  尻尾角度
 */
void Runner::run(int forward, int turn, int tailAngle, float krgb) {
    space = inspanel->update();

    int totalRGB = inspanel->getTotalRGB() / krgb;
    if (style == 1) {
        cm->runningL(forward, turn, tailAngle, totalRGB);
    }
    else {
        cm->noBalanceRun(forward, turn, tailAngle, totalRGB);
    }
    if (totalRGB <= 7 || inspanel->getBtCmd() == 6) {
        stop();
    }
}

/**
 * BT更新
 */
void Runner::btUpdate() {
    inspanel->btUpdate();
}

/**
 * 総走行距離取得
 * @return 総走行距離
 */
int Runner::getDistance() {
    return inspanel->getRunDistance();
}

/**
 * 衝撃検知量取得
 * @return 衝撃検知量取得
 */
int Runner::getGyroImpact() {
    return inspanel->getGyroImpact();
}

/**
 * 障害物検知距離取得
 * @param 障害物検知距離
 */
int Runner::getSonarDis() {
    return inspanel->getSonarDis();
}

/**
 * BtCmd取得
 * @return BtCmd
 */
int Runner::getBtCmd() {
    return inspanel->getBtCmd();
}

/**
 * PID係数設定
 * @param kp 係数P
 * @param ki 係数I
 * @param kd 係数D
 */
void Runner::setPID(float kp, float ki, float kd) {
    cm->setPID(kp, ki, kd);
}

/**
 * 走行方法設定
 * @return style
 */
void Runner::setStyle(int style) {
    this->style = style;
}

/**
 * 走行コース選択
 * @return Course
 */
void Runner::setCourse(int course) {
    this->course=course;
}

/**
 * ジャイロオフセット設定
 * @param gyroOffset ジャイロオフセット
 */
void Runner::setGyroOffset(int gyroOffset) {
    cm->setGyroOffset(gyroOffset);
}

/**

 *走行情報記録
 */
void Runner::recordLog(int time){
    databank->writeLogFile(
        time,
        inspanel->getRunDistance(),
        inspanel->getTotalRGB(),
        inspanel->getNaturalTotalRGB(),
        inspanel->getRunDistance(),
        inspanel->getMA(),
        inspanel->getMV(),
        inspanel->getGyroImpact()
        );
}


/**
 * 停止
 */
void Runner::stop() {
    ev3_led_set_color(LED_RED);
    wup_tsk(MAIN_TASK);
    ev3_stp_cyc(CYC_HANDLER);
    cm->stop();
    inspanel->stop();
    databank->closeLogFile();
}
