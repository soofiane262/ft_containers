/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:37:52 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/19 17:15:48 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

#include <cstddef>
#include <unistd.h>

#define compare( ctr1, ctr2, str, err ) compare( ctr1, ctr2, str, err, __LINE__ )
#define check( ctr1, ctr2 )				check( ctr1, ctr2, __LINE__ )

void testResult( int error_count, const std::string ctr, const std::string executable ) {
	std::string cmd[ 2 ] = { "leaks " + executable + " | grep '0 leaks' > .logs; rm -f .logs",
							 "leaks " + executable + " | tail -n +17" };
	if ( std::system( cmd[ 0 ].c_str() ) ) error_count++;
	std::system( cmd[ 1 ].c_str() );
	if ( error_count ) {
		std::cout << RED BLINK WARNING _BLINK << "  " << STRIKE;
		for ( int i = 0; i < 25; i++ ) std::cout << ' ';
		std::cout << _STRIKE " " << ctr << " failed " << error_count << " test"
				  << ( error_count == 1 ? "" : "s" ) << " " STRIKE;
		for ( int i = 0; i < 25; i++ ) std::cout << ' ';
		std::cout << _STRIKE " " BLINK WARNING RESET "\n\n";
	} else {
		std::cout << GREEN CHECK << " " << STRIKE;
		for ( int i = 0; i < 25; i++ ) std::cout << ' ';
		std::cout << _STRIKE " " << ctr << " succeeded all tests " STRIKE;
		for ( int i = 0; i < 25; i++ ) std::cout << ' ';
		std::cout << _STRIKE " " CHECK RESET "\n\n";
	}
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
			std::cout << "/* " STRIKE;
			for ( int j = 0; j < length; j++ ) std::cout << ' ';
			std::cout << _STRIKE " */\n";
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
	std::cout << RED << e.what() << '\n';
	error_count++;
	std::cout << WHITE << "Press \u21B5  to proceed" << RESET;
	while ( std::getchar() != '\n' ) continue;
	std::cout << "\n";
}

void mapTest( const std::string executable ) {
	if ( !std::system( NULL ) ) {
		std::cout << RED "No command processor available\n";
		exit( 1 );
	}
	std::system( "clear" );
	std::cout.imbue( std::locale( "en_US.UTF-8" ) );
	std::cout << std::boolalpha;
	srand( time( NULL ) );

	int			error_count = 0;
	std::string testName	= "Map";
	{
		int	 test_idx  = 0;
		bool waitState = false;
		printHead( testName );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";
			ft::map< int, char >							 mp;
			ft::pair< ft::map< int, char >::iterator, bool > pr(
				mp.insert( ft::pair< const int, char >( 'f', 'f' ) ) );
			std::cout << "insert( " << pr.first->first << ", " << pr.first->second
					  << " ) : " << pr.second << '\n';
			pr = mp.insert( ft::pair< const int, char >( 'f', 'f' ) );
			std::cout << "insert( " << pr.first->first << ", " << pr.first->second
					  << " ) : " << pr.second << '\n';
			pr = mp.insert( ft::pair< const int, char >( 'e', 'e' ) );
			std::cout << "insert( " << pr.first->first << ", " << pr.first->second
					  << " ) : " << pr.second << '\n';
			std::cout << "erase( f ) : " << mp.erase( 'f' ) << '\n';
			std::cout << "erase( f ) : " << mp.erase( 'f' ) << '\n';
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		//
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";

			ft::map< char, int > mymap;

			mymap.insert( ft::pair< const char, int >( 'b', 100 ) );
			mymap.insert( ft::pair< const char, int >( 'a', 200 ) );
			mymap.insert( ft::pair< const char, int >( 'c', 300 ) );

			// mymap[ 'b' ] = 100;
			// mymap[ 'a' ] = 200;
			// mymap[ 'c' ] = 300;

			std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
			sleep( 2 );

			for ( ft::map< char, int >::iterator it = mymap.begin(); it != mymap.end(); ++it ) {
				std::cout << "here\n";
				sleep( 1 );
				std::cout << it->first << " => " << it->second << '\n';
			}

			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		//
		std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
	} // vector
	testResult( error_count, testName, executable );
}

int main( int, char **av ) {
	mapTest( std::string( av[ 0 ] ).erase( 0, 2 ) );
	return ( 0 );
}
