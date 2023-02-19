/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:18:08 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/19 16:58:27 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../iterators/map_iterator.hpp"
#include "../utils/redBlackTree.hpp"
#include "../utils/utils.hpp"

#include <algorithm>  // min
#include <cstddef>	  // size_t - ptrdiff_t
#include <functional> // less
#include <limits>	  // numeric_limits
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
	  private:
		typedef redBlackTree< value_type, value_compare, allocator_type >		red_black_tree;
		typedef redBlackTree< const value_type, value_compare, allocator_type > c_red_black_tree;
		typedef typename red_black_tree::node_type								node_type;
		typedef typename c_red_black_tree::node_type							c_node_type;

	  public:
		typedef ft::map_iterator< node_type >			iterator;
		typedef ft::map_iterator< c_node_type >			const_iterator;
		typedef std::reverse_iterator< iterator >		reverse_iterator;
		typedef std::reverse_iterator< const_iterator > const_reverse_iterator;

	  private:
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                  Member Attributes                                 */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		size_type	   _size;
		key_compare	   _key_comp;
		value_compare  _value_comp;
		allocator_type _alloc;
		red_black_tree _tree;

	  public:
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                             Construct / Copy / Destroy                             */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		explicit map( const key_compare&	comp  = key_compare(),
					  const allocator_type& alloc = allocator_type() )
			: _size( 0 ), _key_comp( comp ), _value_comp( value_compare( comp ) ), _alloc( alloc ),
			  _tree( red_black_tree( _value_comp, _alloc ) ) {}; // ctor_default
		template < class InputIterator > map( InputIterator first, InputIterator last,
											  const Compare& comp = Compare(),
											  const Allocator&	  = Allocator() ); // ctor_range
		map( const ft::map< Key, T, Compare, Allocator >& x );					// ctor_copy
		~map( void ) {};														// dtor
		map< Key, T, Compare, Allocator >&
		operator=( const map< Key, T, Compare, Allocator >& x ); // assignemnt
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                      Iterators                                     */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		iterator begin( void ) { return _tree.begin(); } // begin
		// const_iterator		   begin() const;  // const_begin
		iterator end( void ) { return _tree.end(); } // end
		// const_iterator		   end() const;	   // const_end
		// reverse_iterator	   rbegin();	   // rbegin
		// const_reverse_iterator rbegin() const; // const_rbegin
		// reverse_iterator	   rend();		   // rend
		// const_reverse_iterator rend() const;   // const_rend
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                              Capacity - Element Access                             */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		bool	  empty() const { return _size == 0; }; // empty
		size_type size() const { return _size; };		// size
		size_type max_size() const {
			return std::min(
				std::numeric_limits< size_type >::max() / sizeof( value_type ),
				static_cast< size_type >( std::numeric_limits< difference_type >::max() ) );
		} // max_size
		mapped_type& operator[]( const key_type& x ) {
			return insert( ft::make_pair( x, mapped_type() ) ).first->second;
		}
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                      Modifiers                                     */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		ft::pair< iterator, bool > insert( const value_type& x ) {
			ft::pair< node_type*, bool > ret = _tree.insert( x );
			_size += ret.second;
			return ft::pair< iterator, bool >( ret );
		}
		// iterator insert( iterator position, const value_type& x );
		// template < class InputIterator > void insert( InputIterator first, InputIterator last );
		// void								  erase( iterator position );
		size_type erase( const key_type& x ) {
			return _tree.erase( value_type( x, mapped_type() ) );
		}
		// void								  erase( iterator first, iterator last );
		void swap( map< Key, T, Compare, Allocator >& );
		void clear();
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                      Observers                                     */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		key_compare	  key_comp() const { return _key_comp; };
		value_compare value_comp() const { return _value_comp; };
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
