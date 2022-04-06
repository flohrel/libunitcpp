#include "TestCase.hpp"

TestCase::TestCase( void )
{ return ; }

TestCase::TestCase( const std::string& str, test_ft ft, unsigned time = 0, unsigned nb_fail = 0 )
: TestUnit(t_case, str, time, nb_fail), _ft_ptr(ft)
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