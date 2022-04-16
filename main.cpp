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
	unit_test::TestRunner	runner;

	unit_test::TestCase		test1("size test", size_test);
	unit_test::TestSuite	suite1("suite1");
	suite1.push_back(test1);
	unit_test::TestSuite	suite2("suite2");

	unit_test::MasterSuite::instance().push_back(suite1);
	unit_test::MasterSuite::instance().push_back(suite2);

	
	runner.run_all();
	return (0);

}
