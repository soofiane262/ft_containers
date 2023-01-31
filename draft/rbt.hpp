/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:55:21 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/31 19:25:39 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <iostream>

#define BLACK_NODE true
#define RED_NODE   false

template < class T > struct node {
	T		   _elt;
	int		   _lvl;
	bool	   _color;
	node< T > *left, *right;
	node( const T &elt = T() ) {
		_elt   = elt;
		_lvl   = 0;
		_color = BLACK_NODE;
		left   = NULL;
		right  = NULL;
		// left->_color  = BLACK_NODE;
		// right->_color = BLACK_NODE;
	};
};

template < class T > class rbt {
  private:
	int lvl( node< T > *nd ) {
		if ( !nd ) return -1;
		return nd->_lvl;
	};
	int getBalance( node< T > *nd ) {
		if ( !nd ) return 0;
		return lvl( nd->left ) - lvl( nd->right );
	};
	void rightRotation( node< T > *&nd ) {
		struct node< T > *l = nd->left, *lr = l->right;
		l->right = nd;
		nd->left = lr;
		nd->_lvl = std::max( lvl( nd->left ), lvl( nd->right ) ) + 1;
		l->_lvl	 = std::max( lvl( l->left ), lvl( l->right ) ) + 1;
		nd		 = l;
	};
	void leftRotation( node< T > *&nd ) {
		struct node< T > *r = nd->right, *rl = r->left;
		r->left	  = nd;
		nd->right = rl;
		nd->_lvl  = std::max( lvl( nd->left ), lvl( nd->right ) ) + 1;
		r->_lvl	  = std::max( lvl( r->left ), lvl( r->right ) ) + 1;
		nd		  = r;
	};
	void balance( node< T > *&nd ) {
		nd->_lvl = std::max( lvl( nd->left ), lvl( nd->right ) ) + 1;
		int bal	 = getBalance( nd );
		if ( bal > 1 && nd->left->left ) rightRotation( nd );
		else if ( bal > 1 && nd->left->right ) {
			leftRotation( nd->left );
			rightRotation( nd );
		} else if ( bal < -1 && nd->right->right )
			leftRotation( nd );
		else if ( bal < -1 && nd->right->left ) {
			rightRotation( nd->right );
			leftRotation( nd );
		}
	}
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
	void _insert( node< T > *&nd, const T &elt ) {
		if ( !nd ) {
			nd = new node< T >( elt );
			return;
		} else if ( elt < nd->_elt )
			_insert( nd->left, elt );
		else if ( elt > nd->_elt )
			_insert( nd->right, elt );
		else
			return;
		balance( nd );
	};
	void _del( struct node< T > *&nd, const T &elt ) {
		if ( !nd ) return;
		else if ( elt < nd->_elt )
			_del( nd->left, elt );
		else if ( elt > nd->_elt )
			_del( nd->right, elt );
		else {
			if ( !nd->left && !nd->right ) {
				delete nd;
				nd = NULL;
				return;
			} else if ( !nd->left || !nd->right ) {
				node< T > *tmp = nd->left ? nd->left : nd->right;
				tmp->_lvl	   = std::max( lvl( nd->left ), lvl( nd->right ) );
				delete nd;
				nd = tmp;
				return;
			} else {
				node< T > *tmp = nd->right;
				while ( tmp->left ) tmp = tmp->left;
				nd->_elt = tmp->_elt;
				_del( nd->right, nd->_elt );
				return;
			}
		}
		balance( nd );
	};
	void destruct( node< T > *&nd ) {
		if ( nd->left ) destruct( nd->left );
		if ( nd->right ) destruct( nd->right );
		delete nd;
		nd = NULL;
	};
	node< T > *root;

  public:
	rbt( void ) { root = NULL; };
	rbt( const T &n ) { root = new node< T >( n ); };
	~rbt( void ) { destruct( root ); };
	void insert( const T &elt ) { _insert( root, elt ); };
	bool find( const T &elt ) {
		if ( !root ) return false;
		else
			return find( *root, elt );
	};
	void log( void );
	void del( const T &elt ) { _del( root, elt ); };
};
