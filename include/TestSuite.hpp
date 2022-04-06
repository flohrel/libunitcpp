#ifndef __TESTSUITE__H__
# define __TESTSUITE__H__

# include <list>
# include <string>
# include "TestUnit.hpp"
# include "TestCase.hpp"

class TestSuite : public TestUnit
{
	public:
		typedef std::list<TestSuite>::const_iterator	suite_iter;
		typedef std::list<TestCase>::const_iterator		tcase_iter;


	private:
		std::list< TestCase >				_suite;


	public:
		static std::list< TestSuite >		suite_list;


	public:
		TestSuite( void );
		TestSuite( const TestSuite& src );
		TestSuite( const std::string& name );
		~TestSuite( void );

		TestSuite&	operator=( const TestSuite& rhs );

		static void
		add( TestSuite& new_suite );

		void
		add( TestCase& tc );

		void
		run( void );

		static void
		print( void );


};

#endif