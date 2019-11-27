#include "colorManager.h"


using namespace std;

ColorManager::ColorManager()
{
	gray = 0.0;
}

void ColorManager::getGrayValue(float value)
{
	gray = value;
}

void ColorManager::writeOddBGRValue(float* BGR)
{
	BGR[0] = oddBGR[0];
	BGR[1] = oddBGR[1];
	BGR[2] = oddBGR[2];
}

void ColorManager::writeEvenBGRValue(float* BGR)
{
	BGR[0] = evenBGR[0];
	BGR[1] = evenBGR[1];
	BGR[2] = evenBGR[2];
}

void ColorManager::writeOrgBGRValue(float* BGR)
{
	BGR[0] = orgBGR[0];
	BGR[1] = orgBGR[1];
	BGR[2] = orgBGR[2];
}

bool ColorManager::GRAY2BGRColorChangeFunction()
{
	cv::Mat colorBGRMat(1, 1, CV_8UC3);
	cv::Mat colorGRAYMat(1, 1, CV_8UC1);

	colorGRAYMat.at<cv::Vec3b>(0, 0)[0] = gray;
	cout << endl;
	cout << "GRAY : " << colorGRAYMat << endl;

	cv::cvtColor(colorGRAYMat, colorBGRMat, cv::COLOR_GRAY2BGR);

	orgBGR[0] = colorBGRMat.at<cv::Vec3b>(0, 0)[0];
	orgBGR[1] = colorBGRMat.at<cv::Vec3b>(0, 0)[1];
	orgBGR[2] = colorBGRMat.at<cv::Vec3b>(0, 0)[2];
	pre_BGR[0] = colorBGRMat.at<cv::Vec3b>(0, 0)[0];
	pre_BGR[1] = colorBGRMat.at<cv::Vec3b>(0, 0)[1];
	pre_BGR[2] = colorBGRMat.at<cv::Vec3b>(0, 0)[2];

	cout << "orgBGR : " << colorBGRMat << endl;
	return true;
}

bool ColorManager::BGR2XYZColorChangeFunction()
{
	cv::Mat colorBGRMat(1, 1, CV_8UC3);
	cv::Mat colorXYZMat(1, 1, CV_8UC3);

	colorBGRMat.at<cv::Vec3b>(0, 0)[0] = orgBGR[0];
	colorBGRMat.at<cv::Vec3b>(0, 0)[1] = orgBGR[1];
	colorBGRMat.at<cv::Vec3b>(0, 0)[2] = orgBGR[2];

	cout << "orgBGR : " << colorBGRMat << endl;

	cv::cvtColor(colorBGRMat, colorXYZMat, cv::COLOR_BGR2XYZ);

	orgXYZ[0] = colorXYZMat.at<cv::Vec3b>(0, 0)[0];
	orgXYZ[1] = colorXYZMat.at<cv::Vec3b>(0, 0)[1];
	orgXYZ[2] = colorXYZMat.at<cv::Vec3b>(0, 0)[2];

	cout << "XYZ : " << colorXYZMat << endl;
	return true;
}

