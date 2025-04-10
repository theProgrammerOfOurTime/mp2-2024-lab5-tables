#include <gtest.h>
#include "hashTable.h"
#include "polinom.h"

TEST(hashTable, can_create_hashTable)
{
	ASSERT_NO_THROW(hashTable<polinom> t(1000));
}

TEST(hashTable, cant_insert_empty_item)
{
	hashTable<polinom> t(1000);
	Vector<unsigned char> n1;
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	ASSERT_ANY_THROW(t.insert({ n1, p1 }));
}

TEST(hashTable, can_insert_polynomial)
{
	hashTable<polinom> t(1000);
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	ASSERT_NO_THROW(t.insert({ n1, p1 }));
}

TEST(hashTable, cant_find_in_empty_table)
{
	hashTable<polinom> t(1000);
	Vector<unsigned char> n1("p1");
	EXPECT_EQ(nullptr, t.search(n1));
}

TEST(hashTable, can_find_inserted_polynomial)
{
	hashTable<polinom> t(1000);
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	EXPECT_NE(nullptr, t.search(n1));
}

TEST(hashTable, cant_find_empty_item)
{
	hashTable<polinom> t(1000);
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	Vector<unsigned char> n2;
	EXPECT_EQ(nullptr, t.search(n2));
}

TEST(hashTable, finds_valid_polynomial)
{
	hashTable<polinom> t(1000);
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	EXPECT_EQ(*p1, *t.search(n1));
}

TEST(hashTable, can_erase_polinomial_in_empty_table)
{
	hashTable<polinom> t(1000);
	Vector<unsigned char> n1("p1");
	ASSERT_NO_THROW(t.erase(n1));
}

TEST(hashTable, can_erase_polinomial)
{
	hashTable<polinom> t(1000);
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	ASSERT_NO_THROW(t.erase(n1));
}

TEST(hashTable, cant_find_where_to_delete)
{
	hashTable<polinom> t(1000);
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	t.erase(n1);
	EXPECT_EQ(nullptr, t.search(n1));
}