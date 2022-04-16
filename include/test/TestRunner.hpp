#ifndef __TESTRUNNER__H__
# define __TESTRUNNER__H__

# include <algorithm>
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
# include "ansi_colors.hpp"

namespace unit_test
{

class TestRunner
{
	public:
		TestRunner( void );
		TestRunner( const TestRunner& src );
		~TestRunner( void );

		TestRunner&
		operator=( const TestRunner& rhs );

		void
		run_all( void );

		void
		run_suite( TestSuite& unit );

		void
		run_test( TestCase& unit );

		void
		get_results( TestCase& test, TestSuite& suite );

		void
		print_suite_results( TestSuite& suite );


};

}	// namespace unit_test

#endif