bool ColorManager::XYZ2xyColorChangeFunction(int angle)
{
	double rad = angle * (PI / 180.0);

	cv::Mat colorXYZMat(1, 1, CV_8UC3);
	float colorDifferencexy = 0.001;
	float oddx, evenx, oddy, eveny;

	colorXYZMat.at<cv::Vec3b>(0, 0)[0] = orgXYZ[0];
	colorXYZMat.at<cv::Vec3b>(0, 0)[1] = orgXYZ[1];
	colorXYZMat.at<cv::Vec3b>(0, 0)[2] = orgXYZ[2];

	float sumXYZ = orgXYZ[0] + orgXYZ[1] + orgXYZ[2];
	oddCIExy[0] = orgXYZ[0] / sumXYZ;
	oddCIExy[1] = orgXYZ[1] / sumXYZ;
	evenCIExy[0] = orgXYZ[0] / sumXYZ;
	evenCIExy[1] = orgXYZ[1] / sumXYZ;

	cout << "CIExy : " << oddCIExy[0] << ", " << oddCIExy[1] << endl;
	cout << endl;

	oddx = colorDifferencexy * cos(rad);
	oddy = colorDifferencexy * sin(rad);
	evenx = colorDifferencexy * cos(rad);
	eveny = colorDifferencexy * sin(rad);

	//oddCIExy座標を変化させる
	oddCIExy[0] = oddCIExy[0] + oddx;
	oddCIExy[1] = oddCIExy[1] + oddy;
	cout << "angle : " << angle << endl;
	cout << "oddCIExy = oddCIExy + cos(angle) or sin(angle)" << endl;
	cout << "Updated oddCIExy : " << oddCIExy[0] << " " << oddCIExy[1] << endl;

	//evenCIExy座標を変化させる
	evenCIExy[0] = evenCIExy[0] - evenx;
	evenCIExy[1] = evenCIExy[1] - eveny;
	cout << "evenCIExy[1] = evenCIExy - cos(angle) or sin(angle)" << endl;
	cout << "Updated evenCIExy : " << evenCIExy[0] << " " << evenCIExy[1] << endl;

	return true;
}

bool  ColorManager::xy2XYZColorChangeFunction()
{
	cv::Mat colorXYZMat(1, 1, CV_8UC3);

	oddXYZ[0] = oddCIExy[0] / oddCIExy[1] * orgXYZ[1];
	oddXYZ[1] = orgXYZ[1];
	oddXYZ[2] = (1.0 - oddCIExy[0] - oddCIExy[1]) / oddCIExy[1] * orgXYZ[1];

	evenXYZ[0] = evenCIExy[0] / evenCIExy[1] * orgXYZ[1];
	evenXYZ[1] = orgXYZ[1];
	evenXYZ[2] = (1.0 - evenCIExy[0] - evenCIExy[1]) / evenCIExy[1] * orgXYZ[1];

	colorXYZMat.at<cv::Vec3b>(0, 0)[0] = oddXYZ[0];
	colorXYZMat.at<cv::Vec3b>(0, 0)[1] = oddXYZ[1];
	colorXYZMat.at<cv::Vec3b>(0, 0)[2] = oddXYZ[2];

	cout << "Updated oddXYZ : " << colorXYZMat << endl;

	colorXYZMat.at<cv::Vec3b>(0, 0)[0] = evenXYZ[0];
	colorXYZMat.at<cv::Vec3b>(0, 0)[1] = evenXYZ[1];
	colorXYZMat.at<cv::Vec3b>(0, 0)[2] = evenXYZ[2];

	cout << "Updated evenXYZ : " << colorXYZMat << endl;

	return true;
}

bool  ColorManager::XYZ2BGRColorChangeFunction()
{
	cv::Mat colorBGRMat(1, 1, CV_8UC3);
	cv::Mat colorXYZMat(1, 1, CV_8UC3);

	colorXYZMat.at<cv::Vec3b>(0, 0)[0] = oddXYZ[0];
	colorXYZMat.at<cv::Vec3b>(0, 0)[1] = oddXYZ[1];
	colorXYZMat.at<cv::Vec3b>(0, 0)[2] = oddXYZ[2];
	cv::cvtColor(colorXYZMat, colorBGRMat, cv::COLOR_XYZ2BGR);

	oddBGR[0] = colorBGRMat.at<cv::Vec3b>(0, 0)[0];
	oddBGR[1] = colorBGRMat.at<cv::Vec3b>(0, 0)[1];
	oddBGR[2] = colorBGRMat.at<cv::Vec3b>(0, 0)[2];

	colorXYZMat.at<cv::Vec3b>(0, 0)[0] = evenXYZ[0];
	colorXYZMat.at<cv::Vec3b>(0, 0)[1] = evenXYZ[1];
	colorXYZMat.at<cv::Vec3b>(0, 0)[2] = evenXYZ[2];
	cv::cvtColor(colorXYZMat, colorBGRMat, cv::COLOR_XYZ2BGR);

	evenBGR[0] = colorBGRMat.at<cv::Vec3b>(0, 0)[0];
	evenBGR[1] = colorBGRMat.at<cv::Vec3b>(0, 0)[1];
	evenBGR[2] = colorBGRMat.at<cv::Vec3b>(0, 0)[2];
	float rgbDistance = powf(evenBGR[0] - oddBGR[0], 2) + powf(evenBGR[1] - oddBGR[1], 2) + powf(evenBGR[2] - oddBGR[2], 2);
	rgbDistance = sqrt(rgbDistance);
	cout << "Updated evenBGR : " << colorBGRMat << endl;
	cout << "Updated oddBGR : " << colorBGRMat << endl;
	cout << "evenDistance : " << rgbDistance << endl;

	return true;
}

