#ifndef __TESTUNIT__H__
# define __TESTUNIT__H__

# include "global_typedefs.hpp"
# include <list>
# include <string>

namespace unit_test
{

class TestUnit
{
	private:
		test_unit_type		_type;


	public:
		std::string		name;
		unsigned		timeout;
		unsigned		expected_failures;

		TestUnit( void );
		TestUnit( const TestUnit& src );
		TestUnit( test_unit_type ut, const std::string& n, unsigned t = 0, unsigned ex = 0 );
		~TestUnit( void );

		TestUnit&
		operator=( const TestUnit& rhs );

		test_unit_type
		get_type( void ) const;


};


}	// namespace unit_test

#endif