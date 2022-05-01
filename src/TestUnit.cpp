#include "test/TestUnit.hpp"
#include <iostream>
namespace unit_test
{

TestUnit::TestUnit( void )
{ return ; }

TestUnit::TestUnit( const TestUnit& src )
: _type(src._type), name(src.name), timeout(src.timeout), expected_failures(src.expected_failures)
{ return ; }

TestUnit::TestUnit( test_unit_type ut, const std::string& n, unsigned t, unsigned ex )
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

test_unit_type
TestUnit::get_type( void ) const
{ return (this->_type); }


}	// namespace unit_test