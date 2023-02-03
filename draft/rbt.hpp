/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:55:21 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/03 22:21:51 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <iostream>

#define BLACK_NODE true
#define RED_NODE   false
#define LEFT_ROT   1
#define RIGHT_ROT  2

template < class T > struct node {
	T		   _elt;
	bool	   _color;
	int		   _change;
	node< T > *_parent, *_left, *_right;
	node( const T &elt, node< T > *parent ) {
		_elt	= elt;
		_color	= RED_NODE;
		_change = 0;
		_left	= NULL;
		_right	= NULL;
		_parent = parent;
	};
	void recolour( void ) { _color = !_color; };
};

template < class T > class rbt {
  private:
	node< T > *getSibling( node< T > *nd ) {
		if ( !nd->_parent ) return NULL;
		else if ( nd == nd->_parent->_left )
			return nd->_parent->_right;
		return nd->_parent->_left;
	};
	void swapColors( node< T > *&x, node< T > *&y ) {
		bool tmpColor = x->_color;
		x->_color	  = y->_color;
		y->_color	  = tmpColor;
	};
	void leftRotation( node< T > *&nd ) {
		node< T > *init = nd;
		node< T > *r = nd->_right, *rl = r->_left;
		r->_left	  = nd;
		nd->_right	  = rl;
		nd			  = r;
		nd->_parent	  = init->_parent;
		init->_parent = nd;
		if ( rl ) rl->_parent = init;
	};
	void rightRotation( node< T > *&nd ) {
		node< T > *init = nd;
		node< T > *l = nd->_left, *lr = l->_right;
		l->_right	  = nd;
		nd->_left	  = lr;
		nd			  = l;
		nd->_parent	  = init->_parent;
		init->_parent = nd;
		if ( lr ) lr->_parent = init;
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
		if ( !nd ) {
			nd = new node< T >( elt, parent );
			return;
		} else if ( elt < nd->_elt )
			_insert( nd->_left, elt, nd );
		else if ( elt > nd->_elt )
			_insert( nd->_right, elt, nd );
		else
			return;
		switch ( nd->_change ) {
			case RIGHT_ROT:
				nd->_change = 0;
				rightRotation( nd );
				swapColors( nd, nd->_right );
				return;
			case LEFT_ROT:
				nd->_change = 0;
				leftRotation( nd );
				swapColors( nd, nd->_left );
				return;
		}
		node< T > *sibling = getSibling( nd );
		if ( !nd->_parent || nd->_color == BLACK_NODE ||
			 ( ( !nd->_left || nd->_left->_color == BLACK_NODE ) &&
			   ( !nd->_right || nd->_right->_color == BLACK_NODE ) ) )
			return;
		else if ( !sibling || sibling->_color == BLACK_NODE ) {
			if ( nd == nd->_parent->_left && elt < nd->_elt ) nd->_parent->_change = RIGHT_ROT;
			else if ( nd == nd->_parent->_right && elt > nd->_elt )
				nd->_parent->_change = LEFT_ROT;
			else if ( nd == nd->_parent->_left && elt > nd->_elt ) {
				leftRotation( nd );
				nd->_parent->_change = RIGHT_ROT;
			} else {
				rightRotation( nd );
				nd->_parent->_change = LEFT_ROT;
			}
		} else {
			nd->_color			= BLACK_NODE;
			sibling->_color		= BLACK_NODE;
			nd->_parent->_color = RED_NODE;
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
	node< T > *root;

  public:
	rbt( void ) { root = NULL; };
	rbt( const T &n ) { root = new node< T >( n ); };
	~rbt( void ) { destruct( root ); };
	void insert( const T &elt ) {
		_insert( root, elt, NULL );
		root->_color = BLACK_NODE;
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
