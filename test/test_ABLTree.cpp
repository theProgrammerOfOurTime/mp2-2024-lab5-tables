#include <gtest.h>
#include "ABLtree.h"
#include "polinom.h"

TEST(ABLtree, can_create_ABLtree)
{
	ASSERT_NO_THROW(ABLtree<polinom> t);
}

TEST(ABLtree, cant_insert_empty_item)
{
	ABLtree<polinom> t;
	Vector<unsigned char> n1;
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	ASSERT_ANY_THROW(t.insert({ n1, p1 }));
}

TEST(ABLtree, can_insert_polynomial)
{
	ABLtree<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	ASSERT_NO_THROW(t.insert({ n1, p1 }));
}

TEST(ABLtree, cant_find_in_empty_table)
{
	ABLtree<polinom> t;
	Vector<unsigned char> n1("p1");
	EXPECT_EQ(nullptr, t.search(n1));
}

TEST(ABLtree, can_find_inserted_polynomial)
{
	ABLtree<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	EXPECT_NE(nullptr, t.search(n1));
}

TEST(ABLtree, cant_find_empty_item)
{
	ABLtree<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	Vector<unsigned char> n2;
	EXPECT_EQ(nullptr, t.search(n2));
}

TEST(ABLtree, finds_valid_polynomial)
{
	ABLtree<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	EXPECT_EQ(*p1, *t.search(n1));
}

TEST(ABLtree, can_erase_polinomial_in_empty_table)
{
	ABLtree<polinom> t;
	Vector<unsigned char> n1("p1");
	ASSERT_NO_THROW(t.erase(n1));
}

TEST(ABLtree, can_erase_polinomial)
{
	ABLtree<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	ASSERT_NO_THROW(t.erase(n1));
}

TEST(ABLtree, cant_find_where_to_delete)
{
	ABLtree<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	t.erase(n1);
	EXPECT_EQ(nullptr, t.search(n1));
}