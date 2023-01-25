/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:37:52 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/25 20:36:18 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

#define compare( ctr1, ctr2, str, err ) compare( ctr1, ctr2, str, err, __LINE__ )
#define check( ctr1, ctr2 )				check( ctr1, ctr2, __LINE__ )

void testResult( int error_count, const std::string ctr ) {
	std::string cmd[ 2 ] = { "leaks " + ctr + " | grep '0 leaks' > .logs; rm -f .logs",
							 "leaks " + ctr + " | tail -n +17" };
	if ( std::system( cmd[ 0 ].c_str() ) ) error_count++;
	std::system( cmd[ 1 ].c_str() );
	if ( error_count )
		std::cout << RED WARNING "  ---------------------- " << ctr << " failed " << error_count
				  << " test" << ( error_count == 1 ? "" : "s" )
				  << " ---------------------- " WARNING RESET "\n\n";
	else
		std::cout << GREEN CHECK " ---------------------- " << ctr
				  << " succeeded all tests ---------------------- " CHECK RESET "\n\n";
	std::cout << WHITE << "Press \u21B5  to proceed with the next container" << RESET "\n";
	while ( std::getchar() != '\n' ) continue;
}

void printHead( std::string str ) {
	int length	  = 74;
	int in_length = length - str.length();
	std::cout << BLUE;
	for ( int i = 0; i < 4; i++ ) {
		if ( i == 1 ) {
			std::cout << "/* ";
			for ( int j = 0, end = in_length / 2; j < end; j++ ) std::cout << ' ';
			std::cout << str;
		} else if ( i == 2 ) {
			for ( int j = 0, end = in_length - in_length / 2; j < end; j++ ) std::cout << ' ';
			std::cout << " */\n";
		} else {
			std::cout << "/* ";
			for ( int j = 0; j < length; j++ ) std::cout << '-';
			std::cout << " */\n";
		}
	}
	std::cout << RESET "\n";
}

void waitForTests( std::string str, bool state ) {
	if ( !state ) return;
	std::cout << WHITE << "Press \u21B5  to proceed with the next test" << RESET;
	while ( std::getchar() != '\n' ) continue;
	std::system( "clear" );
	printHead( str );
}

void catchExcept( std::exception &e, int &error_count ) {
	std::cout << e.what() << '\n';
	error_count++;
	std::cout << WHITE << "Press \u21B5  to proceed with the next test" << RESET;
	while ( std::getchar() != '\n' ) continue;
	std::cout << "\n";
}

