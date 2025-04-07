#include "polinom.h"
#include "queue.h"
#include "Vector.h"
#include <string>
#include <sstream>

listMonomial* polinom::merge(listMonomial* t1, listMonomial* t2)
{
	listMonomial tmp(Monomial({ 0, 0.0 }));
	listMonomial* res = &tmp, *tres = res;
	while (t1 != nullptr && t2 != nullptr)
	{
		if (t1->monomial.data.first < t2->monomial.data.first)
		{
			tres->next = t1;
			t1 = t1->next;
		}
		else
		{
			tres->next = t2;
			t2 = t2->next;
		}
		tres = tres->next;
	}
	if (t1 == nullptr) tres->next = t2;
	else tres->next = t1;
	return res->next;
}

//коэффиценты при равных степенях складываются
void polinom::countSort()
{
	Vector<double> coefs(1000, 0.0);// макс степень 999
	listMonomial* t = head;
	while (head != nullptr)
	{
		coefs[head->monomial.data.first] += head->monomial.data.second;
		head = head->next;
	}
	head = t;
	for (int i = 0; i < 1000; i++)
	{
		if (abs(coefs[i]) > 1e-14)
		{
			t = t->next;
			t->monomial = Monomial({ i , coefs[i] });
		}
	}
	t = t->next;
	listMonomial* t2 = t;
	while (t != nullptr) //количество мнономов невозрастает
	{
		t2 = t;
		t = t->next;
		delete t2;
	}
	return;
}

void polinom::mergeSort()
{
	if (head->next == nullptr) return;
	Queue<listMonomial*> q;
	for (listMonomial* t = nullptr; head != nullptr; head = t)
	{
		t = head->next;
		head->next = nullptr;
		q.push(head);
	}
	head = q.front();
	q.pop();
	while (!q.empty())
	{
		q.push(head);
		listMonomial* t1 = q.front();
		q.pop();
		listMonomial* t2 = q.front();
		q.pop();
		head = merge(t1, t2);
	}
	return;
}

polinom::polinom()
{
	head = new listMonomial();
}

polinom::polinom(const char* str)
{
	head = new listMonomial();
	initPolinom(std::string(str));
}

polinom::polinom(const std::string& str)
{
	head = new listMonomial();
	initPolinom(str);
}

polinom::polinom(const polinom& p)
{
	head = new listMonomial();
	listMonomial* thead1 = p.head->next, *thead2 = head;
	while (thead1 != nullptr)
	{
		thead2->next = new listMonomial(Monomial({ thead1->monomial.data.first , thead1->monomial.data.second }));
		thead1 = thead1->next;
		thead2 = thead2->next;
	}
}

polinom::polinom(polinom&& p)
{
	std::swap(head, p.head);
}

polinom::~polinom()
{
	listMonomial* t = head;
	while (head != nullptr)
	{
		head = head->next;
		delete t;
		t = head;
	}
}

void polinom::initPolinom(const std::string& str)
{
	Vector<double> vals;
	for (int i = 0; i < str.size(); i++)
	{
		bool coef = false;
		if (str[i] == '-' && i + 1 < str.size())
		{
			if (!(str[i + 1] == '.' || (str[i + 1] >= '0' && str[i + 1] <= '9')))
			{
				throw std::exception("invalid character");
			}
			else
			{
				coef = true;
				i++;
			}
		}
		if (str[i] == '.' || (str[i] >= '0' && str[i] <= '9'))
		{
			size_t lenLex = 0;
			while (i != str.size() && str[i] != ' ')
			{
				lenLex++;
				i++;
			}
			i -= lenLex;
			std::string val = str.substr(i, lenLex);
			vals.push_back(ToOperand(val));
			i += lenLex - 1;
		}
		else if (str[i] != ' ')
		{
			throw std::exception("invalid character");
		}
		if (coef)
		{
			vals[vals.length() - 1] *= -1.0;
		}
	}
	listMonomial* thead1 = this->head;
	if (vals.length() % 4 != 0)
	{
		throw std::exception("monom is not completed");
	}
	for (int i = 0; i < vals.length(); i += 4)
	{
		if (vals[i + 1] > 9 || vals[i + 2] > 9 || vals[i + 3] > 9)
		{
			throw std::logic_error("The degree is too high");
		}
		if (std::abs(vals[i + 1] - int(vals[i + 1])) > 1e-14 || std::abs(vals[i + 2] - int(vals[i + 2])) > 1e-14 || std::abs(vals[i + 3] - int(vals[i + 3])) > 1e-14)
		{
			throw std::exception("the degree can only be an integer");
		}
		if (vals[i + 1] < 0 || vals[i + 2] < 0 || vals[i + 3] < 0)
		{
			throw std::exception("The degree cannot be negative");
		}
		int pow = vals[i + 1] * 100 + vals[i + 2] * 10 + vals[i + 3];
		if (thead1->next == nullptr)
		{
			thead1->next = new listMonomial(Monomial({ pow , vals[i] }));
		}
		else
		{
			thead1->next->monomial = Monomial({ pow , vals[i] });
		}
		thead1 = thead1->next;
	}
	if (thead1->next != nullptr)
	{
		listMonomial* thead2 = thead1->next, * t;
		thead1->next = nullptr;
		while (thead2 != nullptr)
		{
			t = thead2;
			thead2 = thead2->next;
			delete t;
		}
	}
	mergeSort();
	return;
}

