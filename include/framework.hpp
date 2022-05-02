#ifndef __FRAMEWORK__H__
# define __FRAMEWORK__H__

# include "global_typedefs.hpp"
# include "forward_decl.hpp"

// STL
# include <string>

namespace unit_test {

typedef test_suite* (*init_unit_test_ft)( int, char* [] );

namespace framework {

void					init( init_unit_test_ft init_func, int argc, char* argv[] );
void					shutdown();

test_suite&				current_auto_test_suite( test_suite* ts = 0, bool push_or_pop = true );
void					register_test_unit( test_case* tc );
void					register_test_unit( test_suite* ts );
void					deregister_test_unit( test_unit* tu );
void					clear();

master_test_suite_t&	master_test_suite();
test_unit const&		current_test_unit();
test_case const&		current_test_case();
test_unit_id			current_test_case_id();
test_unit&				get( test_unit_id tu_id, test_unit_type tu_type );

template<typename UnitType>
inline UnitType&		get( test_unit_id id )
{
    return static_cast<UnitType&>( get( id, static_cast<test_unit_type>(UnitType::type) ) );
}

void					run( test_unit_id tu = INV_TEST_UNIT_ID, bool continue_test = true );
void					run( test_unit const* tu, bool continue_test = true );

namespace impl {
struct master_test_suite_name_setter {
	master_test_suite_name_setter( std::string name );
};
}	// namespace impl
}	// namespace framework
}	// namespace unit_test

#endif