/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_rbt.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:13:21 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/17 16:14:20 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// for ckecker
#include <cstddef>
#include <map>
#include <ostream>
#include <queue>
#include <vector>
// end

#include "../utils/utils.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unistd.h>

enum e_colors { RED, BLACK, DOUBLE_BLACK };
enum e_directions { LEFT, DEFAULT, RIGHT };

template < class T > struct node {
	T			 _elt;
	e_colors	 _color;
	e_directions _rotate;
	node		*_parent, *_left, *_right;
	node( const T &elt, node *parent ) : _elt( elt ) {
		_color	= RED;
		_rotate = DEFAULT;
		_parent = parent;
		_left = _right = NULL;
	}
	node *getSibling( void ) {
		if ( !_parent ) return NULL;
		else if ( _elt < _parent->_elt )
			return _parent->_right;
		return _parent->_left;
	}
	bool hasRedChild( void ) {
		if ( ( _left && _left->_color == RED ) || ( _right && _right->_color == RED ) ) return true;
		return false;
	}
	bool hasRedNiece( void ) {
		node *sibling = getSibling();
		if ( sibling && sibling->hasRedChild() &&
			 ( ( sibling->_elt < _parent->_elt && sibling->_right &&
				 sibling->_right->_color == RED ) ||
			   ( sibling->_elt > _parent->_elt && sibling->_left &&
				 sibling->_left->_color == RED ) ) )
			return true;
		return false;
	}
};

// tmp
// template < class T > struct output {
template < class Key, class T, class Compare = std::less< Key > > struct output {
	typedef node< ft::pair< const Key, T > > node_type;
	node_type								*_nd;
	int										 _lvl;
	int										 _spaces;
	int										 _addit;
	int										 _length;
	e_directions							 _dir;
	static int								 total_lvls;
	static int								 total_diff;
	static int								 _width;
	output( node_type *nd, int lvl, int length, e_directions dir )
		: _nd( nd ), _lvl( lvl ), _length( length ? length : 1 ), _dir( dir ), _addit( 0 ) {};
};
template < class Key, class T, class Compare > int output< Key, T, Compare >::total_lvls = 0;
template < class Key, class T, class Compare > int output< Key, T, Compare >::total_diff = 2;
template < class Key, class T, class Compare > int output< Key, T, Compare >::_width	 = 0;
// tmp

template < class Key, class T, class Compare = std::less< Key >,
		   class Allocator = std::allocator< ft::pair< const Key, T > > >
class generic_rbt {
  private:
	typedef Key									key_type;
	typedef T									mapped_type;
	typedef ft::pair< const Key, T >			value_type;
	typedef Compare								key_compare;
	typedef Allocator							allocator_type;
	typedef typename Allocator::reference		reference;
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer			pointer;
	typedef typename Allocator::const_pointer	const_pointer;
	class value_compare : public std::binary_function< value_type, value_type, bool > {
		friend class map;

	  protected:
		Compare comp;

