/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:54:01 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/24 13:23:30 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

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
		template < class, class > friend class rbt_iterator;

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
		rbt_iterator( NodeType* other = NULL ) : _nd( other ) {} // ctor_default
		template < class U, class U_NodeType >
		rbt_iterator( const rbt_iterator< U, U_NodeType >& other )
			: _nd( other._nd ) {} // ctor_copy
		/* dtor ───────────────────────────────────────────────────────────────────────────── */
		~rbt_iterator( void ) { _nd = NULL; } // dtor
		/* assignment ─────────────────────────────────────────────────────────────────────── */
		template < class U, class U_NodeType >
		rbt_iterator& operator=( const rbt_iterator< U, U_NodeType >& other ) {
			_nd = other._nd;
			return *this;
		} // assignment
		/* conversion ─────────────────────────────────────────────────────────────────────── */
		reference operator*( void ) const { return _nd->_elt; }			// operator *
		pointer	  operator->( void ) const { return &( operator*() ); } // operator ->
		/* operations ─────────────────────────────────────────────────────────────────────── */
		rbt_iterator& operator++( void ) {
			_nd = _nd->next();
			return *this;
		} // pre ++
		rbt_iterator operator++( int ) {
			rbt_iterator tmp = *this;
			_nd				 = _nd->next();
			return tmp;
		} // post ++
		rbt_iterator& operator--( void ) {
			_nd = _nd->previous();
			return *this;
		} // pre --
		rbt_iterator operator--( int ) {
			rbt_iterator tmp = *this;
			_nd				 = _nd->previous();
			return tmp;
		} // post --
	};
	template < class T1, class NodeType1, class T2, class NodeType2 >
	bool operator==( const ft::rbt_iterator< T1, NodeType1 >& lhs,
					 const ft::rbt_iterator< T2, NodeType2 >& rhs ) {
		return lhs._nd == rhs._nd;
	} // operator ==
	template < class T1, class NodeType1, class T2, class NodeType2 >
	bool operator!=( const ft::rbt_iterator< T1, NodeType1 >& lhs,
					 const ft::rbt_iterator< T2, NodeType2 >& rhs ) {
		return lhs._nd != rhs._nd;
	} // operator !=
} // namespace ft
