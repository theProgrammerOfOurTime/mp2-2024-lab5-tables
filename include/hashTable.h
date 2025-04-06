#pragma once
#include "Vector"
#include "strcmp.h"
#include "tableLogs.h"

template<class Item>
class hashTable
{
private:
	Vector<std::pair<Vector<unsigned char>, std::shared_ptr<Item>>> table;
	Vector<int8_t> states; //1 - ���������, 0 - �����, -1 - �������
	std::shared_ptr<Item> nullItem;
	const uint32_t p;
	Strcmp strcmp;
	bool logs;
	size_t count�omparisons;

	uint32_t murmurHash(const Vector<unsigned char>& key)
	{
		uint32_t m = 0x5bd1e995;
		uint32_t r = 24;
		uint32_t seed = 0;
		uint32_t k, i = 0;
		uint32_t len = key.length();
		uint32_t hash = seed ^ len;
		while (len >= 4)
		{
			if (logs) count�omparisons++;
			k = key[i];
			k |= key[i + 1] << 8;
			k |= key[i + 2] << 16;
			k |= key[i + 3] << 24;
			k *= m;
			k ^= k >> r;
			k *= m;//���������
			hash *= m;
			hash ^= k;
			i += 4;
			len -= 4;
		}
		switch (len)
		{
		case 3:
			hash ^= key[i + 2] << 16;
		case 2:
			hash ^= key[i + 1] << 16;
		case 1:
			hash ^= key[i];
			hash *= r;
		}
		hash ^= hash >> 13;
		hash *= m;
		hash ^= hash >> 15;
		return hash;
	}
	
	void includeLogs(const bool& logs)
	{
		this->logs = logs;
		strcmp.includeLogs(logs, &count�omparisons);
		return;
	}
	size_t getCount�omparisons() noexcept
	{
		size_t res = count�omparisons;
		count�omparisons = 0;
		return res;
	}

public:
	hashTable(size_t n) : table(n), states(n, 0), p(1)
	{
		nullItem = nullptr;
		includeLogs(0);
		count�omparisons = 0;
	}
	~hashTable() { }
	std::shared_ptr<Item> search(const Vector<unsigned char>& key)
	{
		uint32_t hash = murmurHash(key) % table.length();
		for (int i = 0; i < table.length(); i++)
		{
			if (logs) count�omparisons += 2;
			if (states[hash] == 0) return nullItem;
			if (logs) count�omparisons += 2;
			if (states[hash] == 1 && strcmp(table[hash].first, key) == 0) return table[hash].second;
			hash = (hash + i * p) % table.length();
		}
		return nullItem;
	}
	void insert(std::pair<Vector<unsigned char>, std::shared_ptr<Item>> it)
	{
		uint32_t hash = murmurHash(it.first) % table.length();
		for (int i = 0; i < table.length(); i++)
		{
			if (logs) count�omparisons += 2;
			if (states[hash] <= 0)
			{
				table[hash] = it;
				states[hash] = 1;
				return;
			}
			else if (states[hash] == 1 && strcmp(table[hash].first, it.first) == 0)
			{
				if (logs) count�omparisons += 2;
				throw std::exception("Already in the table.");
			}
			hash = (hash + i * p) % table.length();
		}
		throw std::exception("Table is full");
	}
	void erase(const Vector<unsigned char>& key)
	{
		uint32_t hash = murmurHash(key) % table.length();
		for (int i = 0; i < table.length(); i++)
		{
			if (logs) count�omparisons += 3;
			if (states[hash] == 1 && strcmp(table[hash].first, key) == 0)
			{
				states[hash] = -1;
				return;
			}
			if (logs) count�omparisons += 1;
			if (states[hash] == 0) return;
			hash = (hash + i * p) % table.length();
		}
		return;
	}
	
	template <class Item> friend class tableLogs;
};