polinom polinom::operator+(const polinom& p) const
{
#define pow		monomial.data.first
#define coef	monomial.data.second
	polinom res;
	listMonomial* thead1 = head->next, *thead2 = p.head->next, *theadRes = res.head;
	while (thead1 != nullptr && thead2 != nullptr)
	{
		if (thead1->pow == thead2->pow)
		{
			if (abs(thead1->coef + thead2->coef) > 1e-14)
			{
				theadRes->next = new listMonomial(Monomial({ thead1->pow, thead1->coef + thead2->coef }));
				theadRes = theadRes->next;
			}
			thead1 = thead1->next;
			thead2 = thead2->next;
		}
		else if (thead1->pow < thead2->pow)
		{
			theadRes->next = new listMonomial(Monomial({ thead1->pow, thead1->coef }));
			theadRes = theadRes->next;
			thead1 = thead1->next;
		}
		else
		{
			theadRes->next = new listMonomial(Monomial({ thead2->pow, thead2->coef }));
			theadRes = theadRes->next;
			thead2 = thead2->next;
		}
	}
	if (thead1 == nullptr && thead2 != nullptr) thead1 = thead2;
	while (thead1 != nullptr)
	{
		theadRes->next = new listMonomial(Monomial({ thead1->pow, thead1->coef }));
		theadRes = theadRes->next;
		thead1 = thead1->next;
	}
	return res;
#undef pow
#undef coef
}

polinom polinom::operator-(const polinom& p) const // проверка отсортированности не нужна
{
	return *this + (p * (-1.0));
}

polinom polinom::operator*(const double& alpha) const // проверка отсортированности не нужна
{
	polinom res;
	listMonomial* theadRes = res.head, *thead = head->next;
	while (thead != nullptr)
	{
		if (abs(thead->monomial.data.second * alpha) > 1e-14)
		{
			theadRes->next = new listMonomial(Monomial({ thead->monomial.data.first, thead->monomial.data.second * alpha }));
			theadRes = theadRes->next;
		}
		thead = thead->next;
	}
	return res;
}

//умножение за квадрат
polinom polinom::operator*(const polinom& p) const
{
#define pow		monomial.data.first
#define coef	monomial.data.second
	polinom res;
	listMonomial* thead1 = head->next, * thead2 = p.head->next, * theadRes = res.head;
	while (thead1 != nullptr)
	{
		while (thead2 != nullptr)
		{
			if ( (thead1->pow / 100 + thead2->pow / 100) > 9 ||
				 ((thead1->pow / 10) % 10 + (thead2->pow / 10) % 10) > 9 ||
				 (thead1->pow % 10 + thead2->pow % 10) > 9
			   )
			{
				throw std::logic_error("The degree is too high");
			}
			theadRes->next = new listMonomial(Monomial({ thead1->pow + thead2->pow, thead1->coef * thead2->coef }));
			theadRes = theadRes->next;
			thead2 = thead2->next;
		}
		thead2 = p.head->next;
		thead1 = thead1->next;
	}
	res.mergeSort();
	return res;
#undef pow
#undef coef
}

double polinom::calc(const double& x, const double& y, const double& z)
{
	double res = 0.0;
	listMonomial* thead1 = head->next;
	while (thead1 != nullptr)
	{
		int px = thead1->monomial.data.first / 100;
		int py = (thead1->monomial.data.first / 10) % 10;
		int pz = thead1->monomial.data.first % 10;
		res += thead1->monomial.data.second * std::pow(x, px) * std::pow(y, py) * std::pow(z, pz);
		thead1 = thead1->next;
	}
	return res;
}

