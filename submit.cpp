/*****************************************************************************
		FILE : submit.cpp (Assignment 1)
		NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
		Student Information
		Student ID: 
		Student Name: 
*****************************************************************************/

#include <stdlib.h>
#include <gl\glut.h>
#include <iostream>
#include <Windows.h>
using namespace std;

const GLdouble FRUSTDIM = 100.0f;
string option = "";
bool enableLight = 1;

static float fps = 0.0f;
static float lastTime = 0.0f;
bool falling = false;
float startTime = 0.0f;

/* Do animation*/
GLfloat angleFan = 0;
GLUquadricObj* quadobj;

/* For lighting*/
GLfloat light0pos[] = { 0.0f, 76.f, 0.f, 0.f };
GLfloat light0_mat1[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat light0_diff[] = { 0.8, 0.8, 0.8, 1.0 };

GLfloat chairX = -77.f, chairY = -70.f, chairZ = 150.f;
GLfloat bed_z = -100;
GLfloat ballX = 50.0, ballY = 50, ballRadius = 15.0f;

int direction = 0;
double v0 = 0;
float lastBallY = ballY;


void init(void) // All Setup For OpenGL Goes Here
{
	/* Light 0 Settings */
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);

	quadobj = gluNewQuadric();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW); /* Define Counter-Clockwise as front face */

	glEnable(GL_COLOR_MATERIAL);
}

void CalculateFrameRate()
{
	float currentTime = GetTickCount64() * 0.001f;
	fps++;
	if (currentTime - lastTime > 1.0f)
	{
		lastTime = currentTime;
		cout << "fps:" << fps << endl;
		fps = 0;
	}
}


void drawLightBulb() {
	/* Initialize material properties */
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat mat_specular[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat high_shininess[] = { 20.0 };
	GLfloat high_mat[] = { 1.0, 1.0, 1.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	/*Draw Light bulb START*/
	glPushMatrix();
	glColor4f(0.6f, 0.8f, 0.8f, 0.1f);
	glTranslatef(0.f, 90.f, 200);
	glRotatef(-90.f, 1.f, 0.f, 0.f);
	glutSolidTorus(1.5, 1.5, 110.f, 110.f);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.6f, 0.8f, 0.8f, 0.1f);
	glTranslatef(0.f, 87.f, 200);
	glRotatef(-90.f, 1.f, 0.f, 0.f);
	glutSolidTorus(1.5, 1.5, 110.f, 110.f);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.6f, 0.8f, 0.8f, 0.1f);
	glTranslatef(0.f, 84.f, 200);
	glRotatef(-90.f, 1.f, 0.f, 0.f);
	glutSolidTorus(1.5, 1.5, 110.f, 110.f);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, light0_mat1);
	glColor4f(0.8f, 0.8f, 0.7f, 0.1f);
	glTranslatef(0.f, 78.f, 200.f);
	glutSolidSphere(5.f, 50.f, 50.f);
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	/*Draw Light bulb END*/
}

