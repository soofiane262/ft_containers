/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:54:01 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/23 18:50:53 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"
#include "redBlackTree.hpp"

#include <cstddef>	// ptrdiff_t
#include <iterator> // bidirectional_iterator_tag

namespace ft {

	template < class T, class NodeType > class rbt_iterator {
	  private:
		template < class T1, class NodeType1, class T2, class NodeType2 >
		friend bool operator==( const ft::rbt_iterator< T1, NodeType1 >&,
								const ft::rbt_iterator< T2, NodeType2 >& );
		template < class T1, class NodeType1, class T2, class NodeType2 >
		friend bool operator!=( const ft::rbt_iterator< T1, NodeType1 >&,
								const ft::rbt_iterator< T2, NodeType2 >& );

	  public:
		/* Member Types ───────────────────────────────────────────────────────────────────── */
		typedef typename ft::iterator_traits< T* >::value_type		value_type;
		typedef typename ft::iterator_traits< T* >::difference_type difference_type;
		typedef typename ft::iterator_traits< T* >::pointer			pointer;
		typedef typename ft::iterator_traits< T* >::reference		reference;
		typedef typename std::bidirectional_iterator_tag			iterator_category;

	  protected:
		NodeType* _nd;

	  public:
		/* ctors ──────────────────────────────────────────────────────────────────────────── */
		rbt_iterator( NodeType* other = NULL ) : _nd( other ) {}
		template < class U, class U_NodeType >
		rbt_iterator( const rbt_iterator< U, U_NodeType >& other ) : _nd( other._nd ) {}
		/* dtor ───────────────────────────────────────────────────────────────────────────── */
		~rbt_iterator( void ) { _nd = NULL; }
		/* assignment ─────────────────────────────────────────────────────────────────────── */
		template < class U, class U_NodeType >
		rbt_iterator& operator=( const rbt_iterator< U, U_NodeType >& other ) {
			_nd = other._nd;
			return *this;
		}
		/* conversion ─────────────────────────────────────────────────────────────────────── */
		reference operator*( void ) const { return _nd->_elt; }
		pointer	  operator->( void ) const { return &( operator*() ); }
		/* operations ─────────────────────────────────────────────────────────────────────── */
		rbt_iterator& operator++( void ) {
			_nd = _nd->next();
			return *this;
		}
		rbt_iterator operator++( int ) {
			rbt_iterator tmp = *this;
			_nd				 = _nd->next();
			return tmp;
		}
		rbt_iterator& operator--( void ) {
			_nd = _nd->previous();
			return *this;
		}
		rbt_iterator operator--( int ) {
			rbt_iterator tmp = *this;
			_nd				 = _nd->previous();
			return tmp;
		}
	};

	template < class T1, class NodeType1, class T2, class NodeType2 >
	bool operator==( const ft::rbt_iterator< T1, NodeType1 >& lhs,
					 const ft::rbt_iterator< T2, NodeType2 >& rhs ) {
		return lhs._nd == rhs._nd;
	}
	template < class T1, class NodeType1, class T2, class NodeType2 >
	bool operator!=( const ft::rbt_iterator< T1, NodeType1 >& lhs,
					 const ft::rbt_iterator< T2, NodeType2 >& rhs ) {
		return lhs._nd != rhs._nd;
	}

} // namespace ft
