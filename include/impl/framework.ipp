#ifndef __FRAMEWORK__IPP__
# define __FRAMEWORK__IPP__

# include "framework.hpp"
# include "test_unit.hpp"
# include "visitor.hpp"
# include "traverse.hpp"
# include "global_typedefs.hpp"

// STL
# include <cassert>
// #include <limits>
// #include <map>
// #include <set>
// #include <cstdlib>
// #include <ctime>
// #include <numeric>
// #include <cmath>
// #include <iterator>

namespace unit_test {
namespace framework {

namespace impl {

// ************************************************************************** //
// **************            test_init call wrapper            ************** //
// ************************************************************************** //

static void
invoke_init_func( init_unit_test_ft init_func )
{
    test_suite*  manual_test_units = (*init_func)( framework::master_test_suite().argc, framework::master_test_suite().argv );

    if ( manual_test_units )
        framework::master_test_suite().add( manual_test_units );
}

}	// namespace impl

// ************************************************************************** //
// **************               framework::state               ************** //
// ************************************************************************** //

unsigned long int const TIMEOUT_EXCEEDED = static_cast<unsigned long int>( -1 );

class state {
public:
    state()
    : m_master_test_suite( 0 )
    , m_curr_test_unit( INV_TEST_UNIT_ID )
    , m_next_test_case_id( MIN_TEST_CASE_ID )
    , m_next_test_suite_id( MIN_TEST_SUITE_ID )
    , m_test_in_progress( false )
    {
    }

    ~state() { clear(); }

    void            clear()
    {
        while( !m_test_units.empty() ) {
            test_unit_store::value_type const& tu     = *m_test_units.begin();
            test_unit const*                   tu_ptr = tu.second;

            // the delete will erase this element from map
            if( ut_detail::test_id_2_unit_type( tu.second->p_id ) == TUT_SUITE )
                delete static_cast<test_suite const*>(tu_ptr);
            else
                delete static_cast<test_case const*>(tu_ptr);
        }
    }

    void            set_tu_id( test_unit& tu, test_unit_id id ) { tu.p_id = id; }

    int execute_test_tree( test_unit_id tu_id )
    {
        int result = 0;

        test_unit const& tu = framework::get( tu_id, TUT_ANY );

        if( tu.p_type == TUT_SUITE ) {
            test_suite const& ts = static_cast<test_suite const&>( tu );

            for (std::vector<test_unit_id>::const_iterator tc = ts.m_children.begin(); tc != ts.m_children.end(); tc++)
            {
                result |= execute_test_tree( *tc );
            }
        }
        else {
            test_case const& tc = static_cast<test_case const&>( tu );

            tc.p_test_func();
        }

        return result;
    }

	    // Data members
    typedef std::map<test_unit_id,test_unit*>       test_unit_store;
    // typedef ::std::set<test_observer*,priority_order> observer_store;

    master_test_suite_t*			m_master_test_suite;
    std::vector<test_suite*>		m_auto_test_suites;

    test_unit_id					m_curr_test_unit;
    test_unit_store					m_test_units;

    test_unit_id					m_next_test_case_id;
    test_unit_id					m_next_test_suite_id;

    bool							m_test_in_progress;

    // observer_store				m_observers;

	// ::std::set<global_fixture*>  m_global_fixtures;

