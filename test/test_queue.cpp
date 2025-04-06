#include <gtest.h>
#include "Queue.h"

TEST(Queue, can_create_Queue)
{
	ASSERT_NO_THROW(Queue<int> q);
}

TEST(Queue, can_push)
{
	Queue<int> q;
	for (int i = 0; i < 100; i++)
	{
		ASSERT_NO_THROW(q.push(i));
	}
}

TEST(Queue, can_get_size)
{
	Queue<int> q;
	for (int i = 0; i < 10; i++)
	{
		q.push(i);
	}
	EXPECT_EQ(10, q.length());
}

TEST(Queue, can_set_and_get_element)
{
	Queue<int> q;
	for (int i = 0; i < 10; i++)
	{
		q.push(i);
	}
	q.front() = 4;
	EXPECT_EQ(4, q.front());
}

TEST(Queue, check_pushed_items)
{
	Queue<int> q;
	for (int i = 0; i < 100; i++)
	{
		q.push(i);
	}
	for (int i = 99; i >= 0; i--)
	{
		int item = q.front();
		q.pop();
		EXPECT_EQ(99 - i, item);
	}
}

TEST(Queue, can_pop)
{
	Queue<int> q;
	for (int i = 0; i < 100; i++)
	{
		q.push(i);
	}
	q.pop();
	EXPECT_EQ(99, q.length());
}

TEST(Queue, can_clear)
{
	Queue<int> q;
	for (int i = 0; i < 100; i++)
	{
		q.push(i);
	}
	ASSERT_NO_THROW(q.clear());
}

TEST(Queue, check_length_after_clear)
{
	Queue<int> q;
	for (int i = 0; i < 100; i++)
	{
		q.push(i);
	}
	q.clear();
	EXPECT_EQ(0, q.length());
}