#include "random.hpp"
#include <algorithm>

int main(void)
{
	// std::vector< unit_test::Random<char> >	array(100);

	// std::for_each(array.begin(), array.end(), func);

	// unit_test::RandomString	str(25);

	// std::vector< unit_test::RandomString > array(10, unit_test::RandomString(25));

	// std::for_each(array.begin(), array.end(), func);

	std::map< std::string, int > map;

	unit_test::MapGenerator< unit_test::StringGenerator, unit_test::RandomGenerator<int> > random_map(20);

	map = static_cast<std::map< std::string, int > >(random_map);

	for (std::map< std::string, int >::iterator it = map.begin(); it != map.end(); it++)
	{
		std::cout << "key=" << (*it).first << "/value=" << (*it).second << std::endl;
	}

	return (0);
}