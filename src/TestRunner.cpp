#include "TestRunner.hpp"

TestRunner::TestRunner( void )
{
	return;
}

TestRunner::TestRunner( const TestRunner& src )
{
	return;
}

TestRunner::~TestRunner( void )
{
	return;
}

TestRunner&
TestRunner::operator=( const TestRunner& rhs )
{
	return (*this);
}

void
TestRunner::run_test( const TestCase& unit )
{
	
}

void
TestRunner::run_suite( const TestSuite& unit )
{
	TestRunner::tcase_iter current = unit.suite.begin();
	TestRunner::tcase_iter end = unit.suite.end();

	for (; current != end; current++)
	{
		run_test(*current);
	}
}

void
TestRunner::run_all( void )
{
	TestRunner::suite_iter current = TestSuite::suite_list.begin();
	TestRunner::suite_iter end = TestSuite::suite_list.end();

	for (; current != end; current++)
	{
		run_suite(*current);
	}
}