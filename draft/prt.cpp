#include "../iterators/reverse_iterator.hpp"
#include "../stack/stack.hpp"
#include "../vector/vector.hpp"

#include <iostream>
#include <ostream>
#include <stack>
#include <vector>

typedef ft::vector< std::string > strvector;
#define PRINT_MSG( msg )   \
	{                      \
		std::cout << msg;  \
		PRINT_FILE_LINE(); \
	}

#define PRINT_FILE_LINE() \
	{ std::cout << " (file: " << __FILE__ << ", line: " << __LINE__ << ")" << std::endl; }

#define PRINT_LINE( msg, value )              \
	{                                         \
		std::cout << msg << " " << ( value ); \
		PRINT_FILE_LINE();                    \
	}

#define CHECK_CAPACITY( vec )                             \
	{                                                     \
		if ( !( vec.capacity() >= vec.size() ) ) {        \
			PRINT_MSG( "Capacity is smaller than size" ); \
		} else {                                          \
			PRINT_MSG( "Capacity Ok" );                   \
		}                                                 \
	}
#define PRINT_SIZE( c ) \
	{ PRINT_LINE( "Size:", c.size() ); }

#define PRINT_CAPACITY( c ) \
	{ PRINT_LINE( "Capacity :", c.capacity() ); }
template < typename Iter > void print_range( Iter first, Iter last ) {
	for ( Iter it = first; it != last; ++it ) { std::cout << *it << " "; }
	std::cout << std::endl;
}

#define PRINT_VEC( vec )                       \
	{                                          \
		std::cout << "\nVector content:\n";    \
		print_range( vec.begin(), vec.end() ); \
		std::cout << std::endl;                \
	}

#define PRINT_ALL( vec )       \
	{                          \
		PRINT_SIZE( vec );     \
		PRINT_CAPACITY( vec ); \
		PRINT_VEC( vec );      \
	}

#define CHECK_AND_PRINT_ALL( vec ) \
	{                              \
		CHECK_CAPACITY( vec );     \
		PRINT_ALL( vec );          \
	}

int main( void ) {
	// const int								   size = 5;
	// std::vector< int >						   vct( size );
	// std::vector< int >::reverse_iterator	   it  = vct.rbegin();
	// std::vector< int >::const_reverse_iterator ite = vct.rbegin();

	// for ( int i = 0; i < size; ++i ) it[ i ] = ( size - i ) * 5;

	// it = it + 5;
	// it = 1 + it;
	// it = it - 4;
	// std::cout << *( it += 2 ) << std::endl;
	// std::cout << *( it -= 1 ) << std::endl;

	// *( it -= 2 ) = 42;
	// *( it += 2 ) = 21;

	// std::cout << "const_ite +=/-=: " << *( ite += 2 ) << " | " << *( ite -= 2 ) << std::endl;

	// std::cout << "(it == const_it): " << ( ite == it ) << std::endl;
	// std::cout << "(const_ite - it): " << ( ite - it ) << std::endl;
	// std::cout << "(ite + 3 == it): " << ( ite + 3 == it ) << std::endl;

	{
		std::stack< int >::value_type	   a = 10;
		std::stack< int >::reference	   b = a;
		std::stack< int >::const_reference c = a;
		(void)a;
		(void)b;
		(void)c;
	}
	// printSize( vct, true );
	return ( 0 );
}
