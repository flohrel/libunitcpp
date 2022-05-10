#ifndef __TEST_UNIT__H__
# define __TEST_UNIT__H__

# include "global_typedefs.hpp"
# include "forward_decl.hpp"
# include "framework.hpp"

# include <vector>
# include <string>
# include <map>

namespace unit_test {

namespace framework {
  class state;

  master_test_suite_t& master_test_suite();
}

typedef std::vector<test_unit_id> test_unit_id_list;

// ************************************************************************** //
// **************                   test_unit                  ************** //
// ************************************************************************** //

class test_unit {
public:
    enum { type = TUT_ANY };
    enum run_status { RS_DISABLED, RS_ENABLED, RS_INHERIT, RS_INVALID };

	typedef std::vector<test_unit_id>					id_list;
	typedef test_unit_id								id_t;
	typedef test_unit_id								parent_id_t;
	typedef id_list										id_list_t;

    void												increase_exp_fail( counter_t num );
    bool                                                is_enabled() const    { return p_run_status == RS_ENABLED; }
    std::string					    					full_name( void ) const;

	test_unit_type const								p_type;					///< type for this test unit
	std::string const									p_type_name;			///< "case"/"suite"/"module"
	std::string const									p_file_name;
	std::size_t const									p_line_num;
	id_t												p_id;					///< unique id for this test unit
	parent_id_t											p_parent_id;			///< parent test suite id	

	std::string										    p_name;					///< name for this test unit
	unsigned											p_timeout;				///< timeout for the test unit execution in seconds
	counter_t											p_expected_failures;	///< number of expected failures in this test unit

    run_status                                          p_default_status;       ///< run status obtained by this unit during setup phase
    run_status                                          p_run_status;           ///< run status assigned to this unit before execution phase after applying all filters

    counter_t											p_sibling_rank;			///< rank of this test unit amoung siblings of the same parent

protected:
    ~test_unit( void );
    // Constructor
    test_unit( std::string tu_name, std::string tc_file, std::size_t tc_line, test_unit_type t );
    // Master test suite constructor
    explicit	test_unit( std::string module_name );
};

// ************************************************************************** //
// **************              test_unit_generator             ************** //
// ************************************************************************** //

class test_unit_generator {
public:
    virtual test_unit*  next() const = 0;

protected:
    virtual ~test_unit_generator() {}
};

// ************************************************************************** //
// **************                   test_case                  ************** //
// ************************************************************************** //

class test_case : public test_unit {
public:
    enum { type = TUT_CASE };

    // Constructor
    test_case( std::string tc_name, test_ft test_func );
    test_case( std::string tc_name, std::string tc_file, std::size_t tc_line, test_ft test_func );

    test_ft   p_test_func;

private:
    friend class framework::state;
    ~test_case() {}
};

// ************************************************************************** //
// **************                  test_suite                  ************** //
// ************************************************************************** //

//! Class representing test suites
class test_suite : public test_unit {
public:
    enum { type = TUT_SUITE };

    explicit		test_suite( std::string ts_name, std::string ts_file, std::size_t ts_line );

	void			add( test_unit* tu, counter_t expected_failures = 0, unsigned timeout = 0 );
	void			remove( test_unit_id id );
	// void			generate();
	void			check_for_duplicate_test_cases();

	test_unit_id        get( std::string tu_name ) const;
	std::size_t		    size() const { return m_children.size(); }

protected:
	explicit        test_suite( std::string module_name );

    friend void     traverse_test_tree( test_suite const&, test_tree_visitor&, bool );
	friend class	framework::state;
	virtual			~test_suite() {}

    typedef std::multimap<counter_t,test_unit_id> children_per_rank;

    test_unit_id_list   m_children;
    children_per_rank   m_ranked_children; ///< maps child sibling rank to list of children with that rank

};

// ************************************************************************** //
// **************            user_tc_method_invoker            ************** //
// ************************************************************************** //

namespace ut_detail {

std::string normalize_test_case_name( std::string tu_name );

template<typename InstanceType,typename UserTestCase>
struct user_tc_method_invoker {
    typedef void (UserTestCase::*TestMethod )();

    user_tc_method_invoker( InstanceType inst, TestMethod test_method )
    : m_inst( inst ), m_test_method( test_method ) {}

    void operator()() { ((*m_inst).*m_test_method)(); }

    InstanceType                m_inst;
    TestMethod                  m_test_method;
};

}   // namespace ut_detail


// ************************************************************************** //
// **************               master_test_suite              ************** //
// ************************************************************************** //

class master_test_suite_t : public test_suite {
private:
    master_test_suite_t();
    master_test_suite_t( const master_test_suite_t& ); // undefined
    master_test_suite_t& operator=( const master_test_suite_t& ); // undefined
  
public:
    // Data members
    int      argc;
    char**   argv;
    
    friend master_test_suite_t& unit_test::framework::master_test_suite();
};

namespace ut_detail {

std::string normalize_test_case_name( std::string tu_name );

}

// ************************************************************************** //
// **************                make_test_case                ************** //
// ************************************************************************** //

inline test_case*
make_test_case( test_ft test_func, std::string tc_name, std::string tc_file, std::size_t tc_line )
{
    return new test_case( ut_detail::normalize_test_case_name( tc_name ), tc_file, tc_line, test_func );
}

}

#endif