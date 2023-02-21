#include <cstdlib>
#include <ctime>
#include <ios>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

class A {
	std::string& str;

  public:
	A( std::string& x ) : str( x ) {}
	std::string& getStr( void ) { return str; }
	void		 log( void ) { std::cout << "inside : " << str << '\n'; }
};

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
	std::system( "clear" );
	std::cout << std::boolalpha;
	srand( time( NULL ) );
	std::random_device rd;
	std::mt19937	   mt( rd() );
	{
		std::map< int, int > mp;
		for ( int i = 0; i < 20; i++ ) mp[ i ] = i;
		for ( int i = 0; i < 20; i++ ) std::cout << "key : " << i << ", elt : " << mp[ i ] << '\n';
		std::cout << '\n';
		mp.erase( mp.lower_bound( 20 ), mp.upper_bound( 10 ) );
		for ( std::map< int, int >::iterator it = mp.begin(); it != mp.end(); ++it )
			std::cout << it->first << " => " << it->second << '\n';
	}
	// {
	// 	std::string init = "salam";
	// 	A			a( init );
	// 	// std::string mstr( a.getStr() );
	// 	std::cout << "outside : " << init << '\n';
	// 	a.log();
	// 	init = "coucou";
	// 	std::cout << "outside : " << init << '\n';
	// 	a.log();
	// }
	// {
	// 	std::map< int, int > mp;
	// 	for ( int i = 0; i < 4; i++ ) mp[ i ] = i;
	// 	for ( int i = 0; i < 4; i++ ) std::cout << "key : " << i << ", elt : " << mp[ i ] << '\n';
	// 	std::cout << '\n';
	// 	mp.erase( 1 );
	// 	for ( int i = 0; i < 4; i++ ) std::cout << "key : " << i << ", elt : " << mp[ i ] << '\n';
	// }
	// {
	// 	std::map< int, int > mp;
	// 	for ( int i = 0; i < 4; i++ ) mp[ i ] = i;
	// 	for ( int i = 0; i < 4; i++ ) std::cout << "key : " << i << ", elt : " << mp[ i ] << '\n';
	// 	std::cout << '\n';
	// 	mp.erase( 1 );
	// 	for ( int i = 0; i < 4; i++ ) std::cout << "key : " << i << ", elt : " << mp[ i ] << '\n';
	// }
	// {
	// 	std::pair< const int, int >		 p1( std::make_pair< const int, int >( 1, 1 ) );
	// 	std::pair< const int, int >		 p2( std::make_pair< const int, int >( 1, 1 ) );
	// 	S< std::pair< const int, int > > st1( &p1 );
	// 	S< std::pair< const int, int > > st2( &p2 );
	// 	std::cout << st1.elt << ' ' << '\n';
	// 	std::cout << st2.elt << ' ' << '\n';
	// 	swapSts( st1, st2 );
	// 	std::cout << st1.elt << ' ' << '\n';
	// 	std::cout << st2.elt << ' ' << '\n';
	// }
	// {
	// 	std::map< int, int > mp;
	// 	for ( int test = 0, total_tests = 1, sz = 1000000, range = INT_MAX / sz;
	// 		  test < total_tests; test++ )
	// 		for ( int i = 0, x; i < sz; i++ ) {
	// 			x = rand() % range + range * i;
	// 			mp.insert( std::make_pair( x, x ) );
	// 		}
	// }
}
