#pragma once

#include "Vector"
#include "strcmp.h"
#include "tableLogs.h"

template<class Item>
class unOrderedTable
{
private:
	Vector<std::pair<Vector<unsigned char>, std::shared_ptr<Item>>> table;
	std::shared_ptr<Item> nullItem;
	Strcmp strcmp;
	bool logs;
	size_t countComparisons;
	void includeLogs(const bool& logs)
	{
		this->logs = logs;
		strcmp.includeLogs(logs, &countComparisons);
		return;
	}
	size_t getCountComparisons() noexcept
	{
		size_t res = countComparisons;
		countComparisons = 0;
		return res;
	}

public:
	unOrderedTable()
	{
		nullItem = nullptr;
		includeLogs(0);
		countComparisons = 0;
		logs = false;
	}
	~unOrderedTable() { }
	std::shared_ptr<Item> search(const Vector<unsigned char>& key)
	{
		for (size_t i = 0; i < table.length(); i++)
		{
			if (logs) countComparisons++;
			if (strcmp(table[i].first, key) == 0) return table[i].second;
		}
		return nullItem;
	}
	void insert(std::pair<Vector<unsigned char>, std::shared_ptr<Item>> it)
	{	
		if (logs) countComparisons++;
		if (it.first.length() == 0) throw std::logic_error("an empty name is not allowed");
		table.push_back(it);
		return;
	}
	void erase(const Vector<unsigned char>& key)
	{
		for (size_t i = 0; i < table.length(); i++)
		{
			if (logs) countComparisons++;
			if (strcmp(table[i].first, key) == 0)
			{
				std::swap(table[i], table[table.length() - 1]);
				table[table.length() - 1].second = nullItem;
				if (logs) countComparisons++;
				table.pop_back();
				return;
			}
		}
		return;
	}
	template <class Item> friend class tableLogs;
};