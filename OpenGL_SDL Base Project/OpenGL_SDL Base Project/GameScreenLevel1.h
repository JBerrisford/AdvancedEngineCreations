#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Loader.h"
#include "Pinwheel.h"

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1();
	~GameScreenLevel1();

	bool SetUpLevel();
	void Render();
	void Update(float deltaTime, SDL_Event e);

	
	Pinwheel* newObj;

private:
	void SetLight();
	void SetMaterial();
	
	void KeyboardInput(SDL_Event e);
	void OutputLine(float x, float y, std::string text);
	void OutputRotations();
	void OutputControls();
	
	float fTimePassed = 0.0f;
	float mCurrentTime;
	Vertex3 vRotation;
};


#endif //_GAMESCREENLEVEL1_H