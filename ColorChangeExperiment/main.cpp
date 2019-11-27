#include "opencv2/opencv.hpp"
#include <GL/glut.h>

#include "param.h"
#include "colorManager.h"

#include <math.h>

//色調整用の変数
int gBGR[3] = {};
int angle = 0.0;
int grayValue = 128;

ColorManager color_manager;

using namespace std;

void idle()
{
	glutPostRedisplay();
}

void display()
{
	int i;
	float BGR1[3] = {};
	float BGR2[3] = {};
	float orgBGR[3] = {};
	static int color = 0;

	color_manager.writeOddBGRValue(BGR1);
	color_manager.writeEvenBGRValue(BGR2);
	color_manager.writeOrgBGRValue(orgBGR);

	glClear(GL_COLOR_BUFFER_BIT);

	glutIdleFunc(idle);
	//BGR2
	glBegin(GL_POLYGON);
	glColor3d((double)BGR2[2] / 255.0, (double)BGR2[1] / 255.0, (double)BGR2[0] / 255.0);
	glVertex2d(-3.2, -0.9);
	glVertex2d(-1.5, -0.9);
	glVertex2d(-1.5, 0.9);
	glVertex2d(-3.2, 0.9);
	glEnd();
	//オリジナル
	glBegin(GL_POLYGON);
	glColor3d((double)orgBGR[2] / 255.0, (double)orgBGR[1] / 255.0, (double)orgBGR[0] / 255.0);
	glVertex2d(-1.3, 0.1);
	glVertex2d(0.4, 0.1);
	glVertex2d(0.4, 1.9);
	glVertex2d(-1.3, 1.9);
	glEnd();
	//BGR1
	glBegin(GL_POLYGON);
	glColor3d((double)BGR1[2] / 255.0, (double)BGR1[1] / 255.0, (double)BGR1[0] / 255.0);
	glVertex2d(0.6, -0.9);
	glVertex2d(2.3, -0.9);
	glVertex2d(2.3, 0.9);
	glVertex2d(0.6, 0.9);
	glEnd();
	//継時加法混色
	if (color == 0) {
		color = 1;
		glColor3d((double)BGR1[2] / 255.0, (double)BGR1[1] / 255.0, (double)BGR1[0] / 255.0);
	}
	else if (color == 1) {
		color = 0;
		glColor3d((double)BGR2[2] / 255.0, (double)BGR2[1] / 255.0, (double)BGR2[0] / 255.0);
	}
	glBegin(GL_POLYGON);
	glVertex2d(-1.3, -1.9);
	glVertex2d(0.4, -1.9);
	glVertex2d(0.4, -0.1);
	glVertex2d(-1.3, -0.1);
	glEnd();


	glutSwapBuffers();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glLoadIdentity();
	/* スクリーン上の表示領域をビューポートの大きさに比例させる */
	glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);

	/* モデルビュー変換行列の設定 */
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a': cout << "a" << endl;
		break;
	case '1': cout << "1" << endl;
		color_manager.calculateDifferencexyWithBGRDistanc180(128);
		break;
	case '2': cout << "2" << endl;
		color_manager.calculateDifferencexyWithBGRDistanc180(80);
		break;
	case 'q':
	case 'Q':
	case '\033':  /* '\033' は ESC の ASCII コード */
		exit(0);
	default:
		break;
	}
}

void trackbarColorChangeCallback(int pos, void* userdata)
{
	/*
	color_manager.getGrayValue((float)grayValue);
	color_manager.GRAY2BGRColorChangeFunction();
	color_manager.BGR2XYZColorChangeFunction();
	color_manager.XYZ2xyColorChangeFunction(angle);
	color_manager.xy2XYZColorChangeFunction();
	color_manager.XYZ2BGRColorChangeFunction();
	*/
	if (grayValue < 10) grayValue = 10;
	color_manager.getGrayValue((float)grayValue);
	color_manager.GRAY2BGRColorChangeFunction();
	float distance = color_manager.calculateDifferencexyWithBGRdistance(angle);
	cout << "distance : " << distance << endl;
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void ColorChangeFunction()
{
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}

int main(int argc, char* argv[])
{
	//glutInitWindowPosition(PROJECTION_SIZE_X, 0);
	glutInitWindowSize(PROJECTION_SIZE_X / 4, PROJECTION_SIZE_Y / 4);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow(argv[0]);
	init();

	cv::namedWindow("ColorChange", cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("Gray", "ColorChange", &grayValue, 200, trackbarColorChangeCallback);
	cv::createTrackbar("Angle", "ColorChange", &angle, 180, trackbarColorChangeCallback);
	cv::createTrackbar("B", "ColorChange", &gBGR[0], 255, trackbarColorChangeCallback);
	cv::createTrackbar("G", "ColorChange", &gBGR[1], 255, trackbarColorChangeCallback);
	cv::createTrackbar("R", "ColorChange", &gBGR[2], 255, trackbarColorChangeCallback);

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	cv::destroyAllWindows();

	return 0;
}