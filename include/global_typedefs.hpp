#ifndef __GLOBAL_TYPEDEFS__H__
# define __GLOBAL_TYPEDEFS__H__

// Concatenates strings
# define JOIN_IMPL_(foo, bar) foo##bar
# define JOIN(foo, bar) JOIN_IMPL_(foo, bar)

// Creates a string literal, enclosing the argument between quotes
# define STRINGIZE(name) #name

namespace unit_test {

typedef unsigned long   counter_t;

enum test_unit_type { TUT_CASE = 0x01, TUT_SUITE = 0x10, TUT_ANY = 0x11 };

typedef unsigned long   test_unit_id;
typedef void   			 (*test_ft)();

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

#define SINGLETON_CONS_NO_CTOR( type )					\
public:                                                 \
	static type& instance();							\
private:                                                \
	type(type const&) {}								\
	type& operator=(type const&) {}						\
	~type() {}											\
/**/

#define SINGLETON_CONS( type )							\
	SINGLETON_CONS_NO_CTOR(type)						\
private:                                                \
	type(), {}											\
/**/

#define SINGLETON_CONS_IMPL( type )						\
	type& type::instance() {							\
		static type the_inst; return the_inst;			\
  }                                                     \
/**/

#define SINGLETON_INST( inst ) \
namespace { JOIN( inst, _t)& inst = JOIN( inst, _t)::instance(); }

}	// namespace unit_test

#endif