#ifndef __LIBUNITCPP__H__
# define __LIBUNITCPP__H__

# include "impl/framework.ipp"
# include "impl/test_tree.ipp"
# include "impl/unit_test_main.ipp"

# include "unit_test_suite.hpp"
# include "utils/random.hpp"
# include "utils/ansi_colors.hpp"
# include <cstdlib>
# include <cassert>

# include "framework.hpp"
# include "test/TestSuite.hpp"
# include "test/TestRunner.hpp"
# include "utils/random.hpp"

namespace unit_test {

int	unit_test_main( init_unit_test_ft init_func, int argc, char* argv[] );

}

#endif