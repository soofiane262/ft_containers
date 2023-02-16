/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:02:04 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/16 19:47:46 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../iterators/random_access_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../utils/utils.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>

#define LENGTH_EXCPT \
	throw std::length_error( "ft::vector<T> : 'new_capacity' exceeds maximum supported size" );
#define RANGE_EXCPT throw std::out_of_range( "ft::vector<T> : range_check" );

namespace ft {
	template < class T, class Allocator = std::allocator< T > > class vector {
	  public:
		/* ------------------------------------------------------------------------ */
		/*                               Member Types                               */
		/* ------------------------------------------------------------------------ */
		typedef typename Allocator::reference		   reference;
		typedef typename Allocator::const_reference	   const_reference;
		typedef ft::random_access_iterator< T >		   iterator;
		typedef ft::random_access_iterator< const T >  const_iterator;
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
		template < class Iterator > size_type ctorRangeHelper( Iterator first, Iterator last,
															   std::random_access_iterator_tag ) {
			return last - first;
		} // ctor_range_helper : random_access_iterator
		template < class Iterator >
		size_type ctorRangeHelper( Iterator first, Iterator last,
								   typename ft::iterator_traits< Iterator >::iterator_category ) {
			for ( ; first != last; ) push_back( *first++ );
			return 0;
		} // ctor_range_helper : single_pass_iterators
		/* ----------------------------- assign range ----------------------------- */
		template < class Iterator >
		void assignRangeHelper( Iterator first, Iterator last, std::random_access_iterator_tag ) {
			size_type n = last - first;
			if ( n > _capacity ) {
				if ( n > max_size() ) LENGTH_EXCPT;
				size_type	tmp_size	 = _size;
				size_type	tmp_capacity = _capacity;
				value_type *tmp_ctr		 = _container;
				_container				 = _alloc.allocate( n );
				_size					 = 0;
				_capacity				 = n;
				for ( ; _size < tmp_size; _size++ ) {
					_alloc.construct( _container + _size, *first++ );
					_alloc.destroy( tmp_ctr + _size );
				}
				for ( ; _size < n; _size++ ) _alloc.construct( _container + _size, *first++ );
				if ( tmp_capacity ) _alloc.deallocate( tmp_ctr, tmp_capacity );
			} else {
				for ( size_type i = 0, end = std::min( _size, n ); i < end; i++ ) {
					_alloc.destroy( _container + i );
					_alloc.construct( _container + i, *first++ );
				}
				for ( ; _size < n; _size++ ) _alloc.construct( _container + _size, *first++ );
				for ( size_type i = n; i < _size; i++ ) _alloc.destroy( _container + i );
				_size = n;
			}
		} // assign_range_helper : random_access_iterator
		template < class Iterator >
		void assignRangeHelper( Iterator first, Iterator last,
								typename ft::iterator_traits< Iterator >::iterator_category ) {
			clear();
			for ( ; first != last; ) push_back( *first++ );
		} // assign_range_helper: single_pass_iterators
		  /* -------------------------------- insert -------------------------------- */
		size_type insertHelper( iterator position, size_type n ) {
			size_type pos	  = position - begin();
			size_type newSize = _size + n;
			if ( newSize > _capacity ) {
				size_type new_capacity = std::max( _capacity * 2, newSize );
				if ( newSize > max_size() ) LENGTH_EXCPT;
				size_type	tmp_capacity = _capacity;
				size_type	tmp_size	 = _size;
				value_type *tmp_ctr		 = _container;
				_container				 = _alloc.allocate( new_capacity );
				_size					 = 0;
				_capacity				 = new_capacity;
				for ( ; _size < pos; _size++ ) {
					_alloc.construct( _container + _size, tmp_ctr[ _size ] );
					_alloc.destroy( tmp_ctr + _size );
				}
				for ( ; _size < tmp_size; _size++ ) {
					_alloc.construct( _container + _size + n, tmp_ctr[ _size ] );
					_alloc.destroy( tmp_ctr + _size );
				}
				if ( tmp_capacity ) _alloc.deallocate( tmp_ctr, tmp_capacity );
			} else if ( n ) {
				for ( size_type i = _size + n - 1; i >= pos + n; i-- ) {
					_alloc.construct( _container + i, _container[ i - n ] );
					_alloc.destroy( _container + i - n );
				}
			}
			return pos;
		}; // insert_helper
		template < class Iterator > void insertRangeHelper( iterator position, Iterator first,
															Iterator last,
															std::random_access_iterator_tag ) {
			size_type n		  = last - first;
			size_type pos	  = insertHelper( position, n );
			size_type newSize = _size + n;
			for ( ; _size < newSize; pos++, _size++ )
				_alloc.construct( _container + pos, *first++ );
		} // insert_range_helper : random_access_iterator
		template < class Iterator >
		void insertRangeHelper( iterator position, Iterator first, Iterator last,
								typename ft::iterator_traits< Iterator >::iterator_category ) {
			size_type				 n = 0;
			ft::vector< value_type > tmp;
			for ( ; first != last; n++ ) tmp.push_back( *first++ );
			size_type pos	  = insertHelper( position, n );
			size_type newSize = _size + n;
			for ( size_type i = 0; _size < newSize; i++, pos++, _size++ )
				_alloc.construct( _container + pos, tmp[ i ] );
		} // insert_range_helper : single_pass_iterators

	  public:
		/* ------------------------------------------------------------------------ */
		/*                        Construct / Copy / Destroy                        */
		/*                                  ..::..                                  */
		/* -------------------------- Default Constructor ------------------------- */
		explicit vector( const Allocator &alloc = Allocator() ) {
			_size = _capacity = 0;
			_alloc			  = alloc;
			_container		  = NULL;
		} // ctor_default
		/* --------------------------- Fill Constructor --------------------------- */
		explicit vector( size_type n, const T &value = T(), const Allocator &alloc = Allocator() ) {
			_capacity = _size = 0;
			_container		  = NULL;
			_alloc			  = alloc;
			if ( !n ) return;
			else if ( n > max_size() )
				LENGTH_EXCPT;
			_container = _alloc.allocate( n );
			_capacity  = n;
			for ( ; _size < n; _size++ ) _alloc.construct( _container + _size, value );
		} // ctor_fill
		/* --------------------------- Range Constructor -------------------------- */
		template < class InputIterator >
		vector( typename ft::enable_if< !ft::is_integral< InputIterator >::value,
										InputIterator >::type first,
				InputIterator last, const Allocator &alloc = Allocator() ) {
			_size = _capacity = 0;
			_container		  = NULL;
			_alloc			  = alloc;
			size_type n		  = ctorRangeHelper(
				  first, last, typename ft::iterator_traits< InputIterator >::iterator_category() );
			if ( !n ) return;
			else if ( n > max_size() )
				LENGTH_EXCPT;
			_container = _alloc.allocate( n );
			_capacity  = n;
			for ( ; _size < n; _size++ ) _alloc.construct( _container + _size, *first++ );
		} // ctor_range
		/* --------------------------- Copy Constructor --------------------------- */
		vector( const ft::vector< T, Allocator > &vec ) {
			_capacity = _size = 0;
			_container		  = NULL;
			_alloc			  = vec.get_allocator();
			size_type n		  = vec.size();
			if ( !n ) return;
			else if ( n > max_size() )
				LENGTH_EXCPT;
			_container = _alloc.allocate( n );
			_capacity  = n;
			for ( ; _size < n; _size++ ) _alloc.construct( _container + _size, vec[ _size ] );
		} // ctor_copy
		/* ------------------------------ Destructor ------------------------------ */
		~vector( void ) {
			if ( !_capacity ) return;
			clear();
			_alloc.deallocate( _container, _capacity );
			_capacity  = 0;
			_container = NULL;
		} // dtor
		/* ------------------------------ operator = ------------------------------ */
		vector< T, Allocator > &operator=( const ft::vector< T, Allocator > &vec ) {
			if ( this != &vec ) {
				size_type n = vec.size();
				if ( n > _capacity ) {
					if ( n > max_size() ) LENGTH_EXCPT;
					size_type	   tmp_size		= _size;
					size_type	   tmp_capacity = _capacity;
					value_type	  *tmp_ctr		= _container;
					allocator_type tmp_alloc	= _alloc;
					allocator_type new_alloc	= vec.get_allocator();
					_container					= new_alloc.allocate( n );
					_size						= 0;
					_capacity					= n;
					_alloc						= new_alloc;
					for ( ; _size < tmp_size; _size++ ) {
						_alloc.construct( _container + _size, vec[ _size ] );
						tmp_alloc.destroy( tmp_ctr + _size );
					}
					for ( ; _size < n; _size++ )
						_alloc.construct( _container + _size, vec[ _size ] );
					if ( tmp_capacity ) tmp_alloc.deallocate( tmp_ctr, tmp_capacity );
				} else {
					for ( size_type i = 0, end = std::min( _size, n ); i < end; i++ ) {
						_alloc.destroy( _container + i );
						_alloc.construct( _container + i, vec[ i ] );
					}
					for ( ; _size < n; _size++ )
						_alloc.construct( _container + _size, vec[ _size ] );
					for ( size_type i = n; i < _size; i++ ) _alloc.destroy( _container + i );
					_size = n;
				}
			}
			return *this;
		} // assignment
		/* -------------------------------- assign -------------------------------- */
		void assign( size_type n, const T &val ) {
			if ( n > _capacity ) {
				if ( n > max_size() ) LENGTH_EXCPT;
				size_type	tmp_size	 = _size;
				size_type	tmp_capacity = _capacity;
				value_type *tmp_ctr		 = _container;
				_container				 = _alloc.allocate( n );
				_size					 = 0;
				_capacity				 = n;
				for ( ; _size < tmp_size; _size++ ) {
					_alloc.construct( _container + _size, val );
					_alloc.destroy( tmp_ctr + _size );
				}
				for ( ; _size < n; _size++ ) _alloc.construct( _container + _size, val );
				if ( tmp_capacity ) _alloc.deallocate( tmp_ctr, tmp_capacity );
			} else {
				for ( size_type i = 0, end = std::min( _size, n ); i < end; i++ ) {
					_alloc.destroy( _container + i );
					_alloc.construct( _container + i, val );
				}
				for ( ; _size < n; _size++ ) _alloc.construct( _container + _size, val );
				for ( size_type i = n; i < _size; i++ ) _alloc.destroy( _container + i );
				_size = n;
			}
		} // assign
		template < class InputIterator >
		typename ft::enable_if< !ft::is_integral< InputIterator >::value, void >::type
		assign( InputIterator first, InputIterator last ) {
			assignRangeHelper( first, last,
							   typename ft::iterator_traits< InputIterator >::iterator_category() );
		} // assign_range
		/* ----------------------------- get_allocator ---------------------------- */
		allocator_type get_allocator( void ) const { return _alloc; } // get_allocator
		/* ------------------------------------------------------------------------ */
		/*                                 Iterators                                */
		/*                                  ..::..                                  */
		/* --------------------------------- begin -------------------------------- */
		iterator			   begin( void ) { return _container; }					// begin
		const_iterator		   begin( void ) const { return _container; }			// const_begin
		iterator			   end( void ) { return _container + _size; }			// end
		const_iterator		   end( void ) const { return _container + _size; }		// const_end
		reverse_iterator	   rbegin( void ) { return reverse_iterator( end() ); } // rbegin
		const_reverse_iterator rbegin( void ) const {
			return const_reverse_iterator( end() );
		}																			// const_rbegin
		reverse_iterator	   rend( void ) { return reverse_iterator( begin() ); } // rend
		const_reverse_iterator rend( void ) const {
			return const_reverse_iterator( begin() );
		} // const_rend
		/* ------------------------------------------------------------------------ */
		/*                                 Capacity                                 */
		/*                                  ..::..                                  */
		/* --------------------------------- size --------------------------------- */
		size_type size( void ) const { return _size; } // size
		/* ------------------------------- max_size ------------------------------- */
		size_type max_size( void ) const {
			return std::min(
				_alloc.max_size(),
				static_cast< size_type >( std::numeric_limits< difference_type >::max() ) );
		} // max_size
		/* -------------------------------- resize -------------------------------- */
		void resize( size_type n, T val = T() ) {
			if ( n < _size )
				for ( size_type i = n; i < _size; i++ ) _alloc.destroy( _container + i );
			else if ( n > _size ) {
				if ( n > _capacity ) {
					if ( n > max_size() ) LENGTH_EXCPT;
					size_type	tmp_size	 = _size;
					size_type	tmp_capacity = _capacity;
					value_type *tmp_ctr		 = _container;
					size_type	new_capacity = std::max( _capacity * 2, n );
					_container				 = _alloc.allocate( new_capacity );
					_size					 = 0;
					_capacity				 = new_capacity;
					for ( ; _size < tmp_size; _size++ ) {
						_alloc.construct( _container + _size, tmp_ctr[ _size ] );
						_alloc.destroy( tmp_ctr + _size );
					}
					for ( ; _size < n; _size++ ) _alloc.construct( _container + _size, val );
					if ( tmp_capacity ) _alloc.deallocate( tmp_ctr, tmp_capacity );
				} else
					for ( size_type i = _size; i < n; i++ ) _alloc.construct( _container + i, val );
			}
			_size = n;
		} // resize
		/* ------------------------------- capacity ------------------------------- */
		size_type capacity( void ) const { return _capacity; } // capacity
		/* --------------------------------- empty -------------------------------- */
		bool empty( void ) const { return _size == 0; } // size
		/* -------------------------------- reserve ------------------------------- */
		void reserve( size_type n ) {
			if ( n <= _capacity ) return;
			else if ( n > max_size() )
				LENGTH_EXCPT;
			size_type	tmp_capacity = _capacity;
			value_type *tmp_ctr		 = _container;
			_container				 = _alloc.allocate( n );
			_capacity				 = n;
			for ( size_type i = 0; i < _size; i++ ) {
				_alloc.construct( _container + i, tmp_ctr[ i ] );
				_alloc.destroy( tmp_ctr + i );
			}
			if ( tmp_capacity ) _alloc.deallocate( tmp_ctr, tmp_capacity );
		} // reserve
		/* ------------------------------------------------------------------------ */
		/*                              Element Access                              */
		/*                                  ..::..                                  */
		/* ------------------------------ operator [] ----------------------------- */
		reference		operator[]( size_type n ) { return _container[ n ]; }		// []
		const_reference operator[]( size_type n ) const { return _container[ n ]; } // const []
		/* ---------------------------------- at ---------------------------------- */
		reference at( size_type n ) {
			if ( n >= _size ) RANGE_EXCPT;
			return _container[ n ];
		} // at
		const_reference at( size_type n ) const {
			if ( n >= _size ) RANGE_EXCPT;
			return _container[ n ];
		} // const at
		/* --------------------------------- front -------------------------------- */
		reference		front( void ) { return _container[ 0 ]; }		// front
		const_reference front( void ) const { return _container[ 0 ]; } // const front
		/* --------------------------------- back --------------------------------- */
		reference		back( void ) { return _container[ _size - 1 ]; }	   // back
		const_reference back( void ) const { return _container[ _size - 1 ]; } // const back
		/* ------------------------------------------------------------------------ */
		/*                                 Modifiers                                */
		/*                                  ..::..                                  */
		/* ------------------------------- push_back ------------------------------ */
		void push_back( const T &val ) {
			if ( _size == _capacity )
				reserve( std::min( max_size(),
								   std::max( _capacity * 2, static_cast< size_type >( 1 ) ) ) );
			_alloc.construct( _container + _size++, val );
		} // push_back
		/* ------------------------------- pop_back ------------------------------- */
		void pop_back( void ) { _alloc.destroy( _container + --_size ); } // pop_back
		/* -------------------------------- insert -------------------------------- */
		iterator insert( iterator position, const T &val ) {
			size_type pos = insertHelper( position, static_cast< size_type >( 1 ) );
			_alloc.construct( _container + pos, val );
			_size++;
			return begin() + pos;
		} // insert
		void insert( iterator position, size_type n, const T &val ) {
			size_type newSize = _size + n;
			size_type pos	  = insertHelper( position, n );
			for ( ; _size < newSize; pos++, _size++ ) _alloc.construct( _container + pos, val );
		} // insert_size
		template < class InputIterator >
		typename ft::enable_if< !ft::is_integral< InputIterator >::value, void >::type
		insert( iterator position, InputIterator first, InputIterator last ) {
			insertRangeHelper( position, first, last,
							   typename ft::iterator_traits< InputIterator >::iterator_category() );
		} // insert_range
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
		} // erase
		iterator erase( iterator first, iterator last ) {
			if ( first == last ) return last;
			size_type pos = first - begin();
			size_type n	  = last - first;
			for ( size_type i = pos; i < _size - n; i++ ) {
				_alloc.destroy( _container + i );
				_alloc.construct( _container + i, _container[ i + n ] );
			}
			for ( size_type i = _size - n; i < _size; i++ ) _alloc.destroy( _container + i );
			_size -= n;
			return begin() + pos;
		} // erase_range
		/* --------------------------------- swap --------------------------------- */
		void swap( ft::vector< T, Allocator > &x ) {
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
		} // swap
		/* --------------------------------- clear -------------------------------- */
		void clear( void ) {
			for ( size_type i = 0; i < _size; i++ ) _alloc.destroy( _container + i );
			_size = 0;
		} // clear
	};
	/* -------------------------------------------------------------------------- */
	/*                        Non-member function overloads                       */
	/*                                   ..::..                                   */
	/* -------------------------- relational operators -------------------------- */
	template < class T, class Alloc >
	bool operator==( const ft::vector< T, Alloc > &lhs, const ft::vector< T, Alloc > &rhs ) {
		if ( lhs.size() != rhs.size() ) return false;
		return ft::equal( lhs.begin(), lhs.end(), rhs.begin() );
	}
	template < class T, class Alloc >
	bool operator!=( const ft::vector< T, Alloc > &lhs, const ft::vector< T, Alloc > &rhs ) {
		return !( lhs == rhs );
	}
	template < class T, class Alloc >
	bool operator<( const ft::vector< T, Alloc > &lhs, const ft::vector< T, Alloc > &rhs ) {
		return ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
	}
	template < class T, class Alloc >
	bool operator<=( const ft::vector< T, Alloc > &lhs, const ft::vector< T, Alloc > &rhs ) {
		return !( lhs > rhs );
	}
	template < class T, class Alloc >
	bool operator>( const ft::vector< T, Alloc > &lhs, const ft::vector< T, Alloc > &rhs ) {
		return ft::lexicographical_compare( rhs.begin(), rhs.end(), lhs.begin(), lhs.end() );
	}
	template < class T, class Alloc >
	bool operator>=( const ft::vector< T, Alloc > &lhs, const ft::vector< T, Alloc > &rhs ) {
		return !( lhs < rhs );
	}
	/* ------------------------- specialized algorithm ------------------------- */
	template < class T, class Alloc >
	void swap( ft::vector< T, Alloc > &x, ft::vector< T, Alloc > &y ) {
		x.swap( y );
	}
} // namespace ft
