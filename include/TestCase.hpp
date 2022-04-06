#ifndef __TESTCASE__H__
#define __TESTCASE__H__

class TestCase
{
	public:
		TestCase( void );
		TestCase( const TestCase& src );
		~TestCase( void );

		TestCase&	operator=( const TestCase& rhs );

};

#endif