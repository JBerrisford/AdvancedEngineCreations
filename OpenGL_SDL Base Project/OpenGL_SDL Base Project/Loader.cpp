#include "Loader.h"
#include "Commons.h"
#include <fstream>
#include <vector>

// Uses the correct loader based on the file type.
ObjectProperties Loader::FindFileType(std::string path)
{
	int index = path.find_last_of(".");

	if (path.substr(index + 1) == "txt")
		return LoadTXT(path);
	else if (path.substr(index + 1) == "obj")
		return LoadOBJ(path);
	else if (path.substr(index + 1) == "3ds")
		return Load3DS(path);
	else
		std::cout << "Failed To find file type. Unable to load File." << std::endl;
		
	return ObjectProperties();
	
}

// ----- Loads .txt files ----- BUGGED, Normals are calculated wrong and product weird ligthing
ObjectProperties Loader::LoadTXT(std::string path)
{
	ObjectProperties tempProperties;
	std::ifstream inFile;
	inFile.open(path);

	if (!inFile.good())
	{
		std::cerr << "Can't Find Model File - " << path << std::endl;
		return tempProperties;
	}

	char temp;

	while (!inFile.eof())
	{
		inFile >> temp;

		if (temp == 'v')
		{
			Vertex3 tempVec = Vertex3();
			inFile >> tempVec.x;
			inFile >> tempVec.y;
			inFile >> tempVec.z;

			tempProperties.vertices.push_back(tempVec);
		}
		else if (temp == 'f')
		{
			FaceDetails tempArrInd = FaceDetails();
			inFile >> tempArrInd.pointA.vertex;
			inFile >> tempArrInd.pointB.vertex;
			inFile >> tempArrInd.pointC.vertex;

			tempArrInd.pointA.texture = 0;
			tempArrInd.pointB.texture = 0;
			tempArrInd.pointC.texture = 0;

			Vertex3 edge1 = tempProperties.vertices[tempArrInd.pointB.vertex] - tempProperties.vertices[tempArrInd.pointA.vertex];
			Vertex3 edge2 = tempProperties.vertices[tempArrInd.pointC.vertex] - tempProperties.vertices[tempArrInd.pointA.vertex];

			Vertex3 tempNormal = CrossProduct(edge1, edge2).Normalise();
			tempArrInd.faceNormal = tempNormal;

			tempProperties.indices.push_back(tempArrInd);
		}
		else if (temp == 'c')
		{
			//inFile >> tempStr;
			//std::cout << "c " << tempStr << std::endl;
		}
	}

	std::vector<char> vertexUses;
	Vertex3 tempVertNormal = Vertex3();

	for (size_t i = 0; i < tempProperties.vertices.size(); i++)
	{
		vertexUses.clear();
		tempVertNormal = Vertex3();

		for (size_t j = 0; j < tempProperties.indices.size(); j++)
		{
			if (i == tempProperties.indices[j].pointA.vertex)
			{
				tempVertNormal += tempProperties.indices[j].faceNormal;
				vertexUses.push_back('A');
			}
			else if (i == tempProperties.indices[j].pointB.vertex)
			{
				tempVertNormal += tempProperties.indices[j].faceNormal;
				vertexUses.push_back('B');
			}
			else if (i == tempProperties.indices[j].pointC.vertex)
			{
				tempVertNormal += tempProperties.indices[j].faceNormal;
				vertexUses.push_back('C');
			}
		}

		std::cout << "Normal Generated = " << tempVertNormal.x << "/" << tempVertNormal.y << "/" << tempVertNormal.z << std::endl;
		tempVertNormal /= static_cast<float>(vertexUses.size());
		tempProperties.normals.push_back(tempVertNormal);
		std::cout << "Normal Avg Generated = " << tempVertNormal.x << "/" << tempVertNormal.y << "/" << tempVertNormal.z << std::endl;

		for (size_t j = 0; j < vertexUses.size(); j++)
		{
			switch (vertexUses[j])
			{
			case 'A':
				tempProperties.indices[j].pointA.normal = i;
				break;
			case 'B':
				tempProperties.indices[j].pointB.normal = i;
				break;
			case 'C':
				tempProperties.indices[j].pointC.normal = i;
				break;
			}
		}
	}

	inFile.close();
	return tempProperties;
}
// ----------------------------

