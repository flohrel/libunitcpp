#include "TestSuite.hpp"
#include <iostream>

std::list< TestSuite >		TestSuite::suite_list;

TestSuite::TestSuite( void )
: TestUnit()
{ return ; }

TestSuite::TestSuite( const TestSuite& src )
: TestUnit(t_suite, src.name), suite(src.suite)
{ return ; }

TestSuite::TestSuite( const std::string& str, unsigned time = 0, unsigned nb_fail = 0 )
: TestUnit(t_suite, str, time, nb_fail)
{ return ; }

TestSuite::~TestSuite( void )
{ return ; }

TestSuite&
TestSuite::operator=( const TestSuite& rhs )
{
	if (this != &rhs)
	{
		TestUnit::operator=(rhs);
		this->suite = rhs.suite;
	}
	return (*this);
}

void
TestSuite::add( TestCase& tc )
{ suite.push_back(tc); }

void
TestSuite::add( TestSuite& new_suite )
{ suite_list.push_back(new_suite); }
