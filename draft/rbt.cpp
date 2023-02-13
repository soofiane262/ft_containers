/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:57:44 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/13 18:50:35 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// for checker
#include <algorithm>
#include <climits>
#include <random>
#include <set>
// end

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
	std::random_device rd;
	std::mt19937	   mt( rd() );

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
		for ( int test = 0, total_tests = 5, sz = 100000; test < 5; test++ ) {
			std::system( "clear" );
			std::vector< int > in;
			for ( int i = 0, range = INT_MAX / sz; i < sz; i++ )
				in.push_back( rand() % range + range * i );
			std::vector< int > out( in );
			std::shuffle( in.begin(), in.end(), mt );
			std::shuffle( out.begin(), out.end(), mt );
			// std::cout << "insert ";
			// for ( int i = 0; i < sz; i++ ) std::cout << in.at( i ) << ' ';
			// std::cout << '\n';
			// std::cout << "delete ";
			// for ( int i = 0; i < sz; i++ ) std::cout << out.at( i ) << ' ';
			// std::cout << '\n';
			// exit( 0 );
			rbt< int > n;
			std::cout << "\e[1;34m"
					  << "───────────────>    STARTING INSERTION    <───────────────"
					  << "\e[0m\n";
			sleep( 2 );
			for ( int i = 0; i < sz; i++ ) n.insert( in.at( i ), /* tmp */ i );
			std::cout << "\e[1;32m"
					  << "───────────────>    INSERTION SUCCESS    <───────────────"
					  << "\e[0m\n";
			sleep( 2 );
			// n.log();
			std::cout << "\e[1;34m"
					  << "───────────────>    STARTING DELETION    <───────────────"
					  << "\e[0m\n";
			sleep( 2 );
			for ( int i = 0; i < sz; i++ ) n.del( out.at( i ), /* tmp */ i );
			std::cout << "\e[1;32m"
					  << "───────────────>    DELETION SUCCESS    <───────────────"
					  << "\e[0m\n";
			sleep( 2 );
			// n.log();
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
