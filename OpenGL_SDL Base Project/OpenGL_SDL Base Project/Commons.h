#pragma once

#include <cmath>
#include <Windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include <vector>
#include <string>
#include <iostream>

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};
enum ComponentTypes
{
	MODEL_RENDERER = 0,
	COLLISION_BOX,
	COLLISION_CAPSULE,
	COLLISION_SPHERE,
	PHYSICS_COMPONENT
};

struct Vertex2
{
	float x;
	float y;

	// Base Constuctors for the struct
	Vertex2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vertex2(int initialX, int initialY)
	{
		x = initialX;
		y = initialY;
	}

	// Arithmetic operators overriders.
	Vertex2 operator+ (const Vertex2 b)
	{
		Vertex2 result;

		result.x = x + b.x;
		result.y = y + b.y;

		return result;
	}
	Vertex2 operator+= (const Vertex2 b)
	{
		x += b.x;
		y += b.y;
		return *this;
	}
	Vertex2 operator- (const Vertex2 b)
	{
		Vertex2 result;

		result.x = x - b.x;
		result.y = y - b.y;

		return result;
	}
	Vertex2 operator-= (const Vertex2 b)
	{
		x -= b.x;
		y -= b.y;
		return *this;
	}
	Vertex2 operator* (const Vertex2 b)
	{
		Vertex2 result;

		result.x = x * b.x;
		result.y = y * b.y;

		return result;
	}
	Vertex2 operator* (const float b)
	{
		Vertex2 result;

		result.x = x * b;
		result.y = y * b;

		return result;
	}
	Vertex2 operator*= (const Vertex2 b)
	{
		x *= b.x;
		y *= b.y;
		return *this;
	}
	Vertex2 operator/ (const Vertex2 b)
	{
		Vertex2 result;

		result.x = x / b.x;
		result.y = y / b.y;

		return result;
	}
	Vertex2 operator/ (const float b)
	{
		Vertex2 result;

		result.x = x / b;
		result.y = y / b;

		return result;
	}
	Vertex2 operator/= (const Vertex2 b)
	{
		x /= b.x;
		y /= b.y;
		return *this;
	}
};
struct Vertex3
{
	float x;
	float y;
	float z;

	// Base Constuctors for the struct
	Vertex3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vertex3(int initialX, int initialY, int initialZ)
	{
		x = initialX;
		y = initialY;
		z = initialZ;
	}

	void PlotVertext()
	{
		glVertex3f(x, y, z);
	}
	void PlotNormal()
	{
		glNormal3f(x, y, z);
	}
	float Magnatude()
	{
		float temp = (x*x) + (y*y) + (z*z);
		return sqrt(temp);
	}
	Vertex3 Normalise()
	{
		Vertex3 temp = Vertex3(x, y, z);
		return Vertex3(x/temp.Magnatude(), y/temp.Magnatude(), z/temp.Magnatude());
	}

	// Arithmetic operators overriders.
	Vertex3 operator+ (const Vertex3 b)
	{
		Vertex3 result;

		result.x = x + b.x;
		result.y = y + b.y;
		result.z = z + b.z;

		return result;
	}
	Vertex3 operator+= (const Vertex3 b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	}
	Vertex3 operator- (const Vertex3 b)
	{
		Vertex3 result;

		result.x = x - b.x;
		result.y = y - b.y;
		result.z = z - b.z;

		return result;
	}
	Vertex3 operator-= (const Vertex3 b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	}
	Vertex3 operator* (const Vertex3 b)
	{
		Vertex3 result;

		result.x = x * b.x;
		result.y = y * b.y;
		result.z = z * b.z;

		return result;
	}
	Vertex3 operator* (const float b)
	{
		Vertex3 result;

		result.x = x * b;
		result.y = y * b;
		result.z = z * b;

		return result;
	}
	Vertex3 operator*= (const Vertex3 b)
	{
		x *= b.x;
		y *= b.y;
		z *= b.z;
		return *this;
	}
	Vertex3 operator*= (const float b)
	{
		x *= b;
		y *= b;
		z *= b;
		return *this;
	}
	Vertex3 operator/ (const Vertex3 b)
	{
		Vertex3 result;

		result.x = x / b.x;
		result.y = y / b.y;
		result.z = z / b.z;

		return result;
	}
	Vertex3 operator/ (const float b)
	{
		Vertex3 result;

		result.x = x / b;
		result.y = y / b;
		result.z = z / b;

		return result;
	}
	Vertex3 operator/= (const Vertex3 b)
	{
		x /= b.x;
		y /= b.y;
		z /= b.z;
		return *this;
	}
	Vertex3 operator/= (const float b)
	{
		x /= b;
		y /= b;
		z /= b;
		return *this;
	}
};

struct ArrayIndices
{
	int vertexA;
	int vertexB;
	int vertexC;

	ArrayIndices()
	{
		vertexA = 0;
		vertexB = 0;
		vertexC = 0;
	}
};
struct Indices
{
	int vertex;
	int texture; // /Colour/Material
	int normal;
};
struct FaceDetails
{
	Indices pointA;
	Indices pointB;
	Indices pointC;
	Vertex3 faceNormal;
};
struct ObjectProperties
{
	std::vector<FaceDetails> indices;
	std::vector<Vertex3> vertices;
	std::vector<Vertex2> textures;
	std::vector<Vertex3> normals;
};

struct Lighting {
	float ambient[4];
	float diffuse[4];
	float specular[4];
};
struct Material {
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess;
};
