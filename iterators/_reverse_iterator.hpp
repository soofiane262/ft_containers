/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:28:33 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/22 13:13:20 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft {

	template < class Iterator > class _reverse_iterator {
	  protected:
		Iterator _iter;

	  public:
		typedef Iterator													 iterator_type;
		typedef typename iterator_traits< iterator_type >::difference_type	 difference_type;
		typedef typename iterator_traits< iterator_type >::value_type		 value_type;
		typedef typename iterator_traits< iterator_type >::pointer			 pointer;
		typedef typename iterator_traits< iterator_type >::reference		 reference;
		typedef typename iterator_traits< iterator_type >::iterator_category iterator_category;
		/* ------------------------------ Constructor ----------------------------- */
		_reverse_iterator( void ) {};
		explicit _reverse_iterator( iterator_type it ) : _iter( it ) {};
		template < class Iter > _reverse_iterator( const _reverse_iterator< Iter >& rev_it )
			: _iter( rev_it._iter ) {};
		/* ------------------------------ Conversion ------------------------------ */
		iterator_type base( void ) const { return ( _iter ); };
		reference	  operator*( void ) const {
			iterator_type tmp = _iter;
			return *--tmp;
		};
		pointer operator->( void ) const { return &( operator*() ); };
		/* ------------------------------ Operations ------------------------------ */
		_reverse_iterator& operator++( void ) {
			--_iter;
			return *this;
		};
		_reverse_iterator operator++( int ) {
			_reverse_iterator tmp = *this;
			--_iter;
			return tmp;
		};
		_reverse_iterator& operator--( void ) {
			++_iter;
			return *this;
		};
		_reverse_iterator operator--( int ) {
			_reverse_iterator tmp = *this;
			++_iter;
			return tmp;
		};

		_reverse_iterator operator+( difference_type n ) const {
			return _reverse_iterator( _iter - n );
		};
		_reverse_iterator& operator+=( difference_type n ) {
			_iter -= n;
			return *this;
		};
		_reverse_iterator operator-( difference_type n ) const {
			return _reverse_iterator( _iter + n );
		};
		_reverse_iterator& operator-=( difference_type n ) {
			_iter += n;
			return *this;
		};

		reference operator[]( difference_type n ) const { return ( _iter[ -n - 1 ] ); };
	};

	template < class Iterator > bool operator==( const _reverse_iterator< Iterator >& lhs,
												 const _reverse_iterator< Iterator >& rhs ) {
		return ( lhs.base() == rhs.base() );
	};
	template < class Iterator > bool operator!=( const _reverse_iterator< Iterator >& lhs,
												 const _reverse_iterator< Iterator >& rhs ) {
		return ( lhs.base() != rhs.base() );
	};
	template < class Iterator > bool operator<( const _reverse_iterator< Iterator >& lhs,
												const _reverse_iterator< Iterator >& rhs ) {
		return ( lhs.base() > rhs.base() );
	};
	template < class Iterator > bool operator<=( const _reverse_iterator< Iterator >& lhs,
												 const _reverse_iterator< Iterator >& rhs ) {
		return ( lhs.base() >= rhs.base() );
	};
	template < class Iterator > bool operator>( const _reverse_iterator< Iterator >& lhs,
												const _reverse_iterator< Iterator >& rhs ) {
		return ( lhs.base() < rhs.base() );
	};
	template < class Iterator > bool operator>=( const _reverse_iterator< Iterator >& lhs,
												 const _reverse_iterator< Iterator >& rhs ) {
		return ( lhs.base() <= rhs.base() );
	};

	template < class Iterator > typename _reverse_iterator< Iterator >::difference_type
	operator-( const _reverse_iterator< Iterator >& lhs,
			   const _reverse_iterator< Iterator >& rhs ) {
		return ( rhs.base() - lhs.base() );
	};

	template < class Iterator > _reverse_iterator< Iterator >
	operator+( typename _reverse_iterator< Iterator >::difference_type n,
			   const _reverse_iterator< Iterator >&					   rev_it ) {
		return _reverse_iterator< Iterator >( rev_it - n );
	};

} // namespace ft