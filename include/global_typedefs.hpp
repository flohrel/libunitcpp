#ifndef __GLOBAL_TYPEDEFS__H__
# define __GLOBAL_TYPEDEFS__H__

// Concatenates strings
# define UCPP_JOIN_IMPL_(foo, bar) foo##bar
# define UCPP_JOIN(foo, bar) UCPP_JOIN_IMPL_(foo, bar)

// Creates a string literal, enclosing the argument between quotes
# define UCPP_STRINGIZE(name) #name

namespace unit_test {

typedef unsigned long   counter_t;

enum test_unit_type { TUT_CASE = 0x01, TUT_SUITE = 0x10, TUT_ANY = 0x11 };

typedef unsigned long   test_unit_id;

const test_unit_id INV_TEST_UNIT_ID  = 0xFFFFFFFF;
const test_unit_id MAX_TEST_CASE_ID  = 0xFFFFFFFE;
const test_unit_id MIN_TEST_CASE_ID  = 0x00010000;
const test_unit_id MAX_TEST_SUITE_ID = 0x0000FF00;
const test_unit_id MIN_TEST_SUITE_ID = 0x00000001;

namespace ut_detail {

inline test_unit_type
test_id_2_unit_type( test_unit_id id )
{
    return (id & 0xFFFF0000) != 0 ? TUT_CASE : TUT_SUITE;
}

} // namespace ut_detail

template< typename T >
class singleton
{
	public:
        static T&		instance() { static T instance; return (instance); }


	protected:
		singleton() { return ; }
		~singleton() { return ; }


	private:
		singleton( singleton const& src ) { (void)src; return; }
        singleton&	operator=( singleton const& ) { return (*this); }

};

}	// namespace unit_test

#endif