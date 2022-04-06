#include "libunitcpp.hpp"
#include <iostream>
#include <vector>

struct fixture
{
	std::vector<int>	v;

	fixture() : v() { };
	~fixture() { }
};

void	size_test( void )
{
	fixture f;

	assert( f.v.size() == 0 );
}

int	main( void )
{
	TestRunner	runner;

	TestSuite	suite1("suite1");
	TestSuite	suite2("suite2");

	TestSuite::add(suite1);
	TestSuite::add(suite2);

	TestCase test1("size test", size_test);
	suite1.add(test1);
	
	runner.run_all();

}
