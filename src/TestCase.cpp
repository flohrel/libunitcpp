#include "TestCase.hpp"

TestCase::TestCase( void )
{ return ; }

TestCase::TestCase( const std::string& str, test_ft ft )
: TestUnit(str), _ft_ptr(ft)
{
	return ;
}

TestCase::TestCase( const TestCase& src )
: TestUnit(src), _ft_ptr(src._ft_ptr)
{
	return ;
}

TestCase::~TestCase( void )
{
	return;
}

TestCase&	TestCase::operator=( const TestCase& rhs )
{
	(void)rhs;
	return (*this);
}

void		TestCase::operator()( void ) const
{
	_ft_ptr();
	return ;
}