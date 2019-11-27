#pragma once

//#define PROJECTION_SIZE_X 1280 //プロジェクタ画像サイズ
//#define PROJECTION_SIZE_Y 768
//#define PROJECTION_SIZE_X 1600  //プロジェクタ画像サイズ
//#define PROJECTION_SIZE_Y 1200
#define PROJECTION_SIZE_X 3840  //プロジェクタ画像サイズ
#define PROJECTION_SIZE_Y 2160
//#define PROJECTION_SIZE_X 1920  //プロジェクタ画像サイズ
//#define PROJECTION_SIZE_Y 1080

#define CAMERA_SIZE_X 1280 //カメラ画像サイズ
#define CAMERA_SIZE_Y 720

//#define PC_DISPLAY_SIZE_X 1920 //PC画面サイズ (プロジェクタ画像の配置に使用)
//#define PC_DISPLAY_SIZE_Y 1080
#define PC_DISPLAY_SIZE_X 3840 //PC画面サイズ (プロジェクタ画像の配置に使用)
#define PC_DISPLAY_SIZE_Y 2160

#define RECTANGLE_NUM_IN_LINE 7 //キャリブレーションボックス上の一列の黒矩形数
#define RECTANGLE_NUM_IN_ONE_PLANE (RECTANGLE_NUM_IN_LINE * 4) //キャリブレーションボックスの一平面上の黒矩形数
#define DISTANCE_BET_RECTANGLES 20.0 //キャリブレーションボックスの黒矩形間の距離[mm]
#define BOX_SIZE 160.0 //キャリブレーションボックスのサイズ[mm]
#define POINT_NUM (RECTANGLE_NUM_IN_LINE*RECTANGLE_NUM_IN_LINE*3) //キャリブレーションボックス上で最終的に算出する点数

#define PI 3.1415926535897932

//-----------------------------------------------------------------------
//プロジェクタカラーキャリブレーション用

#define GAMMA_VALUE 1.25
//#define PROJECTION_COLOR_NUM_FOR_CALIBRATION 23
#define PROJECTION_COLOR_NUM_FOR_CALIBRATION 7


//---------------------------------------------------------------------
//#define AUTO_CALIB
//#define CALIBRATION_MODE //プロジェクタカメラ間のキャリブレーションを行う際に定義
//#define APP1_MODE  //キャリブレーションボックスへの投影を行う際(アプリケーション１)に定義
//#define APP2_MODE  //任意物体への動的投影を行う際(アプリケーション２)に定義

//#define IMPERCEPTIBLE_CODE_PROJECTION_QUICKTRY

#define USE_FLYCAP2CV_WRAPPER
//---------------------------------------------------------------------

//for PGR camera
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        101
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif