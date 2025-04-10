#include <gtest.h>
#include "orderedTable.h"
#include "polinom.h"

TEST(orderedTable, can_create_orderedTable)
{
	ASSERT_NO_THROW(orderedTable<polinom> t);
}

TEST(orderedTable, cant_insert_empty_item)
{
	orderedTable<polinom> t;
	Vector<unsigned char> n1;
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	ASSERT_ANY_THROW(t.insert({ n1, p1 }));
}

TEST(orderedTable, can_insert_polynomial)
{
	orderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	ASSERT_NO_THROW(t.insert({ n1, p1 }));
}

TEST(orderedTable, cant_find_in_empty_table)
{
	orderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	EXPECT_EQ(nullptr, t.search(n1));
}

TEST(orderedTable, can_find_inserted_polynomial)
{
	orderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	EXPECT_NE(nullptr, t.search(n1));
}

TEST(orderedTable, cant_find_empty_item)
{
	orderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	Vector<unsigned char> n2;
	EXPECT_EQ(nullptr, t.search(n2));
}

TEST(orderedTable, finds_valid_polynomial)
{
	orderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	EXPECT_EQ(*p1, *t.search(n1));
}

TEST(orderedTable, can_erase_polinomial_in_empty_table)
{
	orderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	ASSERT_NO_THROW(t.erase(n1));
}

TEST(orderedTable, can_erase_polinomial)
{
	orderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	ASSERT_NO_THROW(t.erase(n1));
}

TEST(orderedTable, cant_find_where_to_delete)
{
	orderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	t.erase(n1);
	EXPECT_EQ(nullptr, t.search(n1));
}