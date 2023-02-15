/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:09:54 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/15 19:45:27 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../utils/utils.hpp"
#include "iterator_traits.hpp"

namespace ft {
	template < class T > struct is_pointer {
		static const bool value = false;
	};

	template < class T > struct is_pointer< T* > {
		static const bool value = true;
	};
	template < class T > struct is_pointer< T* const > {
		static const bool value = true;
	};
	template < class T > class vec_iterator {
	  private:
		template < class T_Iter, class U_Iter > friend bool operator==(
			const typename ft::enable_if< !ft::is_pointer< T_Iter >::value, T_Iter >::type*& lhs,
			const U_Iter*&																	 rhs );
		template < class T_Iter, class U_Iter > friend bool operator!=(
			const typename ft::enable_if< !ft::is_pointer< T_Iter >::value, T_Iter >::type*& lhs,
			const U_Iter*&																	 rhs );
		template < class T_Iter, class U_Iter >
		friend bool operator==( const T_Iter& lhs, const U_Iter& rhs );
		template < class T_Iter, class U_Iter >
		friend bool operator!=( const T_Iter& lhs, const U_Iter& rhs );
		template < class T_Iter, class U_Iter >
		friend bool operator<( const T_Iter& lhs, const U_Iter& rhs );
		template < class T_Iter, class U_Iter >
		friend bool operator>( const T_Iter& lhs, const U_Iter& rhs );
		template < class T_Iter, class U_Iter >
		friend bool operator<=( const T_Iter& lhs, const U_Iter& rhs );
		template < class T_Iter, class U_Iter >
		friend bool operator>=( const T_Iter& lhs, const U_Iter& rhs );

	  protected:
		T* _ptr;

	  public:
		typedef typename iterator_traits< T* >::value_type		  value_type;
		typedef typename iterator_traits< T* >::difference_type	  difference_type;
		typedef typename iterator_traits< T* >::pointer			  pointer;
		typedef typename iterator_traits< T* >::reference		  reference;
		typedef typename iterator_traits< T* >::iterator_category iterator_category;
		/* ------------------------------ Constructor ----------------------------- */
		vec_iterator( void ) { _ptr = NULL; }
		template < class Iter > vec_iterator( const Iter& other ) : _ptr( &*other ) {}
		/* ------------------------------ Destructor ------------------------------ */
		~vec_iterator( void ) { _ptr = NULL; }
		/* ----------------------- Copy assignment operator ----------------------- */
		vec_iterator& operator=( vec_iterator& other ) {
			if ( this != &other ) _ptr = other._ptr;
			return *this;
		}
		vec_iterator& operator=( const vec_iterator& other ) {
			if ( this != &other ) _ptr = other._ptr;
			return *this;
		}
		/* ------------------------------ Conversion ------------------------------ */
		reference operator*( void ) const { return *_ptr; }
		pointer	  operator->( void ) const { return &( operator*() ); }

		vec_iterator& operator++( void ) {
			++_ptr;
			return *this;
		}
		vec_iterator operator++( int ) {
			vec_iterator tmp = *this;
			++_ptr;
			return tmp;
		}
		vec_iterator& operator--( void ) {
			--_ptr;
			return *this;
		}
		vec_iterator operator--( int ) {
			vec_iterator tmp = *this;
			--_ptr;
			return tmp;
		}

		vec_iterator  operator+( difference_type n ) const { return _ptr + n; }
		vec_iterator  operator-( difference_type n ) const { return _ptr - n; }
		vec_iterator& operator+=( difference_type n ) {
			_ptr += n;
			return *this;
		}
		vec_iterator& operator-=( difference_type n ) {
			_ptr -= n;
			return *this;
		}
		difference_type operator-( const vec_iterator& other ) const { return _ptr - other._ptr; }
		reference		operator[]( difference_type n ) const { return _ptr[ n ]; }
	};

	template < class T_Iter, class U_Iter >
	bool operator==( const T_Iter& lhs, const U_Iter& rhs ) {
		return lhs._ptr == rhs._ptr;
	}
	template < class T_Iter, class U_Iter >
	bool operator!=( const T_Iter& lhs, const U_Iter& rhs ) {
		return lhs._ptr != rhs._ptr;
	}
	template < class T_Iter, class U_Iter > bool operator==(
		const typename ft::enable_if< !ft::is_pointer< T_Iter >::value, T_Iter >::type*& lhs,
		const U_Iter*&																	 rhs ) {
		return lhs->_ptr == rhs->_ptr;
	}
	template < class T_Iter, class U_Iter > bool operator!=(
		const typename ft::enable_if< !ft::is_pointer< T_Iter >::value, T_Iter >::type*& lhs,
		const U_Iter*&																	 rhs ) {
		return lhs->_ptr != rhs->_ptr;
	}
	template < class T_Iter, class U_Iter > bool operator<( const T_Iter& lhs, const U_Iter& rhs ) {
		return lhs._ptr < rhs._ptr;
	}
	template < class T_Iter, class U_Iter > bool operator>( const T_Iter& lhs, const U_Iter& rhs ) {
		return lhs._ptr > rhs._ptr;
	}
	template < class T_Iter, class U_Iter >
	bool operator<=( const T_Iter& lhs, const U_Iter& rhs ) {
		return lhs._ptr <= rhs._ptr;
	}
	template < class T_Iter, class U_Iter >
	bool operator>=( const T_Iter& lhs, const U_Iter& rhs ) {
		return lhs._ptr >= rhs._ptr;
	}
	template < class Iterator >
	vec_iterator< Iterator > operator+( typename vec_iterator< Iterator >::difference_type n,
										const vec_iterator< Iterator >&					   it ) {
		return it + n;
	}
} // namespace ft
