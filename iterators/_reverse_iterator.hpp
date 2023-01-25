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

	template < class T > class _reverse_iterator {
	  private:
		T _iter;
		// _reverse_iterator( const long x ) { (void)x; };

	  public:
		typedef T															 iterator_type;
		typedef typename iterator_traits< iterator_type >::value_type		 value_type;
		typedef typename iterator_traits< iterator_type >::difference_type	 difference_type;
		typedef typename iterator_traits< iterator_type >::pointer			 pointer;
		typedef typename iterator_traits< iterator_type >::reference		 reference;
		typedef typename iterator_traits< iterator_type >::iterator_category iterator_category;
		_reverse_iterator( void ) : _iter() {};
		explicit _reverse_iterator( iterator_type it ) : _iter( it ) {};
		template < class Iter > _reverse_iterator( const _reverse_iterator< Iter >& rev_it )
			: _iter( rev_it._iter ) {};
		iterator_type	  base( void ) const { return ( _iter ); };
		reference		  operator*( void ) const { return ( *( base() - 1 ) ); };
		_reverse_iterator operator+( difference_type n ) const {
			return _reverse_iterator( _iter - n );
		};
		_reverse_iterator& operator++( void ) {
			_iter--;
			return ( *this );
		};
		_reverse_iterator operator++( int ) {
			_reverse_iterator tmp = *this;
			++( *this );
			return ( tmp );
		};
		_reverse_iterator& operator+=( difference_type n ) {
			_iter -= n;
			return ( *this );
		};
		_reverse_iterator operator-( difference_type n ) const {
			return _reverse_iterator( _iter + n );
		};
		_reverse_iterator& operator--( void ) {
			_iter++;
			return ( *this );
		};
		_reverse_iterator operator--( int ) {
			_reverse_iterator tmp = *this;
			--( *this );
			return ( tmp );
		};
		_reverse_iterator& operator-=( difference_type n ) {
			_iter += n;
			return ( *this );
		};
		pointer	  operator->( void ) const { return &( operator*() ); }
		reference operator[]( difference_type n ) const { return ( base()[ -n - 1 ] ); };
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

	template < class Iterator > _reverse_iterator< Iterator >
	operator+( typename _reverse_iterator< Iterator >::difference_type n,
			   const _reverse_iterator< Iterator >&					   rev_it ) {
		rev_it + n;
	};

	template < class Iterator > typename _reverse_iterator< Iterator >::difference_type
	operator-( const _reverse_iterator< Iterator >& lhs,
			   const _reverse_iterator< Iterator >& rhs ) {
		return ( lhs.base() - rhs.base() );
	};

} // namespace ft