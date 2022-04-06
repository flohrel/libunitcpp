#include "TestCase.hpp"

TestCase::TestCase( void )
{
	return;
}

TestCase::TestCase( const TestCase& src )
{
	(void)src;
	return;
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