void drawWall() {
	/* Draw the wall START */
	glBegin(GL_QUADS);

	/* Back wall */
	glColor3f(1.f, 0.5f, 0.f);
	glVertex3f(-110.0f, 110.0f, -200.0f);
	glVertex3f(110.0f, 110.0f, -200.0f);
	glColor3f(0.4f, 0.2f, 0.4f);
	glVertex3f(110.0f, -110.0f, -200.0f);
	glVertex3f(-110.0f, -110.0f, -200.0f);

	/* Top wall */
	glColor3f(0.7f, 0.8f, 0.3f);
	glVertex3f(-110.0f, 110.0f, -220.0f);
	glVertex3f(110.0f, 110.0f, -220.0f);
	glColor3f(0.8f, 0.6f, 0.3f);
	glVertex3f(110.0f, 110.0f, 220.0f);
	glVertex3f(-110.0f, 110.0f, 220.0f);

	/* Bottom wall */
	glColor3f(0.8f, 0.44f, 0.0f);
	glVertex3f(-110.f, -110.f, -200.f);
	glVertex3f(110.f, -110.f, -200.f);
	glColor3f(1.f, 0.54f, 0.5f);
	glVertex3f(110.f, -110.f, 220.f);
	glVertex3f(-110.f, -110.f, 220.f);

	/* Right wall */
	glColor3f(1.f, 0.54f, 0.4f);
	glVertex3f(110.0f, 110.0f, -200.0f);
	glColor3f(1.f, 0.54f, 0.f);
	glVertex3f(110.0f, -110.0f, -200.0f);
	glColor3f(1.f, 0.54f, 0.3f);
	glVertex3f(110.0f, -110.0f, 220.0f);
	glColor3f(0.9f, 0.87f, 0.9f);
	glVertex3f(110.0f, 110.0f, 220.0f);

	/* Window */
	glColor3f(0.9f, 0.0f, 0.0f);
	glVertex3f(109.0f, 40.0f, -10.0f);
	glVertex3f(109.0f, -40.0f, -10.0f);
	glVertex3f(109.0f, -40.0f, 190.0f);
	glVertex3f(109.0f, 40.0f, 190.0f);

	/* Left wall */
	glColor3f(1.f, 0.54f, 0.4f);
	glVertex3f(-110.0f, 110.0f, -200.0f);
	glColor3f(1.f, 0.54f, 0.f);
	glVertex3f(-110.0f, -110.0f, -200.0f);
	glColor3f(0.9f, 0.87f, 0.9f);
	glVertex3f(-110.0f, -110.0f, 220.0f);
	glColor3f(1.f, 0.54f, 0.3f);
	glVertex3f(-110.0f, 110.0f, 220.0f);

	glEnd();
	/* Draw the wall END */
}

void drawBed() {
	// bed
	glPushMatrix();
	//glColor4f(0.8f, 0.8f, 0.3f, 0.1f);
	glColor4f(0.5f, 0.8f, 0.5f, 0.1f);
	glTranslatef(0.f, -100.f, bed_z);
	glScalef(110.f, 20.0f, 200.f);
	glutSolidCube(1.f);
	glPopMatrix();

	// bed head board
	glPushMatrix();
	//glColor4f(0.7f, 0.5f, 0.2f, 0.1f);
	glColor4f(0.5f, 0.8f, 0.5f, 0.1f);
	glTranslatef(0.f, -80.f, bed_z - 100);
	glScalef(110.f, 60.0f, 10.f);
	glutSolidCube(1.f);
	glPopMatrix();
}

void drawText() {
	// text
	glColor4f(0.3f, 0.5f, 0.5f, 0.1f);
	const char* str = "NUAA CS";
	glRasterPos2i(-24, -55);
	for (int i = 0; i < strlen(str); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *(str + i));
}

void drawBedstandAndLamp() {
	// bedstand1
	glPushMatrix();
	glColor4f(0.8f, 0.8f, 0.3f, 0.1f);
	glTranslatef(-90.f, -95.f, -180);
	glScalef(30.f, 30.0f, 60.f);
	glutSolidCube(1.f);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5f, 0.1f, 0.5f);
	glTranslatef(-82.f, -95.f, -152);
	glutSolidSphere(3.f, 10.f, 10.f);
	glPopMatrix();

	// lamp1-top
	glPushMatrix();
	glColor3f(0.168f, 0.23f, 1.0f);
	glTranslatef(-90.f, -80.f, -180.f);
	glRotatef(-90, 1.f, 0.f, 0.f);
	gluCylinder(quadobj, 6.f, 4.f, 20.f, 20.f, 20.f);
	glPopMatrix();
	// lamp1-bottom
	glPushMatrix();
	glTranslatef(-90.f, -65.f, -180.f);
	glRotatef(-90, 1.f, 0.f, 0.f);
	gluCylinder(quadobj, 12.f, 5.f, 18.f, 20.f, 20.f);
	glPopMatrix();

	// bedstand2
	glPushMatrix();
	glColor4f(0.8f, 0.8f, 0.3f, 0.1f);
	glTranslatef(90.f, -95.f, -180);
	glScalef(30.f, 30.0f, 60.f);
	glutSolidCube(1.f);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5f, 0.1f, 0.5f);
	glTranslatef(98.f, -95.f, -152);
	glutSolidSphere(3.f, 10.f, 10.f);
	glPopMatrix();

	// lamp2-top
	glPushMatrix();
	glColor3f(0.168f, 0.23f, 1.0f);
	glTranslatef(90.f, -80.f, -180.f);
	glRotatef(-90, 1.f, 0.f, 0.f);
	gluCylinder(quadobj, 6.f, 4.f, 20.f, 20.f, 20.f);
	glPopMatrix();
	// lamp1-bottom
	glPushMatrix();
	glTranslatef(90.f, -65.f, -180.f);
	glRotatef(-90, 1.f, 0.f, 0.f);
	gluCylinder(quadobj, 12.f, 5.f, 18.f, 20.f, 20.f);
	glPopMatrix();
}

