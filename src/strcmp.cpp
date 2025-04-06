#include "strcmp.h"

void Strcmp::includeLogs(const bool& logs, size_t* count�omparisons)
{
	this->logs = logs;
	if (logs) this->count�omparisons = count�omparisons;
	else count�omparisons = nullptr;
	return;
}

int Strcmp::operator()(const Vector<unsigned char>& s1, const Vector<unsigned char>& s2)
{
	if (logs) (*count�omparisons)++;
	if (s1.length() > s2.length()) return 1;
	if (logs) (*count�omparisons)++;
	if (s1.length() < s2.length()) return -1;
	for (size_t i = 0; i < s1.length(); i++)
	{
		if (logs) (*count�omparisons) += 2;
		if (s1[i] > s2[i]) return 1;
		if (logs) (*count�omparisons)++;
		if (s1[i] < s2[i]) return -1;
	}
	return 0;
}
