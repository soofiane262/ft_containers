/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:18:08 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/23 18:41:38 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../utils/rbt_iterator.hpp"
#include "../utils/redBlackTree.hpp"
#include "../utils/utils.hpp"

#include <algorithm>  // min
#include <cstddef>	  // size_t - ptrdiff_t
#include <functional> // less
#include <limits>	  // numeric_limits
#include <memory>	  // allocator

namespace ft {
	template < class Key, class Compare = std::less< Key >,
			   class Allocator = std::allocator< Key > >
	class set {
	  public:
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                    Member Types                                    */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		typedef Key									key_type;
		typedef Key									value_type;
		typedef Compare								key_compare;
		typedef Compare								value_compare;
		typedef Allocator							allocator_type;
		typedef std::size_t							size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef typename Allocator::reference		reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

	  private:
		typedef redBlackTree< value_type, value_compare, allocator_type > red_black_tree;
		typedef node< value_type >										  node_type;

	  public:
		typedef ft::rbt_iterator< value_type, node_type >		iterator;
		typedef ft::rbt_iterator< const value_type, node_type > const_iterator;
		typedef std::reverse_iterator< iterator >				reverse_iterator;
		typedef std::reverse_iterator< const_iterator >			const_reverse_iterator;

	  private:
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                  Member Attributes                                 */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		size_type	   _size;
		value_compare  _value_comp;
		allocator_type _alloc;
		red_black_tree _tree;

	  public:
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                             Construct / Copy / Destroy                             */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		explicit set( const key_compare&	comp  = key_compare(),
					  const allocator_type& alloc = allocator_type() )
			: _size( 0 ), _value_comp( value_compare( comp ) ), _alloc( alloc ),
			  _tree( red_black_tree( _value_comp, _alloc ) ) {}; // ctor_default
		template < class InputIterator >
		set( InputIterator first, InputIterator last, const Compare& comp = Compare(),
			 const Allocator& alloc = Allocator() )
			: _size( 0 ), _value_comp( value_compare( comp ) ), _alloc( alloc ),
			  _tree( red_black_tree( _value_comp, _alloc ) ) {
			insert( first, last );
		} // ctor_range
		set( const ft::set< Key, Compare, Allocator >& x )
			: _size( x._size ), _value_comp( x.value_comp() ), _alloc( x.get_allocator() ),
			  _tree( x._tree ) {} // ctor_copy
		~set( void ) {};		  // dtor
		set& operator=( const set< Key, Compare, Allocator >& other ) {
			if ( this != &other ) {
				_value_comp = other.value_comp();
				_alloc		= other.get_allocator();
				clear();
				_size = other._size;
				_tree.clone( other._tree );
			}
			return *this;
		} // assignemnt
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                      Iterators                                     */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		iterator			   begin( void ) { return _tree.begin(); }				// begin
		const_iterator		   begin( void ) const { return _tree.begin(); };		// const_begin
		iterator			   end( void ) { return _tree.end(); }					// end
		const_iterator		   end( void ) const { return _tree.end(); };			// const_end
		reverse_iterator	   rbegin( void ) { return reverse_iterator( end() ); } // rbegin
		const_reverse_iterator rbegin( void ) const {
			return const_reverse_iterator( end() );
		}																			// const_rbegin
		reverse_iterator	   rend( void ) { return reverse_iterator( begin() ); } // rend
		const_reverse_iterator rend( void ) const {
			return const_reverse_iterator( begin() );
		} // const_rend
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                              Capacity - Element Access                             */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		bool	  empty() const { return _size == 0; }; // empty
		size_type size() const { return _size; };		// size
		size_type max_size() const {
			return std::min(
				std::numeric_limits< size_type >::max() / sizeof( node_type ),
				static_cast< size_type >( std::numeric_limits< difference_type >::max() ) );
		}														// max_size
		allocator_type get_allocator() const { return _alloc; } // get_allocator
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                      Modifiers                                     */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		ft::pair< iterator, bool > insert( const value_type& x ) {
			ft::pair< node_type*, bool > ret = _tree.insert( x );
			_size += ret.second;
			return ft::pair< iterator, bool >( ret );
		} // insert_value
		iterator insert( iterator position, const value_type& x ) {
			(void)position;
			return insert( x ).first;
		} // insert_hint
		template < class InputIterator > void insert( InputIterator first, InputIterator last ) {
			while ( first != last ) insert( *first++ );
		}															 // insert_range
		void	  erase( iterator position ) { erase( *position ); } // erase_hint
		size_type erase( const key_type& x ) {
			bool erased = _tree.erase( x );
			_size -= erased;
			return erased;
		} // erase_value
		void erase( iterator first, iterator last ) {
			while ( first != last ) erase( *first++ );
		} // erase_range
		void swap( set< Key, Compare, Allocator >& other ) {
			size_type	   tmp_size		  = _size;
			value_compare  tmp_value_comp = _value_comp;
			allocator_type tmp_alloc	  = _alloc;
			_size						  = other._size;
			_value_comp					  = other._value_comp;
			_alloc						  = other._alloc;
			other._size					  = tmp_size;
			other._value_comp			  = tmp_value_comp;
			other._alloc				  = tmp_alloc;
			_tree.swap( other._tree );
		} // swap
		void clear( void ) {
			_tree.clear();
			_size = 0;
		} // clear
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                      Observers                                     */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		key_compare	  key_comp() const { return _value_comp; };	  // key_comp
		value_compare value_comp() const { return _value_comp; }; // value_comp
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		/*                                   Map Operations:                                  */
		/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
		iterator find( const key_type& x ) {
			ft::pair< node_type*, bool > pr = _tree.find( x );
			if ( pr.second ) return iterator( pr.first );
			return end();
		} // find
		const_iterator find( const key_type& x ) const {
			ft::pair< node_type*, bool > pr = _tree.find( x );
			if ( pr.second ) return const_iterator( pr.first );
			return end();
		}																			  // const_find
		size_type count( const key_type& x ) const { return _tree.find( x ).second; } // count
		iterator  lower_bound( const key_type& x ) { return _tree.lower_bound( x ); } // lower_bound
		const_iterator lower_bound( const key_type& x ) const {
			return _tree.lower_bound( x );
		} // const_lower_bound
		iterator upper_bound( const key_type& x ) { return _tree.upper_bound( x ); } // upper_bound
		const_iterator upper_bound( const key_type& x ) const {
			return _tree.upper_bound( x );
		} // const_upper_bound
		ft::pair< iterator, iterator > equal_range( const key_type& x ) {
			return ft::make_pair( lower_bound( x ), upper_bound( x ) );
		} // equal_range
		ft::pair< const_iterator, const_iterator > equal_range( const key_type& x ) const {
			return ft::make_pair( lower_bound( x ), upper_bound( x ) );
		} // const_equal_range
	};	  // class set

