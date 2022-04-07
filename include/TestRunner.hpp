#ifndef __TESTRUNNER__H__
# define __TESTRUNNER__H__

# include <cstdio>
# include <cstdlib>
# include <cerrno>
# include <iostream>
# include <string.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include "TestSuite.hpp"
# include "TestCase.hpp"

namespace unit_test
{

class TestRunner
{
	public:
		typedef std::list<TestSuite>::const_iterator	suite_iter;
		typedef std::list<TestCase>::const_iterator		tcase_iter;

		struct chrono
		{
			clock_t		s;
			clock_t		e;

			chrono() : s(0), e(0) { }
			~chrono() { }
			void start() { s = clock(); }
			void end() { e = clock(); }
			float get_execution_time() { return (((float)(e - s) * 1000) / CLOCKS_PER_SEC); }
		};

	private:
		chrono	_chrono;

	public:
		TestRunner( void );
		TestRunner( const TestRunner& src );
		~TestRunner( void );

		TestRunner&
		operator=( const TestRunner& rhs );

		void
		run_all( void );

		void
		run_suite( const TestSuite& unit );

		void
		run_test( const TestCase& unit );


};

}	// namespace unit_test

#endif