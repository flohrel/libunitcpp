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

#define AUTO_TU_REGISTRAR( test_name )                                                          \
static unit_test::ut_detail::auto_test_unit_registrar                                           \
TEST_APPEND_UNIQUE_ID( JOIN( test_name, _registrar ) ) __attribute__ ((__unused__))             \
/**/
#define AUTO_TC_INVOKER( test_name )      JOIN( test_name, _invoker )
#define AUTO_TC_UNIQUE_ID( test_name )    JOIN( test_name, _id )

// ************************************************************************** //
// **************             AUTO_TEST_SUITE                  ************** //
// ************************************************************************** //

#define AUTO_TEST_SUITE_NO_DECOR( suite_name )					    \
namespace suite_name {											    \
AUTO_TU_REGISTRAR( suite_name )(								    \
    STRINGIZE( suite_name ),								    	\
    __FILE__, __LINE__);								    		\

#define AUTO_TEST_SUITE( suite_name )			    				\
    AUTO_TEST_SUITE_NO_DECOR( suite_name )		    				\
/**/

// ************************************************************************** //
// **************           AUTO_TEST_SUITE_END                ************** //
// ************************************************************************** //

#define AUTO_TEST_SUITE_END()                                       \
AUTO_TU_REGISTRAR( end_suite )( 1 );                                \
}                                                                   \
/**/

// ************************************************************************** //
// **************               AUTO_TEST_CASE                 ************** //
// ************************************************************************** //

#define AUTO_TEST_CASE( test_name )                                 \
struct test_name { void test_method(); };		                	\
                                                                	\
static void AUTO_TC_INVOKER( test_name )()                      	\
{                                                               	\
    test_name t;                                                	\
    t.test_method();                                            	\
}                                                               	\
                                	                        		\
struct AUTO_TC_UNIQUE_ID( test_name ) {};                       	\
                                                                    \
AUTO_TU_REGISTRAR( test_name )(                                 	\
    unit_test::make_test_case(										\
        &AUTO_TC_INVOKER( test_name ),                          	\
        #test_name, __FILE__, __LINE__ ));                          \
                                                            		\
void test_name::test_method()										\
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