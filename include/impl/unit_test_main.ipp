#ifndef __UNIT_TEST_MAIN__I__
# define __UNIT_TEST_MAIN__I__

# include "framework.hpp"
# include "test_unit.hpp"

namespace unit_test {

int
unit_test_main( init_unit_test_ft init_func, int argc, char* argv[] )
{
	int result_code = 0;

	framework::init( init_func, argc, argv );

	framework::run();

	// result_code = results_collector.results( framework::master_test_suite().p_id ).result_code();

	return (result_code);
}

}	// namespace unit_test

int
main( int argc, char* argv[] )
{
	extern unit_test::test_suite*	init_unit_test_suite( int argc, char* argv[] );

	unit_test::init_unit_test_ft init_func = &init_unit_test_suite;

    return (unit_test::unit_test_main( init_func, argc, argv ));
}

#endif