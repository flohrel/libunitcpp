# include "TestSuite.hpp"
#include <iostream>

int	main( void )
{
	TestSuite test1("test1");
	TestSuite test2("test2");
	TestSuite test3("test3");
	test2 = test3;

	TestSuite::add_suite(test1);
	TestSuite::add_suite(test2);
	TestSuite::add_suite(test3);
	TestSuite::print_list();

}