void drawElectricFan() {
	// fan blade 1
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.9f, 0.1f);
	glTranslatef(0.f, 40.f, -190);
	glRotatef(angleFan + 0, 0.f, 0.f, 1.f);
	glScalef(100.f, 6.0f, 5.f);
	glutSolidCube(1.f);
	glPopMatrix();

	// fan blade 2
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.9f, 0.1f);
	glTranslatef(0.f, 40.f, -190);
	glRotatef(angleFan + 45, 0.f, 0.f, 1.f);
	glScalef(100.f, 6.0f, 5.f);
	glutSolidCube(1.f);
	glPopMatrix();

	// fan blade 3
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.9f, 0.1f);
	glTranslatef(0.f, 40.f, -190);
	glRotatef(angleFan + 90, 0.f, 0.f, 1.f);
	glScalef(100.f, 6.0f, 5.f);
	glutSolidCube(1.f);
	glPopMatrix();

	// fan blade 4
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.9f, 0.1f);
	glTranslatef(0.f, 40.f, -190);
	glRotatef(angleFan + 135, 0.f, 0.f, 1.f);
	glScalef(100.f, 6.0f, 5.f);
	glutSolidCube(1.f);
	glPopMatrix();

	// outer
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.9f, 0.1f);
	glTranslatef(0.f, 40.f, -180.f);
	gluCylinder(quadobj, 50.f, 52.f, 6.f, 30.f, 30.f);
	glPopMatrix();
}

void drawChair() {
	// chair pan
	glPushMatrix();
	glColor3f(0.0f, 0.2f, 0.2f);
	glTranslatef(chairX, chairY, chairZ);
	glScalef(30.f, 5.0f, 80.f);
	glutSolidCube(1.f);
	glPopMatrix();

	// chair back
	glPushMatrix();
	glColor3f(0.0f, 0.2f, 0.2f);
	glTranslatef(chairX - 13, chairY + 15, chairZ);
	glScalef(5.f, 30.0f, 80.f);
	glutSolidCube(1.f);
	glPopMatrix();

	// chair support
	glPushMatrix();
	glColor3f(0.0f, 0.2f, 0.2f);
	glTranslatef(chairX, chairY, chairZ);
	glRotatef(90, 1.f, 0.f, 0.f);
	gluCylinder(quadobj, 4.f, 4.f, 30.f, 20.f, 20.f);
	glPopMatrix();

	// chair bottom
	glPushMatrix();
	glColor3f(0.0f, 0.2f, 0.2f);
	glTranslatef(chairX, chairY - 36, chairZ);
	glRotatef(-90, 1.f, 0.f, 0.f);
	gluCylinder(quadobj, 25.f, 4.f, 8.f, 20.f, 20.f);
	glPopMatrix();
}

void drawBall() {
	// ball
	glPushMatrix();
	glColor3f(0.1f, 0.6f, 0.1f);
	glTranslatef(ballX, ballY, 150);
	glutSolidSphere(ballRadius, 20.f, 30.f);
	glPopMatrix();
}

