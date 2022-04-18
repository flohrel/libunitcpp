#ifndef __SINGLETON__H__
# define __SINGLETON__H__

namespace unit_test
{

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

}

#endif