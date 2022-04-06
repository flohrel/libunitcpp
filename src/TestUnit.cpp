#include "TestUnit.hpp"

TestUnit::TestUnit( void )
{ return ; }

TestUnit::TestUnit( const TestUnit& src )
: _type(src._type), name(src.name), timeout(src.timeout), expected_failures(src.expected_failures)
{ return ; }

TestUnit::TestUnit( t_unit_type ut, const std::string& n, unsigned t = 0, unsigned ex = 0 )
: _type(ut), name(n), timeout(t), expected_failures(ex)
{ return ; }

TestUnit::~TestUnit( void )
{ return ; }

TestUnit&
TestUnit::operator=( const TestUnit& rhs )
{
	if (this != &rhs)
	{
		this->name = rhs.name;
		this->timeout = rhs.timeout;
		this->expected_failures = rhs.expected_failures;
	}
	return (*this);
}

std::string
TestUnit::get_name( void ) const
{ return (this->name); }
