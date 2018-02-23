#ifndef _SINGLETON_H
#define _SINGLETON_H

#include "Loader.h"

class Singleton
{
public:
	static Singleton * GetInstance();
	static Loader * GetLoader();

private:
	Singleton();
	~Singleton();

	static Singleton * mInstance;
	static Loader * mLoader;
};

#endif //_SINGLETON_H