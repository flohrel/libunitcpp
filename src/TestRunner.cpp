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
TestRunner::run_test( TestCase& unit )
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
		unit();
	}
	else
	{
		_chrono.start();
	}
}

void
TestRunner::run_suite( TestSuite& unit )
{
	TestRunner::unit_iter current = unit.suite.begin();
	TestRunner::unit_iter end = unit.suite.end();
	int32_t	status;

	std::cout << unit.suite.size() << std::endl;
	for (; current != end; current++)
	{
		TestCase *curr_tc = static_cast<TestCase *>(&(*current));
		run_test(*curr_tc);
		wait(&status);
		_chrono.end();
		std::cout << _chrono.get_execution_time() << "ms" << std::endl;
	}
}

void
TestRunner::run_all( void )
{
	TestRunner::unit_iter current = MasterSuite::instance().suite.begin();
	TestRunner::unit_iter end = MasterSuite::instance().suite.end();

	for (; current != end; current++)
	{
		if ((*current).get_type() == t_suite)
		{
			TestSuite *curr_ts = static_cast<TestSuite *>(&(*current));
			run_suite(*curr_ts);
		}
		else
		{
			run_test(*static_cast<TestCase *>(&(*current)));
		}
	}
}

}	// namespace unit_test