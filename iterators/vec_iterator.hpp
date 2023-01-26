/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:09:54 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/26 20:00:05 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft {

	template < class T > class vec_iterator {
	  private:
		T* _ptr;

	  public:
		typedef typename iterator_traits< T* >::value_type		  value_type;
		typedef typename iterator_traits< T* >::difference_type	  difference_type;
		typedef typename iterator_traits< T* >::pointer			  pointer;
		typedef typename iterator_traits< T* >::reference		  reference;
		typedef typename iterator_traits< T* >::iterator_category iterator_category;
		vec_iterator( void ) { _ptr = NULL; };
		template < class iter > vec_iterator( const iter& other ) : _ptr( &*other ) {};
		vec_iterator& operator=( vec_iterator& other ) {
			if ( this != &other ) _ptr = other._ptr;
			return *this;
		};
		vec_iterator& operator=( const vec_iterator& other ) {
			if ( this != &other ) _ptr = other._ptr;
			return *this;
		};
		~vec_iterator( void ) { _ptr = NULL; };
		vec_iterator& operator++( void ) {
			_ptr++;
			return *this;
		};
		vec_iterator operator++( int ) {
			vec_iterator tmp = *this;
			++( *this );
			return tmp;
		};
		vec_iterator& operator--( void ) {
			_ptr--;
			return *this;
		};
		vec_iterator operator--( int ) {
			vec_iterator tmp = *this;
			_ptr--;
			return tmp;
		};
		vec_iterator  operator+( difference_type n ) const { return _ptr + n; };
		vec_iterator  operator-( difference_type n ) const { return _ptr - n; };
		vec_iterator& operator+=( difference_type n ) {
			_ptr += n;
			return *this;
		};
		vec_iterator& operator-=( difference_type n ) {
			_ptr -= n;
			return *this;
		};
		difference_type operator-( const vec_iterator& other ) const { return _ptr - other._ptr; };
		reference		operator*( void ) const { return *_ptr; };
		pointer			operator->( void ) const { return _ptr; };
		reference		operator[]( difference_type n ) const { return _ptr[ n ]; };
		bool operator==( const vec_iterator& other ) const { return _ptr == other._ptr; };
		bool operator!=( const vec_iterator& other ) const { return _ptr != other._ptr; };
		bool operator<( const vec_iterator& other ) const { return _ptr < other._ptr; };
		bool operator>( const vec_iterator& other ) const { return _ptr > other._ptr; };
		bool operator<=( const vec_iterator& other ) const { return _ptr <= other._ptr; };
		bool operator>=( const vec_iterator& other ) const { return _ptr >= other._ptr; };
	};

} // namespace ft