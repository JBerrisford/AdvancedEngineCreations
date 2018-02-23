#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "Commons.h"

class Object;
class Component
{
public:
	// Constructor + Deconstructor
	Component(Object * pObject);
	~Component();

	// Virtual fucntions for polymorpharism
	virtual void Update();
	virtual void Render();

	template<class CompClass>
	CompClass * GetComponent()
	{
		return *this;
	};

protected:
	Object * mObject;

private:

};

#endif //_COMPONENT_H
