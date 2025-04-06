#pragma once
#include "Vector.h"

class Strcmp
{
private:
	bool logs;
	size_t* count—omparisons;
	
public:
	void includeLogs(const bool& logs, size_t* count—omparisons);
	Strcmp() : count—omparisons(nullptr), logs(0) { }
	int operator()(const Vector<unsigned char>& s1, const Vector<unsigned char>& s2);
};
