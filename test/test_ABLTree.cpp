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

TEST(ABLtree, multiple_insertion)
{
	ABLtree<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	ASSERT_NO_THROW(t.insert({ n1, p1 }));
	Vector<unsigned char> n2("p2");
	std::shared_ptr<polinom> p2(new polinom("4.5 1 3 4"));
	ASSERT_NO_THROW(t.insert({ n2, p2 }));
	Vector<unsigned char> n3("p3");
	std::shared_ptr<polinom> p3(new polinom("5.6 1 2 3"));
	ASSERT_NO_THROW(t.insert({ n3, p3 }));
	Vector<unsigned char> n4("p4");
	std::shared_ptr<polinom> p4(new polinom("1 1 1 1"));
	ASSERT_NO_THROW(t.insert({ n4, p4 }));
	Vector<unsigned char> n5("p5");
	std::shared_ptr<polinom> p5(new polinom("2 2 2 2"));
	ASSERT_NO_THROW(t.insert({ n5, p5 }));
}

TEST(ABLtree, multiple_find)
{
	ABLtree<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	EXPECT_EQ(*p1, *t.search(n1));
	Vector<unsigned char> n2("p2");
	std::shared_ptr<polinom> p2(new polinom("4.5 1 3 4"));
	t.insert({ n2, p2 });
	EXPECT_EQ(*p2, *t.search(n2));
	Vector<unsigned char> n3("p3");
	std::shared_ptr<polinom> p3(new polinom("5.6 1 2 3"));
	t.insert({ n3, p3 });
	EXPECT_EQ(*p3, *t.search(n3));
	Vector<unsigned char> n4("p4");
	std::shared_ptr<polinom> p4(new polinom("1 1 1 1"));
	t.insert({ n4, p4 });
	EXPECT_EQ(*p4, *t.search(n4));
	Vector<unsigned char> n5("p5");
	std::shared_ptr<polinom> p5(new polinom("2 2 2 2"));
	t.insert({ n5, p5 });
	EXPECT_EQ(*p5, *t.search(n5));
}

TEST(ABLtree, multiple_delete)
{
	ABLtree<polinom> t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	Vector<unsigned char> n2("p2");
	std::shared_ptr<polinom> p2(new polinom("4.5 1 3 4"));
	t.insert({ n2, p2 });
	Vector<unsigned char> n3("p3");
	std::shared_ptr<polinom> p3(new polinom("5.6 1 2 3"));
	t.insert({ n3, p3 });
	Vector<unsigned char> n4("p4");
	std::shared_ptr<polinom> p4(new polinom("1 1 1 1"));
	t.insert({ n4, p4 });
	Vector<unsigned char> n5("p5");
	std::shared_ptr<polinom> p5(new polinom("2 2 2 2"));
	t.insert({ n5, p5 });
	ASSERT_NO_THROW(t.erase(n5));
	ASSERT_NO_THROW(t.erase(n2));
	ASSERT_NO_THROW(t.erase(n3));
	ASSERT_NO_THROW(t.erase(n1));
	ASSERT_NO_THROW(t.erase(n4));
}

TEST(ABLtree, test_balance1)
{
	AVLTreeInterface t;
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	Vector<unsigned char> n2("p2");
	std::shared_ptr<polinom> p2(new polinom("4.5 1 3 4"));
	t.insert({ n2, p2 });
	Vector<unsigned char> n3("p3");
	std::shared_ptr<polinom> p3(new polinom("5.6 1 2 3"));
	t.insert({ n3, p3 });
	auto root = t.getRoot();
	EXPECT_EQ(n2, root->key);
	EXPECT_EQ(n1, root->left->key);
	EXPECT_EQ(n3, root->right->key);
}

TEST(ABLtree, test_balance2)
{
	AVLTreeInterface t;
	Vector<unsigned char> n3("p3");
	std::shared_ptr<polinom> p3(new polinom("5.6 1 2 3"));
	t.insert({ n3, p3 });
	Vector<unsigned char> n2("p2");
	std::shared_ptr<polinom> p2(new polinom("4.5 1 3 4"));
	t.insert({ n2, p2 });
	Vector<unsigned char> n1("p1");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	t.insert({ n1, p1 });
	auto root = t.getRoot();
	EXPECT_EQ(n2, root->key);
	EXPECT_EQ(n1, root->left->key);
	EXPECT_EQ(n3, root->right->key);
}