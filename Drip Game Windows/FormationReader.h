#pragma once
// TODO: Get rid of this class, it's really pointless!!!
class FormationReader
{
public:
	static int readInt32(unsigned char temp[4]);		// Convert a char[4] array into an Int32
	static float readSingle(unsigned char temp[4]);		// Convert a char[4] array into a float
};

