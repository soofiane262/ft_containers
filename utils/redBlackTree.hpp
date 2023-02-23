/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:54:13 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/23 16:56:59 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../utils/utils.hpp"

#include <cstddef>
#include <iostream>
#include <unistd.h>

#define RED_COLOR		   0
#define BLACK_COLOR		   1
#define DOUBLE_BLACK_COLOR 2

#define DEFAULT_DIR 0
#define LEFT_DIR	-1
#define RIGHT_DIR	1

template < class T > struct node {
	/* member types ────────────────────────────────────────────────────────────────────── */
	typedef T  value_type;
	typedef T &reference;
	typedef T *pointer;
	/* member attributes ──────────────────────────────────────────────────────────────── */
	T			_elt;
	signed char _color;
	signed char _rotate;
	node	   *_parent, *_left, *_right, *_end_;
	/* ctor - dtor ────────────────────────────────────────────────────────────────────── */
	node( void ) { _parent = _left = _right = _end_ = NULL; }
	node( const T &elt, node *parent, node *end )
		: _elt( elt ), _color( RED_COLOR ), _rotate( DEFAULT_DIR ), _parent( parent ),
		  _left( NULL ), _right( NULL ), _end_( end ) {}	   // ctor_param
	~node( void ) { _parent = _left = _right = _end_ = NULL; } // dtor
	/* helper functions ───────────────────────────────────────────────────────────────── */
	node *getSibling( void ) {
		if ( !_parent ) return NULL;
		else if ( this == _parent->_left )
			return _parent->_right;
		return _parent->_left;
	} // get_sibling
	bool hasRedChild( void ) {
		if ( ( _left && _left->_color == RED_COLOR ) || ( _right && _right->_color == RED_COLOR ) )
			return true;
		return false;
	} // has_red_child
	bool hasRedNiece( void ) {
		node *sibling = getSibling();
		if ( sibling && sibling->hasRedChild() &&
			 ( ( sibling == _parent->_left && sibling->_right &&
				 sibling->_right->_color == RED_COLOR ) ||
			   ( sibling == _parent->_right && sibling->_left &&
				 sibling->_left->_color == RED_COLOR ) ) )
			return true;
		return false;
	} // has_red_niece
	void swapColors( node *&y ) {
		char tmpColor = _color;
		_color		  = y->_color;
		y->_color	  = tmpColor;
	} // swap_colors
	/* min - max ──────────────────────────────────────────────────────────────────────── */
	node *min( void ) {
		node *min_ = this;
		while ( min_->_left ) min_ = min_->_left;
		return min_;
	}
	node *max( void ) {
		node *max_ = this;
		while ( max_->_right ) max_ = max_->_right;
		return max_;
	}
	/* successor - predecessor ────────────────────────────────────────────────────────── */
	node *successor( void ) const {
		if ( !_right ) return _parent;
		return _right->min();
	}
	node *predecessor( void ) {
		if ( !_left ) return _parent;
		return _left->max();
	}
	/* next ───────────────────────────────────────────────────────────────────────────── */
	node *next( void ) const {
		node *next_ = successor();
		if ( _parent && this != _parent->_left && next_ == _parent ) {
			while ( next_->_parent && next_ == next_->_parent->_right ) next_ = next_->_parent;
			next_ = next_->_parent;
		}
		if ( !next_ ) return _end_;
		return next_;
	}
	/* previous ───────────────────────────────────────────────────────────────────────── */
	node *previous( void ) {
		node *prev_ = predecessor();
		if ( _parent && this != _parent->_right && prev_ == _parent ) {
			while ( prev_->_parent && prev_ == prev_->_parent->_left ) prev_ = prev_->_parent;
			prev_ = prev_->_parent;
		}
		return prev_;
	}
}; // struct node

