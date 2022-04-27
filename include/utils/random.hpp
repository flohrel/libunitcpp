#ifndef __RANDOM_OBJ__H__
# define __RANDOM_OBJ__H__

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <limits>
# include <cstdlib>
# include <iostream>
# include <unistd.h>
# include "time.h"

namespace unit_test {

template< typename T >
class Random
{
	public:
		Random( void )
		: _max_value(std::numeric_limits<T>::max() < RAND_MAX ? std::numeric_limits<T>::max() : RAND_MAX)
		{
			srand(time(0) * getpid());
			return ;
		}

		Random( const Random& src )
		: _max_value(src._max_value)
		{ return ; }

		~Random( void )
		{ return ; }

		operator T() const
		{
			return (rand() % _max_value);
		}

		Random&
		operator=( const Random& rhs )
		{
			if (this != &rhs)
			{
				_max_value = rhs._max_value;
			}
			return (*this);
		}


	private:
		size_t			_max_value;

};

class RandomString
{
	public:
		RandomString( size_t size )
		: _size(size)
		{
			srand(time(0) * getpid());
			return ;
		}

		RandomString( const RandomString& src )
		: _size(src._size)
		{ return ; }

		~RandomString( void )
		{ return ; }

		operator	std::string() const
		{
			static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";

			std::string		str;
			str.reserve(_size);

			for (size_t i = 0; i != _size; i++)
			{
				str += alphanum[rand() % (sizeof(alphanum) - 1)];
    		}
			return (str);
		}


	private:
		RandomString( void )
		: _size()
		{ return; }

		size_t	_size;

};

std::ostream& operator<<(std::ostream& os, RandomString str)
{
	return (os << static_cast<std::string>(str));
}

template< typename Key, typename Value, typename Container = std::map<Key, Value> >
class RandomMap : public Container
{
	public:
		typedef typename Container::iterator	iterator;

		RandomMap( size_t size )
		: Container()
		{
			if (size > Container::max_size())
				return ;
			_size = size;
			gen_random();
			return ;
		}

		RandomMap( const RandomMap& src )
		: Container(src)
		{ return ; }

		~RandomMap( void )
		{ return ; }

		void
		set_size( size_t size )
		{
			if (size > Container::max_size())
				return ;
			_size = size;
			Container::clear();
			gen_random();
		}

		void
		gen_random( void )
		{
			for (size_t i = 0; i < _size; i++)
			{
				Container::insert(std::make_pair(Key(), Value()));
			}
		}

	private:
		RandomMap( void )
		: Container()
		{ return; }

		size_t	_size;

};

}

#endif