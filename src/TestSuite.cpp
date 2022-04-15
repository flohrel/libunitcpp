#include "test/TestSuite.hpp"

namespace unit_test
{

TestSuite::TestSuite( void )
: TestUnit()
{ return ; }

TestSuite::TestSuite( const TestSuite& src )
: TestUnit(t_suite, src.name), suite(src.suite)
{ return ; }

TestSuite::TestSuite( const std::string& str, unsigned time, unsigned nb_fail )
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
TestSuite::add( TestUnit& tc )
{ suite.push_back(tc); }


}	// namespace unit_test