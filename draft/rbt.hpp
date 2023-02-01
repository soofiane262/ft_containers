/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:55:21 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/01 19:38:14 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <iostream>

#define BLACK_NODE true
#define RED_NODE   false

template < class T > struct node {
	T		   _elt;
	bool	   _color;
	node< T > *_parent, *_left, *_right;
	node( const T &elt, node< T > *parent ) {
		_elt	= elt;
		_color	= RED_NODE;
		_left	= NULL;
		_right	= NULL;
		_parent = parent;
	};
	void recolour( void ) { _color = !_color; };
};

template < class T > class rbt {
  private:
	node< T > *getGrandfather( node< T > *nd ) {
		return nd->_parent ? nd->_parent->_parent : NULL;
	};
	node< T > *getUncle( node< T > *nd ) {
		node< T > *grandFather = getGrandfather( nd );
		if ( nd->_parent == grandFather->_left ) return grandFather->_right;
		return grandFather->_left;
	};
	void leftRotation( node< T > *&nd ) {
		struct node< T > *r = nd->_right, *rl = r->_left;
		r->_left   = nd;
		nd->_right = rl;
		nd		   = r;
	};
	void rightRotation( node< T > *&nd ) {
		struct node< T > *l = nd->_left, *lr = l->_right;
		l->_right = nd;
		nd->_left = lr;
		nd		  = l;
	};
	bool find( node< T > &nd, const T &elt ) {
		if ( elt == nd._elt ) return true;
		else if ( elt < nd._elt ) {
			if ( !nd.left ) return false;
			else
				return find( *( nd.left ), elt );
		} else {
			if ( !nd.right ) return false;
			else
				return find( *( nd.right ), elt );
		}
	};
	void _insert( node< T > *&nd, const T &elt, node< T > *parent ) {
		if ( !nd ) nd = new node< T >( elt, parent );
		else if ( elt < nd->_elt )
			_insert( nd->_left, elt, nd );
		else if ( elt > nd->_elt )
			_insert( nd->_right, elt, nd );
		else
			return;
		node< T > *grandfather = getGrandfather( nd );
		if ( !nd->_parent ) nd->_color = BLACK_NODE;
		if ( !grandfather ) return;
		std::cout << "i am " << nd->_elt << "\nmy parent is " << ( parent ? parent->_elt : NULL )
				  << "\n";
		node< T > *uncle = getUncle( nd );
		std::cout << "my grandfather is " << ( grandfather ? grandfather->_elt : NULL )
				  << "\nand my uncle is " << ( uncle ? uncle->_elt : NULL ) << '\n';
		if ( nd->_parent->_color == RED_NODE && uncle ) {
			if ( uncle->_color == RED_NODE ) {
				nd->_parent->_color = BLACK_NODE;
				uncle->_color		= BLACK_NODE;
				grandfather->_color = RED_NODE;
			} else {
				// if ( grandfather && nd == grandfather->_left->_left ) {
				// 	rightRotation( grandfather );
				// 	bool tmpColor				= nd->_parent->_color;
				// 	nd->_parent->_color			= nd->_parent->_right->_color;
				// 	nd->_parent->_right->_color = tmpColor;
				// }
			}
		}
	};
	void destruct( node< T > *&nd ) {
		if ( nd->_left ) destruct( nd->_left );
		if ( nd->_right ) destruct( nd->_right );
		delete nd;
		nd = NULL;
	};
	void _log( node< T > *x, const int lvl ) {
		if ( !x ) return;
		_log( x->_right, lvl + 1 );
		for ( int i = 0; i < lvl * 4; i++ ) std::cout << ' ';
		std::cout << ( x->_color == BLACK_NODE ? "\e[1;37m" : "\e[1;31m" ) << x->_elt << "\e[0m\n";
		_log( x->_left, lvl + 1 );
	};

  public:
	node< T > *root;
	rbt( void ) { root = NULL; };
	rbt( const T &n ) { root = new node< T >( n ); };
	~rbt( void ) { destruct( root ); };
	void insert( const T &elt ) {
		_insert( root, elt, NULL );
		// temporary
		log();
		//
	};
	// bool find( const T &elt ) {
	// 	if ( !root ) return false;
	// 	else
	// 		return find( *root, elt );
	// };
	// void del( const T &elt ) { _del( root, elt ); };
	void log( void ) {
		_log( root, 0 );
		std::cout << "\n";
	};
};