void drawTriangle() {
	// triangle
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-0.7, -0.7);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.7, -0.7);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-0.0, 0.7);
	glEnd();
}
void drawFlag() {
	glBegin(GL_POLYGON);
	glColor3f(0.9f, 0.9f, 0.0f);

	const GLfloat Pi = 3.1415926536f;  //定义Pi值
	GLfloat X[5], Y[5];  //用数组声明5组坐标
	int R = 12;

	for (int i = 0; i <= 4; i++)
	{
		X[i] = R * cos(2 * Pi * i / 5)+20;
		Y[i] = R * sin(2 * Pi * i / 5)+20;
	}
	glVertex3f(108.0f, Y[0], X[0]);
	glVertex3f(108.0f, Y[2], X[2]);
	glVertex3f(108.0f, Y[4], X[4]);
	glVertex3f(108.0f, Y[1], X[1]);
	glVertex3f(108.0f, Y[3], X[3]);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.9f, 0.9f, 0.0f);
	R = 5;
	for (int i = 0; i <= 4; i++)
	{
		//在圆上初始化5个坐标点
		X[i] = R * cos(2 * Pi * i / 5) + 60;
		Y[i] = R * sin(2 * Pi * i / 5) + 30;
	}
	glVertex3f(108.0f, Y[0], X[0]);
	glVertex3f(108.0f, Y[2], X[2]);
	glVertex3f(108.0f, Y[4], X[4]);
	glVertex3f(108.0f, Y[1], X[1]);
	glVertex3f(108.0f, Y[3], X[3]);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.9f, 0.9f, 0.0f);
	R = 5;
	for (int i = 0; i <= 4; i++)
	{
		//在圆上初始化5个坐标点
		X[i] = R * cos(2 * Pi * i / 5) + 70;
		Y[i] = R * sin(2 * Pi * i / 5) + 20;
	}
	glVertex3f(108.0f, Y[0], X[0]);
	glVertex3f(108.0f, Y[2], X[2]);
	glVertex3f(108.0f, Y[4], X[4]);
	glVertex3f(108.0f, Y[1], X[1]);
	glVertex3f(108.0f, Y[3], X[3]);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.9f, 0.9f, 0.0f);
	R = 5;
	for (int i = 0; i <= 4; i++)
	{
		//在圆上初始化5个坐标点
		X[i] = R * cos(2 * Pi * i / 5) + 67;
		Y[i] = R * sin(2 * Pi * i / 5) + 10;
	}
	glVertex3f(108.0f, Y[0], X[0]);
	glVertex3f(108.0f, Y[2], X[2]);
	glVertex3f(108.0f, Y[4], X[4]);
	glVertex3f(108.0f, Y[1], X[1]);
	glVertex3f(108.0f, Y[3], X[3]);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.9f, 0.9f, 0.0f);
	R = 5;
	for (int i = 0; i <= 4; i++)
	{
		//在圆上初始化5个坐标点
		X[i] = R * cos(2 * Pi * i / 5) + 57;
		Y[i] = R * sin(2 * Pi * i / 5) + 0;
	}
	glVertex3f(108.0f, Y[0], X[0]);
	glVertex3f(108.0f, Y[2], X[2]);
	glVertex3f(108.0f, Y[4], X[4]);
	glVertex3f(108.0f, Y[1], X[1]);
	glVertex3f(108.0f, Y[3], X[3]);
	glEnd();
	

}
void display(void) // Here's Where We Do All The Drawing
{
	/* Clear the buffer */
	glClearColor(0.0, 0.0, 0.0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0, 0, -550);

	drawLightBulb(); // light buble
	drawWall(); // wall
	drawBed(); // bed
	drawText(); // text
	drawBedstandAndLamp(); // bedstand lamp
	drawElectricFan(); // electric fan
	drawChair(); // chair
	drawBall(); // ball
	drawFlag();

	glPopMatrix();

	glutSwapBuffers(); // double buffer
	glFlush();

	glutPostRedisplay(); // Refresh the frame
	CalculateFrameRate(); // fps
}

