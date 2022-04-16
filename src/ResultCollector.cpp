# include "test/ResultCollector.hpp"

namespace unit_test
{

ResultCollector::ResultCollector( void )
: timed_out(false), aborted(false), test_cases_passed(0), test_cases_failed(0), test_cases_aborted(0),
	test_cases_timed_out(0), test_suites_timed_out(0), duration_milliseconds(0), exit_status(0), signal(0)
{ return ; }

ResultCollector::~ResultCollector( void )
{ return ; }

ResultCollector::ResultCollector( const ResultCollector& src )
: timed_out(src.timed_out), aborted(src.aborted), test_cases_passed(src.test_cases_passed), test_cases_failed(src.test_cases_failed),
	test_cases_aborted(src.test_cases_aborted), test_cases_timed_out(src.test_cases_timed_out), test_suites_timed_out(src.test_suites_timed_out),
	duration_milliseconds(src.duration_milliseconds), exit_status(src.exit_status), signal(src.signal)
{ return ; }

ResultCollector&
ResultCollector::operator=( const ResultCollector& rhs )
{
	(void)rhs;
	return (*this);
}

void
ResultCollector::get_results( void )
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
ResultCollector::get_exit_status( int status )
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

}