#pragma once
#include "Vector.h"
#include "stack.h"
#include "strcmp.h"
#include "queue.h"
#include "tableLogs.h"
#include "polinom.h"

template<class Item>
class ABLtree
{
protected:
	
	struct node
	{
		int16_t height;
		node* left;
		node* right;
		Vector<unsigned char> key;
		std::shared_ptr<Item> data;
		node()
		{
			height = 1;
			left = nullptr;
			right = nullptr;
			key = Vector<unsigned char>();
			data = nullptr;
		}
		node(Vector<unsigned char> key, std::shared_ptr<Item> data) : key(key), data(data)
		{
			height = 1;
			left = nullptr;
			right = nullptr;
		}
	};
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
	int16_t heightNode(node* p)
	{
		if (logs) countComparisons++;
		if (p == nullptr) return 0;
		return p->height;
	}
	node* rotateRight(node* p) //������ ����� �������
	{
		node* t = p->left;
		p->left = t->right;
		t->right = p;
		if (logs) countComparisons++;
		p->height = std::max(heightNode(p->left), heightNode(p->right)) + 1;
		if (logs) countComparisons++;
		t->height = std::max(heightNode(t->left), heightNode(t->right)) + 1;
		return t;
	}
	node* rotateLeft(node* p) //����� ����� �������
	{
		node* t = p->right;
		p->right = t->left;
		t->left = p;
		if (logs) countComparisons++;
		p->height = std::max(heightNode(p->left), heightNode(p->right)) + 1;
		if (logs) countComparisons++;
		t->height = std::max(heightNode(t->left), heightNode(t->right)) + 1;
		return t;
	}
	int16_t diff(node* a)
	{
		if (logs) countComparisons++;
		if (a == nullptr) return 0;
		return heightNode(a->left) - heightNode(a->right);
	}
	node* balance(node* p)
	{
		if (logs) countComparisons++;
		if (p == nullptr) return p;
		if (logs) countComparisons++;
		p->height = std::max(heightNode(p->left), heightNode(p->right)) + 1;
		if (logs) countComparisons +=2;
		if (diff(p) == 2 && diff(p->left) != -1)
		{
			return rotateRight(p);
		}
		if (logs) countComparisons += 2;
		if (diff(p) == -2 && diff(p->right) != 1)
		{
			return rotateLeft(p);
		}
		if (logs) countComparisons += 2;
		if (diff(p) == -2 && diff(p->right) == 1)
		{
			p->right = rotateRight(p->right);
			return rotateLeft(p);
		}
		if (logs) countComparisons += 2;
		if (diff(p) == 2 && diff(p->left) == -1)
		{
			p->left = rotateLeft(p->left);
			return rotateRight(p);
		}
		return p;
	}
	std::shared_ptr<Item> nullItem;
	node* head;
public:
	ABLtree()
	{
		head = nullptr;
		nullItem = nullptr;
		includeLogs(0);
		countComparisons = 0;
		logs = false;
	}
	~ABLtree()
	{
		if (head != nullptr)
		{
			Stack<node*> nodes;
			nodes.push(head);
			while (!nodes.empty())
			{
				node* t = nodes.top();
				nodes.pop();
				if (t->left != nullptr) nodes.push(t->left);
				if (t->right != nullptr) nodes.push(t->right);
				if (logs) countComparisons += 3;
				delete t;
			}
		}
	}
	std::shared_ptr<Item> search(const Vector<unsigned char>& key)
	{
		node* tHead = head;
		while (tHead != nullptr)
		{
			if (logs) countComparisons++;
			int cmp = strcmp(tHead->key, key);
			if (cmp == 0) return tHead->data;
			if (cmp == 1) tHead = tHead->left;
			if (cmp == -1) tHead = tHead->right;
		}
		return nullItem;
	}
	void insert(std::pair<Vector<unsigned char>, std::shared_ptr<Item>> it)
	{
		if (logs) countComparisons++;
		if (it.first.length() == 0) throw std::logic_error("an empty name is not allowed");
		if (logs) countComparisons++;
		if (head == nullptr)
		{
			head = new node(it.first, it.second);
			return;
		}
		node* t = head;
		Stack<std::pair<node*, int>> nodes;
		while (t != nullptr)
		{
			if (logs) countComparisons++;
			int cmp = strcmp(t->key, it.first);
			if (logs) countComparisons++;
			if (cmp == 0) throw std::exception("Already in the tree.");
			if (cmp == 1)
			{
				nodes.push({ t, 0 });
				if (t->left == nullptr)
				{
					t->left = new node(it.first, it.second);
					t = nullptr;
				}
				else t = t->left;
				if (logs) countComparisons++;
			}
			if (cmp == -1)
			{
				nodes.push({ t, 1 });
				if (t->right == nullptr)
				{
					t->right = new node(it.first, it.second);
					t = nullptr;
				}
				else t = t->right;
				if (logs) countComparisons++;
			}
			if (logs) countComparisons += 2;
		}
		while (!nodes.empty())
		{
			t = nodes.top().first;
			if (nodes.top().second) t->right = balance(t->right);
			else t->left = balance(t->left);
			nodes.pop();
			if (logs) countComparisons += 2;
		}
		head = balance(head);
		return;
	}
	void erase(const Vector<unsigned char>& key)
	{
		node* tHead = head, *prevtHead = nullptr;
		Stack<std::pair<node*, int>> nodes;
		while (tHead != nullptr)
		{
			if (logs) countComparisons++;
			int cmp = strcmp(tHead->key, key);
			if (logs) countComparisons++;
			if (cmp == 0) break;
			prevtHead = tHead;
			if (cmp == 1)
			{
				nodes.push({ tHead, 0 });
				tHead = tHead->left;
			}
			if (cmp == -1)
			{
				nodes.push({ tHead, 1 });
				tHead = tHead->right;
			}
			if (logs) countComparisons += 2;
		}
		if (logs) countComparisons++;
		if (tHead == nullptr) return;
		node* curNode = tHead, *parentNode = prevtHead;
		prevtHead = tHead;
		if (logs) countComparisons++;
		if (tHead->right == nullptr)
		{
			if (logs) countComparisons++;
			if (tHead->left != nullptr) tHead = tHead->left;
			else tHead = nullptr;
		}
		else
		{
			tHead = tHead->right;
			while (tHead->left != nullptr)
			{
				if (logs) countComparisons++;
				prevtHead = tHead;
				tHead = tHead->left;
			}
		}
		node* minNode = tHead;
		if (logs) countComparisons++;
		if (minNode != nullptr)
		{
			if (logs) countComparisons++;
			if (prevtHead->left == minNode) prevtHead->left = nullptr;
			else prevtHead->right = nullptr;
			std::swap(minNode->data, curNode->data);
			std::swap(minNode->key, curNode->key);
			if (logs) countComparisons += 2;
			delete minNode;
		}
		else
		{
			if (logs) countComparisons += 2;
			if(parentNode != nullptr && parentNode->right == curNode) parentNode->right = nullptr;
		    else if (parentNode != nullptr && parentNode->left == curNode) parentNode->left = nullptr;
			delete curNode;
			curNode = nullptr;
		}
		if (logs) countComparisons++;
		if (parentNode != nullptr && parentNode->right == curNode) parentNode->right = balance(curNode);
		else if (parentNode != nullptr && parentNode->left == curNode) parentNode->left = balance(curNode);
		else head = balance(curNode);
		while (!nodes.empty())
		{
			tHead = nodes.top().first;
			if (nodes.top().second) tHead->right = balance(tHead->right);
			else tHead->left = balance(tHead->left);
			nodes.pop();
			if (logs) countComparisons++;
		}
		head = balance(head);
		return;
	}
	template<class Item> friend class tableLogs;
};

class AVLTreeInterface : public ABLtree<polinom>
{
public:
	node* getRoot() const noexcept
	{
		return head;
	}
};