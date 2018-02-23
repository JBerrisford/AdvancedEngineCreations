#ifndef _OBJECT_H
#define _OBJECT_H

#include "Commons.h"
#include "Component.h"
#include "ModelRenderer.h"
#include "Collision.h"

class Object
{
public:
	Object();
	Object(std::string pPath);
	~Object();

	void Render();
	void Update();

	void AddComponent(ComponentTypes newComp);

protected:
	std::vector<Component*> mComponents;
	std::string mModelPath;
};

#endif // _OBJECT_H
