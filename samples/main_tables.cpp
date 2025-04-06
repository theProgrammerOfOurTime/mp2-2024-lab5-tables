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
	/*orderedTable<polinom> t1;
	unOrderedTable<polinom> t2;
	hashTable<polinom> t3(1000);
	ABLtree<polinom> t4;
	tableLogs<polinom> tl(&t1, &t2, &t3, &t4);
	Vector<unsigned char> n0("a0"), n1("a1"), n2("a2"), n3("a3"), n4("a4"), n5("a5"), n6("a6");
	std::shared_ptr<polinom> p1(new polinom("4.5 1 3 4 5.6 1 2 3"));
	std::shared_ptr<polinom> p2(new polinom("4.5 1 3 4"));
	std::shared_ptr<polinom> p3(new polinom("4.5 1 1 6"));
	t1.insert({ n0, p1 });
	t1.insert({ n1, p1 });
	t1.insert({ n2, p1 });
	t1.insert({ n3, p1 });
	t1.insert({ n4, p1 });
	t1.insert({ n5, p1 });
	t1.insert({ n6, p1 });
	t2.insert({ n0, p1 });
	t2.insert({ n1, p1 });
	t2.insert({ n2, p1 });
	t2.insert({ n3, p1 });
	t2.insert({ n4, p1 });
	t2.insert({ n5, p1 });
	t2.insert({ n6, p1 });
	t3.insert({ n0, p1 });
	t3.insert({ n1, p1 });
	t3.insert({ n2, p1 });
	t3.insert({ n3, p1 });
	t3.insert({ n4, p1 });
	t3.insert({ n5, p1 });
	t3.insert({ n6, p1 });
	t4.insert({ n0, p1 });
	std::cout << std::endl;
	t4.printTree();
	std::cout << std::endl;
	t4.insert({ n1, p1 });
	std::cout << std::endl;
	t4.printTree();
	std::cout << std::endl;
	t4.insert({ n2, p2 });
	std::cout << std::endl;
	t4.printTree();
	std::cout << std::endl;
	t4.insert({ n3, p3 });
	std::cout << std::endl;
	t4.printTree();
	std::cout << std::endl;
	t4.insert({ n4, p3 });
	std::cout << std::endl;
	t4.printTree();
	std::cout << std::endl;
	t4.insert({ n5, p3 });
	std::cout << std::endl;
	t4.printTree();
	std::cout << std::endl;
	t4.insert({ n6, p3 });
	std::cout << std::endl;
	t4.printTree();
	std::cout << std::endl;
	std::cout << t1.search(n0) << std::endl;
	std::cout << t1.search(n1) << std::endl;
	std::cout << t1.search(n2) << std::endl;
	std::cout << t1.search(n3) << std::endl;
	std::cout << t1.search(n4) << std::endl;
	std::cout << t1.search(n5) << std::endl;
	std::cout << t2.search(n0) << std::endl;
	std::cout << t2.search(n1) << std::endl;
	std::cout << t2.search(n2) << std::endl;
	std::cout << t2.search(n3) << std::endl;
	std::cout << t2.search(n4) << std::endl;
	std::cout << t2.search(n5) << std::endl;
	std::cout << t3.search(n0) << std::endl;
	std::cout << t3.search(n1) << std::endl;
	std::cout << t3.search(n2) << std::endl;
	std::cout << t3.search(n3) << std::endl;
	std::cout << t3.search(n4) << std::endl;
	std::cout << t3.search(n5) << std::endl;
	std::cout << t4.search(n0) << std::endl;
	std::cout << t4.search(n1) << std::endl;
	std::cout << t4.search(n2) << std::endl;
	std::cout << t4.search(n3) << std::endl;
	std::cout << t4.search(n4) << std::endl;
	std::cout << t4.search(n5) << std::endl;
	t1.erase(n1);
	t1.erase(n2);
	t1.erase(n0);
	t1.erase(n5);
	t1.erase(n3);
	t1.erase(n4);
	t1.erase(n6);
	t2.erase(n1);
	t2.erase(n2);
	t2.erase(n0);
	t2.erase(n5);
	t2.erase(n3);
	t2.erase(n4);
	t2.erase(n6);
	t3.erase(n1);
	t3.erase(n2);
	t3.erase(n0);
	t3.erase(n5);
	t3.erase(n3);
	t3.erase(n4);
	t3.erase(n6);
	t4.erase(n1);
	std::cout << std::endl;
	t4.printTree();
	std::cout << std::endl;
	t4.erase(n2);
	std::cout << std::endl;
	t4.printTree();
	std::cout << std::endl;
	t4.erase(n0);
	std::cout << std::endl;
	t4.printTree();
	std::cout << std::endl;
	t4.erase(n5);
	std::cout << std::endl;
	t4.printTree();
	std::cout << std::endl;
	t4.erase(n3);
	std::cout << std::endl;
	t4.printTree();
	std::cout << std::endl;
	t4.erase(n4);
	std::cout << std::endl;
	t4.printTree();
	std::cout << std::endl;
	t4.erase(n6);
	std::cout << std::endl;
	std::cout << tl.getAllLogs();*/
	return 0;
}