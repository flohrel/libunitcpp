#ifndef __TRAVERSE__H__
# define __TRAVERSE__H__

# include "test_unit.hpp"
# include "visitor.hpp"

namespace unit_test {

void    traverse_test_tree( test_case const&, test_tree_visitor&, bool ignore_status = false );
void    traverse_test_tree( test_suite const&, test_tree_visitor&, bool ignore_status = false );
void    traverse_test_tree( test_unit_id     , test_tree_visitor&, bool ignore_status = false );

inline void
traverse_test_tree( test_unit const& tu, test_tree_visitor& V, bool ignore_status = false )
{
    if( tu.p_type == TUT_CASE )
        traverse_test_tree( static_cast<test_case const&>( tu ), V, ignore_status );
    else
        traverse_test_tree( static_cast<test_suite const&>( tu ), V, ignore_status );
}

} // namespace unit_test

#endif