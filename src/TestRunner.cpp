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
TestRunner::print_suite_results( ResultCollector& results, unsigned count )
{
	unsigned passed = results.test_cases_passed;
	unsigned failed = results.test_cases_failed;
	unsigned aborted = results.test_cases_aborted;

	std::cout << "===> ";
	if (passed == count)
		std::cout << "No errors detected" << std::endl;
	else
	{
		std::cout 
			<< YEL << failed << RESET << " failed, "
			<< RED << aborted << RESET << " aborted, "
			<< GRN << passed << RESET << " passed."
		<< std::endl;
	}
	std::cout << std::endl;
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
TestRunner::run_suite( TestSuite& suite )
{
	ResultCollector	results;
	chrono			chrono;

	std::cout << "Entering test suite " << "\"" << suite.name << "\"" << std::endl;
	std::cout << "Running " << suite.size() << " " << ((suite.size() > 1) ? "tests" : "test") << "..." << std::endl;
	chrono.start();
	for (TestSuite::iterator it = suite.begin(); it != suite.end(); it++)
	{
		std::cout << "Entering test case " << "\"" << it->name << "\"" << std::endl;
		run_test(*it);
		results.get_results();
		std::cout << "Leaving test case " << "\"" << it->name
					<< "\"; testing time: " << results.duration_milliseconds << "ms" << std::endl;
	}
	chrono.end();
	results.duration_milliseconds = chrono.get_execution_time();
	std::cout << "Leaving test suite " << "\"" << suite.name
				<< "\"; testing time: " << results.duration_milliseconds << "ms" << std::endl;
	print_suite_results(results, suite.size());
}

void
TestRunner::run_all( void )
{
	ResultCollector	results;
	chrono			chrono;

	chrono.start();
	std::for_each(MasterSuite::instance().begin(), MasterSuite::instance().end(), run_suite);
	chrono.end();
	results.duration_milliseconds = chrono.get_execution_time();
	std::cout << std::endl << "Total elapsed time: " << results.duration_milliseconds << "ms" << std::endl;

}

}	// namespace unit_test