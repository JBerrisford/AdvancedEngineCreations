#include "Singleton.h"

Singleton* Singleton::mInstance = GetInstance();
Loader* Singleton::mLoader = GetLoader();

Singleton::Singleton()
{

}

Singleton::~Singleton()
{
	delete mInstance;
	delete mLoader;
}

Singleton * Singleton::GetInstance()
{
	if (!mInstance)
	{
		mInstance = new Singleton();
	}
	return mInstance;
}

Loader * Singleton::GetLoader()
{
	if (!mLoader)
	{
		mLoader = new Loader();
	}

	return mLoader;
}