#ifndef __AUTO_REGISTRATION__H__
# define __AUTO_REGISTRATION__H__

# include "test_unit.hpp"

// STL
# include <list>

namespace unit_test {
namespace ut_detail {

struct auto_test_unit_registrar {
    // Constructors
				auto_test_unit_registrar( test_case* tc, /*decorator::collector_t& decorators,*/ counter_t exp_fail = 0 );
    explicit	auto_test_unit_registrar( ::std::string ts_name, ::std::string ts_file, ::std::size_t ts_line/*, decorator::collector_t& decorators*/ );
    explicit	auto_test_unit_registrar( int );
};

}	// namespace ut_detail
}	// namespace unit_test

#endif