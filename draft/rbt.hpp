/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:55:21 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/09 19:29:24 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>

// tmp
#include <unistd.h>
//

#define RED			 0
#define BLACK		 1
#define DOUBLE_BLACK 2
#define LEFT		 1
#define RIGHT		 2

template < class T > struct node {
	T		   _elt;
	int		   _color;
	int		   _rotate;
	int		   _nil;
	node< T > *_parent, *_left, *_right;
	node( const T &elt, node< T > *parent ) {
		_elt	= elt;
		_color	= RED;
		_rotate = 0;
		_nil	= 0;
		_left	= NULL;
		_right	= NULL;
		_parent = parent;
	};
};

template < class T > class rbt {
  private:
	typedef node< T > node;
	node			 *getSibling( node *nd ) {
		if ( !nd->_parent ) return NULL;
		else if ( nd == nd->_parent->_left )
			return nd->_parent->_right;
		return nd->_parent->_left;
	};
	node *getDBSibling( node *nd ) {
		if ( nd->_color == DOUBLE_BLACK ) return getSibling( nd );
		else if ( nd->_nil == LEFT )
			return nd->_right;
		return nd->_left;
	};
	void swapColors( node *&x, node *&y ) {
		bool tmpColor = x->_color;
		x->_color	  = y->_color;
		y->_color	  = tmpColor;
	};
	void leftRotation( node *&nd ) {
		node *init = nd;
		node *r = nd->_right, *rl = r->_left;
		r->_left	  = nd;
		nd->_right	  = rl;
		nd			  = r;
		nd->_parent	  = init->_parent;
		init->_parent = nd;
		if ( rl ) rl->_parent = init;
	};
	void rightRotation( node *&nd ) {
		node *init = nd;
		node *l = nd->_left, *lr = l->_right;
		l->_right	  = nd;
		nd->_left	  = lr;
		nd			  = l;
		nd->_parent	  = init->_parent;
		init->_parent = nd;
		if ( lr ) lr->_parent = init;
	};
	void rotate( node *&nd, const bool colorSwap ) {
		switch ( nd->_rotate ) {
			case RIGHT:
				nd->_rotate = 0;
				rightRotation( nd );
				if ( colorSwap ) swapColors( nd, nd->_right );
				return;
			case LEFT:
				nd->_rotate = 0;
				leftRotation( nd );
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
		node *sibling = getSibling( nd );
		if ( !nd->_parent || nd->_color == BLACK ||
			 ( ( !nd->_left || nd->_left->_color == BLACK ) &&
			   ( !nd->_right || nd->_right->_color == BLACK ) ) )
			return;
		else if ( !sibling || sibling->_color == BLACK ) {
			if ( nd == nd->_parent->_left && elt < nd->_elt ) nd->_parent->_rotate = RIGHT;
			else if ( nd == nd->_parent->_right && elt > nd->_elt )
				nd->_parent->_rotate = LEFT;
			else if ( nd == nd->_parent->_left && elt > nd->_elt ) {
				leftRotation( nd );
				nd->_parent->_rotate = RIGHT;
			} else {
				rightRotation( nd );
				nd->_parent->_rotate = LEFT;
			}
		} else {
			nd->_color			= BLACK;
			sibling->_color		= BLACK;
			nd->_parent->_color = RED;
		}
	};
	void fixDBRotate( node *&nd ) {
		if ( !nd->_rotate ) return;
		node *parent = nd->_parent;
		int	  dir	 = 0;
		if ( !parent )
			;
		else if ( nd == parent->_left )
			dir = -1;
		else
			dir = 1;
		rotate( nd, false );
		if ( dir == -1 ) parent->_left = nd;
		else if ( dir == 1 )
			parent->_right = nd;
		else
			root = nd;
	};
	void fixDB( node *&nd ) {
		fixDBRotate( nd );
		if ( nd->_color != DOUBLE_BLACK && !nd->_nil ) return;
		else if ( !nd->_parent )
			nd->_color = BLACK;
		else {
			node *DBsibling = getDBSibling( nd );
			int	  DBdir		= ( nd->_nil ? nd->_nil : ( nd == nd->_parent->_left ? LEFT : RIGHT ) );
			if ( DBsibling->_color == BLACK ) {
				if ( ( !DBsibling->_left && !DBsibling->_right ) ||
					 ( DBsibling->_left && DBsibling->_left->_color == BLACK && DBsibling->_right &&
					   DBsibling->_right->_color == BLACK ) ) {
					DBsibling->_color--;
					if ( nd->_nil ) {
						nd->_color++;
						nd->_nil = 0;
						fixDB( nd );
					} else {
						nd->_color--;
						nd->_parent->_color++;
						fixDB( nd->_parent );
					}
				} else if ( ( DBdir == LEFT && DBsibling->_right &&
							  DBsibling->_right->_color == RED ) ||
							( DBdir == RIGHT && DBsibling->_left &&
							  DBsibling->_left->_color == RED ) ) {
					node *farRed = ( DBdir == LEFT ? DBsibling->_right : DBsibling->_left );
					if ( nd->_nil ) {
						int tmpColor	  = nd->_color;
						nd->_color		  = DBsibling->_color;
						DBsibling->_color = tmpColor;
						nd->_rotate		  = DBdir;
						nd->_nil		  = 0;
						farRed->_color++;
						fixDBRotate( nd );
					} else {
						std::cout << "here\n";
						int tmpColor		 = nd->_parent->_color;
						nd->_parent->_color	 = DBsibling->_color;
						DBsibling->_color	 = tmpColor;
						nd->_parent->_rotate = DBdir;
						nd->_color--;
						farRed->_color++;
						fixDB( nd->_parent );
					}
				} else {
					int tmpColor	  = DBsibling->_color;
					DBsibling->_color = ( DBsibling->_left && DBsibling->_left->_color == RED ?
											  DBsibling->_left->_color :
											  DBsibling->_right->_color );
					( DBsibling->_left && DBsibling->_left->_color == RED ?
						  DBsibling->_left->_color :
						  DBsibling->_right->_color ) = tmpColor;
					DBsibling->_rotate				  = ( DBdir == LEFT ? RIGHT : LEFT );
					fixDBRotate( DBsibling );
					fixDB( nd );
				}
			} else {
				if ( nd->_nil ) {
					int tmpColor	  = nd->_color;
					nd->_color		  = DBsibling->_color;
					DBsibling->_color = tmpColor;
					nd->_rotate		  = DBdir;
					fixDBRotate( nd );
				} else {
					int tmpColor		 = nd->_parent->_color;
					nd->_parent->_color	 = DBsibling->_color;
					DBsibling->_color	 = tmpColor;
					nd->_parent->_rotate = DBdir;
					fixDB( nd->_parent );
				}
			}
		}
	};
	void _del( node **nd, const T &elt ) {
		if ( !*nd ) return;
		else if ( elt < ( *nd )->_elt )
			_del( &( *nd )->_left, elt );
		else if ( elt > ( *nd )->_elt )
			_del( &( *nd )->_right, elt );
		else {
			if ( !( *nd )->_left && !( *nd )->_right ) {
				node *parent = ( *nd )->_parent;
				if ( parent && ( *nd )->_color == BLACK )
					parent->_nil = ( ( *nd ) == parent->_left ? LEFT : RIGHT );
				delete *nd;
				*nd = NULL;
				fixDB( parent );
			} else if ( !( *nd )->_left || !( *nd )->_right ) {
				node *tmp	 = *nd;
				node *sub	 = ( *nd )->_left ? ( *nd )->_left : ( *nd )->_right;
				sub->_color	 = ( *nd )->_color;
				sub->_parent = ( *nd )->_parent;
				( *nd )		 = sub;
				delete tmp;
			} else {
				node *sub = ( *nd )->_right;
				while ( sub->_left ) sub = sub->_left;
				( *nd )->_elt = sub->_elt;
				_del( &( *nd )->_right, sub->_elt );
			}
		}
		if ( *nd ) fixDB( *nd );
	};
	void destruct( node *&nd ) {
		if ( nd->_left ) destruct( nd->_left );
		if ( nd->_right ) destruct( nd->_right );
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
	node *root;

  public:
	rbt( void ) { root = NULL; };
	rbt( const T &n ) { root = new node( n ); };
	~rbt( void ) {
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
	void del( const T &elt ) { _del( &root, elt ); };
	//
	//
	// tmp
	void log( void ) {
		if ( !root ) return;
		_log( root, 0 );
		std::cout << "----------------------\n";
	};
};
