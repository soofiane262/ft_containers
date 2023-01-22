/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:02:48 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/22 18:05:27 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <cstddef>
# include <iterator>

namespace ft {

	template <	class Category,
				class T,
				class Distance = std::ptrdiff_t,
				class Pointer = T*,
				class Reference = T&
		> struct iterator {
			typedef T         value_type;			// iterator::value_type
			typedef Distance  difference_type;		// iterator::difference_type
			typedef Pointer   pointer;				// iterator::pointer
			typedef Reference reference;			// iterator::reference
			typedef Category  iterator_category;	// iterator::iterator_category
		};

		template < class Iterator > class iterator_traits {
			public:
				typedef typename Iterator::value_type         	value_type;
				typedef typename Iterator::difference_type  	difference_type;
				typedef typename Iterator::pointer   			pointer;
				typedef typename Iterator::reference 			reference;
				typedef typename Iterator::iterator_category	iterator_category;
		};

		template < class T > class iterator_traits < T* > {
			public:
				typedef T         						value_type;
				typedef std::ptrdiff_t  				difference_type;
				typedef T*   							pointer;
				typedef T& 								reference;
				typedef std::random_access_iterator_tag	iterator_category;
		};

		template < class T > class iterator_traits < const T* > {
			public:
				typedef const T         				value_type;
				typedef std::ptrdiff_t  				difference_type;
				typedef const T*   						pointer;
				typedef const T& 						reference;
				typedef std::random_access_iterator_tag	iterator_category;
		};

}