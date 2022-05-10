#ifndef __TEST_RUNNER__H__
# define __TEST_RUNNER__H__

# include <algorithm>
# include <cstdio>
# include <cerrno>
# include <iostream>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include "ResultCollector.hpp"
# include "utils/ansi_colors.hpp"

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

		static void
		print_suite_results( ResultCollector& suite, unsigned count );

		static void
		run_test( TestCase& unit );
		
		static void
		run_suite( TestSuite& unit );

		void
		run_all( void );


};

}	// namespace unit_test

#endif