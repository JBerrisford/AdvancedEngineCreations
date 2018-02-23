#include "GameScreenLevel1.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include <sstream>

using namespace::std;

GameScreenLevel1::GameScreenLevel1() : GameScreen()
{
	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f,aspect,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);

	// ----- Face culling -----
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	// ------------------------
	
	// ----- Black background colour -----
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// -----------------------------------

	// ----- Enabling Lighting -----
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// -----------------------------


	// --------- Object Setup ---------
	glPolygonMode(GL_FRONT, GL_LINE);
	vRotation = Vertex3(0.0f, 180.0f, 0.0f);
	newObj = new Pinwheel();
	// --------------------------------

}

GameScreenLevel1::~GameScreenLevel1()
{	
	delete newObj;
}

void GameScreenLevel1::Render()
{
	// ----- Clear the screen -----	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 50.0f,
		      0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	
	// ----- Lighting and Material Setup -----
	SetLight();
	SetMaterial();
	// ---------------------------------------

	// ----- Model Rendering -----
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef(0, -15, 0);
	glRotatef(vRotation.x, 1, 0, 0);
	glRotatef(vRotation.y, 0, 1, 0);
	glRotatef(vRotation.z, 0, 0, 1);
	newObj->Render();
	glPopMatrix();	
	//-----------------------------
	
	// ----- Text Rendering -----
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	
	OutputRotations();
	OutputControls();
	
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	//------------------------------
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	fTimePassed += deltaTime;
	mCurrentTime += deltaTime;

	if (fTimePassed >= 0.02f)
	{
		newObj->Update(deltaTime);
		fTimePassed = 0.0f;
	}
	
	KeyboardInput(e);
}

void GameScreenLevel1::KeyboardInput(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case'd':

			newObj->SetFanRotate(false);
			newObj->SetCanAddFan(true);
			break;
		case'f':
			newObj->SetFanRotate(false);
			break;
		case'c':
			newObj->SetStandRotate(false);
			newObj->SetCanAddStand(true);
			break;
		case'v':
			newObj->SetStandRotate(false);
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case'q':
			if (newObj->GetFanRotate())
			{
				cout << "Fan Turned Off" << endl;
				newObj->SetFanRotate(false);
			}
			else
			{
				cout << "Fan Started" << endl;
				newObj->SetFanRotate(true);
			}
			break;
		case'w':
			if (newObj->GetPoleRotate())
			{
				cout << "Pole Turned Off" << endl;
				newObj->SetStandRotate(false);
			}
			else
			{
				cout << "Pole Started" << endl;
				newObj->SetStandRotate(true);
			}
			break;
		case'a':
			vRotation.y -= 15.0f;
			break;
		case's':
			vRotation.y += 15.0f;
			break;
		case'z':
			vRotation.x -= 15.0f;
			break;
		case'x':
			vRotation.x += 15.0f;
			break;
		case'e':
			vRotation.z -= 15.0f;
			break;
		case'r':
			vRotation.z += 15.0f;
			break;
		case'd':
			newObj->SetFanRotate(true);
			newObj->SetCanAddFan(false);
			break;
		case'f':
			newObj->SetFanRotate(true);
			newObj->SetCanAddFan(true);
			break;
		case'c':
			newObj->SetStandRotate(true);
			newObj->SetCanAddStand(false);
			break;
		case'v':
			newObj->SetStandRotate(true);
			newObj->SetCanAddStand(true);
			break;
		}
		break;
	}
}

void GameScreenLevel1::SetLight()
{
	Lighting light = 
	{{0.2f, 0.2f, 0.2f, 1.0f},	
	{0.7f, 0.7f, 0.7f, 1.0f}, 
	{0.5f, 0.5f, 0.5f, 1.0f}};

	float lightPos[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void GameScreenLevel1::SetMaterial()
{
	Material material = {
		{ 0.80f, 0.05f, 0.05f, 1.0f },
		{ 0.80f, 0.05f, 0.05f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		100.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}


void GameScreenLevel1::OutputLine(float x, float y, std::string text)
{
	glRasterPos2f(x, y);

	for (size_t i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}

void GameScreenLevel1::OutputRotations()
{
	glColor3f(1, 1, 1);
	string stringToOutput = "";
	stringToOutput.append("Rotation X : ");
	stringToOutput += to_string(vRotation.x);
	OutputLine(80, 95, stringToOutput);
	stringToOutput = "";
	stringToOutput.append("Rotation Y : ");
	stringToOutput += to_string(vRotation.y);
	OutputLine(80, 92, stringToOutput);
	stringToOutput = "";
	stringToOutput.append("Rotation Z : ");
	stringToOutput += to_string(vRotation.z);
	OutputLine(80, 89, stringToOutput);
}

void GameScreenLevel1::OutputControls()
{
	glColor3f(1, 1, 1);
	OutputLine(5, 95, "Turn Pinwheel On/Off - Q");
	OutputLine(5, 92, "Turn the Stands Rotation On/Off - W");
	OutputLine(5, 89, "Rotate Object +X/-X - A/S");
	OutputLine(5, 86, "Rotate Object +Y/-Y - Z/X");
	OutputLine(5, 83, "Rotate Object +Z/-Z - E/R");
	OutputLine(5, 80, "Hold to spin the Pinwheel - D/F");
	OutputLine(5, 77, "Hold to spin the Stand - C/V");
}

