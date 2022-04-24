#ifndef __RANDOMARRAY__H__
# define __RANDOMARRAY__H__

# include <vector>
# include <limits>
# include <cstdlib>
# include "time.h"

namespace unit_test
{

template< typename T, typename Container = std::vector<T> >
class RandomArray : public Container
{
	typedef typename Container::iterator	iterator;

	public:
		RandomArray( size_t size )
		: Container(size), _max_value(std::numeric_limits<T>::max() < RAND_MAX ? std::numeric_limits<T>::max() : RAND_MAX)
		{
			generate_random_values();
			return ;
		}

		RandomArray( const RandomArray& src )
		: Container(src), _max_value(src._max_value)
		{ return ; }

		~RandomArray( void )
		{ return ; }

		RandomArray&
		operator=( const RandomArray& rhs )
		{
			if (this != &rhs)
			{
				_max_value = rhs._max_value;
			}
			return (*this);
		}

		void
		set_size( size_t size )
		{
			if (size > Container::max_size())
				return ;
			Container::resize(size);
			generate_random_values();
		}

		void
		generate_random_values( void )
		{
			srand(time(0));
			for (iterator it = Container::begin(); it != Container::end(); it++)
			{
				(*it) = rand() % _max_value;
			}
			return ;
		}


	private:
		RandomArray( void )
		: Container(), _max_value(0)
		{ return; }

		size_t			_max_value;

};

}

#endif