#ifndef __RANDOM__H__
# define __RANDOM__H__

# include <algorithm>
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <limits>
# include <cstdlib>
# include <iostream>
# include <unistd.h>
# include "time.h"

// TODO:
//		->	Make a generator base class
//		->	make it EASIER TO USE ( operator() overload ? OR class inheritance to generate with constructor ? )

namespace unit_test {

/**
 * @brief Generate random values of integral type
 * 
 * @tparam T 
 */
template< typename T >
class RandomGenerator
{
	public:
		typedef	T		value_type;

		RandomGenerator( void )
		: _max_value(std::max(std::numeric_limits<T>::max(), RAND_MAX))
		{ srand(time(0) * getpid()); return ; }

		RandomGenerator( const RandomGenerator& src )
		: _max_value(src._max_value)
		{ return ; }

		~RandomGenerator( void )
		{ return ; }

		operator	value_type() const
		{ return (gen_random()); }

		value_type
		gen_random( void ) const
		{ return (rand() % _max_value); }

		RandomGenerator&
		operator=( const RandomGenerator& rhs )
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

/**
 * @brief Generate random alpha-numeric std::string
 * 
 */
class StringGenerator
{
	public:
		typedef	std::string			value_type;

		StringGenerator( void )
		: _size(StringGenerator::_kDefaultSize)
		{ srand(time(0) * getpid()); return; }

		StringGenerator( size_t size )
		: _size(size)
		{ srand(time(0) * getpid()); return ; }

		StringGenerator( const StringGenerator& src )
		: _size(src._size)
		{ return ; }

		~StringGenerator( void )
		{ return ; }

		operator	std::string() const
		{ return (gen_random()); }

		StringGenerator&
		operator=(StringGenerator const& rhs)
		{
			if (this != &rhs)
			{
				_size = rhs._size;
			}
			return (*this);
		}

		std::string
		gen_random( void ) const
		{
			static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";

			std::string		random_str;
			random_str.reserve(_size);

			for (size_t i = 0; i != _size; i++)
			{
				random_str += alphanum[rand() % (sizeof(alphanum) - 1)];
    		}
			return (random_str);
		}

		void
		set_size( size_t size )
		{ _size = size; }

		friend std::ostream& operator<<(std::ostream& os, StringGenerator str)
		{
			return (os << static_cast<std::string>(str));
		}


	private:
		static const size_t		_kDefaultSize = 10;
		size_t					_size;

};

/**
 * @brief Generate std::map of random values
 * 
 * @tparam KeyGen 		Key generator
 * @tparam ValueGen 	Value generator
 */
template< typename KeyGen, typename ValueGen, typename Container = std::map< typename KeyGen::value_type, typename ValueGen::value_type > >
class MapGenerator
{
	public:
		MapGenerator( void )
		: _size(MapGenerator::_kDefaultSize), _key_gen(), _value_gen()
		{ return; }

		MapGenerator( size_t size, KeyGen keygen = KeyGen(), ValueGen valgen = ValueGen() )
		: _size(size), _key_gen(keygen), _value_gen(valgen)
		{ return ; }

		MapGenerator( const MapGenerator& src )
		: _size(src._size)
		{ return ; }

		~MapGenerator( void )
		{ return ; }

		Container operator()( void ) const
		{ return (gen_random()); }

		MapGenerator&
		operator=(MapGenerator const& rhs)
		{
			if (this != &rhs)
			{
				_size = rhs._size;
				_key_gen = rhs._key_gen;
				_value_gen = rhs._value_gen;
			}
			return (*this);
		}

		Container
		gen_random( void ) const
		{
			Container	random_map;

			for (size_t i = 0; i != _size; i++)
			{
				random_map.insert(std::make_pair(_key_gen.gen_random(), _value_gen.gen_random()));
    		}
			return (random_map);
		}

		void
		set_size( size_t size )
		{ _size = size; }


	private:
		static const size_t		_kDefaultSize = 10;
		size_t					_size;
		KeyGen					_key_gen;
		ValueGen				_value_gen;

};

/**
 * @brief Generate std::set of random values
 * 
 * @tparam KeyGen 		Key generator
 */
template< typename KeyGen, typename Container = std::set< typename KeyGen::value_type > >
class SetGenerator
{
	public:
		SetGenerator( void )
		: _size(SetGenerator::_kDefaultSize), _key_gen()
		{ return; }

		SetGenerator( size_t size, KeyGen keygen = KeyGen() )
		: _size(size), _key_gen(keygen)
		{ return ; }

		SetGenerator( const SetGenerator& src )
		: _size(src._size)
		{ return ; }

		~SetGenerator( void )
		{ return ; }

		Container operator()( void ) const
		{ return (gen_random()); }

		SetGenerator&
		operator=(SetGenerator const& rhs)
		{
			if (this != &rhs)
			{
				_size = rhs._size;
				_key_gen = rhs._key_gen;
			}
			return (*this);
		}

		Container
		gen_random( void ) const
		{
			Container	random_set;

			for (size_t i = 0; i != _size; i++)
			{
				random_set.insert(_key_gen.gen_random());
    		}
			return (random_set);
		}

		void
		set_size( size_t size )
		{ _size = size; }


	private:
		static const size_t		_kDefaultSize = 10;
		size_t					_size;
		KeyGen					_key_gen;

};

}

#endif