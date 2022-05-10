#ifndef __UNIT_TEST_SUITE__H__
# define __UNIT_TEST_SUITE__H__

# include "framework.hpp"

// ************************************************************************** //
// **************   Auto registration facility helper macros   ************** //
// ************************************************************************** //

#if defined(__COUNTER__)
  #define TEST_INTERNAL_HAS_COUNTER
#endif

#if defined(TEST_INTERNAL_HAS_COUNTER)
# define TEST_APPEND_UNIQUE_ID( name ) \
    JOIN( JOIN( name, __LINE__ ), __COUNTER__)
    /**/
#else
    #define TEST_APPEND_UNIQUE_ID( name ) \
    JOIN( name, __LINE__ )
    /**/
#endif
/**/

#define TU_REGISTRAR( test_name )                                                       \
static unit_test::ut_detail::auto_test_unit_registrar                                   \
TEST_APPEND_UNIQUE_ID( JOIN( test_name, _registrar ) ) __attribute__ ((__unused__))     \
/**/
#define TC_INVOKER( test_name )      JOIN( test_name, _invoker )
#define TC_UNIQUE_ID( test_name )    JOIN( test_name, _id )

// ************************************************************************** //
// **************             TEST_SUITE                  ************** //
// ************************************************************************** //

#define TEST_SUITE_NO_DECOR( suite_name )       \
namespace suite_name {                          \
TU_REGISTRAR( suite_name )(                     \
    STRINGIZE( suite_name ),                    \
    __FILE__, __LINE__);                        \

#define TEST_SUITE( suite_name )        \
    TEST_SUITE_NO_DECOR( suite_name )   \
/**/

// ************************************************************************** //
// **************           TEST_SUITE_END                ************** //
// ************************************************************************** //

#define TEST_SUITE_END()            \
TU_REGISTRAR( end_suite )( 1 );     \
}                                   \
/**/

// ************************************************************************** //
// **************               TEST_CASE                 ************** //
// ************************************************************************** //

#define TEST_CASE( test_name )                              \
struct test_name { void test_method(); };                   \
                                                            \
static void TC_INVOKER( test_name )()                       \
{                                                           \
    test_name t;                                            \
    t.test_method();                                        \
}                                                           \
                                	                        \
struct TC_UNIQUE_ID( test_name ) {};                       	\
                                                            \
TU_REGISTRAR( test_name )(                                 	\
    unit_test::make_test_case(							    \
        &TC_INVOKER( test_name ),                          	\
        #test_name, __FILE__, __LINE__ ));                  \
                                                            \
void test_name::test_method()								\
/**/

// ************************************************************************** //
// **************                   TEST_MAIN                  ************** //
// ************************************************************************** //

# ifdef TEST_MODULE
	static const unit_test::framework::impl::master_test_suite_name_setter	mtsetter( STRINGIZE( TEST_MODULE ) );
# endif

unit_test::test_suite*
init_unit_test_suite( int, char* [] )
{
    return 0;
}

#endif