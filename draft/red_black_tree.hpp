/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:54:13 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/18 16:03:23 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../utils/utils.hpp"

enum e_colors { RED = 0, BLACK, DOUBLE_BLACK };
enum e_directions { LEFT = -1, DEFAULT, RIGHT };

template < class T, class Compare = std::less< T >, class Allocator = std::allocator< T > >
class red_black_tree {
  private:
	typedef T		  value_type;
	typedef Allocator allocator_type;
	typedef Compare	  compare_type;
	struct node {
		/* member attributes ──────────────────────────────────────────────────────────────── */
		allocator_type _alloc;
		value_type	  *_elt;
		e_colors	   _color;
		e_directions   _rotate;
		node		  *_parent, *_left, *_right;
		/* ctor - dtor ────────────────────────────────────────────────────────────────────── */
		node( const value_type &elt, const allocator_type &alloc, node *parent ) {
			_alloc = alloc;
			_elt   = _alloc.allocate( 1 );
			_alloc.construct( _elt, elt );
			_color	= RED;
			_rotate = DEFAULT;
			_parent = parent;
			_left = _right = NULL;
		} // ctor
		~node( void ) {
			_alloc.destroy( _elt );
			_alloc.deallocate( _elt, 1 );
			_elt	= NULL;
			_parent = _left = _right = NULL;
		} // dtor
		/* helper functions ───────────────────────────────────────────────────────────────── */
		node *getSibling( void ) {
			if ( !_parent ) return NULL;
			else if ( this == _parent->_left )
				return _parent->_right;
			return _parent->_left;
		} // get_sibling
		bool hasRedChild( void ) {
			if ( ( _left && _left->_color == RED ) || ( _right && _right->_color == RED ) )
				return true;
			return false;
		} // has_red_child
		bool hasRedNiece( void ) {
			node *sibling = getSibling();
			if ( sibling && sibling->hasRedChild() &&
				 ( ( sibling == _parent->_left && sibling->_right &&
					 sibling->_right->_color == RED ) ||
				   ( sibling == _parent->_right && sibling->_left &&
					 sibling->_left->_color == RED ) ) )
				return true;
			return false;
		} // has_red_niece
		void swapContent( node *&y ) {
			value_type *tmp_elt = _elt;
			_elt				= y->_elt;
			y->_elt				= tmp_elt;
		} // swap_content
		void swapColors( node *&y ) {
			e_colors tmpColor = _color;
			_color			  = y->_color;
			y->_color		  = tmpColor;
		} // swap_colors
	};	  // struct
	/* ─────────────────────────────────────────────────────────────────────────────────── */
	/* rotations ───────────────────────────────────────────────────────────────────────── */
	node *leftRotation( node *nd ) {
		node *r = nd->_right, *rl = r->_left;
		nd->_rotate = DEFAULT;
		if ( nd == _root ) _root = r;
		nd->_right = rl;
		if ( rl ) rl->_parent = nd;
		r->_left   = nd;
		r->_parent = nd->_parent;
		if ( nd->_parent && nd == nd->_parent->_right ) nd->_parent->_right = r;
		else if ( nd->_parent && nd == nd->_parent->_left )
			nd->_parent->_left = r;
		nd->_parent = r;
		return r;
	} // left_rotation
	node *rightRotation( node *nd ) {
		node *l = nd->_left, *lr = l->_right;
		nd->_rotate = DEFAULT;
		if ( nd == _root ) _root = l;
		nd->_left = lr;
		if ( lr ) lr->_parent = nd;
		l->_right  = nd;
		l->_parent = nd->_parent;
		if ( nd->_parent && nd == nd->_parent->_right ) nd->_parent->_right = l;
		else if ( nd->_parent && nd == nd->_parent->_left )
			nd->_parent->_left = l;
		nd->_parent = l;
		return l;
	} // right_rotation
	node *rotate( node *nd, const bool colorSwap ) {
		node *ret = nd;
		switch ( nd->_rotate ) {
			case LEFT:
				ret = leftRotation( nd );
				if ( colorSwap ) ret->swapColors( ret->_left );
			case DEFAULT: break;
			case RIGHT:
				ret = rightRotation( nd );
				if ( colorSwap ) ret->swapColors( ret->_right );
		}
		return ret;
	} // rotate
	/* find_helper ─────────────────────────────────────────────────────────────────────── */
	bool _find( node *&nd, const value_type &elt ) {
		if ( !_compare( elt, *nd->_elt ) && !_compare( *nd->_elt, elt ) ) return true;
		else if ( _compare( elt, *nd->_elt ) && nd->_left )
			return _find( nd->_left, elt );
		else if ( _compare( *nd->_elt, elt ) && nd->_right )
			return _find( nd->_right, elt );
		return false;
	} // find_helper
	/* insert_helper ───────────────────────────────────────────────────────────────────── */
	void _insert( node *&nd, const value_type &elt, node *parent = NULL ) {
		if ( nd && _compare( elt, *nd->_elt ) ) _insert( nd->_left, elt, nd );
		else if ( nd && _compare( *nd->_elt, elt ) )
			_insert( nd->_right, elt, nd );
		else {
			if ( !nd ) nd = new node( elt, _alloc, parent );
			return;
		}
		nd			  = rotate( nd, true );
		node *sibling = nd->getSibling();
		if ( !nd->_parent ) _root->_color = BLACK;
		if ( !nd->_parent || nd->_color == BLACK ||
			 ( ( !nd->_left || nd->_left->_color == BLACK ) &&
			   ( !nd->_right || nd->_right->_color == BLACK ) ) )
			return;
		else if ( !sibling || sibling->_color == BLACK ) {
			if ( nd == nd->_parent->_left && _compare( elt, *nd->_elt ) )
				nd->_parent->_rotate = RIGHT;
			else if ( nd == nd->_parent->_right && _compare( *nd->_elt, elt ) )
				nd->_parent->_rotate = LEFT;
			else if ( nd == nd->_parent->_left && _compare( *nd->_elt, elt ) ) {
				nd->_rotate			 = LEFT;
				nd					 = rotate( nd, false );
				nd->_parent->_rotate = RIGHT;
			} else {
				nd->_rotate			 = RIGHT;
				nd					 = rotate( nd, false );
				nd->_parent->_rotate = LEFT;
			}
		} else {
			nd->_color			= BLACK;
			sibling->_color		= BLACK;
			nd->_parent->_color = RED;
		}
	} // insert_helper
	/* fix_double_black ────────────────────────────────────────────────────────────────── */
	void fixDoubleBlack( node *nd ) {
		if ( !nd->_parent ) nd->_color = BLACK;
		else if ( nd->_color == DOUBLE_BLACK ) {
			node		*sibling = nd->getSibling();
			e_directions DBdir = ( nd->_parent->_left && nd == nd->_parent->_left ? LEFT : RIGHT );
			if ( !sibling || ( sibling->_color == BLACK && !sibling->hasRedChild() ) ) {
				if ( sibling ) sibling->_color = RED;
				nd->_color			= BLACK;
				nd->_parent->_color = e_colors( nd->_parent->_color + 1 );
				fixDoubleBlack( nd->_parent );
			} else if ( sibling->_color == BLACK && sibling->hasRedChild() ) {
				node *rot = nd;
				if ( sibling->_color == BLACK && nd->hasRedNiece() ) {
					sibling->_rotate = DBdir == LEFT ? RIGHT : LEFT;
					rot				 = rotate( sibling, false );
				}
				rot->_parent->_rotate = DBdir;
				rot					  = rotate( rot->_parent, true );
				nd->_color			  = BLACK;
				if ( rot->_left ) rot->_left->_color = BLACK;
				if ( rot->_right ) rot->_right->_color = BLACK;
			} else {
				nd->_parent->_rotate = DBdir;
				rotate( nd->_parent, true );
				fixDoubleBlack( nd );
			}
		}
	} // fixDoubleBlack
	/* delete_helper ───────────────────────────────────────────────────────────────────── */
	void _del( node *&nd, const value_type &elt ) {
		if ( nd && _compare( elt, *nd->_elt ) ) _del( nd->_left, elt );
		else if ( nd && _compare( *nd->_elt, elt ) )
			_del( nd->_right, elt );
		else if ( nd ) {
			if ( !nd->_left && !nd->_right ) {
				if ( nd->_color == BLACK ) nd->_color = DOUBLE_BLACK;
				fixDoubleBlack( nd );
				delete nd;
				nd = NULL;
			} else if ( !nd->_left || !nd->_right ) {
				node *tmp = nd, *sub = nd->_left ? nd->_left : nd->_right;
				sub->_color	 = nd->_color;
				sub->_parent = nd->_parent;
				nd			 = sub;
				delete tmp;
				tmp = NULL;
			} else {
				node *sub = nd->_right;
				while ( sub->_left ) sub = sub->_left;
				nd->swapContent( sub );
				_del( nd->_right, elt );
			}
		}
	} // del_helper
	void destruct( node *&nd ) {
		if ( !nd ) return;
		destruct( nd->_left );
		destruct( nd->_right );
		delete nd;
		nd = NULL;
	} // destruct
	/* member attributes ───────────────────────────────────────────────────────────────── */
	node				*_root;
	const allocator_type _alloc;
	const compare_type	 _compare;

  public:
	/* ctor - dtor ─────────────────────────────────────────────────────────────────────── */
	red_black_tree( const compare_type	 &compare = compare_type(),
					const allocator_type &alloc	  = allocator_type() )
		: _root( NULL ), _alloc( alloc ), _compare( compare ) {} // ctor_default
	~red_black_tree( void ) { destruct( _root ); };				 // dtor
	/* main_functions ──────────────────────────────────────────────────────────────────── */
	bool find( const value_type &elt ) {
		if ( !_root ) return false;
		return _find( *_root, elt );
	}																					   // find
	void insert( const value_type &elt, /* tmp */ const int i ) { _insert( _root, elt ); } // insert
	void del( const value_type &elt, /* tmp */ const int i ) { _del( _root, elt ); }	   // delete
};