	  public:
		value_compare( Compare c ) : comp( c ) {}
		bool operator()( const value_type &x, const value_type &y ) const {
			return comp( x.first, y.first );
		}
	}; // class value_compare
	typedef node< ft::pair< const Key, T > > node_type;
	typedef output< Key, T, Compare >		 output_type;
	void									 swapColors( node_type *&x, node_type *&y ) {
		e_colors tmpColor = x->_color;
		x->_color		  = y->_color;
		y->_color		  = tmpColor;
	}
	node_type *leftRotation( node_type *nd ) {
		node_type *r = nd->_right, *rl = r->_left;
		nd->_right = rl;
		if ( rl ) rl->_parent = nd;
		r->_left   = nd;
		r->_parent = nd->_parent;
		if ( nd->_parent && nd->_elt > nd->_parent->_elt ) nd->_parent->_right = r;
		else if ( nd->_parent && nd->_elt < nd->_parent->_elt )
			nd->_parent->_left = r;
		nd->_parent = r;
		return r;
	}
	node_type *rightRotation( node_type *nd ) {
		node_type *l = nd->_left, *lr = l->_right;
		nd->_left = lr;
		if ( lr ) lr->_parent = nd;
		l->_right  = nd;
		l->_parent = nd->_parent;
		if ( nd->_parent && nd->_elt > nd->_parent->_elt ) nd->_parent->_right = l;
		else if ( nd->_parent && nd->_elt < nd->_parent->_elt )
			nd->_parent->_left = l;
		nd->_parent = l;
		return l;
	}
	void swapData( node_type *&x, node_type *&y ) {
		bool	   relationship = y->_parent == x ? true : false;
		node_type *tmp_node		= x;
		x						= y;
		y						= tmp_node;
		e_colors	 tmp_color	= y->_color;
		e_directions tmp_rotate = y->_rotate;
		node_type	*tmp_parent = y->_parent, *tmp_left = y->_left, *tmp_right = y->_right;
		y->_color  = x->_color;
		y->_rotate = x->_rotate;
		y->_parent = x->_parent;
		y->_left   = x->_left;
		y->_right  = x->_right;
		log( y );
		exit( 0 );
		if ( value_compare( key_compare() )( y->_elt, y->_parent->_elt ) ) y->_parent->_left = y;
		else
			y->_parent->_right = y;
		x->_color  = tmp_color;
		x->_rotate = tmp_rotate;
		if ( x->_parent )
			std::cout << "i am " << x->_elt.second << ", my parent is " << x->_parent->_elt.second
					  << "\n";
		x->_parent = tmp_parent;
		if ( x->_parent && value_compare( key_compare() )( x->_elt, x->_parent->_elt ) )
			x->_parent->_left = x;
		else if ( x->_parent )
			x->_parent->_right = x;
		x->_left		   = tmp_left;
		x->_left->_parent  = x;
		x->_right		   = tmp_right;
		x->_right->_parent = x;
	}
	node_type *rotate( node_type *nd, const bool colorSwap ) {
		node_type	*ret	= nd;
		e_directions rotDir = nd->_rotate;
		nd->_rotate			= DEFAULT;
		switch ( rotDir ) {
			case DEFAULT: break;
			case RIGHT:
				ret = rightRotation( nd );
				if ( colorSwap ) swapColors( ret, ret->_right );
				break;
			case LEFT:
				ret = leftRotation( nd );
				if ( colorSwap ) swapColors( ret, ret->_left );
				break;
		}
		return ret;
	};
	bool find( node_type &nd, const value_type &elt ) {
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
	void _insert( node_type *&nd, const value_type &elt, node_type *parent ) {
		if ( !nd ) {
			nd = new node_type( elt, parent );
			return;
		} else if ( value_compare( key_compare() )( elt, nd->_elt ) )
			_insert( nd->_left, elt, nd );
		else if ( value_compare( key_compare() )( nd->_elt, elt ) )
			_insert( nd->_right, elt, nd );
		else
			return;
		nd				   = rotate( nd, true );
		node_type *sibling = nd->getSibling();
		if ( !nd->_parent ) root->_color = BLACK;
		if ( !nd->_parent || nd->_color == BLACK ||
			 ( ( !nd->_left || nd->_left->_color == BLACK ) &&
			   ( !nd->_right || nd->_right->_color == BLACK ) ) )
			return;
		else if ( !sibling || sibling->_color == BLACK ) {
			if ( nd == nd->_parent->_left && value_compare( key_compare() )( elt, nd->_elt ) )
				nd->_parent->_rotate = RIGHT;
			else if ( nd == nd->_parent->_right && value_compare( key_compare() )( nd->_elt, elt ) )
				nd->_parent->_rotate = LEFT;
			else if ( nd == nd->_parent->_left &&
					  value_compare( key_compare() )( nd->_elt, elt ) ) {
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
	};
	void fixDoubleBlack( node_type *nd ) {
		if ( nd->_color != DOUBLE_BLACK ) return;
		else if ( !nd->_parent )
			nd->_color = BLACK;
		else {
			node_type	*sibling = nd->getSibling();
			e_directions DBdir	 = ( nd->_elt < nd->_parent->_elt ? LEFT : RIGHT );
			if ( !sibling || ( sibling->_color == BLACK && !sibling->hasRedChild() ) ) {
				if ( sibling ) sibling->_color = RED;
				nd->_color			= BLACK;
				nd->_parent->_color = e_colors( nd->_parent->_color + 1 );
				fixDoubleBlack( nd->_parent );
			} else if ( sibling->_color == BLACK && sibling->hasRedChild() ) {
				node_type *rot = nd;
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
				node_type *rot		 = rotate( nd->_parent, true );
				nd->_parent			 = ( DBdir == LEFT ? rot->_left : rot->_right );
				fixDoubleBlack( nd );
			}
		}
	};

	void _del( node_type *&nd, const key_type &key ) {
		if ( !nd ) return;
		else if ( key_compare()( key, nd->_elt.first ) )
			_del( nd->_left, key );
		else if ( key_compare()( nd->_elt.first, key ) )
			_del( nd->_right, key );
		else {
			if ( !nd->_left && !nd->_right ) {
				if ( nd->_color == BLACK ) nd->_color = DOUBLE_BLACK;
				fixDoubleBlack( nd );
				delete nd;
				nd = NULL;
			} else if ( !nd->_left || !nd->_right ) {
				node_type *tmp = nd;
				node_type *sub = nd->_left ? nd->_left : nd->_right;
				sub->_color	   = nd->_color;
				sub->_parent   = nd->_parent;
				nd			   = sub;
				delete tmp;
				tmp = NULL;
			} else {
				node_type *sub = nd->_right;
				while ( sub->_left ) sub = sub->_left;
				swapData( nd, sub );
				_del( nd->_right, key );
			}
		}
	};
	void destruct( node_type *&nd ) {
		if ( !nd ) return;
		destruct( nd->_left );
		destruct( nd->_right );
		delete nd;
		nd = NULL;
	};
	void _getTotalLvls( node_type *x, const int lvl ) {
		if ( !x ) return;
		else if ( lvl >= output_type::total_lvls )
			output_type::total_lvls = lvl + 1;
		_getTotalLvls( x->_left, lvl + 1 );
		_getTotalLvls( x->_right, lvl + 1 );
	};
	void _store( node_type *x, std::vector< output_type > &out, const int lvl, e_directions dir ) {
		if ( lvl == output_type::total_lvls ) return;
		_store( ( x ? x->_left : x ), out, lvl + 1, LEFT );
		std::stringstream ss;
		if ( x ) ss << x->_elt.second;
		out.push_back( output_type( x, lvl, ss.str().length(), dir ) );
		_store( ( x ? x->_right : x ), out, lvl + 1, RIGHT );
	};
	void _log( std::vector< output_type > out ) {
		if ( !out.size() ) {
			std::cout << "empty rbt\n";
			return;
		}
		int indent = 2;
		for ( int l = output_type::total_lvls - 1, i = -1, lsl = -1, diff = 2; l >= 0;
			  l--, i = -1, lsl = -1, diff *= 2 ) {
			while ( ++i < out.size() ) {
				if ( l != out[ i ]._lvl ) continue;
				if ( lsl == -1 && l == output_type::total_lvls - 1 ) out[ i ]._spaces = 0;
				else
					out[ i ]._spaces = indent + out[ i ]._addit;
				out[ i ]._addit += out[ i ]._length;
				if ( out[ i ]._dir == RIGHT && out[ i - ( diff / 2 ) ]._dir == RIGHT )
					out[ i - ( diff / 2 ) ]._addit +=
						out[ i ]._addit + ( out[ i ]._length + out[ i - diff ]._length ) / 2;
				if ( lsl == -1 ) indent *= ( indent ? 2 : 1 );
				lsl = i;
			}
			output_type::total_diff = diff;
		}
		// std::cout << std::setw( 5 ) << "@|" << std::setw( 11 ) << "nb|" << std::setw( 7 ) <<
		// "lvl|"
		// 		  << std::setw( 7 ) << "sp|" << std::setw( 7 ) << "addit|" << '\n';
		// for ( int i = 0; i < out.size(); i++ )
		// 	std::cout << std::setw( 4 ) << i << "|" << std::setw( 10 )
		// 			  << ( out[ i ]._nd ? out[ i ]._nd->_elt : 0 ) << "|" << std::setw( 6 )
		// 			  << out[ i ]._lvl << "|" << std::setw( 6 ) << out[ i ]._spaces << "|"
		// 			  << std::setw( 6 ) << out[ i ]._addit << "|" << '\n';
		for ( int l = 0, i = -1, diff = output_type::total_diff, width = 0;
			  l < output_type::total_lvls; l++, i = -1, diff /= 2, width = 0 ) {
			if ( l != 0 ) {
				std::cout << "\e[2m";
				while ( ++i < out.size() ) {
					if ( l != out[ i ]._lvl ) continue;
					for ( int s = 0, end = out[ i ]._spaces + out[ i ]._length / 2; s < end; s++ ) {
						if ( out[ i ]._dir == RIGHT && out[ i ]._nd && out[ i - diff ]._nd )
							std::cout << "─";
						else if ( out[ i ]._dir == RIGHT && out[ i ]._nd && !out[ i - diff ]._nd &&
								  s > end / 2 )
							std::cout << ( s == end / 2 + 1 ? "└" : "─" );
						else if ( out[ i ]._dir == RIGHT && !out[ i ]._nd && out[ i - diff ]._nd &&
								  s < end / 2 )
							std::cout << ( s == end / 2 - 1 ? "┘" : "─" );
						else
							std::cout << " ";
					}
					if ( out[ i ]._nd ) std::cout << ( out[ i ]._dir == LEFT ? "┌" : "┐" );
					else
						std::cout << ' ';
				}
				std::cout << "\e[22m\n";
			}
			i = -1;
			while ( ++i < out.size() ) {
				if ( l != out[ i ]._lvl ) continue;
				for ( int s = 0; s < out[ i ]._spaces; s++, width++ ) std::cout << ' ';
				if ( out[ i ]._nd )
					std::cout << ( out[ i ]._nd->_color == RED ? "\e[1;31m" : "\e[1;37m" )
							  << ( out[ i ]._nd->_color == DOUBLE_BLACK ? "\e[4m" : "" )
							  << out[ i ]._nd->_elt.second << "\e[0m";
				else
					std::cout << ' ';
				width += out[ i ]._length;
			}
			output_type::_width = std::max( width + 10, output_type::_width );
			std::cout << '\n';
		}
		std::cout << "\e[2m";
		for ( int i = 0; i < output_type::_width; i++ ) std::cout << "─";
		std::cout << "\e[22m\n";
	};
	node_type *root;

  public:
	generic_rbt( void ) { root = NULL; };
	generic_rbt( const T n ) { root = new node_type( n ); };
	~generic_rbt( void ) { destruct( root ); };
	bool find( const T &elt ) {
		if ( !root ) return false;
		else
			return find( *root, elt );
	};
	void insert( const key_type &key_, const mapped_type &elt_, /* tmp */ const int i ) {
		_insert( root, value_type( key_, elt_ ), NULL );
		// checking
		std::map< node_type *, std::vector< int > > mp;
		std::cout << "\e[1;31m";
		assert( check( root, mp ) );
		std::cout << "\e[0m";
		std::cout << "idx " << std::setw( 10 ) << i << " INSERTED " << std::setw( 16 ) << elt_
				  << " SUCCESSFULLY\n\e[F\e[K";
	};
	void del( const key_type &key_, /* tmp */ const int i ) {
		_del( root, key_ );
		log();
		if ( root ) {
			// checking
			std::map< node_type *, std::vector< int > > mp;
			std::cout << "\e[1;31m";
			assert( check( root, mp ) );
			std::cout << "\e[0m";
		}
		std::cout << "idx " << std::setw( 10 ) << i << " DELETED ELEMENT @ " << std::setw( 16 )
				  << key_ << " SUCCESSFULLY\n\e[F\e[K";
	};

	// tmp
	void log( node_type *nd ) {
		if ( !nd ) return;
		output_type::total_lvls = 0;
		output_type::total_diff = 2;
		output_type::_width		= 0;
		std::vector< output_type > out;
		_getTotalLvls( nd, 0 );
		_store( nd, out, 0, DEFAULT );
		_log( out );
	};
	void log( void ) {
		if ( !root ) return;
		output_type::total_lvls = 0;
		output_type::total_diff = 2;
		output_type::_width		= 0;
		std::vector< output_type > out;
		_getTotalLvls( root, 0 );
		_store( root, out, 0, DEFAULT );
		_log( out );
	};

	// checker {made by: jalalium}
	bool check( node_type *nd, std::map< node_type *, std::vector< int > > &mp ) {
		bool ok = true;
		if ( nd->_left != NULL ) {
			// if nd->_elt <= nd->_left->_elt ) {
			if ( !value_compare( key_compare() )( nd->_left->_elt,
												  nd->_elt ) /* nd->_elt <= nd->_left->_elt */ ) {
				std::cout << "LEFT CHILD LARGER OR EQUAL TO PARENT " << nd->_elt.first << " "
						  << nd->_left->_elt.first << std::endl;
				return false;
			}
			if ( nd->_color == RED && nd->_left->_color == RED ) {
				std::cout << "RED PARENT WITH RED CHILD: " << nd->_elt.first << " "
						  << nd->_left->_elt.first << std::endl;
				return false;
			}
			ok &= check( nd->_left, mp );
		}
		if ( nd->_right != NULL ) {
			// if ( nd->_elt >= nd->_right->_elt ) {
			if ( !value_compare( key_compare() )( nd->_elt, nd->_right->_elt ) ) {
				std::cout << "RIGHT CHILD SMALLER OR EQUAL TO PARENT " << nd->_elt.first << " "
						  << nd->_left->_elt.first << std::endl;
				return false;
			}
			if ( nd->_color == RED && nd->_right->_color == RED ) {
				std::cout << "RED PARENT WITH RED CHILD: " << nd->_elt.first << " "
						  << nd->_right->_elt.first << std::endl;
				return false;
			}
			ok &= check( nd->_right, mp );
		}
		std::vector< int > tmp;
		if ( nd->_left != NULL ) {
			for ( int z : mp[ nd->_left ] ) tmp.push_back( z );
		} else
			tmp.push_back( 0 );
		if ( nd->_right != NULL ) {
			for ( int z : mp[ nd->_right ] ) tmp.push_back( z );
		} else
			tmp.push_back( 0 );
		std::sort( tmp.begin(), tmp.end() );
		for ( int &z : tmp ) z += ( nd->_color == BLACK );
		mp[ nd ] = tmp;
		if ( tmp[ 0 ] != tmp.back() ) {
			std::cout << "NODE " << nd->_elt.first << std::endl;
			for ( int z : tmp ) std::cout << z << " ";
			std::cout << std::endl;
		}
		return ( ok & ( tmp[ 0 ] == tmp.back() ) );
	}
	// end of checker!
};
