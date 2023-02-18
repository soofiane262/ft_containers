/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:18:08 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/18 17:30:41 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../utils/red_black_tree.hpp"
#include "../utils/utils.hpp"

#include <cstddef>	  // size_t - ptrdiff_t
#include <functional> // less
#include <memory>	  // allocator

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
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                             Construct / Copy / Destroy                             */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		explicit map( const Compare& comp = Compare(),
					  const Allocator&	  = Allocator() ); // ctor_default
		template < class InputIterator > map( InputIterator first, InputIterator last,
											  const Compare& comp = Compare(),
											  const Allocator&	  = Allocator() ); // ctor_range
		map( const ft::map< Key, T, Compare, Allocator >& x );					// ctor_copy
		~map();																	// dtor
		map< Key, T, Compare, Allocator >&
		operator=( const map< Key, T, Compare, Allocator >& x ); // assignemnt
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                      Iterators                                     */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		// iterator			   begin();		   // begin
		// const_iterator		   begin() const;  // const_begin
		// iterator			   end();		   // end
		// const_iterator		   end() const;	   // const_end
		// reverse_iterator	   rbegin();	   // rbegin
		// const_reverse_iterator rbegin() const; // const_rbegin
		// reverse_iterator	   rend();		   // rend
		// const_reverse_iterator rend() const;   // const_rend
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                              Capacity - Element Access                             */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		bool	  empty() const;	// empty
		size_type size() const;		// size
		size_type max_size() const; // max_size
		T&		  operator[]( const key_type& x );
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                      Modifiers                                     */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		// ft::pair< iterator, bool >			  insert( const value_type& x );
		// iterator							  insert( iterator position, const value_type& x );
		template < class InputIterator > void insert( InputIterator first, InputIterator last );
		// void								  erase( iterator position );
		size_type erase( const key_type& x );
		// void								  erase( iterator first, iterator last );
		void swap( map< Key, T, Compare, Allocator >& );
		void clear();
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                      Observers                                     */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		key_compare	  key_comp() const;
		value_compare value_comp() const;
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                   Map Operations:                                  */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		// iterator find( const key_type& x ); // find
		// const_iterator find( const key_type& x ) const; // const_find
		size_type count( const key_type& x ) const; // count
		// iterator	   lower_bound( const key_type& x ); // lower_bound
		// const_iterator lower_bound( const key_type& x ) const; // const_lower_bound
		// iterator upper_bound( const key_type& x ); // upper_bound
		// const_iterator			   upper_bound( const key_type& x ) const; // const_upper_bound
		// pair< iterator, iterator > equal_range( const key_type& x ); // equal_range
		// pair< const_iterator, const_iterator > equal_range( const key_type& x ) const; //
		// const_equal_range
	}; // class map
	template < class Key, class T, class Compare, class Allocator >
	bool operator==( const map< Key, T, Compare, Allocator >& x,
					 const map< Key, T, Compare, Allocator >& y ); // operator==
	template < class Key, class T, class Compare, class Allocator >
	bool operator<( const map< Key, T, Compare, Allocator >& x,
					const map< Key, T, Compare, Allocator >& y ); // operator <
	template < class Key, class T, class Compare, class Allocator >
	bool operator!=( const map< Key, T, Compare, Allocator >& x,
					 const map< Key, T, Compare, Allocator >& y ); // operator !=
	template < class Key, class T, class Compare, class Allocator >
	bool operator>( const map< Key, T, Compare, Allocator >& x,
					const map< Key, T, Compare, Allocator >& y ); // operator >
	template < class Key, class T, class Compare, class Allocator >
	bool operator>=( const map< Key, T, Compare, Allocator >& x,
					 const map< Key, T, Compare, Allocator >& y ); // operator >=
	template < class Key, class T, class Compare, class Allocator >
	bool operator<=( const map< Key, T, Compare, Allocator >& x,
					 const map< Key, T, Compare, Allocator >& y ); // operator <=
	template < class Key, class T, class Compare, class Allocator >
	void swap( map< Key, T, Compare, Allocator >& x, map< Key, T, Compare, Allocator >& y ); // swap
} // namespace ft
