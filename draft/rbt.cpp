/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:57:44 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/13 17:30:30 by sel-mars         ###   ########.fr       */
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
	// 	int sz	  = 15;
	// 	int in[]  = { 15, 62, 12, 93, 81, 33, 49, 39, 54, 68, 97, 54, 49, 86, 26 };
	// 	int out[] = { 49, 49, 86, 33, 26, 97, 81 };
	// 	std::cout << "insert ";
	// 	for ( int i = 0; i < sz; i++ ) std::cout << in[ i ] << ' ';
	// 	std::cout << "\ndelete ";
	// 	for ( int i = 0; i < sz / 2; i++ ) std::cout << out[ i ] << ' ';
	// 	std::cout << '\n';
	// 	rbt< int > n;
	// 	for ( int i = 0; i < sz; i++ ) n.insert( in[ i ] );
	// 	n.log();
	// 	for ( int i = 0; i < sz / 2; i++ ) {
	// 		std::cout << "before del " << out[ i ] << "\n";
	// 		n.log();
	// 		n.del( out[ i ] );
	// 		std::cout << "after del " << out[ i ] << "\n";
	// 		n.log();
	// 	}
	// }
	// std::system( "leaks a.out" );

	// random
	{
		while ( 1 ) {
			{
				int				   sz = 1000000;
				std::vector< int > vec[ 2 ];
				for ( int i = 0; i < sz; i++ ) vec[ 0 ].push_back( rand() % 100 );
				for ( int i = 0; i < sz / 2; i++ )
					vec[ 1 ].push_back( vec[ 0 ][ rand() % vec[ 0 ].size() ] );
				std::cout << "insert ";
				for ( int i = 0; i < sz; i++ ) std::cout << vec[ 0 ][ i ] << ' ';
				std::cout << "\ndelete ";
				for ( int i = 0; i < sz / 2; i++ ) std::cout << vec[ 1 ][ i ] << ' ';
				std::cout << '\n';
				rbt< int > n;
				for ( int i = 0; i < sz; i++ ) n.insert( vec[ 0 ][ i ] );
				// n.log();
				for ( int i = 0; i < sz / 2; i++ ) {
					std::cout << "deleting " << vec[ 1 ][ i ] << "\n";
					n.del( vec[ 1 ][ i ] );
				}
				// n.log();
			}
		}
	}

	// simple test
	// {
	// 	rbt< int > n;
	// 	for ( int i = 10; i < 20; i++ ) n.insert( i );
	// 	for ( int i = 1; i < 10; i++ ) n.insert( i );
	// 	// n.insert( 12011 );
	// 	// n.insert( 130000 );
	// 	// n.insert( 1100 );
	// 	// n.insert( 1200000 );
	// 	// n.insert( 1300000 );
	// 	// n.insert( 110 );
	// 	// n.insert( 120 );
	// 	// for ( int i = 10; i >= 0; i-- ) n.insert( i );
	// 	n.log();
	// 	// std::cout << "find 0\t: " << n.find( 0 ) << '\n';
	// 	// std::cout << "find 1\t: " << n.find( 1 ) << '\n';
	// 	// std::cout << "find 9\t: " << n.find( 9 ) << '\n';
	// 	// std::cout << "find 10\t: " << n.find( 10 ) << '\n';
	// 	// n.del( 8 );
	// 	// n.log();
	// 	// n.del( 6 );
	// 	// n.log();
	// 	// n.del( 4 );
	// 	// n.log();
	// }

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