bool  ColorManager::BGR2LabColorChangeFunction()
{
	cv::Mat colorOddBGRMat(1, 1, CV_8UC3);
	cv::Mat colorEvenBGRMat(1, 1, CV_8UC3);
	cv::Mat colorOddLabMat(1, 1, CV_8UC3);
	cv::Mat colorEvenLabMat(1, 1, CV_8UC3);

	colorOddBGRMat.at<cv::Vec3b>(0, 0)[0] = oddBGR[0];
	colorOddBGRMat.at<cv::Vec3b>(0, 0)[1] = oddBGR[1];
	colorOddBGRMat.at<cv::Vec3b>(0, 0)[2] = oddBGR[2];
	colorEvenBGRMat.at<cv::Vec3b>(0, 0)[0] = evenBGR[0];
	colorEvenBGRMat.at<cv::Vec3b>(0, 0)[1] = evenBGR[1];
	colorEvenBGRMat.at<cv::Vec3b>(0, 0)[2] = evenBGR[2];

	cv::cvtColor(colorOddBGRMat, colorOddLabMat, cv::COLOR_XYZ2BGR);
	cv::cvtColor(colorEvenBGRMat, colorEvenLabMat, cv::COLOR_XYZ2BGR);

	oddLab[0] = colorOddLabMat.at<cv::Vec3b>(0, 0)[0];
	oddLab[1] = colorOddLabMat.at<cv::Vec3b>(0, 0)[1];
	oddLab[2] = colorOddLabMat.at<cv::Vec3b>(0, 0)[2];
	evenLab[0] = colorEvenLabMat.at<cv::Vec3b>(0, 0)[0];
	evenLab[1] = colorEvenLabMat.at<cv::Vec3b>(0, 0)[1];
	evenLab[2] = colorEvenLabMat.at<cv::Vec3b>(0, 0)[2];

	cout << "Updated oddLab : " << colorOddLabMat << endl;
	cout << "Updated evenLab : " << colorEvenLabMat << endl;

	return true;
}



///////////////////////////////////////////////////////

bool ColorManager::GRAY2BGRColorFunction(float value, float* BGR)
{
	cv::Mat colorBGRMat(1, 1, CV_8UC3);
	cv::Mat colorGRAYMat(1, 1, CV_8UC1);

	colorGRAYMat.at<cv::Vec3b>(0, 0)[0] = value;

	cout << "GRAY : " << colorGRAYMat << endl;

	cv::cvtColor(colorGRAYMat, colorBGRMat, cv::COLOR_GRAY2BGR);

	BGR[0] = colorBGRMat.at<cv::Vec3b>(0, 0)[0];
	BGR[1] = colorBGRMat.at<cv::Vec3b>(0, 0)[1];
	BGR[2] = colorBGRMat.at<cv::Vec3b>(0, 0)[2];
	BGR[0] = colorBGRMat.at<cv::Vec3b>(0, 0)[0];
	BGR[1] = colorBGRMat.at<cv::Vec3b>(0, 0)[1];
	BGR[2] = colorBGRMat.at<cv::Vec3b>(0, 0)[2];

	cout << "orgBGR : " << colorBGRMat << endl;
	return true;
}