void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Frustum Setting
	glFrustum(-FRUSTDIM, FRUSTDIM, -FRUSTDIM, FRUSTDIM, 300., 800.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) // Handle the keyboard events here
{
	switch (key)
	{
	case '\033':
		exit(0);
		break;
	case 'p': /*pause*/
		option = "pause";
		break;

	case '1': /*decrease light*/
		if (enableLight)
			if (light0_mat1[0] >= 0)
			{
				for (int i = 0; i <= 3; i++)
				{
					light0_mat1[i] -= 0.03;
					light0_diff[i] -= 0.03;
				}
				glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
				glEnable(GL_LIGHT0);
			}
		break;

	case '2': /*increase light*/
		if (enableLight)
			if (light0_mat1[0] <= 1)
			{
				for (int i = 0; i <= 3; i++)
				{
					light0_mat1[i] += 0.03;
					light0_diff[i] += 0.03;
				}
				glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
				glEnable(GL_LIGHT0);
			}
		break;

	case 'q': /*rotate electric fan anticlockwise*/
		option = "rotate_fan_anticlockwise";
		break;

	case 'w': /*rotate electric fan clockwise*/
		option = "rotate_fan_clockwise";
		break;

	case 'e': /*zoom in ball*/
		option = "zoom_in_ball";
		break;

	case 'r': /*zoom out ball*/
		option = "zoom_out_ball";
		break;

	case 's': /*switch on/off the light*/
		option = "switch_light";
		break;

	case 'f': /*ball falling*/
		if (falling == true) {
			break;
		}
		option = "ball_free_fall";
		startTime = GetTickCount64() * 0.001f;
		break;

	case 'i':
		chairZ -= 4;
		break;

	case 'k':
		chairZ += 4;
		break;

	case 'j':
		chairX -= 4;
		break;

	case 'l':
		chairX += 4;
		break;
	}
}


void idle()
{
	if (option == "nothing")
	{
	}
	else if (option == "rotate_fan_clockwise") /* Clockwise */
	{
		if (angleFan <= -360)
			angleFan = 0;
		angleFan -= 1;
	}
	else if (option == "rotate_fan_anticlockwise") /* Anti-Clockwise */
	{
		if (angleFan >= 360)
			angleFan = 0;
		angleFan += 1;
	}
	else if (option == "zoom_in_ball")
	{
		if (ballRadius >= 5) {
			ballRadius -= 0.1;
		}
	}
	else if (option == "zoom_out_ball")
	{
		if (ballRadius <= 30) {
			ballRadius += 0.1;
		}
	}
	else if (option == "switch_light")
	{
		if (enableLight)
		{
			enableLight = 0;
			for (int i = 0; i <= 3; i++)
			{
				light0_mat1[i] = 0.0;
			}
			glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
			glDisable(GL_LIGHT0);
			option = 1;
		}
		else
		{
			enableLight = 1;
			for (int i = 0; i <= 3; i++)
			{
				light0_diff[i] = 1.0;
				light0_mat1[i] = 1.0;
			}
			glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
			glEnable(GL_LIGHT0);
			option = 1;
		}
	}
	else if (option == "ball_free_fall") {
		if (direction == 0) {
			float accumTime = GetTickCount64() * 0.001 - startTime;
			if (accumTime >= 0) {
				ballY = (lastBallY / 100 - 0.5 * 9.8 * accumTime * accumTime) * 100;
			}
			if (ballY <= -90) {
				ballY = -90;
				direction = 1;
				v0 = 9.8 * accumTime;
				v0 -= 0.4; // energy loss
				cout << "touch down! v0:" << v0 << endl;
				startTime = GetTickCount64() * 0.001;
			}
		}
		if (direction == 1) {
			float accumTime = GetTickCount64() * 0.001 - startTime;
			if (accumTime >= 0) {
				ballY = (-0.9 + v0 * accumTime - 0.5 * 9.8 * accumTime * accumTime) * 100;
				lastBallY = ballY;
				//cout << "accuTime:" << accumTime << " v0:" << v0 << " ballY:" << ballY << endl;
			}
			if (v0 - 9.8 * accumTime <= 0) {
				direction = 0;
				v0 = 0.0;
				cout << "touch up! v0:" << v0 << " last ball y:" << lastBallY << endl;
				startTime = GetTickCount64() * 0.001;
			}
		}
	}
}

void OnMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		ballX -= 4;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		ballX += 4;
	}
}

void main(int argc, char** argv)
{
	/* Initialization of GLUT Library */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	/* Create a window with title specified */
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("A 3D Room");

	init();	/* not GLUT call, initialize several parameters */
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(OnMouse);
	glutIdleFunc(idle); // set global recall function

	glutMainLoop();
}