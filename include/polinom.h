#pragma once
#include "listMonomial.h"

class polinom
{
private:
	listMonomial* head;
	listMonomial* merge(listMonomial* t1, listMonomial* t2);
	double ToOperand(const std::string& str);
	void countSort();
	void mergeSort();

public:
	polinom();
	polinom(const char* str);
	polinom(const std::string& str);
	polinom(const polinom& p);
	polinom(polinom&& p);
	~polinom();

	void initPolinom(const std::string& str);
	polinom operator+(const polinom& p) const;
	polinom operator-(const polinom& p) const;
	polinom operator*(const double& alpha) const;
	polinom operator*(const polinom& p) const;

	double calc(const double& x, const double& y, const double& z);

	polinom& operator=(const polinom& p);
	polinom& operator=(polinom&& p);

	friend std::istream& operator>> (std::istream& s, polinom& p);
	friend std::ostream& operator<< (std::ostream& s, const polinom& p);
};