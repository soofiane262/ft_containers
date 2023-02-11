/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:55:21 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/11 18:52:22 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

#define RED			 0
#define BLACK		 1
#define DOUBLE_BLACK 2
#define LEFT		 -1
#define RIGHT		 1

template < class T > struct node {
	T		   _elt;
	int		   _color;
	int		   _rotate;
	node< T > *_parent, *_left, *_right;
	node( const T &elt, node< T > *parent ) {
		_elt	= elt;
		_color	= RED;
		_rotate = 0;
		_left	= NULL;
		_right	= NULL;
		_parent = parent;
	};
	node *getSibling( void ) {
		if ( !_parent ) return NULL;
		else if ( _elt < _parent->_elt )
			return _parent->_right;
		return _parent->_left;
	};
	bool hasRedChild( void ) {
		if ( ( _left && _left->_color == RED ) || ( _right && _right->_color == RED ) ) return true;
		return false;
	};
	bool hasRedNiece( void ) {
		node *sibling = getSibling();
		if ( sibling && sibling->hasRedChild() &&
			 ( ( _elt < _parent->_elt && sibling->_left && sibling->_left->_color == RED ) ||
			   ( _elt > _parent->_elt && sibling->_right && sibling->_right->_color == RED ) ) )
			return true;
		return false;
	};
	bool hasRedNephew( void ) {
		node *sibling = getSibling();
		if ( sibling && sibling->hasRedChild() &&
			 ( ( _elt < _parent->_elt && sibling->_right && sibling->_right->_color == RED ) ||
			   ( _elt > _parent->_elt && sibling->_left && sibling->_left->_color == RED ) ) )
			return true;
		return false;
	};
	node *RedNiece( void ) {
		if ( !hasRedNiece() ) return NULL;
		node *sibling = getSibling();
		if ( _elt < _parent->_elt ) return sibling->_left;
		return sibling->_right;
	};
	node *RedNephew( void ) {
		if ( !hasRedNiece() ) return NULL;
		node *sibling = getSibling();
		if ( _elt < _parent->_elt ) return sibling->_right;
		return sibling->_left;
	};
};

