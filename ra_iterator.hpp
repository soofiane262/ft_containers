/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:09:54 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/20 21:17:54 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cstddef>

namespace ft {

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
		struct iterator {
			typedef T         value_type;
			typedef Distance  difference_type;
			typedef Pointer   pointer;
			typedef Reference reference;
			typedef Category  iterator_category;
		};
		
		template <class Iterator> class iterator_traits {

		};
		
		template <class T> class iterator_traits<T*> {

		};
		
		template <class T> class iterator_traits<const T*> {

		};

	template< class T > class ra_iterator {
		ra_iterator();
		ra_iterator( const iterator& other );
		~ra_iterator();
		ra_iterator& operator++();
		ra_iterator operator++(int);
		ra_iterator& operator--();
		ra_iterator operator--(int);
		ra_iterator operator+(difference_type n) const;
		ra_iterator operator-(difference_type n) const;
		difference_type operator-(const ra_iterator& other) const;
		reference operator*() const;
		pointer operator->() const;
		reference operator[](difference_type n) const;
		bool operator==(const ra_iterator& other) const;
		bool operator!=(const ra_iterator& other) const;
		bool operator<(const ra_iterator& other) const;
		bool operator>(const ra_iterator& other) const;
		bool operator<=(const ra_iterator& other) const;
		bool operator>=(const ra_iterator& other) const;
	};

}