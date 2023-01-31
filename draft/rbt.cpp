/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:57:44 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/31 18:53:48 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbt.hpp"

#include <cstdlib>
#include <vector>

#define ESC	  "\e["
#define RESET ESC "0m"
#define RED	  ESC "1;31m"
#define WHITE ESC "1;37m"

template < class T > struct output {
	node< T > *_nd;
	int		   _lvl;
	static int lvls;
	output( node< T > *nd, const int lvl ) {
		_nd	 = nd;
		_lvl = lvl;
		if ( _nd->_lvl > lvls ) lvls = _nd->_lvl;
	};
};

template < class T > int output< T >::lvls = 0;

template < class T > void _log( std::vector< output< T > > &vec, node< T > *x, const int lvl ) {
	if ( !x ) return;
	_log( vec, x->left, lvl + 1 );
	vec.push_back( output< T >( x, lvl ) );
	_log( vec, x->right, lvl + 1 );
};

template < class T > void rbt< T >::log( void ) {
	if ( !root ) return;
	std::vector< output< T > > vec;
	_log( vec, root, 0 );
	for ( int lvl = 0, i = -1, lsl = -1; lvl <= output< T >::lvls; lvl++, i = -1, lsl = -1 ) {
		while ( ++i < vec.size() ) {
			if ( vec[ i ]._lvl != lvl ) continue;
			for ( int j = 0; j < i - lsl - 1; j++ ) std::cout << " ";
			std::cout << ( vec[ i ]._nd->_color == RED_NODE ? RED : WHITE ) << vec[ i ]._nd->_elt
					  << RESET;
			lsl = i;
		}
		std::cout << '\n';
	}
	std::cout << "\n";
};

int main( void ) {
	{
		rbt< int > n;
		n.insert( 1 );
		n.log();
		n.insert( 2 );
		n.log();
		n.insert( 3 );
		n.insert( 4 );
		n.insert( 5 );
		n.insert( 6 );
		n.del( 6 );
		n.log();
		n.del( 4 );
		n.log();
		n.del( 2 );
		n.log();
	}
	// std::system( "leaks a.out" );

	return 0;
}
