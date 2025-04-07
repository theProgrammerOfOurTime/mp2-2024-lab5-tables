#pragma once

#include "Vector"
#include "strcmp.h"
#include "tableLogs.h"

template<class Item>
class orderedTable
{
private:
	Vector<std::pair<Vector<unsigned char>, std::shared_ptr<Item>>> table;
	std::shared_ptr<Item> nullItem;
	Strcmp strcmp;
	bool logs;
	size_t count—omparisons;
	void includeLogs(const bool& logs)
	{
		this->logs = logs;
		strcmp.includeLogs(logs, &count—omparisons);
		return;
	}
	size_t getCount—omparisons() noexcept
	{
		size_t res = count—omparisons;
		count—omparisons = 0;
		return res;
	}
public:
	orderedTable()
	{
		nullItem = nullptr;
		includeLogs(0);
		count—omparisons = 0;
	}
	~orderedTable()
	{
		
	}
	std::shared_ptr<Item> search(const Vector<unsigned char>& key)
	{
		int l = 0, r = table.length() - 1;
		while (l <= r)
		{
			if (logs) count—omparisons++;
			int c = l + (r - l) / 2;
			if (strcmp(table[c].first, key) == 0) return table[c].second;
			if (strcmp(table[c].first, key) == 1) r = c - 1;
			else if (strcmp(table[c].first, key) == -1) l = c + 1;
		}
		return nullItem;
	}
	void insert(std::pair<Vector<unsigned char>, std::shared_ptr<Item>> it)
	{
		if (logs) count—omparisons++;
		if(it.first.length() == 0) throw std::logic_error("an empty name is not allowed");
		table.push_back(it);
		int i = table.length() - 1;
		while (i > 0 && strcmp(table[i - 1].first, it.first) == 1)
		{
			swap(table[i], table[i - 1]);
			if (logs) count—omparisons += 3;
			i--;
		}
		return;
	}
	void erase(const Vector<unsigned char>& key)
	{
		if (logs) count—omparisons += 1;
		if (search(key) == nullptr) return;
		std::pair<Vector<unsigned char>, std::shared_ptr<Item>> it;
		it = table.back();
		table.pop_back();
		int i = table.length() - 1;
		while (strcmp(it.first, key) != 0)
		{
			swap(it, table[i]);
			if (logs) count—omparisons += 2;
			i--;
		}
		return;
	}
	template <class Item> friend class tableLogs;
};