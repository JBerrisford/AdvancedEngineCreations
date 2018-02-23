#ifndef _OBJECTBASE_H
#define _OBJECTBASE_H

#include "Commons.h"
#include <vector>

class ObjectBase
{
protected:
	std::vector<Vector3D> vertices;
	std::vector<Vector2D> uvs;
	std::vector<Vector3D> normals;

	int numVertices;
	int indexCount;

	bool Load(char* path);
	void DrawTriangle(short a, short b, short c);

public:
	ObjectBase();
	~ObjectBase();

	virtual void Draw();
	void Update();
	virtual void CleanUp();
};



#endif // _OBJECTBASE_H
