#include <iostream>
#include <sstream>
#include "polinom.h"
#include "Vector.h"
#include "orderedTable.h"
#include "unOrderedTable.h"
#include "hashTable.h"
#include "ABLtree.h"

int main()
{
	orderedTable<polinom> t1;
	unOrderedTable<polinom> t2;
	hashTable<polinom> t3(100000);
	ABLtree<polinom> t4;
	tableLogs<polinom> tl(&t1, &t2, &t3, &t4);

	std::cout << "Enter the polynomial and its name as follows: name, space, coefficients before monomials, and powers of x, y, and z separated by a space." << std::endl;
	std::cout << "You don't need to write * and + and variable names." << std::endl;
	std::cout << "Example:" << std::endl;
	std::cout << "pol1 4.5 * x^1 * y^3 * z^4 - 5.6 * x^1 * y^2 * z^3 == ";
	std::cout << "pol1 4.5 1 3 4 -5.6 1 2 3" << std::endl << std::endl;
	
	try
	{
		std::cout << "Select an action: " << std::endl;
		int action;
		do
		{
			std::cout << "1. find the polynomial" << std::endl;
			std::cout << "2. delete the polynomial" << std::endl;
			std::cout << "3. insert the polynomial" << std::endl;
			std::cout << "4. include logs" << std::endl;
			std::cout << "5. print logs tables(if logging is enabled)" << std::endl;
			std::cout << "6. exit" << std::endl << std::endl;
			std::cin >> action;
			if (action == 1)
			{
				std::cout << std::endl;
				std::cout << "Enter the name of the polynomial:" << std::endl;
				std::string name1;
				std::cin >> name1;
				std::cout << "0. check the presence of a polynomial in the table" << std::endl;
				std::cout << "1. p1 = p1 + p2" << std::endl;
				std::cout << "2. p1 = p1 - p2" << std::endl;
				std::cout << "3. p1 = p1 * p2" << std::endl;
				std::cout << "4. p1 = alpha * p1" << std::endl;
				std::cout << "5. calculating p1 in (x, y, z)" << std::endl;
				int num;
				std::cin >> num;
				num--;
				std::shared_ptr <polinom> tp(new polinom);
				if (num == -1)
				{
					std::shared_ptr<polinom> p1 = t1.search(Vector<unsigned char>(name1.c_str()));
					t2.search(Vector<unsigned char>(name1.c_str()));
					t3.search(Vector<unsigned char>(name1.c_str()));
					t4.search(Vector<unsigned char>(name1.c_str()));
					if (p1.get() == nullptr)
					{
						std::cout << "there is no such polynomial in the table" << std::endl;
					}
					else
					{
						std::cout << "there is such a polynomial in the table" << std::endl;
						std::cout << *p1 << std::endl;
					}
				}
				else if (num == 0)
				{
					std::cout << "Enter the name of the second polynomial: " << std::endl;
					std::string name2;
					std::cin >> name2;
					polinom p1 = *t1.search(Vector<unsigned char>(name1.c_str()));
					polinom p2 = *t1.search(Vector<unsigned char>(name2.c_str()));
					t2.search(Vector<unsigned char>(name1.c_str()));
					t2.search(Vector<unsigned char>(name2.c_str()));
					t3.search(Vector<unsigned char>(name1.c_str()));
					t3.search(Vector<unsigned char>(name2.c_str()));
					t4.search(Vector<unsigned char>(name1.c_str()));
					t4.search(Vector<unsigned char>(name2.c_str()));
					*tp = p1 + p2;
					std::cout << *tp << std::endl;
				}
				else if (num == 1)
				{
					std::cout << "Enter the name of the second polynomial: " << std::endl;
					std::string name2;
					std::cin >> name2;
					polinom p1 = *t1.search(Vector<unsigned char>(name1.c_str()));
					polinom p2 = *t1.search(Vector<unsigned char>(name2.c_str()));
					t2.search(Vector<unsigned char>(name1.c_str()));
					t2.search(Vector<unsigned char>(name2.c_str()));
					t3.search(Vector<unsigned char>(name1.c_str()));
					t3.search(Vector<unsigned char>(name2.c_str()));
					t4.search(Vector<unsigned char>(name1.c_str()));
					t4.search(Vector<unsigned char>(name2.c_str()));
					*tp = p1 - p2;
					std::cout << *tp << std::endl;
				}
				else if (num == 2)
				{
					std::cout << "Enter the name of the second polynomial: " << std::endl;
					std::string name2;
					std::cin >> name2;
					polinom p1 = *t1.search(Vector<unsigned char>(name1.c_str()));
					polinom p2 = *t1.search(Vector<unsigned char>(name2.c_str()));
					t2.search(Vector<unsigned char>(name1.c_str()));
					t2.search(Vector<unsigned char>(name2.c_str()));
					t3.search(Vector<unsigned char>(name1.c_str()));
					t3.search(Vector<unsigned char>(name2.c_str()));
					t4.search(Vector<unsigned char>(name1.c_str()));
					t4.search(Vector<unsigned char>(name2.c_str()));
					*tp = p1 * p2;
					std::cout << *tp << std::endl;
				}
				else if (num == 3)
				{
					std::cout << "Enter the alpha: " << std::endl;
					double alpha;
					std::cin >> alpha;
					polinom p1 = *t1.search(Vector<unsigned char>(name1.c_str()));
					t2.search(Vector<unsigned char>(name1.c_str()));
					t3.search(Vector<unsigned char>(name1.c_str()));
					t4.search(Vector<unsigned char>(name1.c_str()));
					*tp = p1 * alpha;
					std::cout << *tp << std::endl;
				}
				else if (num == 4)
				{
					std::cout << "Enter the x, y and z: " << std::endl;
					double x, y, z;
					std::cout << "x = ";
					std::cin >> x;
					std::cout << "y = ";
					std::cin >> y;
					std::cout << "z = ";
					std::cin >> z;
					polinom p1 = *t1.search(Vector<unsigned char>(name1.c_str()));
					t2.search(Vector<unsigned char>(name1.c_str()));
					t3.search(Vector<unsigned char>(name1.c_str()));
					t4.search(Vector<unsigned char>(name1.c_str()));
					std::cout << p1.calc(x, y, z) << std::endl;
				}
				else if (num != 5)
				{
					throw std::exception("incorrect operation number.");
				}
				if (num >= 0 && num <= 3)
				{
					std::cout << std::endl;
					std::cout << "Save the result to a table? Yes(1)/No(0)" << std::endl;
					int flSave;
					std::cin >> flSave;
					if (flSave == 1)
					{
						std::cout << "Enter a name under which to save the result" << std::endl;
						std::cin >> name1;
						t1.insert({ Vector<unsigned char>(name1.c_str()), tp });
						t2.insert({ Vector<unsigned char>(name1.c_str()), tp });
						t3.insert({ Vector<unsigned char>(name1.c_str()), tp });
						t4.insert({ Vector<unsigned char>(name1.c_str()), tp });
					}
					else if (flSave != 0) throw std::exception("incorrect operation.");
				}
			}
			else if (action == 2)
			{
				std::cout << "Enter the name of the polynomial:" << std::endl;
				std::string name1;
				std::cin >> name1;
				t1.erase(Vector<unsigned char>(name1.c_str()));
				t2.erase(Vector<unsigned char>(name1.c_str()));
				t3.erase(Vector<unsigned char>(name1.c_str()));
				t4.erase(Vector<unsigned char>(name1.c_str()));
				std::cout << "the polynomial was successfully deleted from the table" << std::endl;
			}
			else if (action == 3)
			{
				std::cout << "Enter the name of the polynomial:" << std::endl;
				std::string name1;
				std::cin >> name1;
				std::cout << "Enter the the polynomial:" << std::endl;
				std::shared_ptr<polinom> p1(new polinom);
				std::cin >> *p1;
				t1.insert({ Vector<unsigned char>(name1.c_str()), p1 });
				t2.insert({ Vector<unsigned char>(name1.c_str()), p1 });
				t3.insert({ Vector<unsigned char>(name1.c_str()), p1 });
				t4.insert({ Vector<unsigned char>(name1.c_str()), p1 });
				std::cout << "the polynomial has been successfully saved in the table" << std::endl;
			}
			else if (action == 4)
			{
				tl.includeLogs(true);
				std::cout << "Logging is enabled" << std::endl;
			}
			else if (action == 5)
			{
				std::cout << "Total number of comparisons for the last operations: " << std::endl;
				std::cout << tl.getAllLogs() << std::endl;
			}
			else if (action != 6)
			{
				throw std::exception("incorrect operation number.");
			}
		} while (action != 6);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (const std::logic_error& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "errors" << std::endl;
	}
	return 0;
}