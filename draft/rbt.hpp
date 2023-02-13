/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:55:21 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/13 18:45:36 by sel-mars         ###   ########.fr       */
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
	node< T >	*_parent, *_left, *_right;
	node( const T elt, node< T > *parent ) {
		_elt	= elt;
		_color	= RED;
		_rotate = DEFAULT;
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
			 ( ( sibling->_elt < _parent->_elt && sibling->_right &&
				 sibling->_right->_color == RED ) ||
			   ( sibling->_elt > _parent->_elt && sibling->_left &&
				 sibling->_left->_color == RED ) ) )
			return true;
		return false;
	};
	node *RedNiece( void ) {
		if ( !hasRedNiece() ) return NULL;
		node *sibling = getSibling();
		if ( _elt < _parent->_elt ) return sibling->_left;
		return sibling->_right;
	};
};

template < class T > struct output {
	node< T >	*_nd;
	int			 _lvl;
	int			 _spaces;
	int			 _addit;
	int			 _length;
	e_directions _dir;
	static int	 total_lvls;
	static int	 total_diff;
	static int	 _width;
	output( node< T > *nd, int lvl, int length, e_directions dir )
		: _nd( nd ), _lvl( lvl ), _length( length ? length : 1 ), _dir( dir ), _addit( 0 ) {};
};

template < class T > int output< T >::total_lvls = 0;
template < class T > int output< T >::total_diff = 2;
template < class T > int output< T >::_width	 = 0;

