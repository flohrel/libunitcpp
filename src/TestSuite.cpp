#include "test/TestSuite.hpp"

namespace unit_test
{

TestSuite::TestSuite( void )
: TestUnit(), std::list<TestCase>()
{ return ; }

TestSuite::TestSuite( const TestSuite& src )
: TestUnit(TUT_SUITE, src.name), std::list<TestCase>(src)
{ return ; }

TestSuite::TestSuite( const std::string& str, unsigned time, unsigned nb_fail )
: TestUnit(TUT_SUITE, str, time, nb_fail), std::list<TestCase>()
{ return ; }

TestSuite::~TestSuite( void )
{ return ; }

TestSuite&
TestSuite::operator=( const TestSuite& rhs )
{
	if (this != &rhs)
	{
		TestUnit::operator=(rhs);
		std::list<TestCase>::operator=(rhs);
	}
	return (*this);
}


}	// namespace unit_test