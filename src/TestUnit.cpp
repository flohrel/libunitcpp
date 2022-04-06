#include "TestUnit.hpp"

TestUnit::TestUnit( void )
{ return ; }

TestUnit::TestUnit( const TestUnit& src )
: _name(src._name), _timeout(src._timeout), _expected_failures(src._expected_failures)
{ return ; }

TestUnit::TestUnit( const std::string& name )
: _name(name)
{ return ; }

TestUnit::~TestUnit( void )
{ return ; }

TestUnit&
TestUnit::operator=( const TestUnit& rhs )
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_timeout = rhs._timeout;
		this->_expected_failures = rhs._expected_failures;
	}
	return (*this);
}

std::string
TestUnit::get_name( void ) const
{ return (this->_name); }
