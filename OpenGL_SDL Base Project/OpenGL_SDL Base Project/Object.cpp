#include "Object.h"
#include "Singleton.h"

Object::Object()
{

}

Object::Object(std::string pPath)
{
	mModelPath = pPath;
}

Object::~Object()
{
	while (!mComponents.empty())
	{
		delete mComponents.back();
		mComponents.pop_back();
	}
}

void Object::Render()
{
	for (size_t i = 0; i < mComponents.size(); i++)
	{
		mComponents[i]->Render();
	}
}

void Object::Update()
{
	for (size_t i = 0; i < mComponents.size(); i++)
	{
		mComponents[i]->Update();
	}
}

void Object::AddComponent(ComponentTypes pNewComp)
{
	switch (pNewComp)
	{
	case MODEL_RENDERER:
		ModelRenderer * newComp = new ModelRenderer(this, mModelPath, Singleton::GetInstance()->GetLoader());
		mComponents.push_back(newComp);
		break;
	/*case COLLISION_BOX:
		
		break;
	case COLLISION_CAPSULE:
		
		break;
	case COLLISION_SPHERE:
		
		break;
	case PHYSICS_COMPONENT:
		
		break;*/
	}
}