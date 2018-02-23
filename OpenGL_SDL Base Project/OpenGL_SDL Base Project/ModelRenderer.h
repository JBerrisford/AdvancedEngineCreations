#ifndef _MODEL_RENDERER_H
#define _MODEL_RENDERER_H

#include "Component.h"
#include "Loader.h"

class ModelRenderer : public Component
{
public:
	//Constructor. Renders model from pPath, using a Loader created at compile tine.
	ModelRenderer(Object * pObject, std::string pPath, Loader * pLoader) : Component(pObject) { SetModelProperties(pLoader->FindFileType(pPath)); };
	~ModelRenderer();
	
	// Overides the Render functionality of the base component class.
	void Render() override;
	
	// ---> REFACTOR ---> Change to use a pointer, so all objects of the same model will be created 
	//					  from the same set of variables stored within memory at compile time.
	void SetModelProperties(ObjectProperties pNewProperties) { mProperties = pNewProperties; };

private:
	void DrawObject();
	ObjectProperties mProperties;
};

#endif //_MODEL_RENDERER_H