    // execution_monitor			m_execution_monitor

};

namespace impl {
namespace {

framework::state& s_frk_state() { static framework::state the_inst; return the_inst; }

}	// local namespace
}	// namespace impl

void
init( init_unit_test_ft init_func, int argc, char* argv[] )
{
	// runtime_config::init( argc, argv );

	// register_observer( results_collector );
	// register_observer( unit_test_log );

	master_test_suite().argc = argc;
	master_test_suite().argv = argv;

    impl::invoke_init_func( init_func );
    // s_frk_state().m_execution_monitor.execute( &impl::invoke_init_func( init_func ) );
}

// ************************************************************************** //
// **************              register_test_unit              ************** //
// ************************************************************************** //

void
register_test_unit( test_case* tc )
{
    assert( tc->p_id == INV_TEST_UNIT_ID ); // BOOST_TEST_L( "test case already registered" ) );

    test_unit_id new_id = impl::s_frk_state().m_next_test_case_id;

    assert( new_id != MAX_TEST_CASE_ID ); // BOOST_TEST_L( "too many test cases" ) );

    typedef state::test_unit_store::value_type map_value_type;

    impl::s_frk_state().m_test_units.insert( map_value_type( new_id, tc ) );
    impl::s_frk_state().m_next_test_case_id++;

    impl::s_frk_state().set_tu_id( *tc, new_id );
}

// ************************************************************************** //
// **************              register_test_unit              ************** //
// ************************************************************************** //

void
register_test_unit( test_suite* ts )
{
    assert( ts->p_id == INV_TEST_UNIT_ID ); // BOOST_TEST_L( "test suite already registered" ) );

    test_unit_id new_id = impl::s_frk_state().m_next_test_suite_id;

    assert( new_id != MAX_TEST_SUITE_ID ); // BOOST_TEST_L( "too many test suites" ) );

    typedef state::test_unit_store::value_type map_value_type;

    impl::s_frk_state().m_test_units.insert( map_value_type( new_id, ts ) );
    impl::s_frk_state().m_next_test_suite_id++;

    impl::s_frk_state().set_tu_id( *ts, new_id );
}

// ************************************************************************** //
// **************             deregister_test_unit             ************** //
// ************************************************************************** //

void
deregister_test_unit( test_unit* tu )
{
    impl::s_frk_state().m_test_units.erase( tu->p_id );
}

// ************************************************************************** //
// **************                     clear                    ************** //
// ************************************************************************** //

void
clear()
{
    impl::s_frk_state().clear();
}

// ************************************************************************** //
// **************               register_observer              ************** //
// ************************************************************************** //

// void
// register_observer( test_observer& to )
// {
//     impl::s_frk_state().m_observers.insert( &to );
// }

// ************************************************************************** //
// **************              deregister_observer             ************** //
// ************************************************************************** //

// void
// deregister_observer( test_observer& to )
// {
//     impl::s_frk_state().m_observers.erase( &to );
// }

// ************************************************************************** //
// **************           register_global_fixture            ************** //
// ************************************************************************** //

// void
// register_global_fixture( global_fixture& tuf )
// {
//     impl::s_frk_state().m_global_fixtures.insert( &tuf );
// }

// ************************************************************************** //
// **************           deregister_global_fixture          ************** //
// ************************************************************************** //

// void
// deregister_global_fixture( global_fixture &tuf )
// {
//     impl::s_frk_state().m_global_fixtures.erase( &tuf );
// }

// ************************************************************************** //
// **************               master_test_suite              ************** //
// ************************************************************************** //

master_test_suite_t&
master_test_suite()
{
    if( !impl::s_frk_state().m_master_test_suite )
        impl::s_frk_state().m_master_test_suite = new master_test_suite_t;

    return *impl::s_frk_state().m_master_test_suite;
}

namespace impl {

master_test_suite_name_setter::master_test_suite_name_setter(std::string name) {
	name.erase( name.find_last_not_of( "\" " ) + 1 );
    name.erase( 0, name.find_first_not_of( "\" " ) );
	master_test_suite().p_name = name;
}

}

// ************************************************************************** //
// **************            current_auto_test_suite           ************** //
// ************************************************************************** //

test_suite&
current_auto_test_suite( test_suite* ts, bool push_or_pop )
{
    if( impl::s_frk_state().m_auto_test_suites.empty() )
        impl::s_frk_state().m_auto_test_suites.push_back( &framework::master_test_suite() );

    if( !push_or_pop )
        impl::s_frk_state().m_auto_test_suites.pop_back();
    else if( ts )
        impl::s_frk_state().m_auto_test_suites.push_back( ts );

    return *impl::s_frk_state().m_auto_test_suites.back();
}

// ************************************************************************** //
// **************               current_test_case              ************** //
// ************************************************************************** //

test_case const&
current_test_case()
{
    return get<test_case>( impl::s_frk_state().m_curr_test_unit );
}


test_unit const&
current_test_unit()
{
    return *impl::s_frk_state().m_test_units[impl::s_frk_state().m_curr_test_unit];
}

test_unit_id
current_test_case_id()
{
    return impl::s_frk_state().m_curr_test_unit;
}

test_unit&
get( test_unit_id id, test_unit_type t )
{
    test_unit* res = impl::s_frk_state().m_test_units[id];

    assert( (res->p_type & t) != 0 );		// Invalid test unit type

    return *res;
}

// ************************************************************************** //
// **************                framework::run                ************** //
// ************************************************************************** //

void
run( test_unit_id id )
{
    if( id == INV_TEST_UNIT_ID )
        id = master_test_suite().p_id;

    impl::s_frk_state().execute_test_tree( id );
}

void
run( test_unit const* tu )
{
    run( tu->p_id );
}

}	// namespace framework
}	// namespace unit_test

#endif