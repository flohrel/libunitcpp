#include "TestSuite.hpp"
#include <iostream>

std::vector< TestSuite > TestSuite::suiteList;

TestSuite::TestSuite( void )
: TestUnit()
{ return ; }

TestSuite::TestSuite( const TestSuite& src )
: TestUnit(src), _testSuite(src._testSuite)
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
		this->_testSuite = rhs._testSuite;
	}
	return (*this);
}

void
TestSuite::add_suite( TestSuite& new_suite )
{ suiteList.push_back(new_suite); }

void
TestSuite::print_list( void )
{
	for (std::vector< TestSuite >::const_iterator it = suiteList.begin(); it != suiteList.end(); it++)
	{
		std::cout << (*it).get_name() << std::endl; 
	}
}