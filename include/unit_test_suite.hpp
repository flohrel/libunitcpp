#ifndef __UNIT_TEST_SUITE__H__
# define __UNIT_TEST_SUITE__H__

# include "framework.hpp"

# ifdef TEST_MODULE
	static const unit_test::framework::impl::master_suite_name_setter	mtsetter(STRINGIZE( TEST_MODULE ));
# endif

::unit_test::test_suite*
init_unit_test_suite( int, char* [] )
{
    return 0;
}

#endif