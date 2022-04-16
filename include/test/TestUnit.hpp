#ifndef __TESTUNIT__H__
# define __TESTUNIT__H__

# include <list>
# include <string>
# include "ResultCollector.hpp"

namespace unit_test
{

enum e_unit_type { t_case = 0x01, t_suite = 0x10, t_any = 0x11 };

class TestUnit
{
	private:
		e_unit_type		_type;


	public:
		std::string		name;
		unsigned		timeout;
		unsigned		expected_failures;

		ResultCollector	results;

		TestUnit( void );
		TestUnit( const TestUnit& src );
		TestUnit( e_unit_type ut, const std::string& n, unsigned t = 0, unsigned ex = 0 );
		~TestUnit( void );

		TestUnit&
		operator=( const TestUnit& rhs );

		e_unit_type
		get_type( void ) const;


};


}	// namespace unit_test

#endif