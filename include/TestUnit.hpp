#ifndef __TESTUNIT__H__
# define __TESTUNIT__H__

# include <string>
# include "TestRunner.hpp"

enum t_unit_type { t_case = 0x01, t_suite = 0x10, t_any = 0x11 };

class TestUnit
{
	private:
		t_unit_type		_type;


	public:
		std::string		name;
		unsigned		timeout;
		unsigned		expected_failures;

		TestUnit( void );
		TestUnit( const TestUnit& src );
		TestUnit( t_unit_type ut, const std::string& n, unsigned t = 0, unsigned ex = 0 );
		~TestUnit( void );

		TestUnit&
		operator=( const TestUnit& rhs );

		std::string
		get_name( void ) const;


};

#endif