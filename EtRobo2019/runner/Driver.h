/**
 ******************************************************************************
 ** ファイル名 : Driver.h
 ** クラス名   : Driver
 **
 ** 概要 : 走行体に指示するクラス
 ******************************************************************************
 **/
#ifndef RUNNER_DRIVER_H
#define RUNNER_DRIVER_H

#include "Runner.h"
#include "../scenario/Course.h"
#include "Clock.h"

class Driver
{
private:
    Runner* runner;
    Course* mCourse;
    Course dCourse[4]{
   /* テスト用　ライントレースし続けるだけ　*/
   /*  {  距離,時間,衝撃,障害,  前進,旋回,尻尾,Gyro  P   ,    I   ,    D  ,目標RGB,走行法} */
       {     1,    0,  0,  0,      60,  0, 95,   0, 0.0300F, 0.0000F, 1.0000F, 1.00F, 1 },  //  初期化配列
       {     0,    8,  0,  0,      60,  0, 96,   0, 0.0300F, 0.0000F, 1.0000F, 1.00F, 1 },  //  Start時
       { 20000,    0,  0,  0,      40,  0,  0,   0, 0.0900F, 0.0000F, 0.8000F, 1.10F, 1 },  //  ライントレース
       {     0,    0,  0,  0,       0,  0, 81,   0, 0.0000F, 0.0000F, 0.0000F, 1.00F, 0 }   //  完全停止用終端配列
    };
    Course lCourse[17]{
  /* テスト用　ライントレースし続けるだけ　*/
  /*  {  距離,時間,衝撃,障害,  前進,旋回,尻尾,Gyro  P   ,    I   ,    D  ,目標RGB,走行法} */
      {     1,  0,  0,  0,      60,  0, 95,   0, 0.0300F, 0.0000F, 1.0000F, 1.00F, 1 },  //  初期化配列
      {     0, 20,  0,  0,      60,  0,100,   0, 0.0300F, 0.0000F, 1.0000F, 1.00F, 1 },  //  Start時
      {   570,  0,  0,  0,      120, 0,  0,   0, 0.0500F, 0.0000F, 1.0000F, 1.00F, 1 },  //直線
      {   610,  0,  0,  0,      80,  0,  45,  0, 0.0920F, 0.0001F, 1.1000F, 1.00F, 1 },  //右カーブ
      {   600,  0,  0,  0,      100, 0,  0,   0, 0.0400F, 0.0000F, 1.0000F, 1.00F, 1 },  //直線
      {   720,  0,  0,  0,      80,  0,  45,  0, 0.0900F, 0.0000F, 1.1000F, 1.00F, 1 },  //右カーブ
      {   130,  0,  0,  0,      100, 0,  0,   0, 0.0500F, 0.0000F, 1.0000F, 1.00F, 1 },  //直線
      { 730,    0,  0,  0,      80,  0,  45,  0, 0.0900F, 0.0000F, 1.1000F, 1.00F, 1 },  //右カーブ
      { 1260,   0,  0,  0,      80,  0,  0,   0, 0.0900F, 0.0001F, 1.1000F, 1.00F, 1 },  //左カーブ
      { 260,    0,  0,  0,      100, 0,  45,  0, 0.0400F, 0.0000F, 1.0000F, 1.00F, 1 },  //直線
      { 770,    0,  0,  0,      80,  0,  0,   0, 0.0900F, 0.0000F, 1.1000F, 1.00F, 1 },  //左カーブ
      { 930,    0,  0,  0,      100, 0,  45,  0, 0.0500F, 0.0001F, 1.0000F, 1.00F, 1 },  //直線
      { 610,    0,  0,  0,      80,  0,  0,   0, 0.0900F, 0.0000F, 1.1000F, 1.00F, 1 },  //左カーブ
      { 250,    0,  0,  0,      80, 0,  45,  0, 0.0500F, 0.0000F, 1.0000F, 1.00F, 1 },  //直線
      { 330,    0,  0,  0,      80,  0,  0,   0, 0.0800F, 0.0000F, 0.9000F, 1.00F, 1 },  // 左カーブ
      { 1380,   0,  0,  0,      80,  0,  45,  0, 0.0900F, 0.0001F, 0.9000F, 1.00F, 1 },  //右カーブ
      { 830,    0,  0,  0,      80,  0,  0,   0, 0.0500F, 0.0000F, 1.0000F, 1.00F, 1 }  //直線
    };
    Course rCourse[19]{
   /* テスト用　ライントレースし続けるだけ　*/
   /*  {  距離,時間,衝撃,障害,  前進,旋回,尻尾,Gyro  P   ,    I   ,    D  ,目標RGB,走行法} */
       {     1,    0,  0,  0,      60,  0, 95,   0, 0.0300F, 0.0000F, 1.0000F, 1.00F, 1 },  //  初期化配列
       {     0,    8,  0,  0,      60,  0,100,   0, 0.0300F, 0.0000F, 1.0000F, 1.00F, 1 },  //  Start時
        {   400,    0,  0,  0,      30,  0,  5,   0, 0.0900F, 0.0001F, 0.7000F, 1.60F, 1 },  //  8G 左カーブ及び灰色
        {     0,    0,  0, 10,      10,  0, 70,   0, 0.0500F, 0.0001F, 0.7000F, 1.10F, 1 },  //  ルックアップ検知まで
        {     0,  100,  0,  0,      30,  0, 55,   0, 0.0500F, 0.0000F, 0.0000F, 1.00F, 0 },  //  尻尾走行切り替え
        {     0,  700,  0,  0,       0,  0, 55,   0, 0.0500F, 0.0000F, 0.0000F, 1.00F, 0 },  //  安定化停止
        {   320,    0,  0,  0,      10,  0, 55,   0, 0.0500F, 0.0000F, 0.0000F, 1.00F, 0 },  //  シングル通過
        {     0, 1500,  0,  0,       0,  0, 55,   0, 0.0500F, 0.0000F, 0.0000F, 1.00F, 0 },  //  安定化停止
        {   370,    0,  0,  0,     -10,  0, 55,   0, 0.0500F, 0.0000F, 0.0000F, 1.00F, 0 },  //  バック通過
        {     0, 1200,  0,  0,       0,  0, 55,   0, 0.0500F, 0.0000F, 0.0000F, 1.00F, 0 },  //  安定化停止
        {   320,    0,  0,  0,      10,  0, 55,   0, 0.0500F, 0.0002F, 0.3000F, 1.00F, 0 },  //  ダブル通過(PID ON)
        {   370,    0,  0,  0,     -10,  0, 55,   0, 0.0500F, 0.0000F, 0.0000F, 1.00F, 0 },  //  バック通過
        {     0, 1200,  0,  0,       0,  0, 55,   0, 0.0500F, 0.0000F, 0.0000F, 1.00F, 0 },  //  安定化停止
        {   440,    0,  0,  0,      10,  0, 55,   0, 0.0500F, 0.0002F, 0.3000F, 1.00F, 0 },  //  ダブル通過(PID ON)
        {   280,    0,  0,  0,      10,  0, 55,   0, 0.0500F, 0.0000F, 0.0000F, 1.00F, 0 },  //  灰色通過
        {   195,    0,  0,  0,      10,  0, 70,   0, 0.0500F, 0.0000F, 0.0000F, 1.00F, 0 },  //  ガレージ
        {     0,  300,  0,  0,     -13,  0, 81,   0, 0.0500F, 0.0000F, 0.0000F, 1.00F, 0 },  //  走行体角度上げ
        {     0,    0,  0,  0,       0,  0, 81,   0, 0.0500F, 0.0000F, 0.0000F, 1.00F, 0 },  //  完全停止
        {     0,    0,  0,  0,       0,  0, 81,   0, 0.0000F, 0.0000F, 0.0000F, 1.00F, 0 }   //  完全停止用終端配列
    };
    Clock* clock;
    int beforeDistance;
    int beforeClock;
    int courseNumber = 0;

public:
    Driver();
    void start();
    void exec();
    int courseChange();
    void btUpdate();

};
#endif  // RUNNER_DRIVER_H