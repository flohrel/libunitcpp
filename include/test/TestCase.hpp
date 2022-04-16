#ifndef __TESTCASE__H__
# define __TESTCASE__H__

# include "TestUnit.hpp"

namespace unit_test
{

class TestCase : public TestUnit
{
	public:
		typedef void	(*test_ft)(void);


	private:
		TestCase( void );


	public:
		TestCase( const std::string& str, test_ft ft, unsigned timeout = 0, unsigned expected_fail = 0 );
		TestCase( const TestCase& src );
		~TestCase( void );

		TestCase&	operator=( const TestCase& rhs );
		void		operator()( void ) const;


	private:
		test_ft		_ft_ptr;


};

}	// namespace unit_test

#endif