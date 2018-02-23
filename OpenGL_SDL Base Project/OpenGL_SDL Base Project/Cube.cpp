#include "Cube.h"
#include <fstream>
#include <iostream>

Cube::Cube()
{
	Load("cube.txt");
}

Cube::~Cube()
{
	delete indexedVertices;
	delete colours;
	delete indices;
}

bool Cube::Load(char* path)
{
	
}

void Cube::DrawCube(int a, int b, int c, int d)
{
	glBegin(GL_QUADS);
		indexedVertices[a].PlotVertex();
		indexedVertices[b].PlotVertex();
		indexedVertices[c].PlotVertex();
		indexedVertices[d].PlotVertex();
	glEnd();
}

void Cube::Draw()
{
	for (int i = 0; i < indexCount; i++)
	{
		glColor3f(colours[i].r, colours[i].g, colours[i].b);
		DrawCube(indices[i].a, indices[i].b, indices[i].c, indices[i].d);
	}

}

void Cube::Update()
{

}
