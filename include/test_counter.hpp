#ifndef __TEST_COUNTER__H__
# define __TEST_COUNTER__H__

# include "test_unit.hpp"
# include "visitor.hpp"

// ************************************************************************** //
// **************                test_case_counter             ************** //
// ************************************************************************** //

///! Counts the number of enabled test cases
class test_case_counter : public test_tree_visitor {
public:
    // Constructor
    // @param ignore_disabled ignore the status when counting
    test_case_counter(bool ignore_status = false)
    : p_count( 0 )
    , m_ignore_status(ignore_status)
    {}

    counter_t	p_count;

private:
    // test tree visitor interface
    void    visit( test_case const& tc )                { if( m_ignore_status || tc.is_enabled() ) ++p_count.value; }
    bool    test_suite_start( test_suite const& ts )    { return m_ignore_status || ts.is_enabled(); }
  
    bool m_ignore_status;
};

#endif