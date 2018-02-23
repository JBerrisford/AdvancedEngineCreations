#include "ModelRenderer.h"

/*ModelRenderer::ModelRenderer(Object * pObject, std::string pPath, Loader * pLoader)
{
	SetModelProperties(pLoader->FindFileType(pPath));
}*/

ModelRenderer::~ModelRenderer()
{

}

void ModelRenderer::Render()
{
	DrawObject();
}

void ModelRenderer::DrawObject()
{
	for (size_t i = 0; i < mProperties.indices.size(); ++i)
	{
		glBegin(GL_POLYGON);
			mProperties.normals[mProperties.indices[i].pointA.normal].PlotNormal();
			mProperties.vertices[mProperties.indices[i].pointA.vertex].PlotVertext();
			mProperties.normals[mProperties.indices[i].pointB.normal].PlotNormal();
			mProperties.vertices[mProperties.indices[i].pointB.vertex].PlotVertext();
			mProperties.normals[mProperties.indices[i].pointC.normal].PlotNormal();
			mProperties.vertices[mProperties.indices[i].pointC.vertex].PlotVertext();
		glEnd();
	}
}