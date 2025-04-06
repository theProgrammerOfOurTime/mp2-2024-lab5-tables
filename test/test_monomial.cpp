#include <gtest.h>
#include "listMonomial.h"

TEST(Monomial, can_create_Monomial1)
{
	ASSERT_NO_THROW(Monomial m);
}

TEST(Monomial, can_create_Monomial2)
{
	ASSERT_NO_THROW(Monomial m({ 0, 0.0 }));
}

TEST(Monomial, cheak_created_Monomial)
{
	Monomial m({ 5, -5.7 });
	EXPECT_EQ(5, m.data.first);
	EXPECT_EQ(std::abs( - 5.7 - m.data.second) < 1e-14, 1);
}

TEST(listMonomial, can_create_listMonomial1)
{
	ASSERT_NO_THROW(listMonomial l);
}

TEST(listMonomial, can_create_listMonomial2)
{
	ASSERT_NO_THROW(listMonomial l(Monomial()));
}

TEST(listMonomial, cheak_created_listMonomial)
{
	listMonomial l(Monomial({ 5, -5.7 }));
	EXPECT_EQ(5, l.monomial.data.first);
	EXPECT_EQ(std::abs(-5.7 - l.monomial.data.second) < 1e-14, 1);
}