/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:02:48 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/24 13:18:26 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>	// ptrdiff_t
#include <iterator> // random_access_iterator_tag

namespace ft {
	template < class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*,
			   class Reference = T& >
	struct iterator {
		typedef T		  value_type;
		typedef Distance  difference_type;
		typedef Pointer	  pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	}; // struct iterator
	template < class Iterator > class iterator_traits {
	  public:
		typedef typename Iterator::difference_type	 difference_type;
		typedef typename Iterator::value_type		 value_type;
		typedef typename Iterator::pointer			 pointer;
		typedef typename Iterator::reference		 reference;
		typedef typename Iterator::iterator_category iterator_category;
	}; // class iterator_traits
	template < class T > class iterator_traits< T* > {
	  public:
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag iterator_category;
	}; // class iterator_traits< T* >
	template < class T > class iterator_traits< const T* > {
	  public:
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag iterator_category;
	}; // class iterator_traits< const T* >
} // namespace ft
