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
	char* l;
	int	  i;
	B() : l( nullptr ), i( 1 ) {};
	B( const int& ex ) {
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
	A( const B* ex ) {
		this->l = new char( *( ex->l ) );
		this->i = ex->i;
		if ( ex->i == -1 ) throw "n";
	}
	~A() {
		delete this->l;
		this->l = nullptr;
	};
};

// class A {
// 	std::string& str;

//   public:
// 	A( std::string& x ) : str( x ) {}
// 	std::string& getStr( void ) { return str; }
// 	void		 log( void ) { std::cout << "inside : " << str << '\n'; }
// };

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
		ft::vector< int > ft_vec;
		ft::vector< int > ft_v;
		ft::vector< int > ft_tmp;

		std::vector< int > std_vec;
		std::vector< int > std_v;
		std::vector< int > std_tmp;

		ft_tmp.assign( 2600, 1 );
		ft_vec.assign( 4200, 1 );
		ft_vec.insert( ft_vec.end() - 1000, ft_tmp.begin(), ft_tmp.end() );

		std_tmp.assign( 2600, 1 );
		std_vec.assign( 4200, 1 );
		std_vec.insert( std_vec.end() - 1000, std_tmp.begin(), std_tmp.end() );

		ft_v.push_back( ft_vec[ 3 ] );
		ft_v.push_back( ft_vec.size() );
		ft_v.push_back( ft_vec.capacity() );

		std_v.push_back( std_vec[ 3 ] );
		std_v.push_back( std_vec.size() );
		std_v.push_back( std_vec.capacity() );

		std::unique_ptr< B > ft_k2( new B( 3 ) );
		std::unique_ptr< B > ft_k3( new B( 4 ) );
		std::unique_ptr< B > ft_k4( new B( -1 ) );
		ft::vector< A >		 ft_vv;
		ft::vector< B* >	 ft_v1;

		std::unique_ptr< B > std_k2( new B( 3 ) );
		std::unique_ptr< B > std_k3( new B( 4 ) );
		std::unique_ptr< B > std_k4( new B( -1 ) );
		std::vector< A >	 std_vv;
		std::vector< B* >	 std_v1;

		ft_v1.push_back( &( *ft_k2 ) );
		ft_v1.push_back( &( *ft_k3 ) );
		ft_v1.push_back( &( *ft_k4 ) );

		std_v1.push_back( &( *std_k2 ) );
		std_v1.push_back( &( *std_k3 ) );
		std_v1.push_back( &( *std_k4 ) );

		try {
			ft_vv.insert( ft_vv.begin(), ft_v1.begin(), ft_v1.end() );
		} catch ( ... ) {
			ft_v.push_back( ft_vv.size() );
			ft_v.push_back( ft_vv.capacity() );
		}
		try {
			std_vv.insert( std_vv.begin(), std_v1.begin(), std_v1.end() );
		} catch ( ... ) {
			std_v.push_back( std_vv.size() );
			std_v.push_back( std_vv.capacity() );
		}
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
