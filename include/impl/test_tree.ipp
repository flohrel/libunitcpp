#ifndef __TEST_TREE__I__
# define __TEST_TREE__I__

# include "framework.hpp"
# include "test_unit.hpp"
# include "visitor.hpp"
# include "traverse.hpp"
# include "auto_registration.hpp"

// STL
# include <cassert>
# include <algorithm>
# include <string>
# include <vector>
# include <set>

namespace unit_test {

// ************************************************************************** //
// **************                   test_unit                  ************** //
// ************************************************************************** //

test_unit::test_unit( std::string name, std::string file_name, std::size_t line_num, test_unit_type t )
: p_type( t )
, p_type_name( t == TUT_CASE ? "case" : "suite" )
, p_file_name( file_name )
, p_line_num( line_num )
, p_id( INV_TEST_UNIT_ID )
, p_parent_id( INV_TEST_UNIT_ID )
, p_name( name )
, p_timeout( 0 )
, p_expected_failures( 0 )
, p_sibling_rank(0)
, p_default_status( RS_INHERIT )
, p_run_status( RS_INVALID )
{
}

test_unit::test_unit( std::string module_name )
: p_type( TUT_SUITE )
, p_type_name( "module" )
, p_line_num( 0 )
, p_id( INV_TEST_UNIT_ID )
, p_parent_id( INV_TEST_UNIT_ID )
, p_name( module_name )
, p_timeout( 0 )
, p_expected_failures( 0 )
, p_sibling_rank(0)
, p_default_status( RS_INHERIT )
, p_run_status( RS_INVALID )
{
}

test_unit::~test_unit()
{
    framework::deregister_test_unit( this );
}

void
test_unit::increase_exp_fail( counter_t num )
{
    p_expected_failures += num;

    if( p_parent_id != INV_TEST_UNIT_ID )
        framework::get<test_suite>( p_parent_id ).increase_exp_fail( num );
}

std::string
test_unit::full_name() const
{
    if( p_parent_id == INV_TEST_UNIT_ID || p_parent_id == framework::master_test_suite().p_id )
        return p_name;

    std::string res = framework::get<test_suite>( p_parent_id ).full_name();
    res.append("/");

    res.append( p_name );

    return res;
}

// ************************************************************************** //
// **************                   test_case                  ************** //
// ************************************************************************** //

test_case::test_case( std::string name, test_ft test_func )
: test_unit( name, "", 0, static_cast<test_unit_type>(type) )
, p_test_func( test_func )
{
    framework::register_test_unit( this );
}

test_case::test_case( std::string name, std::string file_name, std::size_t line_num, test_ft test_func )
: test_unit( name, file_name, line_num, static_cast<test_unit_type>(type) )
, p_test_func( test_func )
{
    framework::register_test_unit( this );
}

// ************************************************************************** //
// **************                  test_suite                  ************** //
// ************************************************************************** //

test_suite::test_suite( std::string name, std::string file_name, std::size_t line_num )
: test_unit( ut_detail::normalize_test_case_name( name ), file_name, line_num, static_cast<test_unit_type>(type) )
{
    framework::register_test_unit( this );
}

test_suite::test_suite( std::string module_name )
: test_unit( module_name )
{
    framework::register_test_unit( this );
}

void
test_suite::add( test_unit* tu, counter_t expected_failures, unsigned timeout )
{
    tu->p_timeout = timeout;

    m_children.push_back( tu->p_id );
    tu->p_parent_id = p_id;

    if( tu->p_expected_failures != 0 )
        increase_exp_fail( tu->p_expected_failures );

    if( expected_failures )
        tu->increase_exp_fail( expected_failures );
}

void
test_suite::remove( test_unit_id id )
{
    test_unit_id_list::iterator it = std::find( m_children.begin(), m_children.end(), id );

    if( it != m_children.end() )
        m_children.erase( it );
}

test_unit_id
test_suite::get( std::string tu_name ) const
{
    for( test_unit_id_list::const_iterator it = m_children.begin();
        it != m_children.end();
        it++ ) {
        if( tu_name == framework::get( (*it), ut_detail::test_id_2_unit_type( (*it) ) ).p_name )
            return (*it);
    }

    return INV_TEST_UNIT_ID;
}

// ************************************************************************** //
// **************               master_test_suite              ************** //
// ************************************************************************** //

master_test_suite_t::master_test_suite_t()
: test_suite( "Master Test Suite" )
, argc( 0 )
, argv( 0 )
{
}

// ************************************************************************** //
// **************               traverse_test_tree             ************** //
// ************************************************************************** //

void
traverse_test_tree( test_case const& tc, test_tree_visitor& V, bool ignore_status )
{
    if( tc.is_enabled() || ignore_status )
        V.visit( tc );
}

void
traverse_test_tree( test_suite const& suite, test_tree_visitor& V, bool ignore_status )
{
    // skip disabled test suite unless we asked to ignore this condition
    if( !ignore_status && !suite.is_enabled() )
        return;

    // Invoke test_suite_start callback
    if( !V.test_suite_start( suite ) )
        return;

    // Recurse into children
    std::size_t total_children = suite.m_children.size();
    for( std::size_t i=0; i < total_children; ) {
        // this statement can remove the test unit from this list
        traverse_test_tree( suite.m_children[i], V, ignore_status );
        if( total_children > suite.m_children.size() )
            total_children = suite.m_children.size();
        else
            ++i;
    }

    // Invoke test_suite_finish callback
    V.test_suite_finish( suite );
}

//____________________________________________________________________________//

void
traverse_test_tree( test_unit_id id, test_tree_visitor& V, bool ignore_status )
{
    if( ut_detail::test_id_2_unit_type( id ) == TUT_CASE )
        traverse_test_tree( framework::get<test_case>( id ), V, ignore_status );
    else
        traverse_test_tree( framework::get<test_suite>( id ), V, ignore_status );
}

// ************************************************************************** //
// **************               object generators              ************** //
// ************************************************************************** //

namespace ut_detail {

std::string
normalize_test_case_name( std::string name )
{
	std::string norm_name( name );

    if( name[0] == '&' )
        norm_name = norm_name.substr( 1 );

    // trim spaces
	std::size_t first_not_space = norm_name.find_first_not_of(' ');
    if( first_not_space ) {
        norm_name.erase(0, first_not_space);
    }

    std::size_t last_not_space = norm_name.find_last_not_of(' ');
    if( last_not_space != std::string::npos ) {
        norm_name.erase(last_not_space + 1);
    }

    // sanitize all chars that might be used in runtime filters
    static const char to_replace[] = { ':', '*', '@', '+', '!', '/', ',' };
    for(std::size_t index = 0;
        index < sizeof(to_replace)/sizeof(to_replace[0]);
        index++) {
        std::replace(norm_name.begin(), norm_name.end(), to_replace[index], '_');
    }

    return (norm_name);
}

// ************************************************************************** //
// **************           auto_test_unit_registrar           ************** //
// ************************************************************************** //

auto_test_unit_registrar::auto_test_unit_registrar( test_case* tc/*, decorator::collector_t& decorators*/, counter_t exp_fail )
{
    framework::current_auto_test_suite().add( tc, exp_fail );

	// decorators.store_in( *tc );
	// decorators.reset();
}

auto_test_unit_registrar::auto_test_unit_registrar( std::string ts_name, std::string ts_file, std::size_t ts_line/*, decorator::collector_t& decorators*/ )
{
    test_unit_id id = framework::current_auto_test_suite().get( ts_name );

    test_suite* ts;

    if( id != INV_TEST_UNIT_ID ) {
        ts = &framework::get<test_suite>( id );
        assert( ts->p_parent_id == framework::current_auto_test_suite().p_id );
    }
    else {
        ts = new test_suite( ts_name, ts_file, ts_line );
        framework::current_auto_test_suite().add( ts );
    }

	// decorators.store_in( *ts );
	// decorators.reset();

    framework::current_auto_test_suite( ts );
}

auto_test_unit_registrar::auto_test_unit_registrar( int )
{
    framework::current_auto_test_suite( 0, false );
}

}	// namespace ut_detail
}	// namespace unit_test

#endif