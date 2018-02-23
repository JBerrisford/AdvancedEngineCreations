#ifndef _LOADER_H
#define _LOADER_H

#include "Commons.h"

class Loader
{
public:
	ObjectProperties FindFileType(std::string path);
	
private:
	ObjectProperties LoadTXT(std::string path);
	ObjectProperties LoadOBJ(std::string path);
	ObjectProperties Load3DS(std::string path);
	Vertex3 CrossProduct(Vertex3 vA, Vertex3 vB);
};


#endif //_LOADER_H
