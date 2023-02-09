/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:57:44 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/09 19:27:31 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbt.hpp"

#include <cstdlib>
#include <ctime>
#include <ios>
#include <vector>

int main( void ) {
	std::system( "clear" );
	std::cout << std::boolalpha;
	srand( time( NULL ) );

	// random
	{
		int				   sz = 20;
		std::vector< int > vec;
		for ( int i = 0; i < sz; i++ ) vec.push_back( rand() % 100 );
		rbt< int > n;
		for ( int i = 0; i < sz; i++ ) {
			std::cout << "insert " << vec[ i ] << '\n';
			// while ( std::getchar() != '\n' ) continue;
			n.insert( vec[ i ] );
			n.log();
			// while ( std::getchar() != '\n' ) continue;
		}
		for ( int i = 0, j; i < sz / 2; i++ ) {
			j = rand() % vec.size();
			std::cout << "delete " << vec[ j ] << '\n';
			// while ( std::getchar() != '\n' ) continue;
			n.del( vec[ j ] );
			n.log();
			// while ( std::getchar() != '\n' ) continue;
		}
		n.log();
	}

	// simple test
	// {
	// 	rbt< int > n;
	// 	for ( int i = 1; i < 10; i++ ) n.insert( i );
	// 	n.log();
	// 	std::cout << "find 0\t: " << n.find( 0 ) << '\n';
	// 	std::cout << "find 1\t: " << n.find( 1 ) << '\n';
	// 	std::cout << "find 9\t: " << n.find( 9 ) << '\n';
	// 	std::cout << "find 10\t: " << n.find( 10 ) << '\n';
	// 	n.del( 5 );
	// 	n.log();
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
	// 	n.del( 15 );
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
	// 	n.del( 15 );
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
	// 	n.del( 15 );
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
