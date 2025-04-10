#pragma once
#include "Vector.h"

class Strcmp
{
private:
	bool logs;
	size_t* countComparisons;
	
public:
	void includeLogs(const bool& logs, size_t* countComparisons);
	Strcmp() : countComparisons(nullptr), logs(0) { }
	int operator()(const Vector<unsigned char>& s1, const Vector<unsigned char>& s2);
};
