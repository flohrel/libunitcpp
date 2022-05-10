#ifndef __RESULTCOLLECTOR__H__
# define __RESULTCOLLECTOR__H__

# include <sys/wait.h>
# include <cstdlib>
# include <csignal>
# include <ctime>

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
	ResultCollector( void )
	: timed_out(false), aborted(false), test_cases_passed(0), test_cases_failed(0), test_cases_aborted(0),
		test_cases_timed_out(0), test_suites_timed_out(0), duration_milliseconds(0), exit_status(0), signal(0)
	{ return ; }

	~ResultCollector( void )
	{ return ; }

	ResultCollector( const ResultCollector& src )
	: timed_out(src.timed_out), aborted(src.aborted), test_cases_passed(src.test_cases_passed), test_cases_failed(src.test_cases_failed),
		test_cases_aborted(src.test_cases_aborted), test_cases_timed_out(src.test_cases_timed_out), test_suites_timed_out(src.test_suites_timed_out),
		duration_milliseconds(src.duration_milliseconds), exit_status(src.exit_status), signal(src.signal)
	{ return ; }

	ResultCollector&
	operator=( const ResultCollector& rhs )
	{
		(void)rhs;
		return (*this);
	}

	void
	get_results( void )
	{
		int32_t	status;
		chrono	chrono;

		chrono.start();
		wait(&status);
		chrono.end();
		duration_milliseconds = chrono.get_execution_time();
		get_exit_status(status);
	}

	void
	get_exit_status( int status )
	{
		if (WIFEXITED(status) == true)
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status == EXIT_SUCCESS)
				test_cases_passed++;
			else
				test_cases_failed++;
		}
		else if (WIFSIGNALED(status))
		{
			signal = WTERMSIG(status);
			if (signal == SIGALRM)
			{
				timed_out = true;
				test_cases_timed_out++;
			}
			else
			{
				aborted = true;
				test_cases_aborted++;
			}
		}
	/*
		else
			UNKNOWN ERROR
	*/
	}

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