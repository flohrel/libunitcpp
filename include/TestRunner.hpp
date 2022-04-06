#ifndef __TESTRUNNER__H__
# define __TESTRUNNER__H__

# include <sys/wait.h>
# include <unistd.h>
# include <list>
# include "TestCase.hpp"

class TestRunner
{
	private:
		std::list< TestCase >*	suite;


	public:
		TestRunner( void );
		TestRunner( const TestRunner& src );
		~TestRunner( void );

		TestRunner&
		operator=( const TestRunner& rhs );


};

#endif