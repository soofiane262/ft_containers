#include "../vector/main.hpp"
#include "../vector/vector.hpp"

#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <set>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

class B {
  public:
	char *l;
	int	  i;
	B() : l( nullptr ), i( 1 ) {};
	B( const int &ex ) {
		this->i = ex;
		this->l = new char( 'a' );
	};
	virtual ~B() {
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
  public:
	A() : B() {};
	A( const B *ex ) {
		this->l = new char( *( ex->l ) );
		this->i = ex->i;
		if ( ex->i == -1 ) throw "n";
	}
	~A() {
		delete this->l;
		this->l = nullptr;
	};
};

template < typename T > std::vector< int > swap_test( std::vector< T > vector ) {
	std::vector< int > v;
	vector.assign( 11, 11 );
	std::vector< int > tmp( 5, 5 ), tmp2( 10, 10 ), tmp3( 15, 15 ), tmp4( 30, 30 );
	v.push_back( vector[ 2 ] );
	v.push_back( vector.size() );
	v.push_back( vector.capacity() );
	long *adr1 = reinterpret_cast< long * >( &vector );
	long *adr2 = reinterpret_cast< long * >( &tmp );
	vector.swap( tmp );
	if ( reinterpret_cast< long * >( &vector ) == adr1 &&
		 reinterpret_cast< long * >( &tmp ) == adr2 )
		v.push_back( 1 );
	v.push_back( vector[ 2 ] );
	v.push_back( vector.size() );
	v.push_back( vector.capacity() );
	vector.swap( tmp3 );
	v.push_back( vector[ 2 ] );
	v.push_back( vector.size() );
	v.push_back( vector.capacity() );
	std::swap( vector, tmp2 );
	v.push_back( vector[ 2 ] );
	v.push_back( vector.size() );
	v.push_back( vector.capacity() );
	std::swap( vector, tmp4 );
	v.push_back( vector[ 2 ] );
	v.push_back( vector.size() );
	v.push_back( vector.capacity() );
	return v;
}

template < typename T > std::vector< int > swap_test( ft::vector< T > vector ) {
	std::vector< int > v;
	vector.assign( 11, 11 );
	ft::vector< int > tmp( 5, 5 ), tmp2( 10, 10 ), tmp3( 15, 15 ), tmp4( 30, 30 );
	v.push_back( vector[ 2 ] );
	v.push_back( vector.size() );
	v.push_back( vector.capacity() );
	long *adr1 = reinterpret_cast< long * >( &vector );
	long *adr2 = reinterpret_cast< long * >( &tmp );
	vector.swap( tmp );
	if ( reinterpret_cast< long * >( &vector ) == adr1 &&
		 reinterpret_cast< long * >( &tmp ) == adr2 )
		v.push_back( 1 );
	v.push_back( vector[ 2 ] );
	v.push_back( vector.size() );
	v.push_back( vector.capacity() );
	vector.swap( tmp3 );
	v.push_back( vector[ 2 ] );
	v.push_back( vector.size() );
	v.push_back( vector.capacity() );
	std::swap( vector, tmp2 );
	v.push_back( vector[ 2 ] );
	v.push_back( vector.size() );
	v.push_back( vector.capacity() );
	std::swap( vector, tmp4 );
	v.push_back( vector[ 2 ] );
	v.push_back( vector.size() );
	v.push_back( vector.capacity() );
	return v;
}

// class A {
// 	std::string& str;

//   public:
// 	A( std::string& x ) : str( x ) {}
// 	std::string& getStr( void ) { return str; }
// 	void		 log( void ) { std::cout << "inside : " << str << '\n'; }
// };

// template < class T > struct S {
// 	T* elt;
// 	S( T* x ) : elt( x ) {}
// };

// template < class T > void swapSts( S< T >& x, S< T >& y ) {
// 	T* tmp = x.elt;
// 	x.elt  = y.elt;
// 	y.elt  = tmp;
// }

int main() {
	std::system( "clear" );
	std::cout << std::boolalpha;
	srand( time( NULL ) );
	std::random_device rd;
	std::mt19937	   mt( rd() );

	{
		std::vector< int > std_v;
		std::vector< int > std_vector;

		ft::vector< int > ft_v;
		ft::vector< int > ft_vector;

		std_vector.assign( 11, 11 );
		ft_vector.assign( 11, 11 );

		std::vector< int > std_tmp( 5, 5 ), std_tmp2( 10, 10 ), std_tmp3( 15, 15 ),
			std_tmp4( 30, 30 );
		ft::vector< int > ft_tmp( 5, 5 ), ft_tmp2( 10, 10 ), ft_tmp3( 15, 15 ), ft_tmp4( 30, 30 );

		std_v.push_back( std_vector[ 2 ] );
		std_v.push_back( std_vector.size() );
		std_v.push_back( std_vector.capacity() );

		ft_v.push_back( ft_vector[ 2 ] );
		ft_v.push_back( ft_vector.size() );
		ft_v.push_back( ft_vector.capacity() );

		long *std_adr1 = reinterpret_cast< long * >( &std_vector );
		long *std_adr2 = reinterpret_cast< long * >( &std_tmp );

		long *ft_adr1 = reinterpret_cast< long * >( &ft_vector );
		long *ft_adr2 = reinterpret_cast< long * >( &ft_tmp );

		std_vector.swap( std_tmp );
		ft_vector.swap( ft_tmp );

		if ( reinterpret_cast< long * >( &std_vector ) == std_adr1 &&
			 reinterpret_cast< long * >( &std_tmp ) == std_adr2 )
			std_v.push_back( 1 );

		if ( reinterpret_cast< long * >( &ft_vector ) == ft_adr1 &&
			 reinterpret_cast< long * >( &ft_tmp ) == ft_adr2 )
			ft_v.push_back( 1 );

		std_v.push_back( std_vector[ 2 ] );
		std_v.push_back( std_vector.size() );
		std_v.push_back( std_vector.capacity() );

		ft_v.push_back( ft_vector[ 2 ] );
		ft_v.push_back( ft_vector.size() );
		ft_v.push_back( ft_vector.capacity() );

		std_vector.swap( std_tmp3 );
		ft_vector.swap( ft_tmp3 );

		std_v.push_back( std_vector[ 2 ] );
		std_v.push_back( std_vector.size() );
		std_v.push_back( std_vector.capacity() );

		ft_v.push_back( ft_vector[ 2 ] );
		ft_v.push_back( ft_vector.size() );
		ft_v.push_back( ft_vector.capacity() );

		std::swap( std_vector, std_tmp2 );
		ft::swap( ft_vector, ft_tmp2 );

		std_v.push_back( std_vector[ 2 ] );
		std_v.push_back( std_vector.size() );
		std_v.push_back( std_vector.capacity() );

		ft_v.push_back( ft_vector[ 2 ] );
		ft_v.push_back( ft_vector.size() );
		ft_v.push_back( ft_vector.capacity() );

		std::swap( std_vector, std_tmp4 );
		ft::swap( ft_vector, ft_tmp4 );

		std_v.push_back( std_vector[ 2 ] );
		std_v.push_back( std_vector.size() );
		std_v.push_back( std_vector.capacity() );

		ft_v.push_back( ft_vector[ 2 ] );
		ft_v.push_back( ft_vector.size() );
		ft_v.push_back( ft_vector.capacity() );
		check( ft_v, std_v, __LINE__ );
	}

	// {
	// 	std::ifstream					 s( "a b c e f g h" );
	// 	std::istreambuf_iterator< char > i1( s ), i2( s );
	// 	std::cout << *i1 << '\n';
	// 	std::cout << *i2 << '\n';
	// 	i1++;
	// 	std::cout << *i1 << '\n';
	// 	std::cout << *i2 << '\n';
	// }
	// {
	// 	std::set< int > st1;
	// 	std::set< int > st2;
	// 	st1.insert( 10 );
	// 	st2.insert( 10 );
	// 	std::cout << ( st1.end() == ++st1.begin() ) << '\n';
	// }
	// std::mt19937	   mt( rd() );
	// {
	// 	std::map< int, int > mp;
	// 	for ( int i = 0; i < 20; i++ ) mp[ i ] = i;
	// 	for ( int i = 0; i < 20; i++ ) std::cout << "key : " << i << ", elt : " << mp[ i ] << '\n';
	// 	std::cout << '\n';
	// 	mp.erase( mp.lower_bound( 20 ), mp.upper_bound( 10 ) );
	// 	for ( std::map< int, int >::iterator it = mp.begin(); it != mp.end(); ++it )
	// 		std::cout << it->first << " => " << it->second << '\n';
	// }
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
