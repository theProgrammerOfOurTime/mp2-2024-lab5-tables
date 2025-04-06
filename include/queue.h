#pragma once

#include "stack.h"

template <class T>
class Queue
{
private:
	Stack<T> s1, s2;
	void check()
	{
		if (s2.empty())
		{
			while (!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
		}
		return;
	}

public:
	Queue() { }
	Queue(const Queue& s) = delete;
	~Queue() { }
	size_t length() const noexcept
	{
		return s1.length() + s2.length();
	}
	void clear()
	{
		s1.clear();
		s2.clear();
		return;
	}
	void push(const T& item)
	{
		s1.push(item);
		return;
	}
	T& front()
	{
		check();
		return s2.top();
	}
	void pop()
	{
		check();
		s2.pop();
		return;
	}
	bool empty() const noexcept
	{
		return s1.empty() && s2.empty();
	}
};