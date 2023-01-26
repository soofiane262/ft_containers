/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:37:52 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/27 00:06:25 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

#define compare( ctr1, ctr2, str, err ) compare( ctr1, ctr2, str, err, __LINE__ )
#define check( ctr1, ctr2 )				check( ctr1, ctr2, __LINE__ )

void testResult( int error_count, const std::string ctr ) {
	std::string cmd[ 2 ] = { "leaks " + ctr + " | grep '0 leaks' > .logs && rm -f .logs",
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

	int			error_count = 0;
	int			test_idx	= 0;
	bool		waitState	= false;
	std::string testName	= "ft_utils";
	{
		printHead( testName );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "is_integral()" RESET "\n\n";
			compare( ft::is_integral< char >::value, std::is_integral< char >::value, "char\t\t",
					 "is_integral" );
			compare( ft::is_integral< signed char >::value, std::is_integral< signed char >::value,
					 "signed char\t", "is_integral" );
			compare( ft::is_integral< unsigned char >::value,
					 std::is_integral< unsigned char >::value, "unsigned char\t", "is_integral" );
			compare( ft::is_integral< short >::value, std::is_integral< short >::value, "short\t\t",
					 "is_integral" );
			compare( ft::is_integral< short int >::value, std::is_integral< short int >::value,
					 "short int\t", "is_integral" );
			compare( ft::is_integral< signed short >::value,
					 std::is_integral< signed short >::value, "signed short\t", "is_integral" );
			compare( ft::is_integral< signed short int >::value,
					 std::is_integral< signed short int >::value, "signed short int",
					 "is_integral" );
			compare( ft::is_integral< unsigned short >::value,
					 std::is_integral< unsigned short >::value, "unsigned short\t", "is_integral" );
			compare( ft::is_integral< unsigned short int >::value,
					 std::is_integral< unsigned short int >::value, "unsigned short int",
					 "is_integral" );
			compare( ft::is_integral< int >::value, std::is_integral< int >::value, "int\t\t",
					 "is_integral" );
			compare( ft::is_integral< signed >::value, std::is_integral< signed >::value,
					 "signed\t\t", "is_integral" );
			compare( ft::is_integral< signed int >::value, std::is_integral< signed int >::value,
					 "signed int\t", "is_integral" );
			compare( ft::is_integral< unsigned >::value, std::is_integral< unsigned >::value,
					 "unsigned\t", "is_integral" );
			compare( ft::is_integral< unsigned int >::value,
					 std::is_integral< unsigned int >::value, "unsigned int\t", "is_integral" );
			compare( ft::is_integral< long >::value, std::is_integral< long >::value, "long\t\t",
					 "is_integral" );
			compare( ft::is_integral< long int >::value, std::is_integral< long int >::value,
					 "long int\t", "is_integral" );
			compare( ft::is_integral< signed long >::value, std::is_integral< signed long >::value,
					 "signed long\t", "is_integral" );
			compare( ft::is_integral< signed long int >::value,
					 std::is_integral< signed long int >::value, "signed long int\t",
					 "is_integral" );
			compare( ft::is_integral< unsigned long >::value,
					 std::is_integral< unsigned long >::value, "unsigned long\t", "is_integral" );
			compare( ft::is_integral< unsigned long int >::value,
					 std::is_integral< unsigned long int >::value, "unsigned long int",
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
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		//
		std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
		testResult( error_count, testName );
	} // utils

	return ( 0 );
}
