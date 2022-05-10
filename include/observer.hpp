#ifndef __OBSERVER__H__
# define __OBSERVER__H__

#include <forward_decl.hpp>
#include <global_typedefs.hpp>

namespace unit_test {

// ************************************************************************** //
// **************                 test_observer                ************** //
// ************************************************************************** //

class test_observer {
public:

    virtual void    test_start( counter_t /* number_of_test_cases */, test_unit_id /* root_test_unit_id */ ) {}
    virtual void    test_finish() {}
    virtual void    test_aborted() {}

    virtual void    test_unit_start( test_unit const& /* test */) {}
    virtual void    test_unit_finish( test_unit const& /* test */, unsigned long /* elapsed */ ) {}
    virtual void    test_unit_skipped( test_unit const& ) {}
    virtual void    test_unit_timed_out( test_unit const& ) {}
    virtual void    test_unit_aborted( test_unit const& ) {}

    // virtual void    assertion_result( unit_test::assertion_result /* ar */ ) {}
    // virtual void    exception_caught( execution_exception const& ) {}

    virtual int     priority() { return 0; }

protected:

    virtual ~test_observer() {}
};

#endif