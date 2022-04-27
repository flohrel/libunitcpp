#include "random.hpp"
#include <algorithm>

void	func( char nb )
{
	std::cout << nb << std::endl;
}

int main(void)
{
	// std::vector< unit_test::Random<char> >	array(100);

	// std::for_each(array.begin(), array.end(), func);

	unit_test::RandomString	str(25);

	std::cout << str << std::endl;

	return (0);
}