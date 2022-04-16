#include "test/TestRunner.hpp"

namespace unit_test
{

TestRunner::TestRunner( void )
{
	return;
}

TestRunner::TestRunner( const TestRunner& src )
{
	(void)src;
	return;
}

TestRunner::~TestRunner( void )
{
	return;
}

TestRunner&
TestRunner::operator=( const TestRunner& rhs )
{
	(void)rhs;
	return (*this);
}

void
TestRunner::run_test( TestCase& test )
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		strerror(errno);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		test();
		alarm(test.timeout);
		exit(EXIT_SUCCESS);
	}
}

void
TestRunner::print_suite_results( TestSuite& suite )
{
	std::cout << std::endl;
	std::cout << "===> " << std::endl;
}

void
TestRunner::get_results( TestCase& test, TestSuite& suite )
{
	int32_t	status;
	chrono	chrono;

	chrono.start();
	wait(&status);
	chrono.end();
	test.results.duration_milliseconds = chrono.get_execution_time();
	ResultCollector::get_exit_status(status, test, suite);
}

void
TestRunner::run_suite( TestSuite& suite )
{
	std::cout << "Running " << GRN << suite.size() << RESET << " tests..." << std::endl;
	for (TestSuite::iterator it = suite.begin(); it != suite.end(); it++)
	{
		run_test(*it);
		get_results(*it, suite);
	}
	print_suite_results(suite);
}

void
TestRunner::run_all( void )
{
	std::for_each(MasterSuite::instance().begin(), MasterSuite::instance().end(), run_suite);
}

}	// namespace unit_test