polinom& polinom::operator=(const polinom& p)
{
	if (this == &p) return *this;
	listMonomial* thead1 = p.head->next, * thead2 = head;
	while (thead1 != nullptr)
	{
		
		if (thead2->next == nullptr)
		{
			thead2->next = new listMonomial(thead1->monomial);
		}
		else
		{
			thead2->next->monomial = thead1->monomial;
		}
		thead2 = thead2->next;
		thead1 = thead1->next;
	}
	if (thead2->next != nullptr)
	{
		listMonomial* t1 = thead2->next, * t;
		thead1->next = nullptr;
		while (t1 != nullptr)
		{
			t = t1;
			t1 = t1->next;
			delete t;
		}
	}
	return *this;
}

polinom& polinom::operator=(polinom&& p)
{
	std::swap(head, p.head);
	return *this;
}

bool polinom::operator==(const polinom& p) const noexcept
{
	listMonomial* tHead1 = head;
	listMonomial* tHead2 = p.head;
	double eps = 1e-11;
	while (tHead1 != nullptr && tHead2 != nullptr)
	{
		if (std::abs(tHead1->monomial.data.second - tHead2->monomial.data.second) > eps ||
			std::abs(tHead1->monomial.data.first - tHead2->monomial.data.first) != 0) return false;
		tHead1 = tHead1->next;
		tHead2 = tHead2->next;
	}
	if (tHead1 != nullptr || tHead2 != nullptr) return false;
	return true;
}

bool polinom::operator!=(const polinom& p) const noexcept
{
	return !(*this == p);
}

double polinom::ToOperand(const std::string& str)
{
	int i = 0, sign2 = 0;
	double res = 0.0, c = 10, c2 = 0.0;
	bool flag1 = true, flag2 = true;
	for (; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (flag1)
			{
				res = res * c + str[i] - '0';
			}
			else if (!flag1 && flag2)
			{
				res = res + (str[i] - '0') * c;
				c = c * 0.1;
			}
			else if (!flag2)
			{
				c2 = c2 * c + str[i] - '0';
			}
		}
		else if (str[i] == '.' && flag1 && !(i == 0 && i + 1 < str.size() && (str[i + 1] == 'e' || str[i + 1] == 'E')) && !(i == 0 && str.size() == 1))
		{
			flag1 = false;
			c = 0.1;
		}
		else if ((str[i] == 'e' || str[i] == 'E') && i > 0 && (str[i - 1] >= '0' && str[i - 1] <= '9' || str[i - 1] == '.') && i != str.size() - 1)
		{
			flag1 = false;
			flag2 = false;
			c = 10;
		}
		else if (str[i] == '-' && sign2 == 0 && i > 0 && (str[i - 1] == 'e' || str[i - 1] == 'E') && i + 1 < str.size() && str[i + 1] >= '0' && str[i + 1] <= '9')
		{
			sign2 = -1;
		}
		else if (str[i] == '+' && sign2 == 0 && i > 0 && (str[i - 1] == 'e' || str[i - 1] == 'E') && i + 1 < str.size() && str[i + 1] >= '0' && str[i + 1] <= '9')
		{
			sign2 = 1;
		}
		else
		{
			throw std::exception("a constant was entered incorrectly");
		}
	}
	if (sign2 == 0) sign2 = 1;
	if (!flag2) res = res * std::pow(10, sign2 * c2);
	return res;
}

std::istream& operator>>(std::istream& s, polinom& p)
{
	std::string str;
	s >> std::ws;
	getline(s, str);
	p.initPolinom(str);
	return s;
}

std::ostream& operator<<(std::ostream& s, const polinom& p)
{
	listMonomial* thead = p.head->next;
	if (thead == nullptr)
	{
		s << 0;
		return s;
	}
	while (thead != nullptr)
	{
		int x = thead->monomial.data.first / 100;
		int y = (thead->monomial.data.first / 10) % 10;
		int z = thead->monomial.data.first % 10;
		s << thead->monomial.data.second << " * x^" << x << " * y^" << y << " * z^" << z;
		thead = thead->next;
		if (thead != nullptr) s << " + ";
	}
	return s;
}