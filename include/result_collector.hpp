#ifndef __RESULT_COLLECTOR__H__
# define __RESULT_COLLECTOR__H__

#include <observer.hpp>

#include <global_typedefs.hpp>
#include <forward_decl.hpp>


namespace boost {
namespace unit_test {

namespace {

class test_results {
public:
    test_results();

    counter_t	p_test_suites;              //!< Number of test suites
    counter_t	p_assertions_passed;        //!< Number of successful assertions
    counter_t	p_assertions_failed;        //!< Number of failing assertions
    counter_t	p_warnings_failed;          //!< Number of warnings
    counter_t	p_expected_failures;
    counter_t	p_test_cases_passed;        //!< Number of successfull test cases
    counter_t	p_test_cases_warned;        //!< Number of warnings in test cases
    counter_t	p_test_cases_failed;        //!< Number of failing test cases
    counter_t	p_test_cases_skipped;       //!< Number of skipped test cases
    counter_t	p_test_cases_aborted;       //!< Number of aborted test cases
    counter_t	p_test_cases_timed_out;     //!< Number of timed out test cases
    counter_t	p_test_suites_timed_out;    //!< Number of timed out test suites
    counter_t	p_duration_microseconds;    //!< Duration of the test in microseconds
    bool		p_aborted;                  //!< Indicates that the test unit execution has been aborted
    bool		p_skipped;                  //!< Indicates that the test unit execution has been skipped
    bool		p_timed_out;                //!< Indicates that the test unit has timed out

    bool		passed() const;
    bool		skipped() const;
    bool		aborted() const;

    int 		result_code() const;

    void		operator+=( test_results const& );

    void		clear();
};

class results_collector_t : public test_observer {
public:

    void        test_start( counter_t, test_unit_id );

    void        test_unit_start( test_unit const& );
    void        test_unit_finish( test_unit const&, unsigned long );
    void        test_unit_skipped( test_unit const&, const_string );
    void        test_unit_aborted( test_unit const& );
    void        test_unit_timed_out( test_unit const& );

    // void        assertion_result( unit_test::assertion_result );
    // void        exception_caught( execution_exception const& );

    int         priority() { return 3; }

    test_results const& results( test_unit_id tu_id ) const;

    BOOST_TEST_SINGLETON_CONS( results_collector_t )
};

BOOST_TEST_SINGLETON_INST( results_collector )


#endif