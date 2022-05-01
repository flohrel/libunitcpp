#ifndef __GLOBAL_TYPEDEFS__H__
# define __GLOBAL_TYPEDEFS__H__

// Concatenates strings
# define UCPP_JOIN_IMPL_(foo, bar) foo##bar
# define UCPP_JOIN(foo, bar) UCPP_JOIN_IMPL_(foo, bar)

// Creates a string literal, enclosing the argument between quotes
# define UCPP_STRINGIZE(name) #name

typedef unsigned long   counter_t;

enum test_unit_type { TUT_CASE = 0x01, TUT_SUITE = 0x10, TUT_ANY = 0x11 };

typedef unsigned long   test_unit_id;

const test_unit_id INV_TEST_UNIT_ID  = 0xFFFFFFFF;
const test_unit_id MAX_TEST_CASE_ID  = 0xFFFFFFFE;
const test_unit_id MIN_TEST_CASE_ID  = 0x00010000;
const test_unit_id MAX_TEST_SUITE_ID = 0x0000FF00;
const test_unit_id MIN_TEST_SUITE_ID = 0x00000001;

inline test_unit_type
test_id_2_unit_type( test_unit_id id )
{
    return (id & 0xFFFF0000) != 0 ? TUT_CASE : TUT_SUITE;
}

template< typename T >
class Singleton
{
	public:
        static T&		instance( void ) { static T instance; return (instance); }


	protected:
		Singleton( void ) { return ; }
		~Singleton( void ) { return ; }


	private:
		Singleton( const Singleton& src ) { (void)src; return; }
        Singleton&	operator=( const Singleton& ) { return (*this); }

};

#endif