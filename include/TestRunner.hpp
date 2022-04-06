#ifndef __TESTRUNNER__H__
# define __TESTRUNNER__H__

# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include "TestSuite.hpp"
# include "TestCase.hpp"

class TestRunner
{
	public:
		typedef std::list<TestSuite>::const_iterator	suite_iter;
		typedef std::list<TestCase>::const_iterator		tcase_iter;

		struct chrono
		{
			clock_t		start;
			clock_t		end;

			chrono() : start(0), end(0) { }
			~chrono() { }
			void chrono_start() { start = clock(); }
			void chrono_end() { end = clock(); }
			float get_execution_time() { return (((float)(end - start) * 1000) / CLOCKS_PER_SEC); }
		};


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

#endif