bool ColorManager::BGR2XYZColorFunction(float* BGR, float* XYZ)
{
	cv::Mat colorBGRMat(1, 1, CV_8UC3);
	cv::Mat colorXYZMat(1, 1, CV_8UC3);

	colorBGRMat.at<cv::Vec3b>(0, 0)[0] = BGR[0];
	colorBGRMat.at<cv::Vec3b>(0, 0)[1] = BGR[1];
	colorBGRMat.at<cv::Vec3b>(0, 0)[2] = BGR[2];

	cout << "BGR : " << colorBGRMat << endl;

	cv::cvtColor(colorBGRMat, colorXYZMat, cv::COLOR_BGR2XYZ);

	XYZ[0] = colorXYZMat.at<cv::Vec3b>(0, 0)[0];
	XYZ[1] = colorXYZMat.at<cv::Vec3b>(0, 0)[1];
	XYZ[2] = colorXYZMat.at<cv::Vec3b>(0, 0)[2];

	cout << "XYZ : " << colorXYZMat << endl;
	return true;
}

bool ColorManager::XYZ2xyColorFuncton(float* XYZ, float* xy)
{
	cv::Mat colorXYZMat(1, 1, CV_8UC3);

	colorXYZMat.at<cv::Vec3b>(0, 0)[0] = XYZ[0];
	colorXYZMat.at<cv::Vec3b>(0, 0)[1] = XYZ[1];
	colorXYZMat.at<cv::Vec3b>(0, 0)[2] = XYZ[2];

	float sumXYZ = XYZ[0] + XYZ[1] + XYZ[2];
	xy[0] = XYZ[0] / sumXYZ;
	xy[1] = XYZ[1] / sumXYZ;

	cout << "xy : " << xy[0] << ", " << xy[1] << endl;

	return true;
}

bool ColorManager::xy2XYZColorFunction(float* xy, float* XYZ)
{
	cv::Mat colorXYZMat(1, 1, CV_8UC3);

	XYZ[0] = xy[0] / xy[1] * XYZ[1];
	XYZ[1] = XYZ[1];
	XYZ[2] = (1.0 - xy[0] - xy[1]) / xy[1] * XYZ[1];

	colorXYZMat.at<cv::Vec3b>(0, 0)[0] = XYZ[0];
	colorXYZMat.at<cv::Vec3b>(0, 0)[1] = XYZ[1];
	colorXYZMat.at<cv::Vec3b>(0, 0)[2] = XYZ[2];

	cout << "Updated XYZ : " << colorXYZMat << endl;

	return true;
}

bool ColorManager::XYZ2BGRColorFunction(float* XYZ, float* BGR)
{
	cv::Mat colorBGRMat(1, 1, CV_8UC3);
	cv::Mat colorXYZMat(1, 1, CV_8UC3);

	colorXYZMat.at<cv::Vec3b>(0, 0)[0] = XYZ[0];
	colorXYZMat.at<cv::Vec3b>(0, 0)[1] = XYZ[1];
	colorXYZMat.at<cv::Vec3b>(0, 0)[2] = XYZ[2];
	cv::cvtColor(colorXYZMat, colorBGRMat, cv::COLOR_XYZ2BGR);

	BGR[0] = colorBGRMat.at<cv::Vec3b>(0, 0)[0];
	BGR[1] = colorBGRMat.at<cv::Vec3b>(0, 0)[1];
	BGR[2] = colorBGRMat.at<cv::Vec3b>(0, 0)[2];

	cout << "Updated BGR : " << colorBGRMat << endl;

	return true;
}

