/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:18:08 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/17 10:11:59 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../utils/utils.hpp"

#include <cstddef>
#include <functional>
#include <memory>

namespace ft {
	template < class Key, class T, class Compare = std::less< Key >,
			   class Allocator = std::allocator< ft::pair< const Key, T > > >
	class map {
	  public:
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                    Member Types                                    */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		typedef Key									key_type;
		typedef T									mapped_type;
		typedef ft::pair< const Key, T >			value_type;
		typedef Compare								key_compare;
		typedef Allocator							allocator_type;
		typedef std::size_t							size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef typename Allocator::reference		reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		// typedef implementation defined					iterator;
		// typedef implementation defined					const_iterator;
		// typedef std::reverse_iterator< iterator >		reverse_iterator;
		// typedef std::reverse_iterator< const_iterator > const_reverse_iterator;
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                             Mmeber Class value_compare                             */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		class value_compare : public std::binary_function< value_type, value_type, bool > {
			friend class map;

		  protected:
			Compare comp;
			value_compare( Compare c ) : comp( c ) {}

		  public:
			bool operator()( const value_type& x, const value_type& y ) const {
				return comp( x.first, y.first );
			}
		}; // class value_compare
	};	   // class map
} // namespace ft