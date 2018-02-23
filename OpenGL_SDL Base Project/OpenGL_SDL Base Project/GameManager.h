#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H

#include "Singleton.h"
#include "Loader.h"

class GameManager : SingletonBase
{
public:
	GameManager();
	~GameManager();

	static Loader LOADER;

protected:


private:


};

#endif //_GAME_MANAGER_H