template < class T > class rbt {
  private:
	typedef node< T > node;
	void			  swapColors( node *&x, node *&y ) {
		 bool tmpColor = x->_color;
		 x->_color	   = y->_color;
		 y->_color	   = tmpColor;
	};
	node *leftRotation( node *nd ) {
		node *r = nd->_right, *rl = r->_left;
		nd->_right = rl;
		if ( rl ) rl->_parent = nd;
		r->_left   = nd;
		r->_parent = nd->_parent;
		if ( nd->_parent && nd->_elt > nd->_parent->_elt ) nd->_parent->_right = r;
		else if ( nd->_parent && nd->_elt < nd->_parent->_elt )
			nd->_parent->_left = r;
		nd->_parent = r;
		return r;
	};
	node *rightRotation( node *nd ) {
		node *l = nd->_left, *lr = l->_right;
		nd->_left = lr;
		if ( lr ) lr->_parent = nd;
		l->_right  = nd;
		l->_parent = nd->_parent;
		if ( nd->_parent && nd->_elt > nd->_parent->_elt ) nd->_parent->_right = l;
		else if ( nd->_parent && nd->_elt < nd->_parent->_elt )
			nd->_parent->_left = l;
		nd->_parent = l;
		return l;
	};
	void rotate( node *&nd, const bool colorSwap ) {
		switch ( nd->_rotate ) {
			case RIGHT:
				nd->_rotate = 0;
				nd			= rightRotation( nd );
				if ( colorSwap ) swapColors( nd, nd->_right );
				return;
			case LEFT:
				nd->_rotate = 0;
				nd			= leftRotation( nd );
				if ( colorSwap ) swapColors( nd, nd->_left );
				return;
		}
	};
	bool find( node &nd, const T &elt ) {
		if ( elt == nd._elt ) return true;
		else if ( elt < nd._elt ) {
			if ( !nd._left ) return false;
			else
				return find( *( nd._left ), elt );
		} else {
			if ( !nd._right ) return false;
			else
				return find( *( nd._right ), elt );
		}
	};
	void _insert( node *&nd, const T &elt, node *parent ) {
		if ( !nd ) {
			nd = new node( elt, parent );
			return;
		} else if ( elt < nd->_elt )
			_insert( nd->_left, elt, nd );
		else if ( elt > nd->_elt )
			_insert( nd->_right, elt, nd );
		else
			return;
		rotate( nd, true );
		node *sibling = nd->getSibling();
		if ( !nd->_parent || nd->_color == BLACK ||
			 ( ( !nd->_left || nd->_left->_color == BLACK ) &&
			   ( !nd->_right || nd->_right->_color == BLACK ) ) )
			return;
		else if ( !sibling || sibling->_color == BLACK ) {
			if ( nd == nd->_parent->_left && elt < nd->_elt ) nd->_parent->_rotate = RIGHT;
			else if ( nd == nd->_parent->_right && elt > nd->_elt )
				nd->_parent->_rotate = LEFT;
			else if ( nd == nd->_parent->_left && elt > nd->_elt ) {
				nd->_rotate = LEFT;
				rotate( nd, false );
				nd->_parent->_rotate = RIGHT;
			} else {
				nd->_rotate = RIGHT;
				rotate( nd, false );
				nd->_parent->_rotate = LEFT;
			}
		} else {
			nd->_color			= BLACK;
			sibling->_color		= BLACK;
			nd->_parent->_color = RED;
		}
	};
	void fixDoubleBlack( node *&nd ) {
		if ( nd->_color != DOUBLE_BLACK ) return;
		else if ( !nd->_parent )
			nd->_color = BLACK;
		else {
			node *sibling = nd->getSibling();
			int	  dir	  = ( nd->_elt < nd->_parent->_elt ? LEFT : RIGHT );
			if ( !sibling || ( sibling->_color == BLACK && !sibling->hasRedChild() ) ) {
				std::cout << "\e[1;34m--> "
						  << "black sibling with no/black children"
						  << " \e[0m\n";
				if ( sibling ) sibling->_color = RED;
				nd->_color = BLACK;
				nd->_parent->_color++;
				fixDoubleBlack( nd->_parent );
			} else if ( sibling->_color == BLACK && nd->hasRedNiece() ) {
				std::cout << "\e[1;34m--> "
						  << "black sibling with red niece"
						  << " \e[0m\n";
			} else if ( sibling->_color == BLACK && nd->hasRedNephew() ) {
				std::cout << "\e[1;34m--> "
						  << "black sibling with red nephew"
						  << " \e[0m\n";
			} else {
				std::cout << "\e[1;34m--> "
						  << "red sibling"
						  << " \e[0m\n";
			}
		}
	};
	void _del( node *&nd, const T &elt ) {
		if ( !nd ) return;
		else if ( elt < nd->_elt )
			_del( nd->_left, elt );
		else if ( elt > nd->_elt )
			_del( nd->_right, elt );
		else {
			if ( !nd->_left && !nd->_right ) {
				if ( nd->_color == BLACK ) nd->_color = DOUBLE_BLACK;
				fixDoubleBlack( nd );
				delete nd;
				nd = NULL;
			} else if ( !nd->_left || !nd->_right ) {
				node *tmp	 = nd;
				node *sub	 = nd->_left ? nd->_left : nd->_right;
				sub->_color	 = nd->_color;
				sub->_parent = nd->_parent;
				nd			 = sub;
				delete tmp;
				tmp = NULL;
			} else {
				node *sub = nd->_right;
				while ( sub->_left ) sub = sub->_left;
				nd->_elt = sub->_elt;
				_del( nd->_right, sub->_elt );
			}
		}
		// if nd fixDBnd;
	};
	void destruct( node *&nd ) {
		if ( nd->_left ) destruct( nd->_left );
		if ( nd->_right ) destruct( nd->_right );
		// std::cout << nd->_elt << "\thas adr " << nd << ", its left "
		// 		  << ( nd->_left ? nd->_left->_elt : 0 ) << "\thas adr " << nd->_left << ", right "
		// 		  << ( nd->_right ? nd->_right->_elt : 0 ) << "\thas adr " << nd->_right
		// 		  << ", parent " << ( nd->_parent ? nd->_parent->_elt : 0 ) << "\thas adr "
		// 		  << nd->_parent << '\n';
		delete nd;
		nd = NULL;
	};
	void _log( node *x, const int lvl ) {
		if ( !x ) return;
		_log( x->_right, lvl + 1 );
		for ( int i = 0; i < lvl * 4; i++ ) std::cout << ' ';
		std::cout << ( x->_color == RED ? "\e[1;31m" : "\e[1;37m" )
				  << ( x->_color == DOUBLE_BLACK ? "\e[4m" : "" ) << x->_elt << "\e[0m\n";
		_log( x->_left, lvl + 1 );
	};
	void _logAdr( node *x ) {
		if ( !x ) return;
		_logAdr( x->_right );
		// std::cout << x->_elt << "\thas adr " << x << '\n';
		std::cout << x->_elt << "\t( " << x << " ), parent "
				  << ( x->_parent ? x->_parent->_elt : 0 ) << "\t( " << x->_parent << " )\n";
		_logAdr( x->_left );
	};
	node *root;

  public:
	rbt( void ) { root = NULL; };
	rbt( const T &n ) { root = new node( n ); };
	~rbt( void ) {
		// log();
		// logAdr();
		if ( root ) destruct( root );
	};
	void insert( const T &elt ) {
		_insert( root, elt, NULL );
		root->_color = BLACK;
	};
	bool find( const T &elt ) {
		if ( !root ) return false;
		else
			return find( *root, elt );
	};
	void del( const T &elt ) { _del( root, elt ); };
	//
	//
	// tmp
	void log( void ) {
		if ( !root ) return;
		std::cout << "----------------------\n";
		_log( root, 0 );
		std::cout << "----------------------\n";
	};
	void logAdr( void ) {
		if ( !root ) return;
		std::cout << "----------------------\n";
		_logAdr( root );
		std::cout << "----------------------\n";
	};
};