	template < class Key, class Compare, class Allocator > bool
	operator==( const set< Key, Compare, Allocator >& x, const set< Key, Compare, Allocator >& y ) {
		if ( x.size() != y.size() ) return false;
		return ft::equal( x.begin(), x.end(), y.begin() );
	} // operator==

	template < class Key, class Compare, class Allocator > bool
	operator!=( const set< Key, Compare, Allocator >& x, const set< Key, Compare, Allocator >& y ) {
		return !( x == y );
	} // operator !=

	template < class Key, class Compare, class Allocator > bool
	operator<( const set< Key, Compare, Allocator >& x, const set< Key, Compare, Allocator >& y ) {
		return ft::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end() );
	} // operator <

	template < class Key, class Compare, class Allocator > bool
	operator<=( const set< Key, Compare, Allocator >& x, const set< Key, Compare, Allocator >& y ) {
		return !( x > y );
	} // operator <=

	template < class Key, class Compare, class Allocator > bool
	operator>( const set< Key, Compare, Allocator >& x, const set< Key, Compare, Allocator >& y ) {
		return ft::lexicographical_compare( y.begin(), y.end(), x.begin(), x.end() );
	} // operator >

	template < class Key, class Compare, class Allocator > bool
	operator>=( const set< Key, Compare, Allocator >& x, const set< Key, Compare, Allocator >& y ) {
		return !( x < y );
	} // operator >=

	template < class Key, class Compare, class Allocator >
	void swap( set< Key, Compare, Allocator >& x, set< Key, Compare, Allocator >& y ) {
		x.swap( y );
	} // swap

} // namespace ft
