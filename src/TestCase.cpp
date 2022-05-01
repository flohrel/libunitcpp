#include "test/TestCase.hpp"

namespace unit_test
{

TestCase::TestCase( void )
{ return ; }

TestCase::TestCase( const std::string& str, test_ft ft, unsigned time, unsigned nb_fail )
: TestUnit(TUT_CASE, str, time, nb_fail), _ft_ptr(ft)
{ return ; }

TestCase::TestCase( const TestCase& src )
: TestUnit(src), _ft_ptr(src._ft_ptr)
{ return ; }

TestCase::~TestCase( void )
{ return ; }

TestCase&	TestCase::operator=( const TestCase& rhs )
{
	if (this != &rhs)
	{
		TestUnit::operator=(rhs);
		_ft_ptr = rhs._ft_ptr;
	}
	return (*this);
}

void		TestCase::operator()( void ) const
{
	_ft_ptr();
	return ;
}

}	// namespace unit_test