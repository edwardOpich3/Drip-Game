#include "FormationReader.h"

int FormationReader::readInt32(unsigned char temp[])
{
	return *reinterpret_cast<int*>(temp);
}

float FormationReader::readSingle(unsigned char temp[])
{
	return *reinterpret_cast<float*>(temp);
}
