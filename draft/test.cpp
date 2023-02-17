#include <iostream>
#include <map>
#include <utility>

template < class T > struct S {
	T* elt;
	S( T* x ) : elt( x ) {}
};

template < class T > void swapSts( S< T >& x, S< T >& y ) {
	T* tmp = x.elt;
	x.elt  = y.elt;
	y.elt  = tmp;
}

int main() {
	// {
	// 	std::map< int, int > mp;
	// 	for ( int i = 0; i < 4; i++ ) mp[ i ] = i;
	// 	for ( int i = 0; i < 4; i++ ) std::cout << "key : " << i << ", elt : " << mp[ i ] << '\n';
	// 	std::cout << '\n';
	// 	mp.erase( 1 );
	// 	for ( int i = 0; i < 4; i++ ) std::cout << "key : " << i << ", elt : " << mp[ i ] << '\n';
	// }
	{
		std::pair< const int, int >		 p1( std::make_pair< const int, int >( 1, 1 ) );
		std::pair< const int, int >		 p2( std::make_pair< const int, int >( 1, 1 ) );
		S< std::pair< const int, int > > st1( &p1 );
		S< std::pair< const int, int > > st2( &p2 );
		std::cout << st1.elt << ' ' << '\n';
		std::cout << st2.elt << ' ' << '\n';
		swapSts( st1, st2 );
		std::cout << st1.elt << ' ' << '\n';
		std::cout << st2.elt << ' ' << '\n';
	}
}