float ColorManager::calculateDifferencexyWithBGRdistance(int angle)
{
	cv::Mat colorXYZMat(1, 1, CV_8UC3);
	float colorDifferencexy = 0.0;
	float tmpcolorDifferencexy = 0.0;
	float BGR[3] = {};
	float BGR1[3] = {};
	float BGR2[3] = {};
	float preBGR1[3] = {}; float preBGR2[3] = {};
	float XYZ[3] = {};
	float xy[2] = {};
	float difference = 0.0;

	float XYZ1[3] = {};
	float xy1[2] = {};
	float XYZ2[3] = {};
	float xy2[2] = {};
	float differencexy = 0.001;

	double rad = angle * (PI / 180.0);

	GRAY2BGRColorFunction(gray, BGR);
	BGR2XYZColorFunction(BGR, XYZ);
	XYZ2xyColorFuncton(XYZ, xy);

	while (1) {
		//2つのxy色差を設定する
		colorDifferencexy += differencexy;
		tmpcolorDifferencexy = colorDifferencexy + differencexy;
		cout << colorDifferencexy << "," << tmpcolorDifferencexy << endl;

		//xy色差をもとにBGRに変換し距離を求める
		//まずは
		xy1[0] = xy[0] + colorDifferencexy * cos(rad);
		xy1[1] = xy[1] + colorDifferencexy * sin(rad);
		xy2[0] = xy[0] - colorDifferencexy * cos(rad);
		xy2[1] = xy[1] - colorDifferencexy * sin(rad);
		for (int i = 0; i < 2; i++) {
			XYZ1[i] = XYZ[i]; XYZ2[i] = XYZ[i];
		}

		xy2XYZColorFunction(xy1, XYZ1);
		XYZ2BGRColorFunction(XYZ1, BGR1);
		xy2XYZColorFunction(xy2, XYZ2);
		XYZ2BGRColorFunction(XYZ2, BGR2);
		difference = powf(BGR1[0] - BGR2[0], 2) + powf(BGR1[1] - BGR2[1], 2) + powf(BGR1[2] - BGR2[2], 2);
		difference = sqrt(difference);

		/*
		if (difference >= 20.0) break;
		if (xy1[0] + xy1[1] > 1) break;
		if (xy2[0] + xy2[1] > 1) break;
		*/

		if (difference >= 19.5 && difference < 20.5) break;
		else if (difference >= 20.5) {
			colorDifferencexy -= differencexy;
			differencexy *= 0.1;
			BGR1[0] = preBGR1[0]; BGR2[0] = preBGR2[0];
			BGR1[1] = preBGR1[1]; BGR2[1] = preBGR2[1];
			BGR1[2] = preBGR1[2]; BGR2[2] = preBGR2[2];

		}
		else if (differencexy <= 0.001 * powf(0.1, 6)) break;
		if (xy1[0] + xy1[1] > 1) break;
		if (xy2[0] + xy2[1] > 1) break;

		preBGR1[0] = BGR1[0]; preBGR2[0] = BGR2[0];
		preBGR1[1] = BGR1[1]; preBGR2[1] = BGR2[1];
		preBGR1[2] = BGR1[2]; preBGR2[2] = BGR2[2];

	}

	oddBGR[0] = BGR1[0]; evenBGR[0] = BGR2[0];
	oddBGR[1] = BGR1[1]; evenBGR[1] = BGR2[1];
	oddBGR[2] = BGR1[2]; evenBGR[2] = BGR2[2];
	cout << "oddBGR : " << BGR1[0] << ", " << BGR1[1] << ", " << BGR1[2];
	cout << ", evenBGR : " << BGR2[0] << ", " << BGR2[1] << ", " << BGR2[2] << endl;
	cout << "preBGR1 : " << preBGR1[0] << ", " << preBGR1[1] << ", " << preBGR1[2];
	cout << ", preBGR2 : " << preBGR2[0] << ", " << preBGR2[1] << ", " << preBGR2[2] << endl;
	BGR2LabColorChangeFunction();
	return difference;
}

//Lab空間の軸を考える

bool ColorManager::calculateDifferencexyWithBGRDistanc180(float value)
{
	getGrayValue(value);

	for (int deg = 0; deg < 180; deg++) {
		float distance = calculateDifferencexyWithBGRdistance(deg);
		cout << "distance : " << distance << endl;
		oddLablist[deg][0] = oddLab[0];
		oddLablist[deg][1] = oddLab[1];
		oddLablist[deg][2] = oddLab[2];
		evenLablist[deg][0] = evenLab[0];
		evenLablist[deg][1] = evenLab[1];
		evenLablist[deg][2] = evenLab[2];
		cout << "oddLab : " << oddLab[0] << ", " << oddLab[1] << ", " << oddLab[2];
		cout << ", evenLab : " << evenLab[0] << ", " << evenLab[1] << ", " << evenLab[2] << endl;
	}

	return true;
}