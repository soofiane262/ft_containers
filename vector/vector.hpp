/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:02:04 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/15 11:04:45 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../iterators/reverse_iterator.hpp"
#include "../iterators/vec_iterator.hpp"
#include "../utils/utils.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>

namespace ft {
	template < class T, class Allocator = std::allocator< T > > class vector {
	  public:
		/* ------------------------------------------------------------------------ */
		/*                               Member Types                               */
		/* ------------------------------------------------------------------------ */
		typedef typename Allocator::reference		   reference;
		typedef typename Allocator::const_reference	   const_reference;
		typedef ft::vec_iterator< T >				   iterator;
		typedef ft::vec_iterator< const T >			   const_iterator;
		typedef std::size_t							   size_type;
		typedef std::ptrdiff_t						   difference_type;
		typedef T									   value_type;
		typedef Allocator							   allocator_type;
		typedef typename Allocator::pointer			   pointer;
		typedef typename Allocator::const_pointer	   const_pointer;
		typedef ft::reverse_iterator< iterator >	   reverse_iterator;
		typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;

	  private:
		/* ------------------------------------------------------------------------ */
		/*                             Member Attributes                            */
		/* ------------------------------------------------------------------------ */
		size_type	   _size;
		size_type	   _capacity;
		allocator_type _alloc;
		value_type	  *_container;
		/* ------------------------------------------------------------------------ */
		/*                             Helper Functions                             */
		/* ------------------------------------------------------------------------ */
		/* --------------------------- Range Constructor -------------------------- */
		template < class Iterator >
		void ctorRangeHelper( Iterator first, Iterator last, std::random_access_iterator_tag ) {
			_capacity = _size = last - first;
			if ( !_capacity ) return;
			_container = _alloc.allocate( _capacity );
			for ( size_type i = 0; i < _size; i++ ) _alloc.construct( _container + i, *first++ );
		}
		template < class Iterator >
		void ctorRangeHelper( Iterator first, Iterator last,
							  typename ft::iterator_traits< Iterator >::iterator_category ) {
			for ( ; first != last; ) push_back( *first++ );
		}
		/* ----------------------------- assign range ----------------------------- */
		template < class Iterator >
		void assignRangeHelper( Iterator first, Iterator last, std::random_access_iterator_tag ) {
			size_type n = last - first;
			if ( n > _capacity ) {
				if ( _capacity ) _alloc.deallocate( _container, _capacity );
				_capacity  = n;
				_container = _alloc.allocate( _capacity );
			}
			_size = n;
			for ( size_type i = 0; i < _size; i++ ) _alloc.construct( _container + i, *first++ );
		}
		template < class Iterator >
		void assignRangeHelper( Iterator first, Iterator last,
								typename ft::iterator_traits< Iterator >::iterator_category ) {
			for ( ; first != last; ) push_back( *first++ );
		}
		/* -------------------------------- insert -------------------------------- */
		size_type insertHelper( iterator position, size_type n ) {
			if ( n > max_size() )
				throw std::length_error( "vector : 'new_capacity' exceeds maximum supported size" );
			size_type pos = position - begin();
			if ( _size + n > _capacity ) {
				value_type temp[ _size ];
				for ( size_type i = 0; i < _size; i++ ) {
					temp[ i ] = _container[ i ];
					_alloc.destroy( _container + i );
				}
				if ( _capacity ) _alloc.deallocate( _container, _capacity );
				_capacity  = _capacity ? std::max( _size + n, _capacity * 2 ) : n;
				_container = _alloc.allocate( _capacity );
				_size += n;
				for ( size_type i = 0; i != pos; i++ )
					_alloc.construct( _container + i, temp[ i ] );
				for ( size_type i = pos + n; i != _size; i++ )
					_alloc.construct( _container + i, temp[ i - n ] );
			} else if ( n ) {
				for ( size_type i = _size + n - 1; i >= pos + n; i-- ) {
					_alloc.construct( _container + i, _container[ i - n ] );
					_alloc.destroy( _container + i - n );
				}
				_size += n;
			}
			return pos;
		}
		template < class Iterator > void insertRangeHelper( iterator position, Iterator first,
															Iterator last,
															std::random_access_iterator_tag ) {
			size_type n	  = last - first;
			size_type pos = insertHelper( position, n );
			for ( size_type i = pos; i != pos + n; i++ )
				_alloc.construct( _container + i, *first++ );
		}
		template < class Iterator >
		void insertRangeHelper( iterator position, Iterator first, Iterator last,
								typename ft::iterator_traits< Iterator >::iterator_category ) {
			size_type			 n = 0;
			vector< value_type > tmp;
			for ( ; first != last; n++ ) tmp.push_back( *first++ );
			size_type pos = insertHelper( position, n );
			for ( size_type i = pos; i != pos + n; i++ )
				_alloc.construct( _container + i, tmp[ i - pos ] );
		}

	  public:
		/* ------------------------------------------------------------------------ */
		/*                        Construct / Copy / Destroy                        */
		/*                                  ..::..                                  */
		/* -------------------------- Default Constructor ------------------------- */
		explicit vector( const Allocator &alloc = Allocator() ) {
			_size	   = 0;
			_capacity  = 0;
			_alloc	   = alloc;
			_container = NULL;
		}
		/* --------------------------- Fill Constructor --------------------------- */
		explicit vector( size_type n, const T &value = T(), const Allocator &alloc = Allocator() ) {
			_size	   = n;
			_capacity  = n;
			_alloc	   = alloc;
			_container = NULL;
			if ( _capacity ) {
				_container = _alloc.allocate( _capacity );
				for ( size_type i = 0; i < _size; i++ ) _alloc.construct( _container + i, value );
			}
		}
		/* --------------------------- Range Constructor -------------------------- */
		template < class InputIterator >
		vector( typename ft::enable_if< !ft::is_integral< InputIterator >::value,
										InputIterator >::type first,
				InputIterator last, const Allocator &alloc = Allocator() ) {
			_size	   = 0;
			_capacity  = 0;
			_alloc	   = alloc;
			_container = NULL;
			ctorRangeHelper( first, last,
							 typename ft::iterator_traits< InputIterator >::iterator_category() );
		}
		/* --------------------------- Copy Constructor --------------------------- */
		vector( const vector< T, Allocator > &vec ) {
			_size	   = vec.size();
			_capacity  = _size;
			_alloc	   = vec.get_allocator();
			_container = NULL;
			if ( _capacity ) _container = _alloc.allocate( _capacity );
			for ( size_type i = 0; i < _size; i++ ) _alloc.construct( _container + i, vec[ i ] );
		}
		/* ------------------------------ Destructor ------------------------------ */
		~vector( void ) {
			if ( !_capacity ) return;
			clear();
			_alloc.deallocate( _container, _capacity );
			_container = NULL;
		}
		/* ------------------------------ operator = ------------------------------ */
		vector< T, Allocator > &operator=( const vector< T, Allocator > &x ) {
			if ( this != &x ) {
				clear();
				reserve( std::max( _capacity, x.size() ) );
				_size	  = x.size();
				_capacity = std::max( _capacity, x.size() );
				_alloc	  = x.get_allocator();
				for ( size_type i = 0; i < _size; i++ ) _alloc.construct( _container + i, x[ i ] );
			}
			return *this;
		}
		/* -------------------------------- assign -------------------------------- */
		template < class InputIterator >
		typename ft::enable_if< !ft::is_integral< InputIterator >::value, void >::type
		assign( InputIterator first, InputIterator last ) {
			clear();
			assignRangeHelper( first, last,
							   typename ft::iterator_traits< InputIterator >::iterator_category() );
		}
		void assign( size_type n, const T &val ) {
			clear();
			if ( n > _capacity ) {
				if ( _capacity ) _alloc.deallocate( _container, _capacity );
				_capacity  = n;
				_container = _alloc.allocate( _capacity );
			}
			_size = n;
			for ( size_type i = 0; i < _size; i++ ) _alloc.construct( _container + i, val );
		}
		/* ----------------------------- get_allocator ---------------------------- */
		allocator_type get_allocator( void ) const { return _alloc; }
		/* ------------------------------------------------------------------------ */
		/*                                 Iterators                                */
		/*                                  ..::..                                  */
		/* --------------------------------- begin -------------------------------- */
		iterator	   begin( void ) { return iterator( _container ); }
		const_iterator begin( void ) const { return const_iterator( _container ); }
		/* ---------------------------------- end --------------------------------- */
		iterator	   end( void ) { return iterator( _container + _size ); }
		const_iterator end( void ) const { return const_iterator( _container + _size ); }
		/* -------------------------------- rbegin -------------------------------- */
		reverse_iterator	   rbegin( void ) { return reverse_iterator( end() ); }
		const_reverse_iterator rbegin( void ) const { return const_reverse_iterator( end() ); }
		/* --------------------------------- rend --------------------------------- */
		reverse_iterator	   rend( void ) { return reverse_iterator( begin() ); }
		const_reverse_iterator rend( void ) const { return const_reverse_iterator( begin() ); }
		/* ------------------------------------------------------------------------ */
		/*                                 Capacity                                 */
		/*                                  ..::..                                  */
		/* --------------------------------- size --------------------------------- */
		size_type size( void ) const { return _size; }
		/* ------------------------------- max_size ------------------------------- */
		size_type max_size( void ) const {
			return std::min(
				_alloc.max_size(),
				static_cast< size_type >( std::numeric_limits< difference_type >::max() ) );
		}
		/* -------------------------------- resize -------------------------------- */
		void resize( size_type n, T val = T() ) {
			if ( n < _size )
				for ( size_type i = n; i < _size; i++ ) _alloc.destroy( _container + i );
			else if ( n > _size ) {
				if ( n > _capacity ) reserve( std::max( _capacity * 2, n ) );
				for ( size_type i = _size; i < n; i++ ) _alloc.construct( _container + i, val );
			}
			_size = n;
		}
		/* ------------------------------- capacity ------------------------------- */
		size_type capacity( void ) const { return _capacity; }
		/* --------------------------------- empty -------------------------------- */
		bool empty( void ) const { return !_size; }
		/* -------------------------------- reserve ------------------------------- */
		void reserve( size_type n ) {
			if ( n > max_size() )
				throw std::length_error( "vector : 'new_capacity' exceeds maximum supported size" );
			else if ( n <= _capacity )
				return;
			value_type temp[ _size ];
			for ( size_type i = 0; i < _size; i++ ) {
				temp[ i ] = _container[ i ];
				_alloc.destroy( _container + i );
			}
			if ( _capacity ) _alloc.deallocate( _container, _capacity );
			_capacity  = n;
			_container = _alloc.allocate( _capacity );
			for ( size_type i = 0; i < _size; i++ ) _alloc.construct( _container + i, temp[ i ] );
		}
		/* ------------------------------------------------------------------------ */
		/*                              Element Access                              */
		/*                                  ..::..                                  */
		/* ------------------------------ operator [] ----------------------------- */
		reference		operator[]( size_type n ) { return _container[ n ]; }
		const_reference operator[]( size_type n ) const { return _container[ n ]; }
		/* ---------------------------------- at ---------------------------------- */
		reference at( size_type n ) {
			if ( n >= _size ) throw std::out_of_range( "vector : range_check" );
			return _container[ n ];
		}
		const_reference at( size_type n ) const {
			if ( n >= _size ) throw std::out_of_range( "vector : range_check" );
			return _container[ n ];
		}
		/* --------------------------------- front -------------------------------- */
		reference		front( void ) { return _container[ 0 ]; }
		const_reference front( void ) const { return _container[ 0 ]; }
		/* --------------------------------- back --------------------------------- */
		reference		back( void ) { return _container[ _size - 1 ]; }
		const_reference back( void ) const { return _container[ _size - 1 ]; }
		/* ------------------------------------------------------------------------ */
		/*                                 Modifiers                                */
		/*                                  ..::..                                  */
		/* ------------------------------- push_back ------------------------------ */
		void push_back( const T &val ) {
			if ( _size == _capacity ) {
				value_type temp[ _size ];
				for ( size_type i = 0; i < _size; i++ ) {
					temp[ i ] = _container[ i ];
					_alloc.destroy( _container + i );
				}
				if ( _capacity ) _alloc.deallocate( _container, _capacity );
				_capacity += _capacity ? _capacity : 1;
				_container = _alloc.allocate( _capacity );
				for ( size_type i = 0; i < _size; i++ )
					_alloc.construct( _container + i, temp[ i ] );
			}
			_alloc.construct( _container + _size, val );
			_size++;
		}
		/* ------------------------------- pop_back ------------------------------- */
		void pop_back( void ) {
			_alloc.destroy( _container + _size - 1 );
			_size--;
		}
		/* -------------------------------- insert -------------------------------- */
		iterator insert( iterator position, const T &val ) {
			size_type pos = position - begin();
			if ( _size == _capacity ) {
				value_type temp[ _size ];
				for ( size_type i = 0; i < _size; i++ ) {
					temp[ i ] = _container[ i ];
					_alloc.destroy( _container + i );
				}
				if ( _capacity ) _alloc.deallocate( _container, _capacity );
				_capacity += _capacity ? _capacity : 1;
				_container = _alloc.allocate( _capacity );
				_size++;
				for ( size_type i = 0; i != pos; i++ )
					_alloc.construct( _container + i, temp[ i ] );
				for ( size_type i = pos + 1; i != _size; i++ )
					_alloc.construct( _container + i, temp[ i - 1 ] );
			} else {
				for ( size_type i = _size; i != pos; i-- ) {
					_alloc.construct( _container + i, _container[ i - 1 ] );
					_alloc.destroy( _container + i - 1 );
				}
				_size++;
			}
			_alloc.construct( _container + pos, val );
			return begin() + pos;
		}
		void insert( iterator position, size_type n, const T &val ) {
			size_type pos = insertHelper( position, n );
			for ( size_type i = pos; i != pos + n; i++ ) _alloc.construct( _container + i, val );
		}
		template < class InputIterator >
		typename ft::enable_if< !ft::is_integral< InputIterator >::value, void >::type
		insert( iterator position, InputIterator first, InputIterator last ) {
			insertRangeHelper( position, first, last,
							   typename ft::iterator_traits< InputIterator >::iterator_category() );
		}
		/* --------------------------------- erase -------------------------------- */
		iterator erase( iterator position ) {
			size_type pos = position - begin();
			for ( size_type i = pos; i < _size - 1; i++ ) {
				_alloc.destroy( _container + i );
				_alloc.construct( _container + i, _container[ i + 1 ] );
			}
			_alloc.destroy( _container + _size - 1 );
			_size--;
			return begin() + pos;
		}
		iterator erase( iterator first, iterator last ) {
			if ( first == last ) return last;
			size_type n	  = last - first;
			size_type pos = first - begin();
			for ( size_type i = pos; i < _size - 1; i++ ) {
				_alloc.destroy( _container + i );
				if ( i + n < _size ) _alloc.construct( _container + i, _container[ i + n ] );
			}
			_alloc.destroy( _container + _size - 1 );
			_size -= n;
			return begin() + pos;
		}
		/* --------------------------------- swap --------------------------------- */
		void swap( vector< T, Allocator > &x ) {
			if ( this != &x ) {
				size_type	   tmp_size		 = x._size;
				size_type	   tmp_capacity	 = x._capacity;
				allocator_type tmp_alloc	 = x._alloc;
				value_type	  *tmp_container = x._container;
				x._capacity					 = _capacity;
				x._size						 = _size;
				x._alloc					 = _alloc;
				x._container				 = _container;
				_capacity					 = tmp_capacity;
				_size						 = tmp_size;
				_alloc						 = tmp_alloc;
				_container					 = tmp_container;
			}
		}
		/* --------------------------------- clear -------------------------------- */
		void clear( void ) {
			for ( size_type i = 0; i < _size; i++ ) _alloc.destroy( _container + i );
			_size = 0;
		}
	};
	/* -------------------------------------------------------------------------- */
	/*                        Non-member function overloads                       */
	/*                                   ..::..                                   */
	/* -------------------------- relational operators -------------------------- */
	template < class T, class Alloc >
	bool operator==( const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs ) {
		if ( lhs.size() != rhs.size() ) return false;
		return ft::equal( lhs.begin(), lhs.end(), rhs.begin() );
	}
	template < class T, class Alloc >
	bool operator!=( const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs ) {
		return !( lhs == rhs );
	}
	template < class T, class Alloc >
	bool operator<( const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs ) {
		return ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
	}
	template < class T, class Alloc >
	bool operator<=( const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs ) {
		return !( lhs > rhs );
	}
	template < class T, class Alloc >
	bool operator>( const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs ) {
		return ft::lexicographical_compare( rhs.begin(), rhs.end(), lhs.begin(), lhs.end() );
	}
	template < class T, class Alloc >
	bool operator>=( const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs ) {
		return !( lhs < rhs );
	}
	/* ------------------------- specialized algorithm ------------------------- */
	template < class T, class Alloc > void swap( vector< T, Alloc > &x, vector< T, Alloc > &y ) {
		x.swap( y );
	}
} // namespace ft