// ----- Loads .obj files -----
ObjectProperties Loader::LoadOBJ(std::string path)
{
	ObjectProperties tempProperties;

	std::ifstream inFile;
	inFile.open(path);

	int debug = 0;

	if (!inFile.good())
	{
		std::cerr << "Can't Find Model File - " << path << std::endl;
		return tempProperties;
	}

	std::string typeChar;

	while (!inFile.eof())
	{
		typeChar = "NOT SET";
		inFile >> typeChar;

		if (typeChar == "v")
		{
			Vertex3 tempVec = Vertex3();
			inFile >> tempVec.x;
			inFile >> tempVec.y;
			inFile >> tempVec.z;

			tempProperties.vertices.push_back(tempVec);
		}		
		else if (typeChar == "vn")
		{
			Vertex3 tempNor = Vertex3();
			inFile >> tempNor.x;
			inFile >> tempNor.y;
			inFile >> tempNor.z;

			tempProperties.normals.push_back(tempNor);
		}
		else if (typeChar == "vt")
		{

		}
		else if (typeChar == "f")
		{
			std::string faceValues;
			inFile >> faceValues;

			int slashIndex[2] = { 0 };
			slashIndex[0] = faceValues.find_first_of("/");
			slashIndex[1] = faceValues.find_last_of("/");

			FaceDetails faceDetails = FaceDetails();

			faceDetails.pointA.vertex = std::stoi(faceValues.substr(0)) - 1;
			faceDetails.pointA.texture = std::stoi(faceValues.substr(slashIndex[0] + 1, slashIndex[1])) - 1;
			faceDetails.pointA.normal = std::stoi(faceValues.substr(slashIndex[1] + 1)) - 1;

			inFile >> faceValues;

			slashIndex[0] = faceValues.find_first_of("/");
			slashIndex[1] = faceValues.find_last_of("/");

			faceDetails.pointB.vertex = std::stoi(faceValues.substr(0)) - 1;
			faceDetails.pointB.texture = std::stoi(faceValues.substr(slashIndex[0] + 1, slashIndex[1])) - 1;
			faceDetails.pointB.normal = std::stoi(faceValues.substr(slashIndex[1] + 1)) - 1;

			inFile >> faceValues;

			slashIndex[0] = faceValues.find_first_of("/");
			slashIndex[1] = faceValues.find_last_of("/");

			faceDetails.pointC.vertex = std::stoi(faceValues.substr(0)) - 1;
			faceDetails.pointC.texture = std::stoi(faceValues.substr(slashIndex[0] + 1, slashIndex[1])) - 1;
			faceDetails.pointC.normal = std::stoi(faceValues.substr(slashIndex[1] + 1)) - 1;

			tempProperties.indices.push_back(faceDetails);
		}
	}

	inFile.close();
	return tempProperties;
}
// ----------------------------

// ------ Loads .3ds files ------
ObjectProperties Loader::Load3DS(std::string path)
{
	ObjectProperties tempProperties;



	return tempProperties;
}
// ------------------------------

// ----- Gets the cross product of two verteices ----- 
Vertex3 Loader::CrossProduct(Vertex3 vA, Vertex3 vB)
{
	Vertex3 cross = Vertex3();

	cross.x = (vA.y * vB.z) - (vA.z * vB.y);
	cross.y = (vA.z * vB.x) - (vA.x * vB.z);
	cross.z = (vA.x * vB.y) - (vA.y * vB.x);

	return cross;
}
// ---------------------------------------------------