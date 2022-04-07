#ifndef __TESTSUITE__H__
# define __TESTSUITE__H__

# include <list>
# include <string>
# include "TestUnit.hpp"
# include "TestCase.hpp"

namespace unit_test
{

typedef std::list< TestSuite >		master_suite_t;

static master_suite_t*				master_suite;

class TestSuite : public TestUnit
{
	public:
		std::list< TestUnit >				suite;


	public:
		TestSuite( void );
		TestSuite( const TestSuite& src );
		TestSuite( const std::string& name, unsigned t = 0, unsigned ex = 0 );
		~TestSuite( void );

		TestSuite&	operator=( const TestSuite& rhs );

		void
		add( TestCase& tc );


};

static master_suite_t*
get_master_suite( void );

}	// namespace unit_test

#endif