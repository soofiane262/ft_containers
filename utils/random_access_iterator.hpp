/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:09:54 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/24 13:22:14 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft {
	template < class T > class random_access_iterator {
	  private:
		template < class FirstType, class SecondType >
		friend bool operator==( const ft::random_access_iterator< FirstType >&	lhs,
								const ft::random_access_iterator< SecondType >& rhs );
		template < class FirstType, class SecondType >
		friend bool operator!=( const ft::random_access_iterator< FirstType >&	lhs,
								const ft::random_access_iterator< SecondType >& rhs );
		template < class FirstType, class SecondType >
		friend bool operator<( const ft::random_access_iterator< FirstType >&  lhs,
							   const ft::random_access_iterator< SecondType >& rhs );
		template < class FirstType, class SecondType >
		friend bool operator>( const ft::random_access_iterator< FirstType >&  lhs,
							   const ft::random_access_iterator< SecondType >& rhs );
		template < class FirstType, class SecondType >
		friend bool operator<=( const ft::random_access_iterator< FirstType >&	lhs,
								const ft::random_access_iterator< SecondType >& rhs );
		template < class FirstType, class SecondType >
		friend bool operator>=( const ft::random_access_iterator< FirstType >&	lhs,
								const ft::random_access_iterator< SecondType >& rhs );

	  protected:
		T* _ptr;

	  public:
		/* Member Types ───────────────────────────────────────────────────────────────────── */
		typedef typename ft::iterator_traits< T* >::value_type		  value_type;
		typedef typename ft::iterator_traits< T* >::difference_type	  difference_type;
		typedef typename ft::iterator_traits< T* >::pointer			  iterator_type;
		typedef typename ft::iterator_traits< T* >::pointer			  pointer;
		typedef typename ft::iterator_traits< T* >::reference		  reference;
		typedef typename ft::iterator_traits< T* >::iterator_category iterator_category;
		/* ctors ──────────────────────────────────────────────────────────────────────────── */
		random_access_iterator( void ) : _ptr( NULL ) {} // ctor_default
		template < class Iter > random_access_iterator( const Iter& other )
			: _ptr( &*other ) {} // ctor_copy
		/* dtor ───────────────────────────────────────────────────────────────────────────── */
		~random_access_iterator( void ) { _ptr = NULL; } // dtor
		/* assignment ─────────────────────────────────────────────────────────────────────── */
		random_access_iterator& operator=( random_access_iterator& other ) {
			if ( this != &other ) _ptr = other._ptr;
			return *this;
		} // assignment
		random_access_iterator& operator=( const random_access_iterator& other ) {
			if ( this != &other ) _ptr = other._ptr;
			return *this;
		} // const assignment
		/* conversion ─────────────────────────────────────────────────────────────────────── */
		reference operator*( void ) const { return *_ptr; }				// operator *
		pointer	  operator->( void ) const { return &( operator*() ); } // operator ->
		/* operations ─────────────────────────────────────────────────────────────────────── */
		random_access_iterator& operator++( void ) {
			++_ptr;
			return *this;
		} // pre ++
		random_access_iterator operator++( int ) {
			random_access_iterator tmp = *this;
			++_ptr;
			return tmp;
		} // post ++
		random_access_iterator& operator--( void ) {
			--_ptr;
			return *this;
		} // pre --
		random_access_iterator operator--( int ) {
			random_access_iterator tmp = *this;
			--_ptr;
			return tmp;
		} // post -*
		random_access_iterator operator+( difference_type n ) const {
			return _ptr + n;
		} // operator + n
		random_access_iterator operator-( difference_type n ) const {
			return _ptr - n;
		} // operator - n
		random_access_iterator& operator+=( difference_type n ) {
			_ptr += n;
			return *this;
		} // operator +=
		random_access_iterator& operator-=( difference_type n ) {
			_ptr -= n;
			return *this;
		} // operator -=
		difference_type operator-( const random_access_iterator& other ) const {
			return _ptr - other._ptr;
		}																	  // operator - other
		reference operator[]( difference_type n ) const { return _ptr[ n ]; } // operator[]
	};
	template < class FirstType, class SecondType >
	bool operator==( const ft::random_access_iterator< FirstType >&	 lhs,
					 const ft::random_access_iterator< SecondType >& rhs ) {
		return lhs._ptr == rhs._ptr;
	} // operator ==
	template < class FirstType, class SecondType >
	bool operator!=( const ft::random_access_iterator< FirstType >&	 lhs,
					 const ft::random_access_iterator< SecondType >& rhs ) {
		return lhs._ptr != rhs._ptr;
	} // operator !=
	template < class FirstType, class SecondType >
	bool operator<( const ft::random_access_iterator< FirstType >&	lhs,
					const ft::random_access_iterator< SecondType >& rhs ) {
		return lhs._ptr < rhs._ptr;
	} // operator <
	template < class FirstType, class SecondType >
	bool operator>( const ft::random_access_iterator< FirstType >&	lhs,
					const ft::random_access_iterator< SecondType >& rhs ) {
		return lhs._ptr > rhs._ptr;
	} // operator >
	template < class FirstType, class SecondType >
	bool operator<=( const ft::random_access_iterator< FirstType >&	 lhs,
					 const ft::random_access_iterator< SecondType >& rhs ) {
		return lhs._ptr <= rhs._ptr;
	} // operator <=
	template < class FirstType, class SecondType >
	bool operator>=( const ft::random_access_iterator< FirstType >&	 lhs,
					 const ft::random_access_iterator< SecondType >& rhs ) {
		return lhs._ptr >= rhs._ptr;
	} // operator >=
	template < class Iterator > random_access_iterator< Iterator >
	operator+( typename random_access_iterator< Iterator >::difference_type n,
			   const random_access_iterator< Iterator >&					it ) {
		return it + n;
	} // operator n + it
} // namespace ft
