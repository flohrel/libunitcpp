#include "TestRunner.hpp"

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
TestRunner::run_test( const TestCase& unit )
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
TestRunner::run_suite( const TestSuite& unit )
{
	TestRunner::tcase_iter current = unit.suite.begin();
	TestRunner::tcase_iter end = unit.suite.end();
	int32_t	status;

	std::cout << unit.suite.size() << std::endl;
	for (; current != end; current++)
	{
		run_test(*current);
		wait(&status);
		_chrono.end();
		std::cout << _chrono.get_execution_time() << "ms" << std::endl;
	}

}

void
TestRunner::run_all( void )
{

	std::list<TestSuite>::iterator current = master_suite->begin();
	std::list<TestSuite>::iterator end = master_suite->end();

	for (; current != end; current++)
	{
		run_suite(*current);
	}
}

}	// namespace unit_test