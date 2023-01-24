/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:37:52 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/23 20:11:43 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

#define compare( ctr1, ctr2, str, err ) compare( ctr1, ctr2, str, err, __LINE__ )
#define check( ctr1, ctr2 )				check( ctr1, ctr2, __LINE__ )

void testResult( int error_count, const int total_tests, const std::string ctr ) {
	std::cout << MAGENTA "Vector Test " << total_tests << " of " << total_tests << RESET "\n\n";
	if ( std::system( "leaks Containers | grep '0 leaks' > .logs" ) ) error_count++;
	std::system( "leaks Containers | tail -n +17" );
	if ( error_count )
		std::cout << RED WARNING "  ---------------------- ft::" << ctr << " failed " << error_count
				  << " test" << ( error_count == 1 ? "" : "s" )
				  << " ---------------------- " WARNING RESET "\n\n";
	else
		std::cout << GREEN CHECK " ---------------------- ft::" << ctr
				  << " succeeded all tests ---------------------- " CHECK RESET "\n\n";
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

int main( void ) {
	if ( !std::system( NULL ) ) {
		std::cout << RED "No command processor available\n";
		exit( 1 );
	}
	std::system( "touch .logs; clear && printf '\e[3J'" );
	std::cout << std::boolalpha;
	srand( time( NULL ) );

	int error_count = 0;
	int test_idx	= 0;
	int total_tests;

	{
		{
			std::stringstream ss;
			std::system( "cat main.cpp | grep 'Algorithm Test' | wc -l | awk '{print "
						 "$1}' > .logs" );
			std::ifstream logFile( ".logs" );
			ss << logFile.rdbuf();
			ss >> total_tests;
			total_tests--;
		}
		printHead( "algorithm" );
		try {
			std::cout << MAGENTA "Algorithm Test " << ++test_idx << " of " << total_tests
					  << RESET "\n\n";
			std::cout << TITLE "is_integral()" RESET "\n\n";
			compare( ft::is_integral< bool >::value, std::is_integral< bool >::value, "bool\t\t",
					 "is_integral" );
			compare( ft::is_integral< char >::value, std::is_integral< char >::value, "char\t\t",
					 "is_integral" );
			compare( ft::is_integral< char16_t >::value, std::is_integral< char16_t >::value,
					 "char16_t\t", "is_integral" );
			compare( ft::is_integral< char32_t >::value, std::is_integral< char32_t >::value,
					 "char32_t\t", "is_integral" );
			compare( ft::is_integral< wchar_t >::value, std::is_integral< wchar_t >::value,
					 "wchar_t\t\t", "is_integral" );
			compare( ft::is_integral< signed char >::value, std::is_integral< signed char >::value,
					 "signed char\t", "is_integral" );
			compare( ft::is_integral< short int >::value, std::is_integral< short int >::value,
					 "short int\t", "is_integral" );
			compare( ft::is_integral< int >::value, std::is_integral< int >::value, "int\t\t",
					 "is_integral" );
			compare( ft::is_integral< long int >::value, std::is_integral< long int >::value,
					 "long int\t", "is_integral" );
			compare( ft::is_integral< long long int >::value,
					 std::is_integral< long long int >::value, "long long int\t", "is_integral" );
			compare( ft::is_integral< unsigned char >::value,
					 std::is_integral< unsigned char >::value, "unsigned char\t", "is_integral" );
			compare( ft::is_integral< unsigned short int >::value,
					 std::is_integral< unsigned short int >::value, "unsigned short int",
					 "is_integral" );
			compare( ft::is_integral< unsigned int >::value,
					 std::is_integral< unsigned int >::value, "unsigned int\t", "is_integral" );
			compare( ft::is_integral< unsigned long int >::value,
					 std::is_integral< unsigned long int >::value, "unsigned long int",
					 "is_integral" );
			compare( ft::is_integral< unsigned long long int >::value,
					 std::is_integral< unsigned long long int >::value, "unsigned long long int",
					 "is_integral" );
			compare( ft::is_integral< float >::value, std::is_integral< float >::value, "float\t\t",
					 "is_integral" );
			compare( ft::is_integral< double >::value, std::is_integral< double >::value,
					 "double\t\t", "is_integral" );
			compare( ft::is_integral< long double >::value, std::is_integral< long double >::value,
					 "long double\t", "is_integral" );
			compare( ft::is_integral< std::string >::value, std::is_integral< std::string >::value,
					 "string\t\t", "is_integral" );
			compare( ft::is_integral< std::vector< int > >::value,
					 std::is_integral< std::vector< int > >::value, "std::vector<int>",
					 "is_integral" );
			compare( ft::is_integral< std::vector< char > >::value,
					 std::is_integral< std::vector< char > >::value, "std::vector<char>",
					 "is_integral" );
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception &e ) {
			std::cout << e.what() << '\n';
			error_count++;
		}
		std::cout << WHITE << "Press \u21B5  to proceed with the next algorithm test" << RESET;
		while ( std::getchar() != '\n' )
			;
		std::system( "printf '\e[H\e[J\e[3J'" );
		// endOf algorithm tests
		printHead( "algorithm" );
		testResult( error_count, total_tests, "vector" );
		std::cout << WHITE << "Press \u21B5  to proceed with vector tests" << RESET "\n";
		while ( std::getchar() != '\n' )
			;
		std::system( "printf '\e[H\e[J'" );
	}
	{
		{
			std::stringstream ss;
			std::system( "cat main.cpp | grep 'Vector Test' | wc -l | awk '{print "
						 "$1}' > .logs" );
			std::ifstream logFile( ".logs" );
			ss << logFile.rdbuf();
			ss >> total_tests;
			total_tests--;
		}
		printHead( "vector" );
		try {
			std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests
					  << RESET "\n\n";
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
			std::cout << TITLE "Copy Constructor : new1( old )" RESET "\n\n";
			ft::vector< int >  ft_vec2( ft_vec );
			std::vector< int > std_vec2( std_vec );
			check( ft_vec2, std_vec2 );
			ft::vector< int >  ft_vec3;
			std::vector< int > std_vec3;
			std::cout << TITLE "Copy assignment operator : new2 = old" RESET "\n\n";
			ft_vec3	 = ft_vec;
			std_vec3 = std_vec;
			check( ft_vec3, std_vec3 );
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception &e ) {
			std::cout << e.what() << '\n';
			error_count++;
		}
		std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET;
		while ( std::getchar() != '\n' )
			;
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try {
			std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests
					  << RESET "\n\n";
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
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception &e ) {
			std::cout << e.what() << '\n';
			error_count++;
		}
		std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET;
		while ( std::getchar() != '\n' )
			;
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try {
			std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests
					  << RESET "\n\n";
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
			std::cout << TITLE "const copy Constructor" RESET "\n\n";
			const ft::vector< int >	 c_ft_vec( ft_vec );
			const std::vector< int > c_std_vec( std_vec );
			std::cout << TITLE "compare const and non const back()" RESET "\n\n";
			std::cout << "back";
			compare( ft_vec.back(), std_vec.back(), "vec", "vector" );
			std::cout << "c_back";
			compare( c_ft_vec.back(), c_std_vec.back(), "vec", "vector" );
			std::cout << TITLE "compare const and non const front()" RESET "\n\n";
			std::cout << "front";
			compare( ft_vec.front(), std_vec.front(), "vec", "vector" );
			std::cout << "c_front";
			compare( c_ft_vec.front(), c_std_vec.front(), "vec", "vector" );
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception &e ) {
			std::cout << e.what() << '\n';
			error_count++;
		}
		std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET;
		while ( std::getchar() != '\n' )
			;
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try {
			std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests
					  << RESET "\n\n";
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
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception &e ) {
			std::cout << e.what() << '\n';
			error_count++;
		}
		std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET;
		while ( std::getchar() != '\n' )
			;
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try {
			std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests
					  << RESET "\n\n";
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
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception &e ) {
			std::cout << e.what() << '\n';
			error_count++;
		}
		std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET;
		while ( std::getchar() != '\n' )
			;
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try {
			std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests
					  << RESET "\n\n";
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
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception &e ) {
			std::cout << e.what() << '\n';
			error_count++;
		}
		std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET;
		while ( std::getchar() != '\n' )
			;
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try {
			std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests
					  << RESET "\n\n";
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
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception &e ) {
			std::cout << e.what() << '\n';
			error_count++;
		}
		std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET;
		while ( std::getchar() != '\n' )
			;
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try {
			std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests
					  << RESET "\n\n";
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
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception &e ) {
			std::cout << e.what() << '\n';
			error_count++;
		}
		std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET;
		while ( std::getchar() != '\n' )
			;
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try {
			std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests
					  << RESET "\n\n";
			int n	= ( rand() % 10 ) + 1;
			int val = ( rand() % 100 ) + 1;
			std::cout << TITLE "Parametrized Constructors : vec( " << n << ", " << val << " )"
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
			// n = ( rand() % 10 ) + 1;
			// val = ( rand() % 100 ) + 1;
			// std::cout << TITLE "Parametrized Constructors : vec2( " << n << ", " <<
			// val << " )" << RESET "\n\n"; std::vector<int> std_vec2( n, val );
			// ft::vector<int> ft_vec2( n, val );
			// std::cout << TITLE "insert ( vec.begin() + 2, vec2.begin(), vec2.end()
			// )" << RESET "\n\n"; std_vec.insert ( std_vec.begin() + 2,
			// std_vec2.begin(), std_vec2.end() ); ft_vec.insert ( ft_vec.begin() + 2,
			// ft_vec2.begin(), ft_vec2.end() ); check( ft_vec, std_vec ); n = (
			// rand() % 10 ) + 1; std::cout << TITLE "int arr [] = { " << n << ", " <<
			// n + 1 << ", " << n + 2 << " }" << RESET "\n\n"; int arr [] = { n, n +
			// 1, n + 2 }; std::cout << TITLE "insert ( begin(), arr, arr + 3 )" <<
			// RESET "\n\n"; std_vec.insert ( std_vec.begin(), arr, arr + 3 );
			// ft_vec.insert ( ft_vec.begin(), arr, arr + 3 );
			// check( ft_vec, std_vec );
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception &e ) {
			std::cout << e.what() << '\n';
			error_count++;
		}
		std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET;
		while ( std::getchar() != '\n' )
			;
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try {
			std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests
					  << RESET "\n\n";
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
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception &e ) {
			std::cout << e.what() << '\n';
			error_count++;
		}
		std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET;
		while ( std::getchar() != '\n' )
			;
		std::system( "printf '\e[H\e[J\e[3J'" );
		// endOf vector tests
		printHead( "vector" );
		testResult( error_count, total_tests, "vector" );
		std::cout << WHITE << "Press \u21B5  to proceed with the next container" << RESET "\n";
		while ( std::getchar() != '\n' )
			;
		std::system( "printf '\e[H\e[J'" );
	}

	std::system( "rm -f .logs" );

	return ( 0 );
}
