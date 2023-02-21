/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:37:52 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/21 18:38:32 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

#include <cstddef>
#include <cstdlib>
#include <limits>
#include <random>
#include <unistd.h>

#define compare( ctr1, ctr2, str, err ) compare( ctr1, ctr2, str, err, __LINE__ )
#define check( ctr1, ctr2 )				check( ctr1, ctr2, __LINE__ )

void checkLeaks( int &error_count, const std::string executable ) {
	std::string cmd[ 2 ] = { "leaks " + executable + " | grep '0 leaks' > .logs; rm -f .logs",
							 "leaks " + executable + " | tail -n +17" };
	if ( std::system( cmd[ 0 ].c_str() ) ) error_count++;
	std::system( cmd[ 1 ].c_str() );
}

void testResult( int error_count, const std::string ctr, const std::string executable ) {
	checkLeaks( error_count, executable );
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
	std::random_device rd;
	std::mt19937	   mt( rd() );

	int			error_count = 0;
	std::string testName	= "Map";
	{
		int	 test_idx  = 0;
		bool waitState = false;
		printHead( testName );
		std::cout << sizeof( bool ) << '\n';
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

			std::map< int, int > std_map;
			ft::map< int, int >	 ft_map;

			std_map.insert( std::pair< const int, int >( 400, 400 ) );
			std_map.insert( std::pair< const int, int >( 200, 200 ) );
			std_map.insert( std::pair< const int, int >( 600, 600 ) );
			std_map.insert( std::pair< const int, int >( 100, 100 ) );
			std_map.insert( std::pair< const int, int >( 300, 300 ) );
			std_map.insert( std::pair< const int, int >( 500, 500 ) );
			std_map.insert( std::pair< const int, int >( 700, 700 ) );
			std_map.insert( std::pair< const int, int >( 250, 250 ) );
			std_map.insert( std::pair< const int, int >( 350, 350 ) );

			ft_map.insert( ft::pair< const int, int >( 400, 400 ) );
			ft_map.insert( ft::pair< const int, int >( 200, 200 ) );
			ft_map.insert( ft::pair< const int, int >( 600, 600 ) );
			ft_map.insert( ft::pair< const int, int >( 100, 100 ) );
			ft_map.insert( ft::pair< const int, int >( 300, 300 ) );
			ft_map.insert( ft::pair< const int, int >( 500, 500 ) );
			ft_map.insert( ft::pair< const int, int >( 700, 700 ) );
			ft_map.insert( ft::pair< const int, int >( 250, 250 ) );
			ft_map.insert( ft::pair< const int, int >( 350, 350 ) );

			compare( ft_map.find( 100 ), std_map.find( 100 ), "find ( 100 )", "find" );
			compare( ft_map.count( 100 ), std_map.count( 100 ), "count ( 100 )", "count" );

			std::cout << TITLE "erase ( 100 )" RESET "\n\n";
			std_map.erase( 100 );
			ft_map.erase( 100 );

			compare( ft_map.count( 100 ), std_map.count( 100 ), "count ( 100 )", "count" );

			check( ft_map, std_map );
			ft_map.clear();
			std_map.clear();
			check( ft_map, std_map );

			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";

			std::map< int, std::string > std_map;
			ft::map< int, std::string >	 ft_map;

			compare( ft_map.count( 64 ), std_map.count( 64 ), "cout", "count" );

			compare( ft_map.count( 145 ), std_map.count( 145 ), "cout", "count" );

			compare( ft_map.count( 11 ), std_map.count( 11 ), "cout", "count" );

			std_map.insert( std::make_pair( 34, "seiurhg8347wo83twerw" ) );
			std_map.insert( std::make_pair( 2, "dsghesrzarherheat43" ) );
			std_map.insert( std::make_pair( 9, "awgfawe4t3A4YSDFGAS" ) );
			std_map.insert( std::make_pair( 3, "dzfg45yrthsdfgshju" ) );
			std_map.insert( std::make_pair( 22, "j564wedfshgj6ee5yegrs" ) );
			std_map.insert( std::make_pair( 10, "cfngcvcx56;oiliuee" ) );

			ft_map.insert( ft::make_pair( 34, "seiurhg8347wo83twerw" ) );
			ft_map.insert( ft::make_pair( 2, "dsghesrzarherheat43" ) );
			ft_map.insert( ft::make_pair( 9, "awgfawe4t3A4YSDFGAS" ) );
			ft_map.insert( ft::make_pair( 3, "dzfg45yrthsdfgshju" ) );
			ft_map.insert( ft::make_pair( 22, "j564wedfshgj6ee5yegrs" ) );
			ft_map.insert( ft::make_pair( 10, "cfngcvcx56;oiliuee" ) );

			compare( ft_map.count( 34 ), std_map.count( 34 ), "cout", "count" );

			compare( ft_map.count( 2 ), std_map.count( 2 ), "cout", "count" );

			compare( ft_map.count( 9 ), std_map.count( 9 ), "cout", "count" );

			ft_map.erase( 9 );
			std_map.erase( 9 );

			compare( ft_map.count( 9 ), std_map.count( 9 ), "cout", "count" );

			compare( ft_map.count( 10 ), std_map.count( 10 ), "cout", "count" );

			compare( ft_map.count( 22 ), std_map.count( 22 ), "cout", "count" );

			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";

			int range = 100;

			std::vector< int > in;
			for ( int i = 0; i < 20; i++ ) in.push_back( rand() % range + range * i );
			std::vector< int > out( in );
			std::shuffle( in.begin(), in.end(), mt );
			std::shuffle( out.begin(), out.end(), mt );

			ft::pair< int, int >  ft_in_pr[ 20 ];
			std::pair< int, int > std_in_pr[ 20 ];
			ft::pair< int, int >  ft_out_pr[ 20 ];
			std::pair< int, int > std_out_pr[ 20 ];

			for ( int i = 0; i < 20; i++ ) {
				ft_in_pr[ i ]	= ft::make_pair( in[ i ], in[ i ] );
				std_in_pr[ i ]	= std::make_pair( in[ i ], in[ i ] );
				ft_out_pr[ i ]	= ft::make_pair( out[ i ], out[ i ] );
				std_out_pr[ i ] = std::make_pair( out[ i ], out[ i ] );
			}

			std::map< int, int > std_map;
			ft::map< int, int >	 ft_map;
			ft_map.insert( ft_in_pr, ft_in_pr + 20 );
			std_map.insert( std_in_pr, std_in_pr + 20 );

			check( ft_map, std_map );

			std::map< int, int > std_map2( std_map );
			ft::map< int, int >	 ft_map2( ft_map );

			check( ft_map2, std_map2 );

			ft::swap( ft_map, ft_map2 );
			std::swap( std_map, std_map2 );

			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";

			int range = 100;

			std::vector< int > in;
			for ( int i = 0; i < 20; i++ ) in.push_back( rand() % range + range * i );
			std::vector< int > out( in );
			std::shuffle( in.begin(), in.end(), mt );
			std::shuffle( out.begin(), out.end(), mt );

			ft::pair< int, int >  ft_in_pr[ 20 ];
			std::pair< int, int > std_in_pr[ 20 ];

			for ( int i = 0; i < 20; i++ ) {
				ft_in_pr[ i ]  = ft::make_pair( in[ i ], in[ i ] );
				std_in_pr[ i ] = std::make_pair( in[ i ], in[ i ] );
			}

			std::map< int, int > std_map;
			ft::map< int, int >	 ft_map;

			ft_map.insert( ft_in_pr, ft_in_pr + 20 );
			std_map.insert( std_in_pr, std_in_pr + 20 );

			check( ft_map, std_map );

			for ( int i = 0; i < 20; i++ ) {
				ft_map.erase( out[ i ] );
				std_map.erase( out[ i ] );
			}

			check( ft_map, std_map );

			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";

			std::map< int, int > std_map;
			ft::map< int, int >	 ft_map;

			std_map[ 400 ] = 400;
			std_map[ 200 ] = 200;
			std_map[ 600 ] = 600;
			std_map[ 100 ] = 100;
			std_map[ 300 ] = 300;
			std_map[ 500 ] = 500;
			std_map[ 700 ] = 700;
			std_map[ 250 ] = 250;
			std_map[ 350 ] = 350;

			ft_map[ 400 ] = 400;
			ft_map[ 200 ] = 200;
			ft_map[ 600 ] = 600;
			ft_map[ 100 ] = 100;
			ft_map[ 300 ] = 300;
			ft_map[ 500 ] = 500;
			ft_map[ 700 ] = 700;
			ft_map[ 250 ] = 250;
			ft_map[ 350 ] = 350;

			check( ft_map, std_map );

			compare( ft_map.lower_bound( 300 ), std_map.lower_bound( 300 ), "lower_bound",
					 "lower_bound" );
			compare( ft_map.lower_bound( -15 ), std_map.lower_bound( -15 ), "lower_bound",
					 "lower_bound" );
			// compare( ft_map.lower_bound( 800 ), std_map.lower_bound( 800 ), "lower_bound",
			// "lower_bound" ); // should return end()

			compare( ft_map.upper_bound( 300 ), std_map.upper_bound( 300 ), "upper_bound",
					 "upper_bound" );
			compare( ft_map.upper_bound( -15 ), std_map.upper_bound( -15 ), "upper_bound",
					 "upper_bound" ); // should return end()
			// compare( ft_map.upper_bound( 800 ), std_map.upper_bound( 800 ), "upper_bound",
			// "lower_bound" ); // should return end()

			compare( ft_map.equal_range( 300 ).first, std_map.equal_range( 300 ).first,
					 "equal_range", "equal_range" );
			compare( ft_map.equal_range( 300 ).second, std_map.equal_range( 300 ).second,
					 "equal_range", "equal_range" );

			const ft::map< int, int >				  cft_mp;
			const ft::map< int, int >::const_iterator cft_it  = cft_mp.begin();
			const ft::map< int, int >::const_iterator cft_it2 = cft_mp.end();

			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "max_size()" << RESET "\n\n";
			ft::map< int, char >  ft_char_mp;
			std::map< int, char > std_char_mp;
			compare( ft_char_mp.max_size(), std_char_mp.max_size(), "char\t\t", "max_size" );
			ft::map< int, signed char >	 ft_schar_mp;
			std::map< int, signed char > std_schar_mp;
			compare( ft_schar_mp.max_size(), std_schar_mp.max_size(), "signed_char\t", "max_size" );
			ft::map< int, unsigned char >  ft_uschar_mp;
			std::map< int, unsigned char > std_uschar_mp;
			compare( ft_uschar_mp.max_size(), std_uschar_mp.max_size(), "unsigned_char\t",
					 "max_size" );
			ft::map< int, short >  ft_short_mp;
			std::map< int, short > std_short_mp;
			compare( ft_short_mp.max_size(), std_short_mp.max_size(), "short\t\t", "max_size" );
			ft::map< int, short int >  ft_short_int_mp;
			std::map< int, short int > std_short_int_mp;
			compare( ft_short_int_mp.max_size(), std_short_int_mp.max_size(), "short_int\t",
					 "max_size" );
			ft::map< int, signed short >  ft_sshort_mp;
			std::map< int, signed short > std_sshort_mp;
			compare( ft_sshort_mp.max_size(), std_sshort_mp.max_size(), "signed_short\t",
					 "max_size" );
			ft::map< int, unsigned short >	ft_ushort_mp;
			std::map< int, unsigned short > std_ushort_mp;
			compare( ft_ushort_mp.max_size(), std_ushort_mp.max_size(), "unsigned_short\t",
					 "max_size" );
			ft::map< int, unsigned short int >	ft_ushort_int_mp;
			std::map< int, unsigned short int > std_ushort_int_mp;
			compare( ft_ushort_int_mp.max_size(), std_ushort_int_mp.max_size(),
					 "unsigned_short_int", "max_size" );
			ft::map< int, int >	 ft_int_mp;
			std::map< int, int > std_int_mp;
			compare( ft_int_mp.max_size(), std_int_mp.max_size(), "int\t\t", "max_size" );
			ft::map< int, signed >	ft_signed_mp;
			std::map< int, signed > std_signed_mp;
			compare( ft_signed_mp.max_size(), std_signed_mp.max_size(), "signed\t\t", "max_size" );
			ft::map< int, signed int >	ft_signed_int_mp;
			std::map< int, signed int > std_signed_int_mp;
			compare( ft_signed_int_mp.max_size(), std_signed_int_mp.max_size(), "signed_int\t",
					 "max_size" );
			ft::map< int, unsigned >  ft_unsigned_mp;
			std::map< int, unsigned > std_unsigned_mp;
			compare( ft_unsigned_mp.max_size(), std_unsigned_mp.max_size(), "unsigned\t",
					 "max_size" );
			ft::map< int, unsigned int >  ft_uint_mp;
			std::map< int, unsigned int > std_uint_mp;
			compare( ft_uint_mp.max_size(), std_uint_mp.max_size(), "unsigned_int\t", "max_size" );
			ft::map< int, long >  ft_long_mp;
			std::map< int, long > std_long_mp;
			compare( ft_long_mp.max_size(), std_long_mp.max_size(), "long\t\t", "max_size" );
			ft::map< int, long int >  ft_lint_mp;
			std::map< int, long int > std_lint_mp;
			compare( ft_lint_mp.max_size(), std_lint_mp.max_size(), "long_int\t", "max_size" );
			ft::map< int, signed long >	 ft_slong_mp;
			std::map< int, signed long > std_slong_mp;
			compare( ft_slong_mp.max_size(), std_slong_mp.max_size(), "signed_long\t", "max_size" );
			ft::map< int, signed long int >	 ft_slint_mp;
			std::map< int, signed long int > std_slint_mp;
			compare( ft_slint_mp.max_size(), std_slint_mp.max_size(), "signed_long_int\t",
					 "max_size" );
			ft::map< int, unsigned long >  ft_ulong_mp;
			std::map< int, unsigned long > std_ulong_mp;
			compare( ft_ulong_mp.max_size(), std_ulong_mp.max_size(), "unsigned_long\t",
					 "max_size" );
			ft::map< int, unsigned long int >  ft_ulint_mp;
			std::map< int, unsigned long int > std_ulint_mp;
			compare( ft_ulint_mp.max_size(), std_ulint_mp.max_size(), "unsigned_long_int",
					 "max_size" );
			ft::map< int, char * >	ft_charptr_mp;
			std::map< int, char * > std_charptr_mp;
			compare( ft_charptr_mp.max_size(), std_charptr_mp.max_size(), "char_*\t\t",
					 "max_size" );
			ft::map< int, std::string >	 ft_string_mp;
			std::map< int, std::string > std_string_mp;
			compare( ft_string_mp.max_size(), std_string_mp.max_size(), "std::string\t",
					 "max_size" );
			ft::map< int, std::map< char, char > >	ft_stdcharmap_mp;
			std::map< int, std::map< char, char > > std_stdcharmap_mp;
			compare( ft_stdcharmap_mp.max_size(), std_stdcharmap_mp.max_size(),
					 "std::map<char, char>", "max_size" );
			ft::map< int, ft::map< char, char > >  ft_ftcharmap_mp;
			std::map< int, ft::map< char, char > > std_ftcharmap_mp;
			compare( ft_ftcharmap_mp.max_size(), std_ftcharmap_mp.max_size(), "ft::map<char, char>",
					 "max_size" );
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
