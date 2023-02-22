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

namespace ft {

	template < class Iterator > class reverse_iterator {
	  protected:
		Iterator _iter;

	  public:
		typedef Iterator								  iterator_type;
		typedef typename iterator_type::difference_type	  difference_type;
		typedef typename iterator_type::value_type		  value_type;
		typedef typename iterator_type::pointer			  pointer;
		typedef typename iterator_type::reference		  reference;
		typedef typename iterator_type::iterator_category iterator_category;
		/* ctors ──────────────────────────────────────────────────────────────────────────── */
		reverse_iterator( void ) : _iter( iterator_type() ) {}
		explicit reverse_iterator( iterator_type it ) : _iter( it ) {}
		template < class Iter > reverse_iterator( const reverse_iterator< Iter >& rev_it )
			: _iter( rev_it.base() ) {}
		/* conversion ─────────────────────────────────────────────────────────────────────── */
		iterator_type base( void ) const { return _iter; }
		reference	  operator*( void ) const {
			iterator_type tmp = _iter;
			return *--tmp;
		}
		pointer	  operator->( void ) const { return &operator*(); }
		reference operator[]( difference_type n ) const { return _iter[ -n - 1 ]; }
		/* operations ─────────────────────────────────────────────────────────────────────── */
		reverse_iterator& operator++( void ) {
			--_iter;
			return *this;
		}
		reverse_iterator operator++( int ) {
			reverse_iterator tmp = *this;
			--_iter;
			return tmp;
		}
		reverse_iterator& operator--( void ) {
			++_iter;
			return *this;
		}
		reverse_iterator operator--( int ) {
			reverse_iterator tmp = *this;
			++_iter;
			return tmp;
		}
		reverse_iterator operator+( difference_type n ) const {
			return reverse_iterator( _iter - n );
		}
		reverse_iterator& operator+=( difference_type n ) {
			_iter -= n;
			return *this;
		}
		reverse_iterator operator-( difference_type n ) const {
			return reverse_iterator( _iter + n );
		}
		reverse_iterator& operator-=( difference_type n ) {
			_iter += n;
			return *this;
		}
	};

	template < class T_Iter, class U_Iter > bool
	operator==( const reverse_iterator< T_Iter >& lhs, const reverse_iterator< U_Iter >& rhs ) {
		return ( lhs.base() == rhs.base() );
	}
	template < class T_Iter, class U_Iter > bool
	operator!=( const reverse_iterator< T_Iter >& lhs, const reverse_iterator< U_Iter >& rhs ) {
		return ( lhs.base() != rhs.base() );
	}
	template < class T_Iter, class U_Iter >
	bool operator<( const reverse_iterator< T_Iter >& lhs, const reverse_iterator< U_Iter >& rhs ) {
		return ( lhs.base() > rhs.base() );
	}
	template < class T_Iter, class U_Iter > bool
	operator<=( const reverse_iterator< T_Iter >& lhs, const reverse_iterator< U_Iter >& rhs ) {
		return ( lhs.base() >= rhs.base() );
	}
	template < class T_Iter, class U_Iter >
	bool operator>( const reverse_iterator< T_Iter >& lhs, const reverse_iterator< U_Iter >& rhs ) {
		return ( lhs.base() < rhs.base() );
	}
	template < class T_Iter, class U_Iter > bool
	operator>=( const reverse_iterator< T_Iter >& lhs, const reverse_iterator< U_Iter >& rhs ) {
		return ( lhs.base() <= rhs.base() );
	}
	template < class Iterator > typename reverse_iterator< Iterator >::difference_type
	operator-( const reverse_iterator< Iterator >& lhs, const reverse_iterator< Iterator >& rhs ) {
		return ( rhs.base() - lhs.base() );
	}
	template < class Iterator > reverse_iterator< Iterator >
	operator+( typename reverse_iterator< Iterator >::difference_type n,
			   const reverse_iterator< Iterator >&					  rev_it ) {
		return reverse_iterator< Iterator >( rev_it + n );
	}

} // namespace ft
