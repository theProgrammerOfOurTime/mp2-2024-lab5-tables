#pragma once
#include <string>
#include "orderedTable.h"
#include "unOrderedTable.h"
#include "hashTable.h"
#include "ABLtree.h"
#include "polinom.h"

template<class Item>
class orderedTable;

template<class Item>
class unOrderedTable;

template<class Item>
class hashTable;

template<class Item>
class ABLtree;

template<class Item>
class tableLogs
{
private:
	orderedTable<Item>* t1;
	unOrderedTable<Item>* t2;
	hashTable<Item>* t3;
	ABLtree<Item>* t4;
public:
	tableLogs(orderedTable<Item>* t1, unOrderedTable<Item>* t2,
			  hashTable<Item>* t3, ABLtree<Item>* t4) : t1(t1), t2(t2), t3(t3), t4(t4)
	{
		
	}
	void includeLogs(const bool& logs)
	{
		(*t1).includeLogs(logs);
		(*t2).includeLogs(logs);
		(*t3).includeLogs(logs);
		(*t4).includeLogs(logs);
		return;
	}
	size_t getLogsOrderedTable() const
	{
		return (*t1).getCountComparisons();
	}
	size_t getLogsUnOrderedTable() const
	{
		return (*t2).getCountComparisons();
	}
	size_t getLogsHashTable() const
	{
		return (*t3).getCountComparisons();
	}
	size_t getLogstABLTree() const
	{
		return (*t4).getCountComparisons();
	}
	std::string getAllLogs()
	{
		std::string res;
		res += "orderedTable: \t" + std::to_string(getLogsOrderedTable()) + "\n";
		res += "unOrderedTable: " + std::to_string(getLogsUnOrderedTable()) + "\n";
		res += "hashTable \t" + std::to_string(getLogsHashTable()) + "\n";
		res += "ABLTree: \t" + std::to_string(getLogstABLTree()) + "\n";
		return res;
	}
};