#include "TestSuite.hpp"
#include <iostream>

std::list< TestSuite >		TestSuite::suite_list;

TestSuite::TestSuite( void )
: TestUnit()
{ return ; }

TestSuite::TestSuite( const TestSuite& src )
: TestUnit(src), _suite(src._suite)
{ return ; }

TestSuite::TestSuite( const std::string& str )
: TestUnit(str)
{ return ; }

TestSuite::~TestSuite( void )
{ return ; }

TestSuite&
TestSuite::operator=( const TestSuite& rhs )
{
	if (this != &rhs)
	{
		TestUnit::operator=(rhs);
		this->_suite = rhs._suite;
	}
	return (*this);
}

void
TestSuite::add( TestCase& tc )
{ _suite.push_back(tc); }

void
TestSuite::add( TestSuite& new_suite )
{ suite_list.push_back(new_suite); }

void
TestSuite::run( void )
{
	for (TestSuite::tcase_iter it = _suite.begin(); it != _suite.end(); it++)
	{
		(*it)();
	}
}

void
TestSuite::print( void )
{
	for (TestSuite::suite_iter it = suite_list.begin(); it != suite_list.end(); it++)
	{
		std::cout << (*it).get_name() << std::endl; 
	}
}