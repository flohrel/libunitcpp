#ifndef __TESTSUITE__H__
# define __TESTSUITE__H__

# include <vector>
# include <string>
# include "TestUnit.hpp"
# include "TestCase.hpp"

class TestSuite : public TestUnit
{
	public:
		TestSuite( void );
		TestSuite( const TestSuite& src );
		TestSuite( const std::string& name );
		~TestSuite( void );

		TestSuite& operator=( const TestSuite& rhs );

		static void
		add_suite( TestSuite& new_suite );
		
		static void
		print_list( void );

		static std::vector< TestSuite >	suiteList;


	private:
		std::vector< TestCase >			_testSuite;


};

#endif