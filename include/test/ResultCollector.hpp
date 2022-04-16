#ifndef __RESULTCOLLECTOR__H__
# define __RESULTCOLLECTOR__H__

# include "test/TestUnit.hpp"
# include "test/TestCase.hpp"
# include "test/TestSuite.hpp"

namespace unit_test
{

struct chrono
{
	chrono() : s(0), e(0) { }
	~chrono() { }

	void	start() { s = clock(); }
	void	end() { e = clock(); }
	float	get_execution_time() { return (((float)(e - s) * 1000) / CLOCKS_PER_SEC); }

	clock_t		s;
	clock_t		e;

};

class ResultCollector
{
	public:
		ResultCollector( void );
		~ResultCollector( void );
		ResultCollector( const ResultCollector& src );

		ResultCollector&
		operator=( const ResultCollector& rhs );

		static int
		get_exit_status( int status, TestCase& test, TestSuite& suite );


	public:
		bool		timed_out;				// Indicates that the test unit has timed out. 
		bool		aborted;				// Indicates that the test unit execution has been aborted.
		unsigned	test_cases_passed;		// Number of successfull test cases. 
		unsigned	test_cases_failed;		// Number of failing in test cases.  
		unsigned	test_cases_aborted;		// Number of aborted test cases. 
		unsigned	test_cases_timed_out;	// Number of timed out test cases. 
		unsigned	test_suites_timed_out;  // Number of timed out test suites. 
		float		duration_milliseconds;  // Duration of the test in microseconds.
		int			exit_status;			// Exit status of the test function.
		int			signal;					// Signal emitted by test function.


};

}

#endif