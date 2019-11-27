#pragma once
#pragma once
#include "opencv2/opencv.hpp"
#include <GL/glut.h>

#include "param.h"

#include <math.h>
#include <vector>

class ColorManager
{
	float gray;
	std::vector<float> orgBGR{ 0.0, 0.0, 0.0 };
	std::vector<float> orgXYZ{ 0.0, 0.0, 0.0 };

	std::vector<float> pre_BGR{ 0.0, 0.0, 0.0 };
	std::vector<float> oddBGR{ 0.0, 0.0, 0.0 };
	std::vector<float> oddXYZ{ 0.0, 0.0, 0.0 };
	std::vector<float> oddCIExy{ 0.0, 0.0 };
	std::vector<float> oddLab{ 0.0, 0.0, 0.0 };

	std::vector<float> evenBGR{ 0.0, 0.0, 0.0 };
	std::vector<float> evenXYZ{ 0.0, 0.0, 0.0 };
	std::vector<float> evenCIExy{ 0.0, 0.0 };
	std::vector<float> evenLab{ 0.0, 0.0, 0.0 };

	float oddLablist[180][3] = {};
	float evenLablist[180][3] = {};

public:
	ColorManager();
	//入出力用の関数
	void getGrayValue(float value);
	void writeOddBGRValue(float* BGR);
	void writeEvenBGRValue(float* BGR);
	void writeOrgBGRValue(float* BGR);

	//色空間を移動するための関数
	bool GRAY2BGRColorChangeFunction();
	bool BGR2XYZColorChangeFunction();
	bool XYZ2xyColorChangeFunction(int angle);//ここで色度を付ける
	bool xy2XYZColorChangeFunction();
	bool XYZ2BGRColorChangeFunction();
	bool BGR2LabColorChangeFunction();

	//RGBの色空間の距離をを考えてxyの差を広げていく
	bool GRAY2BGRColorFunction(float value, float* BGR);
	bool BGR2XYZColorFunction(float* BGR, float* XYZ);
	bool XYZ2xyColorFuncton(float* XYZ, float* xy);
	bool xy2XYZColorFunction(float* xy, float* XYZ);
	bool XYZ2BGRColorFunction(float* XYZ, float* BGR);
	float calculateDifferencexyWithBGRdistance(int angle);

	//180度全ての軸にたいして上記の処理を行う。
	bool calculateDifferencexyWithBGRDistanc180(float value);
};