template < class T, class Compare = std::less< T >, class Allocator = std::allocator< T > >
class redBlackTree {
  private:
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	/*                        Member Types - Node - Allocator Rebind                       */
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	typedef T														value_type;
	typedef Allocator												allocator_type;
	typedef Compare													compare_type;
	typedef std::size_t												size_type;
	typedef node< T >												node_type;
	typedef typename Allocator::template rebind< node_type >::other node_allocator_type;
	/* clone_node ──────────────────────────────────────────────────────────────────────── */
	void cloneNode( node_type *&nd, const node_type *x, node_type *end, node_type *parent ) {
		if ( !x ) return;
		nd = _node_alloc.allocate( 1 );
		_node_alloc.construct( nd, node_type( x->_elt, parent, end ) );
		nd->_color = x->_color;
		cloneNode( nd->_left, x->_left, end, nd );
		cloneNode( nd->_right, x->_right, end, nd );
	}
	/* rotations ───────────────────────────────────────────────────────────────────────── */
	node_type *leftRotation( node_type *nd ) {
		node_type *r = nd->_right, *rl = r->_left;
		nd->_rotate = DEFAULT_DIR;
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
	node_type *rightRotation( node_type *nd ) {
		node_type *l = nd->_left, *lr = l->_right;
		nd->_rotate = DEFAULT_DIR;
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
	node_type *rotate( node_type *nd, const bool colorSwap ) {
		node_type *ret = nd;
		switch ( nd->_rotate ) {
			case LEFT_DIR:
				ret = leftRotation( nd );
				if ( colorSwap ) ret->swapColors( ret->_left );
			case DEFAULT_DIR: break;
			case RIGHT_DIR:
				ret = rightRotation( nd );
				if ( colorSwap ) ret->swapColors( ret->_right );
		}
		return ret;
	} // rotate
	/* swapContent ─────────────────────────────────────────────────────────────────────── */
	void swapContent( node_type *&x, node_type *&y ) {
		bool		relationship		   = x == y->_parent;
		signed char tmp_color[ 2 ]		   = { x->_color, y->_color };
		signed char tmp_rotate[ 2 ]		   = { x->_rotate, y->_rotate },
								  dir[ 2 ] = { DEFAULT_DIR, DEFAULT_DIR };
		node_type *tmp_node_x			   = x, *tmp_parent[ 2 ], *tmp_left[ 2 ], *tmp_right[ 2 ];
		if ( !relationship ) {
			if ( !x->_parent ) dir[ 0 ] = DEFAULT_DIR;
			else if ( x == x->_parent->_left )
				dir[ 0 ] = LEFT_DIR;
			else
				dir[ 0 ] = RIGHT_DIR;
			if ( y == y->_parent->_left ) dir[ 1 ] = LEFT_DIR;
			else
				dir[ 1 ] = RIGHT_DIR;
			tmp_parent[ 0 ] = x->_parent, tmp_parent[ 1 ] = y->_parent;
			tmp_left[ 0 ] = x->_left, tmp_left[ 1 ] = y->_left;
			tmp_right[ 0 ] = x->_right, tmp_right[ 1 ] = y->_right;
		} else {
			tmp_parent[ 0 ] = x->_parent, tmp_parent[ 1 ] = y;
			tmp_left[ 0 ] = ( relationship == LEFT_DIR ? x : x->_left ), tmp_left[ 1 ] = y->_left;
			tmp_right[ 0 ]				= ( relationship == RIGHT_DIR ? x : x->_right ),
						 tmp_right[ 1 ] = y->_right;
		}
		x		   = y;
		y		   = tmp_node_x;
		x->_color  = tmp_color[ 0 ];
		x->_rotate = tmp_rotate[ 0 ];
		x->_parent = tmp_parent[ 0 ];
		x->_left   = tmp_left[ 0 ];
		x->_right  = tmp_right[ 0 ];
		y->_color  = tmp_color[ 1 ];
		y->_rotate = tmp_rotate[ 1 ];
		y->_parent = tmp_parent[ 1 ];
		y->_left   = tmp_left[ 1 ];
		y->_right  = tmp_right[ 1 ];
		if ( x->_left ) x->_left->_parent = x;
		if ( x->_right ) x->_right->_parent = x;
		if ( y->_left ) y->_left->_parent = y;
		if ( y->_right ) y->_right->_parent = y;
		if ( relationship ) return;
		if ( dir[ 0 ] == LEFT_DIR ) x->_parent->_left = x;
		else if ( dir[ 0 ] == RIGHT_DIR )
			x->_parent->_right = x;
		if ( dir[ 1 ] == LEFT_DIR ) y->_parent->_left = y;
		else if ( dir[ 1 ] == RIGHT_DIR )
			y->_parent->_right = y;
	}
	/* find_helper ─────────────────────────────────────────────────────────────────────── */
	ft::pair< node_type *, bool > _find( node_type *nd, const value_type &elt ) const {
		if ( nd && !_compare( elt, nd->_elt ) && !_compare( nd->_elt, elt ) )
			return ft::pair< node_type *, bool >( nd, true );
		else if ( nd && _compare( elt, nd->_elt ) && nd->_left )
			return _find( nd->_left, elt );
		else if ( nd && _compare( nd->_elt, elt ) && nd->_right )
			return _find( nd->_right, elt );
		return ft::pair< node_type *, bool >( NULL, false );
	} // find_helper
	/* insert_helper ───────────────────────────────────────────────────────────────────── */
	void _insert( ft::pair< node_type *, bool > &ret, node_type *&nd, const value_type &elt,
				  node_type *end, node_type *parent = NULL ) {
		if ( nd && _compare( elt, nd->_elt ) ) _insert( ret, nd->_left, elt, end, nd );
		else if ( nd && _compare( nd->_elt, elt ) )
			_insert( ret, nd->_right, elt, end, nd );
		else {
			if ( !nd ) {
				nd = _node_alloc.allocate( 1 );
				_node_alloc.construct( nd, node_type( elt, parent, end ) );
				ret.second = true;
			}
			ret.first = nd;
			return;
		}
		nd				   = rotate( nd, true );
		node_type *sibling = nd->getSibling();
		if ( !nd->_parent ) _root->_color = BLACK_COLOR;
		if ( !nd->_parent || nd->_color == BLACK_COLOR ||
			 ( ( !nd->_left || nd->_left->_color == BLACK_COLOR ) &&
			   ( !nd->_right || nd->_right->_color == BLACK_COLOR ) ) )
			return;
		else if ( !sibling || sibling->_color == BLACK_COLOR ) {
			if ( nd == nd->_parent->_left && _compare( elt, nd->_elt ) )
				nd->_parent->_rotate = RIGHT_DIR;
			else if ( nd == nd->_parent->_right && _compare( nd->_elt, elt ) )
				nd->_parent->_rotate = LEFT_DIR;
			else if ( nd == nd->_parent->_left && _compare( nd->_elt, elt ) ) {
				nd->_rotate			 = LEFT_DIR;
				nd					 = rotate( nd, false );
				nd->_parent->_rotate = RIGHT_DIR;
			} else {
				nd->_rotate			 = RIGHT_DIR;
				nd					 = rotate( nd, false );
				nd->_parent->_rotate = LEFT_DIR;
			}
		} else {
			nd->_color			= BLACK_COLOR;
			sibling->_color		= BLACK_COLOR;
			nd->_parent->_color = RED_COLOR;
		}
	} // insert_helper
	/* fix_double_black ────────────────────────────────────────────────────────────────── */
	void fixDoubleBlack( node_type *nd ) {
		if ( !nd->_parent ) nd->_color = BLACK_COLOR;
		else if ( nd->_color == DOUBLE_BLACK_COLOR ) {
			node_type  *sibling = nd->getSibling();
			signed char DBdir =
				( nd->_parent->_left && nd == nd->_parent->_left ? LEFT_DIR : RIGHT_DIR );
			if ( !sibling || ( sibling->_color == BLACK_COLOR && !sibling->hasRedChild() ) ) {
				if ( sibling ) sibling->_color = RED_COLOR;
				nd->_color = BLACK_COLOR;
				nd->_parent->_color += 1;
				fixDoubleBlack( nd->_parent );
			} else if ( sibling->_color == BLACK_COLOR && sibling->hasRedChild() ) {
				node_type *rot = nd;
				if ( sibling->_color == BLACK_COLOR && nd->hasRedNiece() ) {
					sibling->_rotate = DBdir * -1;
					rot				 = rotate( sibling, false );
				}
				rot->_parent->_rotate = DBdir;
				rot					  = rotate( rot->_parent, true );
				nd->_color			  = BLACK_COLOR;
				if ( rot->_left ) rot->_left->_color = BLACK_COLOR;
				if ( rot->_right ) rot->_right->_color = BLACK_COLOR;
			} else {
				nd->_parent->_rotate = DBdir;
				rotate( nd->_parent, true );
				fixDoubleBlack( nd );
			}
		}
	} // fixDoubleBlack
	/* erase_helper ───────────────────────────────────────────────────────────────────── */
	void _erase( bool &ret, node_type *&nd, const value_type &elt ) {
		if ( nd && _compare( elt, nd->_elt ) ) _erase( ret, nd->_left, elt );
		else if ( nd && _compare( nd->_elt, elt ) )
			_erase( ret, nd->_right, elt );
		else if ( nd ) {
			ret = true;
			if ( !nd->_left && !nd->_right ) {
				if ( nd->_color == BLACK_COLOR ) nd->_color = DOUBLE_BLACK_COLOR;
				fixDoubleBlack( nd );
				_node_alloc.destroy( nd );
				_node_alloc.deallocate( nd, 1 );
				nd = NULL;
			} else if ( !nd->_left || !nd->_right ) {
				node_type *tmp = nd, *sub = nd->_left ? nd->_left : nd->_right;
				sub->_color	 = nd->_color;
				sub->_parent = nd->_parent;
				nd			 = sub;
				_node_alloc.destroy( tmp );
				_node_alloc.deallocate( tmp, 1 );
				tmp = NULL;
			} else {
				node_type *sub = nd->_right;
				while ( sub->_left ) sub = sub->_left;
				swapContent( nd, sub );
				_erase( ret, nd->_right, elt );
			}
		}
	} // del_helper
	void destruct( node_type *&nd ) {
		if ( !nd ) return;
		destruct( nd->_left );
		destruct( nd->_right );
		_node_alloc.destroy( nd );
		_node_alloc.deallocate( nd, 1 );
		nd = NULL;
	} // destruct
	/* member attributes ───────────────────────────────────────────────────────────────── */
	node_type		   *_root, *__end_;
	node_allocator_type _node_alloc;
	allocator_type		_alloc;
	compare_type		_compare;

  public:
	/* ctor - dtor ─────────────────────────────────────────────────────────────────────── */
	redBlackTree( const compare_type		&compare	= compare_type(),
				  const allocator_type		&alloc		= allocator_type(),
				  const node_allocator_type &node_alloc = node_allocator_type() )
		: _root( NULL ), _node_alloc( node_alloc ), _alloc( alloc ), _compare( compare ) {
		__end_ = _node_alloc.allocate( 1 );
		_node_alloc.construct( __end_, node_type() );
	} // ctor_default
	redBlackTree( const redBlackTree &x )
		: _root( NULL ), _node_alloc( x._node_alloc ), _alloc( x._alloc ), _compare( x._compare ) {
		__end_ = _node_alloc.allocate( 1 );
		_node_alloc.construct( __end_, node_type() );
		cloneNode( _root, x._root, __end_, NULL );
		__end_->_left = _root;
	} // ctor_copy
	~redBlackTree( void ) {
		destruct( _root );
		_node_alloc.destroy( __end_ );
		_node_alloc.deallocate( __end_, 1 );
		__end_ = NULL;
	}; // dtor
	/* swap ────────────────────────────────────────────────────────────────────────────── */
	void swap( redBlackTree &other ) {
		node_type		   *tmp_root = _root, *tmp__end_ = __end_;
		node_allocator_type tmp_node_alloc = _node_alloc;
		allocator_type		tmp_alloc	   = _alloc;
		compare_type		tmp_compare	   = _compare;
		_root							   = other._root;
		__end_							   = other.__end_;
		_node_alloc						   = other._node_alloc;
		_alloc							   = other._alloc;
		_compare						   = other._compare;
		other._root						   = tmp_root;
		other.__end_					   = tmp__end_;
		other._node_alloc				   = tmp_node_alloc;
		other._alloc					   = tmp_alloc;
		other._compare					   = tmp_compare;
	}
	/* clone - clear ───────────────────────────────────────────────────────────────────── */
	void clone( const redBlackTree &x ) {
		cloneNode( _root, x._root, __end_, NULL );
		// node_type::_end_ = __end_;
		__end_->_left = _root;
	} // clone
	void clear( void ) {
		destruct( _root );
		__end_->_left = NULL;
	}; // clear
	/* begin - end ─────────────────────────────────────────────────────────────────────── */
	node_type *begin( void ) const { return _root ? _root->min() : NULL; }; // begin
	node_type *end( void ) const { return _root ? __end_ : NULL; };			// end
	/* lower_bound ────────────────────────────────────────────────────────────── */
	node_type *lower_bound( const value_type &elt ) const {
		node_type *nd = begin();
		if ( !nd ) nd = end();
		for ( ; nd != end() && _compare( nd->_elt, elt ); nd = nd->next() ) continue;
		return nd;
	} // lower_bound
	/* upper_bound ─────────────────────────────────────────────────────────────────────── */
	node_type *upper_bound( const value_type &elt ) const {
		node_type *nd = begin();
		if ( !nd ) nd = end();
		for ( ; nd != end() && !_compare( elt, nd->_elt ); nd = nd->next() ) continue;
		return nd;
	} // upper_bound
	/* find ────────────────────────────────────────────────────────────────────────────── */
	ft::pair< node_type *, bool > find( const value_type &elt ) const {
		if ( !_root ) return ft::pair< node_type *, bool >( NULL, false );
		return _find( _root, elt );
	} // find
	/* insert ──────────────────────────────────────────────────────────────────────────── */
	ft::pair< node_type *, bool > insert( const value_type &elt ) {
		ft::pair< node_type *, bool > ret( NULL, false );
		_insert( ret, _root, elt, __end_ );
		__end_->_left = _root;
		return ret;
	} // insert
	/* erase ───────────────────────────────────────────────────────────────────────────── */
	bool erase( const value_type &elt ) {
		bool ret = false;
		if ( _root ) {
			_erase( ret, _root, elt );
			__end_->_left = _root;
		}
		return ret;
	} // erase
};
