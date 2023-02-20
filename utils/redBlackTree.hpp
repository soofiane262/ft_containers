/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:54:13 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/20 17:35:29 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../utils/utils.hpp"

#include <cstddef>
#include <iostream>

#define RED_COLOR		   0
#define BLACK_COLOR		   1
#define DOUBLE_BLACK_COLOR 2

#define DEFAULT_DIR 0
#define LEFT_DIR	-1
#define RIGHT_DIR	1

template < class T, class Compare = std::less< T >, class Allocator = std::allocator< T > >
class redBlackTree {
  private:
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	/*                        Member Types - Node - Allocator Rebind                       */
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	typedef T			value_type;
	typedef Allocator	allocator_type;
	typedef Compare		compare_type;
	typedef std::size_t size_type;
	struct node {
		/* member types ────────────────────────────────────────────────────────────────────── */
		typedef T  value_type;
		typedef T &reference;
		typedef T *pointer;
		/* member attributes ──────────────────────────────────────────────────────────────── */
		T			_elt;
		Compare		_compare;
		signed char _color;
		signed char _rotate;
		node	   *_parent, *_left, *_right;
		/* ctor - dtor ────────────────────────────────────────────────────────────────────── */
		node( const Compare &comp = Compare() ) : _compare( comp ) {
			_parent = _left = _right = NULL;
		}
		node( const T &elt, node *parent, const Compare &comp = Compare() )
			: _elt( elt ), _compare( comp ) {
			_color	= RED_COLOR;
			_rotate = DEFAULT_DIR;
			_parent = parent;
			_left = _right = NULL;
		}												   // ctor
		~node( void ) { _parent = _left = _right = NULL; } // dtor
		/* ────────────────────────────────────────────────────────────────────────────────── */
		static node *_end_;
		static void	 setEnd( node *&x ) { _end_ = x; };
		/* helper functions ───────────────────────────────────────────────────────────────── */
		node *getSibling( void ) {
			if ( !_parent ) return NULL;
			else if ( this == _parent->_left )
				return _parent->_right;
			return _parent->_left;
		} // get_sibling
		bool hasRedChild( void ) {
			if ( ( _left && _left->_color == RED_COLOR ) ||
				 ( _right && _right->_color == RED_COLOR ) )
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
		node *successor( void ) {
			if ( !_right ) return _parent;
			return _right->min();
		}
		node *predecessor( void ) {
			if ( !_left ) return _parent;
			return _left->max();
		}
		/* next - previous ────────────────────────────────────────────────────────────────── */
		node *next( void ) {
			node *next_ = successor();
			if ( _parent && this != _parent->_left && next_ == _parent ) {
				while ( next_->_parent && next_ == next_->_parent->_right ) next_ = next_->_parent;
				next_ = next_->_parent;
			}
			if ( !next_ ) return _end_;
			return next_;
		}
		node *previous( void ) {
			node *prev_ = predecessor();
			if ( _parent && this != _parent->_right && prev_ == _parent ) {
				while ( prev_->_parent && prev_ == prev_->_parent->_left ) prev_ = prev_->_parent;
				prev_ = prev_->_parent;
			}
			return prev_;
		}
		/* overloads ──────────────────────────────────────────────────────────────────────── */
		bool operator==( const node *&other ) {
			return !_compare( _elt, other->_elt ) && !_compare( other->_elt, _elt );
		}
		bool operator!=( const node *&other ) { return !( this == other ); }
	}; // struct node
	/* ─────────────────────────────────────────────────────────────────────────────────── */
	typedef typename Allocator::template rebind< node >::other node_allocator_type;
	/* rotations ───────────────────────────────────────────────────────────────────────── */
	node *leftRotation( node *nd ) {
		node *r = nd->_right, *rl = r->_left;
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
	node *rightRotation( node *nd ) {
		node *l = nd->_left, *lr = l->_right;
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
	node *rotate( node *nd, const bool colorSwap ) {
		node *ret = nd;
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
	void swapContent( node *&x, node *&y ) {
		bool		relationship		   = x == y->_parent;
		signed char tmp_color[ 2 ]		   = { x->_color, y->_color };
		signed char tmp_rotate[ 2 ]		   = { x->_rotate, y->_rotate },
								  dir[ 2 ] = { DEFAULT_DIR, DEFAULT_DIR };
		node *tmp_node_x				   = x, *tmp_parent[ 2 ], *tmp_left[ 2 ], *tmp_right[ 2 ];
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
	node *_find( node *nd, const value_type &elt ) {
		if ( !_compare( elt, nd->_elt ) && !_compare( nd->_elt, elt ) ) return nd;
		else if ( _compare( elt, nd->_elt ) && nd->_left )
			return _find( nd->_left, elt );
		else if ( _compare( nd->_elt, elt ) && nd->_right )
			return _find( nd->_right, elt );
		return NULL;
	} // find_helper
	const node *_find( const node *nd, const value_type &elt ) const {
		if ( !_compare( elt, nd->_elt ) && !_compare( nd->_elt, elt ) ) return nd;
		else if ( _compare( elt, nd->_elt ) && nd->_left )
			return _find( nd->_left, elt );
		else if ( _compare( nd->_elt, elt ) && nd->_right )
			return _find( nd->_right, elt );
		return NULL;
	} // find_helper
	/* insert_helper ───────────────────────────────────────────────────────────────────── */
	void _insert( ft::pair< node *, bool > &ret, node *&nd, const value_type &elt,
				  node *parent = NULL ) {
		if ( nd && _compare( elt, nd->_elt ) ) _insert( ret, nd->_left, elt, nd );
		else if ( nd && _compare( nd->_elt, elt ) )
			_insert( ret, nd->_right, elt, nd );
		else {
			if ( !nd ) {
				nd = _node_alloc.allocate( 1 );
				_node_alloc.construct( nd, node( elt, parent, _compare ) );
				ret.second = true;
			}
			ret.first = nd;
			return;
		}
		nd			  = rotate( nd, true );
		node *sibling = nd->getSibling();
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
	void fixDoubleBlack( node *nd ) {
		if ( !nd->_parent ) nd->_color = BLACK_COLOR;
		else if ( nd->_color == DOUBLE_BLACK_COLOR ) {
			node	   *sibling = nd->getSibling();
			signed char DBdir =
				( nd->_parent->_left && nd == nd->_parent->_left ? LEFT_DIR : RIGHT_DIR );
			if ( !sibling || ( sibling->_color == BLACK_COLOR && !sibling->hasRedChild() ) ) {
				if ( sibling ) sibling->_color = RED_COLOR;
				nd->_color = BLACK_COLOR;
				nd->_parent->_color += 1;
				fixDoubleBlack( nd->_parent );
			} else if ( sibling->_color == BLACK_COLOR && sibling->hasRedChild() ) {
				node *rot = nd;
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
	/* delete_helper ───────────────────────────────────────────────────────────────────── */
	void _erase( bool &ret, node *&nd, const value_type &elt ) {
		if ( nd && _compare( elt, nd->_elt ) ) _erase( ret, nd->_left, elt );
		else if ( nd && _compare( nd->_elt, elt ) )
			_erase( ret, nd->_right, elt );
		else if ( nd ) {
			ret = true;
			if ( !nd->_left && !nd->_right ) {
				if ( nd->_color == BLACK_COLOR ) nd->_color = DOUBLE_BLACK_COLOR;
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
				swapContent( nd, sub );
				_erase( ret, nd->_right, elt );
			}
		}
	} // del_helper
	void destruct( node *&nd ) {
		if ( !nd ) return;
		destruct( nd->_left );
		destruct( nd->_right );
		_node_alloc.destroy( nd );
		_node_alloc.deallocate( nd, 1 );
		nd = NULL;
	} // destruct
	/* member attributes ───────────────────────────────────────────────────────────────── */
	node				*_root;
	node_allocator_type	 _node_alloc;
	const allocator_type _alloc;
	const compare_type	 _compare;

  public:
	typedef node node_type;
	/* ctor - dtor ─────────────────────────────────────────────────────────────────────── */
	redBlackTree( const compare_type		&compare	= compare_type(),
				  const allocator_type		&alloc		= allocator_type(),
				  const node_allocator_type &node_alloc = node_allocator_type() )
		: _root( NULL ), _node_alloc( node_alloc ), _alloc( alloc ), _compare( compare ) {
	}											  // ctor_default
	~redBlackTree( void ) { destruct( _root ); }; // dtor
	redBlackTree &operator=( redBlackTree &x ) {
		for ( node *start = x.begin(); start != x.end(); start->next() ) insert( start->_elt );
	}; // assignment
	/* main_functions ──────────────────────────────────────────────────────────────────── */
	node *begin( void ) { return _root ? _root->min() : NULL; }; // begin
	// tmp
	node *end( void ) { return _root ? node::_end_ : NULL; }; // end
	// tmp
	size_type count( value_type &elt ) const {
		size_type ret = 0;
		if ( _root ) _count( ret, _root, elt );
		return ret;
	} // find
	node *find( const value_type &elt ) {
		if ( !_root ) return NULL;
		return _find( _root, elt );
	} // find
	const node *find( const value_type &elt ) const {
		if ( !_root ) return NULL;
		return _find( _root, elt );
	} // find
	ft::pair< node *, bool > insert( const value_type &elt ) {
		if ( !_root ) {
			node::_end_ = _node_alloc.allocate( 1 );
			_node_alloc.construct( node::_end_, node( _compare ) );
		}
		ft::pair< node *, bool > ret( NULL, false );
		_insert( ret, _root, elt );
		node::_end_->_left = _root;
		return ret;
	} // insert
	bool erase( const value_type &elt ) {
		bool ret = false;
		if ( _root ) _erase( ret, _root, elt );
		return ret;
	} // delete
};

template < class T, class Compare, class Allocator >
typename redBlackTree< T, Compare, Allocator >::node
	*redBlackTree< T, Compare, Allocator >::node::_end_ = NULL;
