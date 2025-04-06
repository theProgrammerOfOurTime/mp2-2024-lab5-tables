#include <gtest.h>
#include "polinom.h"

TEST(polinom, can_create_polinom)
{
	ASSERT_NO_THROW(polinom p);
}

TEST(polinom, can_create_copied_polinom)
{
	polinom p;
	ASSERT_NO_THROW(polinom p1(p));
}

TEST(polinom, the_zero_polinom_is_zero)
{
	polinom p;
	std::string s;
	std::ostringstream oss;
	oss << p;
	EXPECT_EQ("0", oss.str());
}

TEST(polinom, can_read_and_write_the_polinom)
{
	polinom p;
	std::istringstream iss;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	std::ostringstream oss;
	oss << p;
	EXPECT_EQ("5.6 * x^1 * y^2 * z^3 + 4.5 * x^1 * y^3 * z^4", oss.str());
}

TEST(polinom, the_copied_polinom_is_equal_to_the_initial_one1)
{
	polinom p;
	std::istringstream iss;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	polinom p1(p);
	std::ostringstream oss1, oss2;
	oss1 << p;
	oss2 << p1;
	EXPECT_EQ(oss1.str(), oss2.str());
}

TEST(polinom, the_copied_polinom_is_equal_to_the_initial_one2)
{
	polinom p;
	std::istringstream iss;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	polinom p1;
	p1 = p;
	std::ostringstream oss1, oss2;
	oss1 << p;
	oss2 << p1;
	EXPECT_EQ(oss1.str(), oss2.str());
}

TEST(polinom, can_add_polinom)
{
	polinom p;
	std::istringstream iss;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	polinom p1(p);
	ASSERT_NO_THROW(p1 + p);
}

TEST(polinom, add_the_polinom_correctly)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	polinom p1;
	iss1.str("4.5 1 3 3 5.6 1 2 3");
	iss1 >> p1;
	p = p + p1;
	std::ostringstream oss;
	oss << p;
	EXPECT_EQ("11.2 * x^1 * y^2 * z^3 + 4.5 * x^1 * y^3 * z^3 + 4.5 * x^1 * y^3 * z^4", oss.str());
}

TEST(polinom, can_sub_polinom)
{
	polinom p;
	std::istringstream iss;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	polinom p1(p);
	ASSERT_NO_THROW(p1 - p);
}

TEST(polinom, sub_the_polinom_correctly)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	polinom p1;
	iss1.str("4.5 1 3 3 5.6 1 2 3");
	iss1 >> p1;
	p = p - p1;
	std::ostringstream oss;
	oss << p;
	EXPECT_EQ("-4.5 * x^1 * y^3 * z^3 + 4.5 * x^1 * y^3 * z^4", oss.str());
}

TEST(polinom, can_mult_polinom)
{
	polinom p;
	std::istringstream iss;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	polinom p1(p);
	ASSERT_NO_THROW(p1 * p);
}

TEST(polinom, mult_the_polinom_correctly1)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	polinom p1;
	iss1.str("4.5 1 3 3 5.6 1 2 3");
	iss1 >> p1;
	p = p * p1;
	std::ostringstream oss;
	oss << p;
	EXPECT_EQ("31.36 * x^2 * y^4 * z^6 + 25.2 * x^2 * y^5 * z^6 + 25.2 * x^2 * y^5 * z^7 + 20.25 * x^2 * y^6 * z^7", oss.str());
}

TEST(polinom, mult_the_polinom_correctly2)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	polinom p1;
	p = p * p1;
	std::ostringstream oss;
	oss << p;
	EXPECT_EQ("0", oss.str());
}

TEST(polinom, can_mult_on_const_polinom)
{
	polinom p;
	std::istringstream iss;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	ASSERT_NO_THROW(p * 2.0);
}

TEST(polinom, mult_on_const_the_polinom_correctly1)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	p = p * 2.0;
	std::ostringstream oss;
	oss << p;
	EXPECT_EQ("11.2 * x^1 * y^2 * z^3 + 9 * x^1 * y^3 * z^4", oss.str());
}
TEST(polinom, mult_on_const_the_polinom_correctly2)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	p = p * 0.0;
	std::ostringstream oss;
	oss << p;
	EXPECT_EQ("0", oss.str());
}

TEST(polinom, can_calc_in_point_polinom)
{
	polinom p;
	std::istringstream iss;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	ASSERT_NO_THROW(p.calc(3.4, 4.6, 1.3));
}

TEST(polinom, calc_in_point_the_polinom_correctly1)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	EXPECT_EQ(std::abs(5138.562069 - p.calc(3.4, 4.6, 1.3)) < 1e-6, 1);
}

TEST(polinom, calc_in_point_the_polinom_correctly2)
{
	polinom p;
	EXPECT_EQ(std::abs(0.0 - p.calc(3.4, 4.6, 1.3)) < 1e-14, 1);
}

TEST(polinom, the_difference_of_equal_polynomials_is_zero)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	polinom p1;
	iss1.str("4.5 1 3 4 5.6 1 2 3");
	iss1 >> p1;
	p = p - p1;
	std::ostringstream oss;
	oss << p;
	EXPECT_EQ("0", oss.str());
}

TEST(polinom, the_add_of_equal_polynomials_is_zero)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 3 4 5.6 1 2 3");
	iss >> p;
	polinom p1;
	iss1.str("-4.5 1 3 4 -5.6 1 2 3");
	iss1 >> p1;
	p = p + p1;
	std::ostringstream oss;
	oss << p;
	EXPECT_EQ("0", oss.str());
}

TEST(polinom, entering_a_polynomial_of_degree_greater_than_ten_is_an_error)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 10 4 5.6 1 2 3");
	ASSERT_ANY_THROW(iss >> p);
}

TEST(polinom, cannot_enter_polynomial_with_negative_degree)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 -1 4 5.6 1 2 3");
	ASSERT_ANY_THROW(iss >> p);
}

TEST(polinom, error_when_multiplying_polynomials_of_large_degree)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 3 5 5.6 1 2 3");
	iss >> p;
	polinom p1;
	iss1.str("4.5 1 3 5 5.6 1 2 3");
	iss1 >> p1;
	ASSERT_ANY_THROW(p * p1);
}

TEST(polinom, incorrect_input_error1)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 5 5.6 1 2 3");
	ASSERT_ANY_THROW(iss >> p);
}

TEST(polinom, incorrect_input_error2)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 5 5.3 5.6 1 2 3");
	ASSERT_ANY_THROW(iss >> p);
}

TEST(polinom, incorrect_input_error3)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("a b c d");
	ASSERT_ANY_THROW(iss >> p);
}

TEST(polinom, reentering_the_polynomial_is_correct)
{
	polinom p;
	std::istringstream iss, iss1;
	iss.str("4.5 1 3 5 5.6 1 2 3");
	iss >> p;
	iss1.str("6 2 3 5");
	iss1 >> p;
	std::ostringstream oss;
	oss << p;
	EXPECT_EQ("6 * x^2 * y^3 * z^5", oss.str());
}