int main( void ) {
	std::cout << CURSOR_HOME ERASE_DISP ERASE_SAVED;
	if ( !std::system( NULL ) ) {
		std::cout << RED "No command processor available\n";
		exit( 1 );
	}
	std::cout.imbue( std::locale( "en_US.UTF-8" ) );
	std::cout << std::boolalpha;
	srand( time( NULL ) );

	{
		int			error_count = 0;
		int			test_idx	= 0;
		bool		waitState	= false;
		std::string testName	= "ft_vector";
		printHead( testName );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";
			ft::vector< int >  ft_vec;
			std::vector< int > std_vec;
			check( ft_vec, std_vec );
			std::cout << TITLE "push_back() inside loop" RESET "\n\n";
			for ( int i = 0, end = ( rand() % 10 ) + 1, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_vec.push_back( n );
				std_vec.push_back( n );
			}
			check( ft_vec, std_vec );
			std::cout << TITLE "Copy Constructor : new2( old )" RESET "\n\n";
			ft::vector< int >  ft_vec2( ft_vec );
			std::vector< int > std_vec2( std_vec );
			check( ft_vec2, std_vec2 );
			std::cout << TITLE "Fill Constructor : new3( vec.begin(), vec.end() )" RESET "\n\n";
			ft::vector< int >  ft_vec3( ft_vec.begin(), ft_vec.end() );
			std::vector< int > std_vec3( std_vec.begin(), std_vec.end() );
			check( ft_vec3, std_vec3 );
			ft::vector< int >  ft_vec4;
			std::vector< int > std_vec4;
			std::cout << TITLE "Copy assignment operator : new4 = old" RESET "\n\n";
			ft_vec4	 = ft_vec;
			std_vec4 = std_vec;
			check( ft_vec4, std_vec4 );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			int size  = ( rand() % 10 ) + 1;
			int value = ( rand() % 10 ) + 1;
			std::cout << TITLE "Parametrized Constructor : vec( " << size << ", " << value
					  << " )" RESET "\n\n";
			ft::vector< int >  ft_vec( size, value );
			std::vector< int > std_vec( size, value );
			check( ft_vec, std_vec );
			size  = ( rand() % 10 ) + 1;
			value = ( rand() % 10 );
			std::cout << TITLE "assign( " << size << ", " << value << " )" RESET "\n\n";
			ft_vec.assign( size, value );
			std_vec.assign( size, value );
			check( ft_vec, std_vec );
			int n	= ( rand() % 10 ) + 1;
			int val = ( rand() % 100 ) + 1;
			std::cout << TITLE "Parametrized Constructor : vec2( " << n << ", " << val
					  << " )" RESET "\n\n";
			std::vector< int > std_vec2( n, val );
			ft::vector< int >  ft_vec2( n, val );
			check( ft_vec2, std_vec2 );
			std::cout << TITLE "assign ( vec2.begin(), vec2.end() )" << RESET "\n\n";
			std_vec.assign( std_vec2.begin(), std_vec2.end() );
			ft_vec.assign( ft_vec2.begin(), ft_vec2.end() );
			check( ft_vec, std_vec );
			n = ( rand() % 10 ) + 1;
			std::cout << TITLE "int arr [] = { " << n << ", " << n + 1 << ", " << n + 2 << " }"
					  << RESET "\n\n";
			int arr[] = { n, n + 1, n + 2 };
			std::cout << TITLE "aarr, arr + 3 )" << RESET "\n\n";
			std_vec.assign( arr, arr + 3 );
			ft_vec.assign( arr, arr + 3 );
			check( ft_vec, std_vec );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";
			ft::vector< int >  ft_vec;
			std::vector< int > std_vec;
			std::cout << TITLE "push_back() inside loop" RESET "\n\n";
			for ( int i = 0, end = ( rand() % 10 ) + 1, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_vec.push_back( n );
				std_vec.push_back( n );
			}
			check( ft_vec, std_vec );
			std::cout << TITLE "const copy Constructor c_vec" RESET "\n\n";
			const ft::vector< int >	 c_ft_vec( ft_vec );
			const std::vector< int > c_std_vec( std_vec );
			check( c_ft_vec, c_std_vec );
			std::cout << TITLE "compare const and non const back()" RESET "\n\n";
			std::cout << "back";
			compare( ft_vec.back(), std_vec.back(), "\t", testName );
			std::cout << "c_back";
			compare( c_ft_vec.back(), c_std_vec.back(), "\t", testName );
			std::cout << "\n" TITLE "compare const and non const front()" RESET "\n\n";
			std::cout << "front";
			compare( ft_vec.front(), std_vec.front(), "\t", testName );
			std::cout << "c_front";
			compare( c_ft_vec.front(), c_std_vec.front(), "\t", testName );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			int size  = ( rand() % 10 ) + 1;
			int value = ( rand() % 10 );
			std::cout << TITLE "Parametrized Constructor" RESET "\n\n";
			ft::vector< int >  ft_vec( size, value );
			std::vector< int > std_vec( size, value );
			check( ft_vec, std_vec );
			size  = ( rand() % 10 ) + 1;
			value = ( rand() % 10 );
			std::cout << TITLE "clear()" RESET "\n\n";
			ft_vec.clear();
			std_vec.clear();
			check( ft_vec, std_vec );
			std::cout << TITLE "push_back() inside loop" RESET "\n\n";
			for ( int i = 0, end = ( rand() % 10 ) + 1, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_vec.push_back( n );
				std_vec.push_back( n );
			}
			check( ft_vec, std_vec );
			std::cout << TITLE "clear()" RESET "\n\n";
			ft_vec.clear();
			std_vec.clear();
			check( ft_vec, std_vec );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";
			ft::vector< int >  ft_vec;
			std::vector< int > std_vec;
			std::cout << TITLE "push_back() inside loop" RESET "\n\n";
			for ( int i = 0, end = ( rand() % 10 ) + 1, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_vec.push_back( n );
				std_vec.push_back( n );
			}
			check( ft_vec, std_vec );
			std::cout << TITLE "pop_back() inside loop" RESET "\n\n";
			for ( int i = 0, end = std_vec.capacity() / 2; i < end; i++ ) {
				ft_vec.pop_back();
				std_vec.pop_back();
			}
			check( ft_vec, std_vec );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";
			ft::vector< int >  ft_vec;
			std::vector< int > std_vec;
			std::cout << TITLE "push_back() inside loop" RESET "\n\n";
			for ( int i = 0, end = ( rand() % 10 ) + 5, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_vec.push_back( n );
				std_vec.push_back( n );
			}
			check( ft_vec, std_vec );
			int n = ( rand() % ( std_vec.capacity() / 2 ) ) + 1;
			std::cout << TITLE "reserve( " << n << " )" RESET "\n\n";
			ft_vec.reserve( n );
			std_vec.reserve( n );
			check( ft_vec, std_vec );
			n = ( rand() % 10 ) + std_vec.capacity() + 1;
			std::cout << TITLE "reserve( " << n << " )" RESET "\n\n";
			ft_vec.reserve( n );
			std_vec.reserve( n );
			check( ft_vec, std_vec );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";
			ft::vector< int >  ft_vec;
			std::vector< int > std_vec;
			std::cout << TITLE "push_back() inside loop" RESET "\n\n";
			for ( int i = 0, end = ( rand() % 10 ) + 1, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_vec.push_back( n );
				std_vec.push_back( n );
			}
			check( ft_vec, std_vec );
			int n = ( rand() % 10 ) + std_vec.capacity() + 1;
			std::cout << TITLE "resize( " << n << " )" RESET "\n\n";
			ft_vec.resize( n );
			std_vec.resize( n );
			check( ft_vec, std_vec );
			std::cout << TITLE "resize( " << n << " )" RESET "\n\n";
			n = ( rand() % ( std_vec.capacity() / 2 ) ) + 1;
			ft_vec.resize( n );
			std_vec.resize( n );
			check( ft_vec, std_vec );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";
			ft::vector< int >  ft_vec;
			std::vector< int > std_vec;
			ft::vector< int >  ft_vec2;
			std::vector< int > std_vec2;
			std::cout << TITLE "push_back() inside loop" RESET "\n\n";
			for ( int i = 0, end = ( rand() % 5 ) + 1, n1, n2; i < end; i++ ) {
				n1 = ( rand() % 10 );
				ft_vec.push_back( n1 );
				std_vec.push_back( n1 );
				n2 = ( rand() % 10 );
				ft_vec2.push_back( n2 );
				std_vec2.push_back( n2 );
			}
			check( ft_vec, std_vec );
			check( ft_vec2, std_vec2 );
			std::cout << TITLE "swap()" RESET "\n\n";
			ft::swap( ft_vec, ft_vec2 );
			std::swap( std_vec, std_vec2 );
			check( ft_vec, std_vec );
			check( ft_vec2, std_vec2 );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			int n	= ( rand() % 10 ) + 1;
			int val = ( rand() % 100 ) + 1;
			std::cout << TITLE "Parametrized Constructor : vec( " << n << ", " << val << " )"
					  << RESET "\n\n";
			std::vector< int > std_vec( n, val );
			ft::vector< int >  ft_vec( n, val );
			check( ft_vec, std_vec );
			val = ( rand() % 100 ) + 1;
			std::vector< int >::iterator std_it;
			ft::vector< int >::iterator	 ft_it;
			std::cout << TITLE "insert ( begin() + 1, " << val << " )" << RESET "\n\n";
			std_it = std_vec.insert( std_vec.begin() + 1, val );
			ft_it  = ft_vec.insert( ft_vec.begin() + 1, val );
			check( ft_vec, std_vec );
			val = ( rand() % 100 ) + 1;
			std::cout << TITLE "insert ( `return of last insert()`, " << val << " )"
					  << RESET "\n\n";
			std_it = std_vec.insert( std_it, val );
			ft_it  = ft_vec.insert( ft_it, val );
			check( ft_vec, std_vec );
			n	= ( rand() % 10 ) + 1;
			val = ( rand() % 100 ) + 1;
			std::cout << TITLE "insert ( `return of last insert()`, " << n << ", " << val << " )"
					  << RESET "\n\n";
			std_vec.insert( std_it, n, val );
			ft_vec.insert( ft_it, n, val );
			check( ft_vec, std_vec );
			n	= ( rand() % 10 ) + 1;
			val = ( rand() % 100 ) + 1;
			std::cout << TITLE "Parametrized Constructor : vec2( " << n << ", " << val
					  << " )" RESET "\n\n";
			std::vector< int > std_vec2( n, val );
			ft::vector< int >  ft_vec2( n, val );
			check( ft_vec2, std_vec2 );
			std::cout << TITLE "insert ( vec.begin() + 2, vec2.begin(), vec2.end() )"
					  << RESET "\n\n";
			std_vec.insert( std_vec.begin() + 2, std_vec2.begin(), std_vec2.end() );
			ft_vec.insert( ft_vec.begin() + 2, ft_vec2.begin(), ft_vec2.end() );
			check( ft_vec, std_vec );
			n = ( rand() % 10 ) + 1;
			std::cout << TITLE "int arr [] = { " << n << ", " << n + 1 << ", " << n + 2 << " }"
					  << RESET "\n\n";
			int arr[] = { n, n + 1, n + 2 };
			std::cout << TITLE "insert ( begin(), arr, arr + 3 )" << RESET "\n\n";
			std_vec.insert( std_vec.begin(), arr, arr + 3 );
			ft_vec.insert( ft_vec.begin(), arr, arr + 3 );
			check( ft_vec, std_vec );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";
			ft::vector< int >  ft_vec;
			std::vector< int > std_vec;
			std::cout << TITLE "push_back() inside loop" RESET "\n\n";
			for ( int i = 0, end = ( rand() % 10 ) + 10, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_vec.push_back( n );
				std_vec.push_back( n );
			}
			check( ft_vec, std_vec );
			std::vector< int >::iterator std_it;
			ft::vector< int >::iterator	 ft_it;
			int							 n = ( rand() % ( std_vec.size() / 3 ) );
			std::cout << TITLE "erase( " << n << " )" RESET << "\n\n";
			std_it = std_vec.erase( std_vec.begin() + n );
			ft_it  = ft_vec.erase( ft_vec.begin() + n );
			check( ft_vec, std_vec );
			std::cout << TITLE "erase( `return of last erase()` )" RESET << "\n\n";
			std_vec.erase( std_it );
			ft_vec.erase( ft_it );
			check( ft_vec, std_vec );
			n = ( rand() % ( std_vec.size() / 3 ) );
			std::cout << TITLE "erase( begin() + " << n << ", begin() + " << n + 3 << " )" RESET
					  << "\n\n";
			std_it = std_vec.erase( std_vec.begin() + n, std_vec.begin() + n + 3 );
			ft_it  = ft_vec.erase( ft_vec.begin() + n, ft_vec.begin() + n + 3 );
			check( ft_vec, std_vec );
			std::cout << TITLE "erase( `return of last erase()` )" RESET << "\n\n";
			std_vec.erase( std_it );
			ft_vec.erase( ft_it );
			check( ft_vec, std_vec );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "max_size()" << RESET "\n\n";
			compare( ft::vector< char >().max_size(), std::vector< char >().max_size(), "char\t\t",
					 "max_size" );
			compare( ft::vector< signed char >().max_size(),
					 std::vector< signed char >().max_size(), "signed char\t", "max_size" );
			compare( ft::vector< unsigned char >().max_size(),
					 std::vector< unsigned char >().max_size(), "unsigned char\t", "max_size" );
			compare( ft::vector< short >().max_size(), std::vector< short >().max_size(),
					 "short\t\t", "max_size" );
			compare( ft::vector< short int >().max_size(), std::vector< short int >().max_size(),
					 "short int\t", "max_size" );
			compare( ft::vector< signed short >().max_size(),
					 std::vector< signed short >().max_size(), "signed short\t", "max_size" );
			compare( ft::vector< signed short int >().max_size(),
					 std::vector< signed short int >().max_size(), "signed short int", "max_size" );
			compare( ft::vector< unsigned short >().max_size(),
					 std::vector< unsigned short >().max_size(), "unsigned short\t", "max_size" );
			compare( ft::vector< unsigned short int >().max_size(),
					 std::vector< unsigned short int >().max_size(), "unsigned short int",
					 "max_size" );
			compare( ft::vector< int >().max_size(), std::vector< int >().max_size(), "int\t\t",
					 "max_size" );
			compare( ft::vector< signed >().max_size(), std::vector< signed >().max_size(),
					 "signed\t\t", "max_size" );
			compare( ft::vector< signed int >().max_size(), std::vector< signed int >().max_size(),
					 "signed int\t", "max_size" );
			compare( ft::vector< unsigned >().max_size(), std::vector< unsigned >().max_size(),
					 "unsigned\t", "max_size" );
			compare( ft::vector< unsigned int >().max_size(),
					 std::vector< unsigned int >().max_size(), "unsigned int\t", "max_size" );
			compare( ft::vector< long >().max_size(), std::vector< long >().max_size(), "long\t\t",
					 "max_size" );
			compare( ft::vector< long int >().max_size(), std::vector< long int >().max_size(),
					 "long int\t", "max_size" );
			compare( ft::vector< signed long >().max_size(),
					 std::vector< signed long >().max_size(), "signed long\t", "max_size" );
			compare( ft::vector< signed long int >().max_size(),
					 std::vector< signed long int >().max_size(), "signed long int\t", "max_size" );
			compare( ft::vector< unsigned long >().max_size(),
					 std::vector< unsigned long >().max_size(), "unsigned long\t", "max_size" );
			compare( ft::vector< unsigned long int >().max_size(),
					 std::vector< unsigned long int >().max_size(), "unsigned long int",
					 "max_size" );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		//
		std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
	} // vector

	return ( 0 );
}
