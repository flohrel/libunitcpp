#ifndef __VISITOR__H__
# define __VISITOR__H__

# include "test_unit.hpp"

namespace unit_test {

class test_tree_visitor {
public:
    // test tree visitor interface
    virtual bool    visit( test_unit const& )                   { return true; }
    virtual void    visit( test_case const& tc )                { visit( (test_unit const&)tc ); }
    virtual bool    test_suite_start( test_suite const& ts )    { return visit( (test_unit const&)ts ); }
    virtual void    test_suite_finish( test_suite const& )      {}

protected:
    virtual ~test_tree_visitor() {}
};

} // namespace unit_test

#endif