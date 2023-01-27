/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:37:52 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/27 19:45:25 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

#include <cstddef>

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

void vectorTest( const std::string executable ) {
	if ( !std::system( NULL ) ) {
		std::cout << RED "No command processor available\n";
		exit( 1 );
	}
	std::system( "clear" );
	std::cout.imbue( std::locale( "en_US.UTF-8" ) );
	std::cout << std::boolalpha;
	srand( time( NULL ) );

	int			error_count = 0;
	std::string testName	= "Stack";
	{
		int	 test_idx  = 0;
		bool waitState = false;
		printHead( testName );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Initializing a vector, deque and list" RESET "\n\n";
			int				   n[ 2 ] = { ( rand() % 10 ) + 1, ( rand() % 100 ) + 1 };
			ft::vector< int >  ft_vector( n[ 0 ], n[ 1 ] );
			std::deque< int >  std_deque( n[ 0 ], n[ 1 ] );
			std::vector< int > std_vector( ( rand() % 10 ) + 1, ( rand() % 100 ) + 1 );
			std::list< int >   std_list( ( rand() % 10 ) + 1, ( rand() % 10 ) + 1 );
			std::cout << TITLE "Copy Constructor : stack( ctnr )" RESET "\n\n";
			ft::stack< int >  ft_stack( ft_vector );
			std::stack< int > std_stack( std_deque );
			check( ft_stack, std_stack );
			ft::stack< int, std::vector< int > >  ft_stack2( std_vector );
			std::stack< int, std::vector< int > > std_stack2( std_vector );
			check( ft_stack2, std_stack2 );
			ft::stack< int, std::deque< int > >	 ft_stack3( std_deque );
			std::stack< int, std::deque< int > > std_stack3( std_deque );
			check( ft_stack3, std_stack3 );
			ft::stack< int, std::list< int > >	ft_stack4( std_list );
			std::stack< int, std::list< int > > std_stack4( std_list );
			check( ft_stack4, std_stack4 );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";
			ft::stack< int >  ft_stack;
			std::stack< int > std_stack;
			std::cout << TITLE "empty()" RESET "\n\n";
			compare( ft_stack.empty(), std_stack.empty(), "\t", testName );
			std::cout << TITLE "push() inside loop" RESET "\n\n";
			for ( int i = 0, end = ( rand() % 10 ) + 1, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_stack.push( n );
				std_stack.push( n );
			}
			check( ft_stack, std_stack );
			std::cout << TITLE "const copy Constructor c_vec" RESET "\n\n";
			const ft::stack< int >	c_ft_stack( ft_stack );
			const std::stack< int > c_std_stack( std_stack );
			std::cout << TITLE "compare const and non const top()" RESET "\n\n";
			std::cout << "top";
			compare( ft_stack.top(), std_stack.top(), "\t", testName );
			std::cout << "c_top";
			compare( c_ft_stack.top(), c_std_stack.top(), "\t", testName );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";
			ft::stack< int >  ft_stack;
			std::stack< int > std_stack;
			std::cout << TITLE "push() inside loop" RESET "\n\n";
			for ( int i = 0, end = ( rand() % 10 ) + 1, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_stack.push( n );
				std_stack.push( n );
			}
			check( ft_stack, std_stack );
			std::cout << TITLE "pop() inside loop" RESET "\n\n";
			for ( int i = 0, end = std_stack.size() / 2; i < end; i++ ) {
				ft_stack.pop();
				std_stack.pop();
			}
			check( ft_stack, std_stack );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";
			ft::stack< int >  ft_stack, ft_stack2, ft_stack3, ft_stack4;
			std::stack< int > std_stack, std_stack2, std_stack3, std_stack4;
			std::cout << TITLE "push() inside loop" RESET "\n\n";
			for ( int i = 0; i < 2; i++ ) {
				ft_stack.push( 100 );
				std_stack.push( 100 );
				ft_stack2.push( 100 );
				std_stack2.push( 100 );
			}
			for ( int i = 0; i < 3; i++ ) {
				ft_stack3.push( 50 );
				std_stack3.push( 50 );
			}
			for ( int i = 0; i < 4; i++ ) {
				ft_stack4.push( 200 );
				std_stack4.push( 200 );
			}
			check( ft_stack, std_stack );
			check( ft_stack2, std_stack2 );
			check( ft_stack3, std_stack3 );
			check( ft_stack4, std_stack4 );
			std::cout << TITLE "relational operators" RESET "\n\n";
			compare( ft_stack == ft_stack2, std_stack == std_stack2, "==\t2", testName );
			compare( ft_stack != ft_stack2, std_stack != std_stack2, "!=\t2", testName );
			compare( ft_stack < ft_stack3, std_stack < std_stack3, "<\t3", testName );
			compare( ft_stack < ft_stack4, std_stack < std_stack4, "<\t4", testName );
			compare( ft_stack > ft_stack3, std_stack > std_stack3, ">\t3", testName );
			compare( ft_stack > ft_stack4, std_stack > std_stack4, ">\t4", testName );
			compare( ft_stack <= ft_stack2, std_stack <= std_stack2, "<=\t2", testName );
			compare( ft_stack <= ft_stack3, std_stack <= std_stack3, "<=\t3", testName );
			compare( ft_stack >= ft_stack2, std_stack >= std_stack2, ">=\t2", testName );
			compare( ft_stack >= ft_stack4, std_stack >= std_stack4, ">=\t4", testName );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		//
		std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
	} // stack
	testResult( error_count, testName, executable );
}

int main( void ) {
	vectorTest( "ft_stack" );
	return ( 0 );
}
