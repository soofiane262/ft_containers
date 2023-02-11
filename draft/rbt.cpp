/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:57:44 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/11 16:55:26 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbt.hpp"

#include <cstdlib>
#include <ctime>
#include <ios>
#include <unistd.h>
#include <vector>

int main( void ) {
	std::system( "clear" );
	std::cout << std::boolalpha;
	srand( time( NULL ) );

	// {
	// 	int		   sz	 = 30;
	// 	int		   in[]	 = { 5,	 66, 35, 64, 26, 40, 78, 35, 32, 21, 61, 86, 9,	 55, 1,
	// 						 93, 47, 61, 0,	 67, 49, 72, 34, 66, 32, 20, 1,	 50, 64, 47 };
	// 	int		   out[] = { 47, 72, 9,	 47, 9,	 64, 86, 93, 1, 93, 9,	32, 32, 64, 50,
	// 						 35, 49, 35, 35, 47, 20, 0,	 67, 0, 64, 86, 86, 55, 47, 78 };
	// 	rbt< int > n;
	// 	for ( int i = 0; i < sz; i++ ) n.insert( in[ i ] );
	// 	// n.log();
	// 	for ( int i = 0; i < sz; i++ ) {
	// 		// std::cout << "before del " << out[ i ] << "\n";
	// 		// n.log();
	// 		n.log();
	// 		n.logAdr();
	// 		std::cout << "del " << out[ i ] << "\n";
	// 		n.del( out[ i ] );
	// 		n.log();
	// 		n.logAdr();
	// 		// std::cout << "after del " << out[ i ] << "\n";
	// 		// n.log();
	// 	}
	// 	std::cout << "hi\n";
	// 	// n.log();
	// 	// n.logAdr();
	// }
	// std::system( "leaks a.out" );

	// random
	// {
	// 	while ( 1 ) {
	// 		{
	// 			int				   sz = 30;
	// 			std::vector< int > vec[ 2 ];
	// 			for ( int i = 0; i < sz; i++ ) vec[ 0 ].push_back( rand() % 100 );
	// 			for ( int i = 0; i < sz; i++ )
	// 				vec[ 1 ].push_back( vec[ 0 ][ rand() % vec[ 0 ].size() ] );
	// 			std::cout << "insert ";
	// 			for ( int i = 0; i < sz; i++ ) std::cout << vec[ 0 ][ i ] << ' ';
	// 			std::cout << "\ndelete ";
	// 			for ( int i = 0; i < sz; i++ ) std::cout << vec[ 1 ][ i ] << ' ';
	// 			std::cout << '\n';
	// 			rbt< int > n;
	// 			for ( int i = 0; i < sz; i++ ) n.insert( vec[ 0 ][ i ] );
	// 			// n.log();
	// 			for ( int i = 0; i < sz; i++ ) {
	// 				// std::cout << "deleting"
	// 				n.del( vec[ 1 ][ i ] );
	// 				// n.log();
	// 			}
	// 			// sleep( 1 );
	// 			// std::system( "clear" );
	// 		}
	// 	}
	// }
	// std::system( "leaks a.out" );

	// simple test
	{
		rbt< int > n;
		for ( int i = 0; i < 10; i++ ) n.insert( i );
		n.log();
		std::cout << "find 0\t: " << n.find( 0 ) << '\n';
		std::cout << "find 1\t: " << n.find( 1 ) << '\n';
		std::cout << "find 9\t: " << n.find( 9 ) << '\n';
		std::cout << "find 10\t: " << n.find( 10 ) << '\n';
		n.del( 8 );
		n.log();
		n.del( 6 );
		n.log();
		n.del( 4 );
		n.log();
	}

	// case 1 --> if ( elt != 5 && elt != 30 && elt != 38 ) _color = BLACK; ==> OK
	// {
	// 	rbt< int > n;
	// 	n.insert( 10 );
	// 	n.insert( 5 );
	// 	n.insert( 30 );
	// 	n.insert( 2 );
	// 	n.insert( 9 );
	// 	n.insert( 25 );
	// 	n.insert( 40 );
	// 	n.insert( 38 );
	// 	n.del( 30 );
	// }

	// case 3 --> if ( elt != 20 ) _color = BLACK; ==> OK
	// {
	// 	rbt< int > n;
	// 	n.insert( 10 );
	// 	n.insert( 5 );
	// 	n.insert( 20 );
	// 	n.insert( 15 );
	// 	n.insert( 30 );
	// 	n.log();
	// 	n.del( 15 );
	// 	n.log();
	// }

	// cases 3 --> if ( elt != 20 ) _color = BLACK; ==> OK
	// {
	// 	rbt< int > n;
	// 	n.insert( 10 );
	// 	n.insert( 5 );
	// 	n.insert( 20 );
	// 	n.insert( 1 );
	// 	n.insert( 7 );
	// 	n.insert( 15 );
	// 	n.insert( 30 );
	// 	n.insert( 25 );
	// 	n.insert( 35 );
	// 	n.log();
	// 	n.del( 15 );
	// 	n.log();
	// }

	// cases 3 & 2 --> _color = BLACK; ==> OK
	// {
	// 	rbt< int > n;
	// 	n.insert( 10 );
	// 	n.insert( 5 );
	// 	n.insert( 20 );
	// 	n.insert( 1 );
	// 	n.insert( 7 );
	// 	n.insert( 15 );
	// 	n.insert( 30 );
	// 	n.log();
	// 	n.del( 15 );
	// 	n.log();
	// }

	// case 4 --> if ( elt != 30 ) _color = BLACK; ==> OK
	// {
	// 	rbt< int > n;
	// 	n.insert( 10 );
	// 	n.insert( 5 );
	// 	n.insert( 20 );
	// 	n.insert( 1 );
	// 	n.insert( 7 );
	// 	n.insert( 15 );
	// 	n.insert( 30 );
	// 	n.insert( 25 );
	// 	n.insert( 40 );
	// 	n.log();
	// 	n.del( 15 );
	// 	n.log();
	// }

	// cases 5 & 6 --> if ( elt != 25 ) _color = BLACK; ==> OK
	// {
	// 	rbt< int > n;
	// 	n.insert( 10 );
	// 	n.insert( 5 );
	// 	n.insert( 30 );
	// 	n.insert( 1 );
	// 	n.insert( 7 );
	// 	n.insert( 25 );
	// 	n.insert( 40 );
	// 	n.insert( 20 );
	// 	n.insert( 28 );
	// 	n.del( 1 );
	// }

	// std::system( "leaks a.out" );

	return 0;
}
