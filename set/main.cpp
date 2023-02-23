/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:37:52 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/23 16:32:49 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

#include <cstddef>
#include <cstdlib>
#include <functional>
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
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";

			int range = 100;

			std::vector< int > in;
			for ( int i = 0; i < 100; i++ ) in.push_back( rand() % range + range * i );
			std::shuffle( in.begin(), in.end(), mt );

			std::set< int > std_set;
			ft::set< int >	ft_set;

			ft_set.insert( in.begin(), in.end() );
			std_set.insert( in.begin(), in.end() );

			check( ft_set, std_set );

			std::set< int > std_set2( std_set );
			ft::set< int >	ft_set2( ft_set );

			check( ft_set2, std_set2 );

			std::cout << "\n" TITLE "swap()" RESET "\n\n";

			ft::swap( ft_set, ft_set2 );
			std::swap( std_set, std_set2 );
			check( ft_set, std_set );
			check( ft_set2, std_set2 );

			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";

			int range = 100;

			std::vector< int > in;
			for ( int i = 0; i < 20; i++ ) in.push_back( rand() % range + range * i );
			std::shuffle( in.begin(), in.end(), mt );

			std::set< int > std_set;
			ft::set< int >	ft_set;

			ft_set.insert( in.begin(), in.end() );
			std_set.insert( in.begin(), in.end() );

			check( ft_set, std_set );

			std::set< int >::iterator std_it = std_set.insert( 100 ).first;
			ft::set< int >::iterator  ft_it	 = ft_set.insert( 100 ).first;

			compare( *ft_it, *std_it, "it insert", "iterator" );

			++ft_it;
			++std_it;
			--ft_it;
			--std_it;

			for ( int i = 40; i < 60; i++ ) in.push_back( rand() % range + range * i );
			std::shuffle( in.begin(), in.end(), mt );

			ft_set.insert( in.begin(), in.end() );
			std_set.insert( in.begin(), in.end() );

			check( ft_set, std_set );

			ft_it  = ft_set.begin();
			std_it = std_set.begin();
			compare( *ft_it, *std_it, "it begin", "iterator" );

			std::set< int >::iterator std_it2 = std_set.end();
			ft::set< int >::iterator  ft_it2  = ft_set.end();

			++ft_it;
			++std_it;

			compare( *ft_it, *std_it, "++it", "iterator" );

			++ft_it;
			++std_it;
			compare( *ft_it, *std_it, "++it", "iterator" );

			ft_it++;
			std_it++;
			compare( *ft_it, *std_it, "it++", "iterator" );

			ft_it++;
			std_it++;
			compare( *ft_it, *std_it, "it++", "iterator" );

			ft_it--;
			std_it--;
			compare( *ft_it, *std_it, "it--", "iterator" );

			--ft_it2;
			--std_it2;
			compare( *ft_it2, *std_it2, "--it2", "iterator" );

			ft_it2--;
			std_it2--;
			compare( *ft_it2, *std_it2, "it2--", "iterator" );

			compare( ft_it == ft_it2, std_it == std_it2, "it == it2", "iterator" );
			compare( ft_it != ft_it2, std_it != std_it2, "it != it2", "iterator" );

			int idxToFind = rand() % in.size();

			std::cout << TITLE "find( " << idxToFind << " )" RESET "\n\n";

			const std::set< int >			c_std_set( std_set );
			const ft::set< int >			c_ft_set( ft_set );
			std::set< int >::const_iterator cstd_it = c_std_set.find( in[ idxToFind ] );
			ft::set< int >::const_iterator	cft_it	= c_ft_set.find( in[ idxToFind ] );

			compare( *cft_it, *cstd_it, "find", "find" );

			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";
			ft::set< char >								mp;
			ft::pair< ft::set< char >::iterator, bool > pr;
			pr = mp.insert( 'f' );

			std::cout << "insert( " << *pr.first << " ) : " << pr.second << '\n';

			pr = mp.insert( 'f' );

			std::cout << "insert( " << *pr.first << " ) : " << pr.second << '\n';

			pr = mp.insert( 'e' );

			std::cout << "insert( " << *pr.first << " ) : " << pr.second << '\n';

			std::cout << "erase( f ) : " << mp.erase( 'f' ) << '\n';

			std::cout << "erase( f ) : " << mp.erase( 'f' ) << '\n';
			mp.erase( mp.begin() );

			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";

			std::set< int > std_set;
			ft::set< int >	ft_set;

			std_set.insert( 400 );
			std_set.insert( 200 );
			std_set.insert( 600 );
			std_set.insert( 100 );
			std_set.insert( 300 );
			std_set.insert( 500 );
			std_set.insert( 700 );
			std_set.insert( 250 );
			std_set.insert( 350 );

			ft_set.insert( 400 );
			ft_set.insert( 200 );
			ft_set.insert( 600 );
			ft_set.insert( 100 );
			ft_set.insert( 300 );
			ft_set.insert( 500 );
			ft_set.insert( 700 );
			ft_set.insert( 250 );
			ft_set.insert( 350 );

			compare( *ft_set.find( 100 ), *std_set.find( 100 ), "find ( 100 )", "find" );
			compare( ft_set.count( 100 ), std_set.count( 100 ), "count ( 100 )", "count" );

			std::cout << TITLE "erase ( 100 )" RESET "\n\n";
			std_set.erase( 100 );
			ft_set.erase( 100 );

			compare( ft_set.count( 100 ), std_set.count( 100 ), "count ( 100 )", "count" );

			check( ft_set, std_set );

			std::cout << "\n" TITLE "clear()" RESET "\n\n";
			ft_set.clear();
			std_set.clear();
			check( ft_set, std_set );

			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";

			std::set< std::string > std_set;
			ft::set< std::string >	ft_set;

			compare( ft_set.count( "abcd" ), std_set.count( "abcd" ), "cout", "count" );

			compare( ft_set.count( "efgh" ), std_set.count( "efgh" ), "cout", "count" );

			compare( ft_set.count( "ijkl" ), std_set.count( "ijkl" ), "cout", "count" );

			std_set.insert( "seiurhg8347wo83twerw" );
			std_set.insert( "dsghesrzarherheat43" );
			std_set.insert( "awgfawe4t3A4YSDFGAS" );
			std_set.insert( "dzfg45yrthsdfgshju" );
			std_set.insert( "j564wedfshgj6ee5yegrs" );
			std_set.insert( "cfngcvcx56;oiliuee" );

			ft_set.insert( "seiurhg8347wo83twerw" );
			ft_set.insert( "dsghesrzarherheat43" );
			ft_set.insert( "awgfawe4t3A4YSDFGAS" );
			ft_set.insert( "dzfg45yrthsdfgshju" );
			ft_set.insert( "j564wedfshgj6ee5yegrs" );
			ft_set.insert( "cfngcvcx56;oiliuee" );

			compare( ft_set.count( "seiurhg8347wo83twerw" ),
					 std_set.count( "seiurhg8347wo83twerw" ), "cout", "count" );

			compare( ft_set.count( "dsghesrzarherheat43" ), std_set.count( "dsghesrzarherheat43" ),
					 "cout", "count" );

			compare( ft_set.count( "dzfg45yrthsdfgshju" ), std_set.count( "dzfg45yrthsdfgshju" ),
					 "cout", "count" );

			ft_set.erase( "dzfg45yrthsdfgshju" );
			std_set.erase( "dzfg45yrthsdfgshju" );

			compare( ft_set.count( "dzfg45yrthsdfgshju" ), std_set.count( "dzfg45yrthsdfgshju" ),
					 "cout", "count" );

			compare( ft_set.count( "cfngcvcx56;oiliuee" ), std_set.count( "cfngcvcx56;oiliuee" ),
					 "cout", "count" );

			compare( ft_set.count( "awgfawe4t3A4YSDFGAS" ), std_set.count( "awgfawe4t3A4YSDFGAS" ),
					 "cout", "count" );

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

			std::set< int > std_set;
			ft::set< int >	ft_set;

			ft_set.insert( &in[ 0 ], &in[ 20 ] );
			std_set.insert( &in[ 0 ], &in[ 20 ] );

			check( ft_set, std_set );

			std::cout << "\n" TITLE "Copy Constructor" RESET "\n\n";

			std::set< int > std_set2( std_set );
			ft::set< int >	ft_set2( ft_set );

			check( ft_set2, std_set2 );

			std::cout << "\n" TITLE "swap()" RESET "\n\n";

			ft::swap( ft_set, ft_set2 );
			std::swap( std_set, std_set2 );
			check( ft_set, std_set );
			check( ft_set2, std_set2 );

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

			std::set< int > std_set;
			ft::set< int >	ft_set;

			ft_set.insert( &in[ 0 ], &in[ 20 ] );
			std_set.insert( &in[ 0 ], &in[ 20 ] );

			check( ft_set, std_set );

			for ( int i = 0; i < 20; i++ ) {
				ft_set.erase( out[ i ] );
				std_set.erase( out[ i ] );
			}

			check( ft_set, std_set );

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

			std::set< int > std_set;
			ft::set< int >	ft_set;

			ft_set.insert( &in[ 0 ], &in[ 20 ] );
			std_set.insert( &in[ 0 ], &in[ 20 ] );

			check( ft_set, std_set );

			compare( *ft_set.lower_bound( 300 ), *std_set.lower_bound( 300 ), "lower_bound",
					 "lower_bound" );
			compare( *ft_set.lower_bound( -15 ), *std_set.lower_bound( -15 ), "lower_bound",
					 "lower_bound" );
			// compare( *ft_set.lower_bound( 800 ), *std_set.lower_bound( 800 ), "lower_bound",
			// "lower_bound" ); // should return end()

			compare( *ft_set.upper_bound( 300 ), *std_set.upper_bound( 300 ), "upper_bound",
					 "upper_bound" );
			compare( *ft_set.upper_bound( -15 ), *std_set.upper_bound( -15 ), "upper_bound",
					 "upper_bound" ); // should return end()
			// compare( *ft_set.upper_bound( 800 ), *std_set.upper_bound( 800 ), "upper_bound",
			// "lower_bound" ); // should return end()

			compare( *ft_set.equal_range( 300 ).first, *std_set.equal_range( 300 ).first,
					 "equal_range", "equal_range" );
			compare( *ft_set.equal_range( 300 ).second, *std_set.equal_range( 300 ).second,
					 "equal_range", "equal_range" );

			std::cout << "\n" TITLE "const_iterator" RESET "\n\n";

			const ft::set< int >		   cft_mp( ft_set );
			ft::set< int >::const_iterator cft_it  = cft_mp.begin();
			ft::set< int >::const_iterator cft_it2 = cft_mp.end();

			const std::set< int >			cstd_mp( std_set );
			std::set< int >::const_iterator cstd_it	 = cstd_mp.begin();
			std::set< int >::const_iterator cstd_it2 = cstd_mp.end();

			compare( cft_mp.size(), cstd_mp.size(), "size\t", "size" );
			if ( !std_set.empty() ) {
				std::cout << DIM STRIKE;
				for ( int i = 0; i < 40; i++ ) std::cout << ' ';
				std::cout << RESET "\n";
				for ( ; cft_it != cft_it2 || cstd_it != cstd_it2; ++cft_it, ++cstd_it ) {
					compare( *cft_it, *cstd_it, "", "map" );
				}
			}

			std::cout << "\n" TITLE "reverse_iterator" RESET "\n\n";
			ft::set< int >::reverse_iterator rft_it	 = ft_set.rbegin();
			ft::set< int >::reverse_iterator rft_it2 = ft_set.rend();

			std::set< int >::reverse_iterator rstd_it  = std_set.rbegin();
			std::set< int >::reverse_iterator rstd_it2 = std_set.rend();

			if ( !std_set.empty() ) {
				std::cout << DIM STRIKE;
				for ( int i = 0; i < 40; i++ ) std::cout << ' ';
				std::cout << RESET "\n";
				for ( ++rft_it, ++rstd_it; rft_it != rft_it2 || rstd_it != rstd_it2;
					  ++rft_it, ++rstd_it ) {
					compare( *rft_it, *rstd_it, "", "map" );
				}
			}

			std::cout << "\n" TITLE "const_reverse_iterator" RESET "\n\n";
			ft::set< int >::const_reverse_iterator crft_it	= cft_mp.rbegin();
			ft::set< int >::const_reverse_iterator crft_it2 = cft_mp.rend();

			std::set< int >::const_reverse_iterator crstd_it  = cstd_mp.rbegin();
			std::set< int >::const_reverse_iterator crstd_it2 = cstd_mp.rend();

			if ( !std_set.empty() ) {
				std::cout << DIM STRIKE;
				for ( int i = 0; i < 40; i++ ) std::cout << ' ';
				std::cout << RESET "\n";
				for ( ++crft_it, ++crstd_it; crft_it != crft_it2 || crstd_it != crstd_it2;
					  ++crft_it, ++crstd_it ) {
					compare( *crft_it, *crstd_it, "", "map" );
				}
			}

			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "Default Constructor" RESET "\n\n";

			int arr[]  = { 100, 110 };
			int arr2[] = { 50, 60, 70 };
			int arr3[] = { 200, 210, 220, 100 };

			std::set< int > std_set( arr, arr + 2 ), std_set2( arr, arr + 2 ),
				std_set3( arr2, arr2 + 3 ), std_set4( arr3, arr3 + 4 );
			ft::set< int > ft_set( arr, arr + 2 ), ft_set2( arr, arr + 2 ),
				ft_set3( arr2, arr2 + 3 ), ft_set4( arr3, arr3 + 4 );

			check( ft_set, std_set );
			check( ft_set2, std_set2 );
			check( ft_set3, std_set3 );
			check( ft_set4, std_set4 );
			std::cout << TITLE "relational operators" RESET "\n\n";
			compare( ft_set == ft_set2, std_set == std_set2, "==\t2", testName );
			compare( ft_set != ft_set2, std_set != std_set2, "!=\t2", testName );
			compare( ft_set < ft_set3, std_set < std_set3, "<\t3", testName );
			compare( ft_set < ft_set4, std_set < std_set4, "<\t4", testName );
			compare( ft_set > ft_set3, std_set > std_set3, ">\t3", testName );
			compare( ft_set > ft_set4, std_set > std_set4, ">\t4", testName );
			compare( ft_set <= ft_set2, std_set <= std_set2, "<=\t2", testName );
			compare( ft_set <= ft_set3, std_set <= std_set3, "<=\t3", testName );
			compare( ft_set >= ft_set2, std_set >= std_set2, ">=\t2", testName );
			compare( ft_set >= ft_set4, std_set >= std_set4, ">=\t4", testName );
			std::cout << "\n" GREEN CHECK " Test " << test_idx << " : Sucess" RESET "\n\n";
		} catch ( std::exception &e ) { catchExcept( e, error_count ); }
		waitForTests( testName, waitState );
		try {
			std::cout << MAGENTA << testName << " Test " << ++test_idx << RESET "\n\n";
			std::cout << TITLE "max_size()" << RESET "\n\n";
			ft::set< char > ft_char_mp;
			print( ft_char_mp.max_size(), "char\t\t" );
			ft::set< signed char > ft_schar_mp;
			print( ft_schar_mp.max_size(), "signed_char\t" );
			ft::set< unsigned char > ft_uschar_mp;
			print( ft_uschar_mp.max_size(), "unsigned_char\t" );
			ft::set< short > ft_short_mp;
			print( ft_short_mp.max_size(), "short\t\t" );
			ft::set< short int > ft_short_int_mp;
			print( ft_short_int_mp.max_size(), "short_int\t" );
			ft::set< signed short > ft_sshort_mp;
			print( ft_sshort_mp.max_size(), "signed_short\t" );
			ft::set< unsigned short > ft_ushort_mp;
			print( ft_ushort_mp.max_size(), "unsigned_short\t" );
			ft::set< unsigned short int > ft_ushort_int_mp;
			print( ft_ushort_int_mp.max_size(), "unsigned_short_int" );
			ft::set< int > ft_int_mp;
			print( ft_int_mp.max_size(), "int\t\t" );
			ft::set< signed > ft_signed_mp;
			print( ft_signed_mp.max_size(), "signed\t\t" );
			ft::set< signed int > ft_signed_int_mp;
			print( ft_signed_int_mp.max_size(), "signed_int\t" );
			ft::set< unsigned > ft_unsigned_mp;
			print( ft_unsigned_mp.max_size(), "unsigned\t" );
			ft::set< unsigned int > ft_uint_mp;
			print( ft_uint_mp.max_size(), "unsigned_int\t" );
			ft::set< long > ft_long_mp;
			print( ft_long_mp.max_size(), "long\t\t" );
			ft::set< long int > ft_lint_mp;
			print( ft_lint_mp.max_size(), "long_int\t" );
			ft::set< signed long > ft_slong_mp;
			print( ft_slong_mp.max_size(), "signed_long\t" );
			ft::set< signed long int > ft_slint_mp;
			print( ft_slint_mp.max_size(), "signed_long_int\t" );
			ft::set< unsigned long > ft_ulong_mp;
			print( ft_ulong_mp.max_size(), "unsigned_long\t" );
			ft::set< unsigned long int > ft_ulint_mp;
			print( ft_ulint_mp.max_size(), "unsigned_long_int" );
			ft::set< char * > ft_charptr_mp;
			print( ft_charptr_mp.max_size(), "char_*\t\t" );
			ft::set< std::string > ft_string_mp;
			print( ft_string_mp.max_size(), "std::string\t" );
			ft::set< std::set< char > > ft_stdcharmap_mp;
			print( ft_stdcharmap_mp.max_size(), "std::set< char>\t" );
			ft::set< ft::set< char > > ft_ftcharmap_mp;
			print( ft_ftcharmap_mp.max_size(), "ft::set< char>\t" );
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
