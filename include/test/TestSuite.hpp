#ifndef __TESTSUITE__H__
# define __TESTSUITE__H__

# include <string>
# include "utils/Singleton.hpp"
# include "TestUnit.hpp"
# include "TestCase.hpp"

namespace unit_test
{

class TestSuite : public TestUnit, public std::list<TestCase>
{
	public:
		TestSuite( void );
		TestSuite( const TestSuite& src );
		TestSuite( const std::string& name, unsigned timeout = 0, unsigned expected_fail = 0 );
		~TestSuite( void );

		TestSuite&	operator=( const TestSuite& rhs );


};

class MasterSuite : public Singleton< std::list<TestSuite> >
{
	friend std::list<TestSuite>&	Singleton<std::list<TestSuite> >::instance();

	private:
		MasterSuite( void ) { return ; }
};

}	// namespace unit_test

#endif