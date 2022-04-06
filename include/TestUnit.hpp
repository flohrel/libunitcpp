#ifndef __TESTUNIT__H__
# define __TESTUNIT__H__

# include <string>

class TestUnit
{
	private:
		std::string		_name;
		unsigned		_timeout;
		unsigned		_expected_failures;


	public:
		TestUnit( void );
		TestUnit( const TestUnit& src );
		TestUnit( const std::string& name );
		~TestUnit( void );

		TestUnit&
		operator=( const TestUnit& rhs );

		std::string
		get_name( void ) const;


};

#endif