template < class T > class rbt {
  private:
	typedef node< T >	node;
	typedef output< T > output;
	void				swapColors( node *&x, node *&y ) {
		   e_colors tmpColor = x->_color;
		   x->_color		 = y->_color;
		   y->_color		 = tmpColor;
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
	node *rotate( node *nd, const bool colorSwap ) {
		node		*ret	= nd;
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
	void _insert( node *&nd, const T elt, node *parent ) {
		if ( !nd ) {
			nd = new node( elt, parent );
			return;
		} else if ( elt < nd->_elt )
			_insert( nd->_left, elt, nd );
		else if ( elt > nd->_elt )
			_insert( nd->_right, elt, nd );
		else
			return;
		nd			  = rotate( nd, true );
		node *sibling = nd->getSibling();
		if ( !nd->_parent ) root->_color = BLACK;
		if ( !nd->_parent || nd->_color == BLACK ||
			 ( ( !nd->_left || nd->_left->_color == BLACK ) &&
			   ( !nd->_right || nd->_right->_color == BLACK ) ) )
			return;
		else if ( !sibling || sibling->_color == BLACK ) {
			if ( nd == nd->_parent->_left && elt < nd->_elt ) nd->_parent->_rotate = RIGHT;
			else if ( nd == nd->_parent->_right && elt > nd->_elt )
				nd->_parent->_rotate = LEFT;
			else if ( nd == nd->_parent->_left && elt > nd->_elt ) {
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
	void fixDoubleBlack( node *nd ) {
		if ( nd->_color != DOUBLE_BLACK ) return;
		else if ( !nd->_parent )
			nd->_color = BLACK;
		else {
			node		*sibling = nd->getSibling();
			e_directions DBdir	 = ( nd->_elt < nd->_parent->_elt ? LEFT : RIGHT );
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
				node *rot			 = rotate( nd->_parent, true );
				nd->_parent			 = ( DBdir == LEFT ? rot->_left : rot->_right );
				fixDoubleBlack( nd );
			}
		}
	};
	void _del( node *&nd, const T elt ) {
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
	};
	void destruct( node *&nd ) {
		if ( !nd ) return;
		destruct( nd->_left );
		destruct( nd->_right );
		delete nd;
		nd = NULL;
	};
	void _getTotalLvls( node *x, const int lvl ) {
		if ( !x ) return;
		else if ( lvl >= output::total_lvls )
			output::total_lvls = lvl + 1;
		_getTotalLvls( x->_left, lvl + 1 );
		_getTotalLvls( x->_right, lvl + 1 );
	};
	void _store( node *x, std::vector< output > &out, const int lvl, e_directions dir ) {
		if ( lvl == output::total_lvls ) return;
		_store( ( x ? x->_left : x ), out, lvl + 1, LEFT );
		std::stringstream ss;
		if ( x ) ss << x->_elt;
		out.push_back( output( x, lvl, ss.str().length(), dir ) );
		_store( ( x ? x->_right : x ), out, lvl + 1, RIGHT );
	};
	void _log( std::vector< output > out ) {
		if ( !out.size() ) {
			std::cout << "empty rbt\n";
			return;
		}
		int indent = 2;
		for ( int l = output::total_lvls - 1, i = -1, lsl = -1, diff = 2; l >= 0;
			  l--, i = -1, lsl = -1, diff *= 2 ) {
			while ( ++i < out.size() ) {
				if ( l != out[ i ]._lvl ) continue;
				if ( lsl == -1 && l == output::total_lvls - 1 ) out[ i ]._spaces = 0;
				else
					out[ i ]._spaces = indent + out[ i ]._addit;
				out[ i ]._addit += out[ i ]._length;
				if ( out[ i ]._dir == RIGHT && out[ i - ( diff / 2 ) ]._dir == RIGHT )
					out[ i - ( diff / 2 ) ]._addit +=
						out[ i ]._addit + ( out[ i ]._length + out[ i - diff ]._length ) / 2;
				if ( lsl == -1 ) indent *= ( indent ? 2 : 1 );
				lsl = i;
			}
			output::total_diff = diff;
		}
		// std::cout << std::setw( 5 ) << "@|" << std::setw( 11 ) << "nb|" << std::setw( 7 ) <<
		// "lvl|"
		// 		  << std::setw( 7 ) << "sp|" << std::setw( 7 ) << "addit|" << '\n';
		// for ( int i = 0; i < out.size(); i++ )
		// 	std::cout << std::setw( 4 ) << i << "|" << std::setw( 10 )
		// 			  << ( out[ i ]._nd ? out[ i ]._nd->_elt : 0 ) << "|" << std::setw( 6 )
		// 			  << out[ i ]._lvl << "|" << std::setw( 6 ) << out[ i ]._spaces << "|"
		// 			  << std::setw( 6 ) << out[ i ]._addit << "|" << '\n';
		for ( int l = 0, i = -1, diff = output::total_diff, width = 0; l < output::total_lvls;
			  l++, i = -1, diff /= 2, width = 0 ) {
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
							  << out[ i ]._nd->_elt << "\e[0m";
				else
					std::cout << ' ';
				width += out[ i ]._length;
			}
			output::_width = std::max( width + 10, output::_width );
			std::cout << '\n';
		}
		std::cout << "\e[2m";
		for ( int i = 0; i < output::_width; i++ ) std::cout << "─";
		std::cout << "\e[22m\n";
	};
	// void _log( node *x, const int lvl ) {
	// 	if ( !x ) return;
	// 	_log( x->_right, lvl + 1 );
	// 	for ( int i = 0; i < lvl * 4; i++ ) std::cout << ' ';
	// 	std::cout << ( x->_color == RED ? "\e[1;31m" : "\e[1;37m" )
	// 			  << ( x->_color == DOUBLE_BLACK ? "\e[4m" : "" ) << x->_elt << "\e[0m\n";
	// 	_log( x->_left, lvl + 1 );
	// };
	node *root;

  public:
	rbt( void ) { root = NULL; };
	rbt( const T n ) { root = new node( n ); };
	~rbt( void ) { destruct( root ); };
	bool find( const T &elt ) {
		if ( !root ) return false;
		else
			return find( *root, elt );
	};
	void insert( const T elt, /* tmp */ const int i ) {
		_insert( root, elt, NULL );
		// checking time!
		std::map< node *, std::vector< int > > mp;
		std::cout << "\e[1;31m";
		assert( check( root, mp ) );
		std::cout << "\e[0m";
		std::cout << "idx\t" << i << "\tINSERTED\t" << elt << "\tSUCCESSFULLY" << std::endl;
	};
	void del( const T elt, /* tmp */ const int i ) {
		_del( root, elt );
		// checking time!
		std::map< node *, std::vector< int > > mp;
		std::cout << "\e[1;31m";
		assert( check( root, mp ) );
		std::cout << "\e[0m";
		std::cout << "idx\t" << i << "\tDELETED\t" << elt << "\tSUCCESSFULLY" << std::endl;
	};
	//
	//
	// tmp
	void log( void ) {
		if ( !root ) return;
		output::total_lvls = 0;
		output::total_diff = 2;
		output::_width	   = 0;
		std::vector< output > out;
		_getTotalLvls( root, 0 );
		_store( root, out, 0, DEFAULT );
		_log( out );
	};

	// checker {made by: jalalium}
	bool check( node *nd, std::map< node *, std::vector< int > > &mp ) {
		bool ok = true;
		if ( nd->_left != NULL ) {
			if ( nd->_elt <= nd->_left->_elt ) {
				std::cout << "LEFT CHILD LARGER OR EQUAL TO PARENT " << nd->_elt << " "
						  << nd->_left->_elt << std::endl;
				return false;
			}
			if ( nd->_color == RED && nd->_left->_color == RED ) {
				std::cout << "RED PARENT WITH RED CHILD: " << nd->_elt << " " << nd->_left->_elt
						  << std::endl;
				return false;
			}
			ok &= check( nd->_left, mp );
		}
		if ( nd->_right != NULL ) {
			if ( nd->_elt >= nd->_right->_elt ) {
				std::cout << "RIGHT CHILD SMALLER OR EQUAL TO PARENT " << nd->_elt << " "
						  << nd->_left->_elt << std::endl;
				return false;
			}
			if ( nd->_color == RED && nd->_right->_color == RED ) {
				std::cout << "RED PARENT WITH RED CHILD: " << nd->_elt << " " << nd->_right->_elt
						  << std::endl;
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
			std::cout << "NODE " << nd->_elt << std::endl;
			for ( int z : tmp ) std::cout << z << " ";
			std::cout << std::endl;
		}
		return ( ok & ( tmp[ 0 ] == tmp.back() ) );
	}
	// end of checker!
};
