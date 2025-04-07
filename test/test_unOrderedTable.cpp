#include <gtest.h>
#include "unOrderedTable.h"
#include "polinom.h"

TEST(unOrderedTable, can_create_unOrderedTable)
{
	ASSERT_NO_THROW(unOrderedTable<polinom> t);
}

TEST(unOrderedTable, cant_insert_empty_item)
{
	unOrderedTable<polinom> t;
	Vector<unsigned char> n1;
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	ASSERT_ANY_THROW(t.insert({ n1, p1 }));
}

TEST(unOrderedTable, can_insert_polynomial)
{
	unOrderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	ASSERT_NO_THROW(t.insert({ n1, p1 }));
}

TEST(unOrderedTable, cant_find_in_empty_table)
{
	unOrderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	EXPECT_EQ(nullptr, t.search(n1));
}

TEST(unOrderedTable, can_find_inserted_polynomial)
{
	unOrderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	EXPECT_NE(nullptr, t.search(n1));
}

TEST(unOrderedTable, cant_find_empty_item)
{
	unOrderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	Vector<unsigned char> n2;
	EXPECT_EQ(nullptr, t.search(n2));
}

TEST(unOrderedTable, finds_valid_polynomial)
{
	unOrderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	
	EXPECT_EQ(*p1, *t.search(n1));
}

TEST(unOrderedTable, can_erase_polinomial_in_empty_table)
{
	unOrderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	ASSERT_NO_THROW(t.erase(n1));
}

TEST(unOrderedTable, can_erase_polinomial)
{
	unOrderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	ASSERT_NO_THROW(t.erase(n1));
}

TEST(unOrderedTable, cant_find_where_to_delete)
{
	unOrderedTable<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	t.erase(n1);
	EXPECT_EQ(nullptr, t.search(n1));
}