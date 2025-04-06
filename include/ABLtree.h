#pragma once
#include "Vector.h"
#include "stack.h"
#include "strcmp.h"
#include "queue.h"
#include "tableLogs.h"

template<class Item>
class ABLtree
{
private:
	
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
	int16_t heightNode(node* p)
	{
		if (logs) count—omparisons++;
		if (p == nullptr) return 0;
		return p->height;
	}
	node* rotateRight(node* p) //Ô‡‚˚È Ï‡Î˚È ÔÓ‚ÓÓÚ
	{
		node* t = p->left;
		p->left = t->right;
		t->right = p;
		if (logs) count—omparisons++;
		p->height = std::max(heightNode(p->left), heightNode(p->right)) + 1;
		if (logs) count—omparisons++;
		t->height = std::max(heightNode(t->left), heightNode(t->right)) + 1;
		return t;
	}
	node* rotateLeft(node* p) //ÎÂ‚˚È Ï‡Î˚È ÔÓ‚ÓÓÚ
	{
		node* t = p->right;
		p->right = t->left;
		t->left = p;
		if (logs) count—omparisons++;
		p->height = std::max(heightNode(p->left), heightNode(p->right)) + 1;
		if (logs) count—omparisons++;
		t->height = std::max(heightNode(t->left), heightNode(t->right)) + 1;
		return t;
	}
	int16_t diff(node* a)
	{
		if (logs) count—omparisons++;
		if (a == nullptr) return 0;
		return heightNode(a->left) - heightNode(a->right);
	}
	node* balance(node* p)
	{
		if (logs) count—omparisons++;
		if (p == nullptr) return p;
		if (logs) count—omparisons++;
		p->height = std::max(heightNode(p->left), heightNode(p->right)) + 1;
		if (logs) count—omparisons +=2;
		if (diff(p) == 2 && diff(p->left) != -1)
		{
			return rotateRight(p);
		}
		if (logs) count—omparisons += 2;
		if (diff(p) == -2 && diff(p->right) != 1)
		{
			return rotateLeft(p);
		}
		if (logs) count—omparisons += 2;
		if (diff(p) == -2 && diff(p->right) == 1)
		{
			p->right = rotateRight(p->right);
			return rotateLeft(p);
		}
		if (logs) count—omparisons += 2;
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
		count—omparisons = 0;
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
				if (logs) count—omparisons += 3;
				delete t;
			}
		}
	}
	std::shared_ptr<Item> search(const Vector<unsigned char>& key)
	{
		node* tHead = head;
		while (tHead != nullptr)
		{
			if (logs) count—omparisons++;
			int cmp = strcmp(tHead->key, key);
			if (cmp == 0) return tHead->data;
			if (cmp == 1) tHead = tHead->left;
			if (cmp == -1) tHead = tHead->right;
		}
		return nullItem;
	}
	void insert(std::pair<Vector<unsigned char>, std::shared_ptr<Item>> it)
	{
		if (logs) count—omparisons++;
		if (head == nullptr)
		{
			head = new node(it.first, it.second);
			return;
		}
		node* t = head;
		Stack<std::pair<node*, int>> nodes;
		while (t != nullptr)
		{
			if (logs) count—omparisons++;
			int cmp = strcmp(t->key, it.first);
			if (logs) count—omparisons++;
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
				if (logs) count—omparisons++;
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
				if (logs) count—omparisons++;
			}
			if (logs) count—omparisons += 2;
		}
		while (!nodes.empty())
		{
			t = nodes.top().first;
			if (nodes.top().second) t->right = balance(t->right);
			else t->left = balance(t->left);
			nodes.pop();
			if (logs) count—omparisons += 2;
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
			if (logs) count—omparisons++;
			int cmp = strcmp(tHead->key, key);
			if (logs) count—omparisons++;
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
			if (logs) count—omparisons += 2;
		}
		if (logs) count—omparisons++;
		if (tHead == nullptr) return;
		node* curNode = tHead, *parentNode = prevtHead;
		prevtHead = tHead;
		if (logs) count—omparisons++;
		if (tHead->right == nullptr)
		{
			if (logs) count—omparisons++;
			if (tHead->left != nullptr) tHead = tHead->left;
			else tHead = nullptr;
		}
		else
		{
			tHead = tHead->right;
			while (tHead->left != nullptr)
			{
				if (logs) count—omparisons++;
				prevtHead = tHead;
				tHead = tHead->left;
			}
		}
		node* minNode = tHead;
		if (logs) count—omparisons++;
		if (minNode != nullptr)
		{
			if (logs) count—omparisons++;
			if (prevtHead->left == minNode) prevtHead->left = nullptr;
			else prevtHead->right = nullptr;
			std::swap(minNode->data, curNode->data);
			std::swap(minNode->key, curNode->key);
			if (logs) count—omparisons += 2;
			delete minNode;
		}
		else
		{
			if (logs) count—omparisons += 2;
			if(parentNode != nullptr && parentNode->right == curNode) parentNode->right = nullptr;
		    else if (parentNode != nullptr && parentNode->left == curNode) parentNode->left = nullptr;
			delete curNode;
			curNode = nullptr;
		}
		if (logs) count—omparisons++;
		if (parentNode != nullptr && parentNode->right == curNode) parentNode->right = balance(curNode);
		else if (parentNode != nullptr && parentNode->left == curNode) parentNode->left = balance(curNode);
		else head = balance(curNode);
		while (!nodes.empty())
		{
			tHead = nodes.top().first;
			if (nodes.top().second) tHead->right = balance(tHead->right);
			else tHead->left = balance(tHead->left);
			nodes.pop();
			if (logs) count—omparisons++;
		}
		head = balance(head);
		return;
	}
	/*void printTree()
	{
		if (head == nullptr) return;
		Queue<std::pair<node*, int>> nodes;
		nodes.push({ head, 0 });
		int curH = 0;
		std::cout << curH << " ";
		while (!nodes.empty())
		{
			std::pair<node*, int > t1 = nodes.front();
			node* t = t1.first;
			nodes.pop();
			if (curH != t1.second)
			{
				curH = t1.second;
				std::cout << std::endl << curH << " ";
			}
			for (int i = 0; i < t->key.length(); i++)
			{
				std::cout << t->key[i];
			}
			std::cout << " " << diff(t) << " ";
			if (t->left != nullptr) nodes.push({ t->left, curH + 1 } );
			if (t->right != nullptr) nodes.push({ t->right, curH + 1 });
		}
		return;
	}*/
	
	template<class Item> friend class tableLogs;
};