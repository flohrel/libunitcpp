#ifndef __TESTSUITE__H__
# define __TESTSUITE__H__

# include <list>
# include <string>
# include "TestUnit.hpp"
# include "TestCase.hpp"

class TestSuite : public TestUnit
{
	public:
		std::list< TestCase >				suite;
		static std::list< TestSuite >		suite_list;


	public:
		TestSuite( void );
		TestSuite( const TestSuite& src );
		TestSuite( const std::string& name, unsigned t = 0, unsigned ex = 0 );
		~TestSuite( void );

		TestSuite&	operator=( const TestSuite& rhs );

		static void
		add( TestSuite& new_suite );

		void
		add( TestCase& tc );


};

#endif