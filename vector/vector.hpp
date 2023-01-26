/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:02:04 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/26 22:45:22 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../iterators/_reverse_iterator.hpp"
#include "../iterators/vec_iterator.hpp"
#include "../utils/utils.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <memory>
#include <stdexcept>

namespace ft {
	template < class T, class Alloc = std::allocator< T > > class vector {
	  public:
		/* ------------------------------------------------------------------------ */
		/*                               Member Types                               */
		/* ------------------------------------------------------------------------ */
		typedef T										 value_type;
		typedef Alloc									 allocator_type;
		typedef typename allocator_type::reference		 reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer		 pointer;
		typedef typename allocator_type::const_pointer	 const_pointer;
		typedef vec_iterator< value_type >				 iterator;
		typedef vec_iterator< const value_type >		 const_iterator;
		typedef _reverse_iterator< iterator >			 reverse_iterator;
		typedef _reverse_iterator< const_iterator >		 const_reverse_iterator;
		typedef std::ptrdiff_t							 difference_type;
		typedef std::size_t								 size_type;

	  private:
		size_type	   _size;
		size_type	   _capacity;
		allocator_type _alloc;
		value_type	  *_container;

	  public:
		/* ------------------------------------------------------------------------ */
		/*                             Member Functions                             */
		/*                                  ..::..                                  */
		/* -------------------------- Default Constructor ------------------------- */
		explicit vector( const allocator_type &alloc = allocator_type() ) {
			_size	   = 0;
			_capacity  = 0;
			_alloc	   = alloc;
			_container = NULL;
		};
		/* --------------------------- Fill Constructor --------------------------- */
		explicit vector( size_type n, const value_type &val = value_type(),
						 const allocator_type &alloc = allocator_type() ) {
			_size	   = n;
			_capacity  = n;
			_alloc	   = alloc;
			_container = NULL;
			if ( _capacity ) {
				_container = _alloc.allocate( _capacity );
				for ( size_type i = 0; i < _size; i++ ) _alloc.construct( _container + i, val );
			}
		};
		/* --------------------------- Range Constructor -------------------------- */
		template < class InputIterator > vector(
			typename enable_if< !is_integral< InputIterator >::value, InputIterator >::type first,
			InputIterator last, const allocator_type &alloc = allocator_type() ) {
			_size	   = 0;
			_capacity  = 0;
			_alloc	   = alloc;
			_container = NULL;
			for ( InputIterator it = first; it != last; it++ ) _size++;
			for ( InputIterator it = first; it != last; it++ ) _capacity++;
			if ( _capacity ) {
				_container = _alloc.allocate( _capacity );
				for ( size_type i = 0; i < _size; i++ )
					_alloc.construct( _container + i, *first++ );
			}
		};
		/* --------------------------- Copy Constructor --------------------------- */
		vector( const vector &vec ) {
			_size	   = vec.size();
			_capacity  = _size;
			_alloc	   = vec.get_allocator();
			_container = NULL;
			if ( _capacity ) _container = _alloc.allocate( _capacity );
			for ( size_type i = 0; i < _size; i++ ) _alloc.construct( _container + i, vec[ i ] );
		};
		/* ------------------------------ Destructor ------------------------------ */
		~vector( void ) {
			clear();
			_alloc.deallocate( _container, _capacity );
			_container = NULL;
		}
		/* ------------------------------ operator = ------------------------------ */
		vector &operator=( const vector &x ) {
			if ( this != &x ) {
				clear();
				reserve( x.size() );
				_size	  = x.size();
				_capacity = x.size();
				_alloc	  = x.get_allocator();
				for ( size_type i = 0; i < _size; i++ ) _alloc.construct( _container + i, x[ i ] );
			}
			return *this;
		};
		/* ------------------------------------------------------------------------ */
		/*                                 Iterators                                */
		/*                                  ..::..                                  */
		/* --------------------------------- begin -------------------------------- */
		iterator	   begin( void ) { return iterator( _container ); };
		const_iterator begin( void ) const { return const_iterator( _container ); };
		/* ---------------------------------- end --------------------------------- */
		iterator	   end( void ) { return iterator( _container + _size ); };
		const_iterator end( void ) const { return const_iterator( _container + _size ); };
		/* -------------------------------- rbegin -------------------------------- */
		reverse_iterator	   rbegin( void ) { return reverse_iterator( end() ); };
		const_reverse_iterator rbegin( void ) const { return const_reverse_iterator( end() ); };
		/* --------------------------------- rend --------------------------------- */
		reverse_iterator	   rend( void ) { return reverse_iterator( begin() ); };
		const_reverse_iterator rend( void ) const { return const_reverse_iterator( begin() ); };
		/* ------------------------------------------------------------------------ */
		/*                                 Capacity                                 */
		/*                                  ..::..                                  */
		/* --------------------------------- size --------------------------------- */
		size_type size( void ) const { return _size; };
		/* ------------------------------- max_size ------------------------------- */
		size_type max_size( void ) const {
			return std::min(
				_alloc.max_size(),
				static_cast< size_type >( std::numeric_limits< difference_type >::max() ) );
		};
		/* -------------------------------- resize -------------------------------- */
		void resize( size_type n, value_type val = value_type() ) {
			if ( n < _size )
				for ( size_type i = _size; i < n; i++ ) _alloc.destroy( _container + i );
			else if ( n > _size ) {
				if ( n > _capacity ) reserve( std::max( _capacity * 2, n ) );
				for ( size_type i = _size; i < n; i++ ) _alloc.construct( _container + i, val );
			}
			_size = n;
		};
		/* ------------------------------- capacity ------------------------------- */
		size_type capacity( void ) const { return _capacity; };
		/* --------------------------------- empty -------------------------------- */
		bool empty( void ) const { return !_size; };
		/* -------------------------------- reserve ------------------------------- */
		void reserve( size_type n ) {
			if ( n > _capacity ) {
				value_type temp[ _size ];
				for ( size_type i = 0; i < _size; i++ ) {
					temp[ i ] = _container[ i ];
					_alloc.destroy( _container + i );
				}
				if ( _capacity ) _alloc.deallocate( _container, _capacity );
				_capacity  = n;
				_container = _alloc.allocate( _capacity );
				for ( size_type i = 0; i < _size; i++ )
					_alloc.construct( _container + i, temp[ i ] );
			}
		};
		/* ------------------------------------------------------------------------ */
		/*                              Element Access                              */
		/*                                  ..::..                                  */
		/* ------------------------------ operator [] ----------------------------- */
		reference		operator[]( size_type n ) { return _container[ n ]; };
		const_reference operator[]( size_type n ) const { return _container[ n ]; };
		/* ---------------------------------- at ---------------------------------- */
		reference at( size_type n ) {
			if ( n >= _size ) throw std::out_of_range( "vector" );
			return _container[ n ];
		};
		const_reference at( size_type n ) const {
			if ( n >= _size ) throw std::out_of_range( "vector" );
			return _container[ n ];
		};
		/* --------------------------------- front -------------------------------- */
		reference		front( void ) { return _container[ 0 ]; };
		const_reference front( void ) const { return _container[ 0 ]; };
		/* --------------------------------- back --------------------------------- */
		reference		back( void ) { return _container[ _size - 1 ]; };
		const_reference back( void ) const { return _container[ _size - 1 ]; };
		/* ------------------------------------------------------------------------ */
		/*                                 Modifiers                                */
		/*                                  ..::..                                  */
		/* -------------------------------- assign -------------------------------- */
		template < class InputIterator >
		typename enable_if< !is_integral< InputIterator >::value >::type
		assign( InputIterator first, InputIterator last ) {
			clear();
			size_type n = 0;
			for ( InputIterator it = first; it != last; it++ ) n++;
			if ( n > _capacity ) {
				if ( _capacity ) _alloc.deallocate( _container, _capacity );
				_capacity  = n;
				_container = _alloc.allocate( _capacity );
			}
			_size = n;
			for ( size_type i = 0; i < _size; i++ ) _alloc.construct( _container + i, *first++ );
		};
		void assign( size_type n, const value_type &val ) {
			clear();
			if ( n > _capacity ) {
				if ( _capacity ) _alloc.deallocate( _container, _capacity );
				_capacity  = n;
				_container = _alloc.allocate( _capacity );
			}
			_size = n;
			for ( size_type i = 0; i < _size; i++ ) _alloc.construct( _container + i, val );
		};
		/* ------------------------------- push_back ------------------------------ */
		void push_back( const value_type &val ) {
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
		};
		/* ------------------------------- pop_back ------------------------------- */
		void pop_back( void ) {
			_alloc.destroy( _container + _size - 1 );
			_size--;
		};
		/* -------------------------------- insert -------------------------------- */
		iterator insert( iterator position, const value_type &val ) {
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
		};
		void insert( iterator position, size_type n, const value_type &val ) {
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
			} else {
				for ( size_type i = _size + n - 1; i != pos; i-- ) {
					_alloc.construct( _container + i, _container[ i - n ] );
					_alloc.destroy( _container + i - n );
				}
				_size += n;
			}
			for ( size_type i = pos; i != pos + n; i++ ) _alloc.construct( _container + i, val );
		};
		template < class InputIterator >
		typename enable_if< !is_integral< InputIterator >::value >::type
		insert( iterator position, InputIterator first, InputIterator last ) {
			size_type n = 0;
			for ( InputIterator it = first; it != last; it++ ) n++;
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
			} else {
				for ( size_type i = _size + n - 1; i != pos; i-- ) {
					_alloc.construct( _container + i, _container[ i - n ] );
					_alloc.destroy( _container + i - n );
				}
				_size += n;
			}
			for ( size_type i = pos; i != pos + n; i++ ) {
				_alloc.construct( _container + i, *first++ );
			}
		};
		/* --------------------------------- erase -------------------------------- */
		iterator erase( iterator position ) {
			size_type pos = position - begin();
			for ( size_type i = pos; i < _size - 1; i++ ) {
				_alloc.destroy( _container + i );
				_alloc.construct( _container + i, _container[ i + 1 ] );
			}
			_size--;
			return begin() + pos;
		};
		iterator erase( iterator first, iterator last ) {
			size_type n	  = last - first;
			size_type pos = first - begin();
			for ( size_type i = pos; i < _size - 1; i++ ) {
				_alloc.destroy( _container + i );
				if ( i + n < _size ) _alloc.construct( _container + i, _container[ i + n ] );
			}
			_size -= n;
			return begin() + pos;
		};
		/* --------------------------------- swap --------------------------------- */
		void swap( vector &x ) {
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
		};
		/* --------------------------------- clear -------------------------------- */
		void clear( void ) {
			for ( size_type i = 0; i < _size; i++ ) _alloc.destroy( _container + i );
			_size = 0;
		};
		/* ------------------------------------------------------------------------ */
		/*                                 Allocator                                */
		/*                                  ..::..                                  */
		/* ----------------------------- get_allocator ---------------------------- */
		allocator_type get_allocator( void ) const { return _alloc; };
	};
	/* -------------------------------------------------------------------------- */
	/*                        Non-member function overloads                       */
	/*                                   ..::..                                   */
	/* -------------------------- relational operators -------------------------- */
	template < class T, class Alloc >
	bool operator==( const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs ) {
		if ( lhs.size() != rhs.size() ) return false;
		return equal( lhs.begin(), lhs.end(), rhs.begin() );
	};
	template < class T, class Alloc >
	bool operator!=( const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs ) {
		return !( lhs == rhs );
	};
	template < class T, class Alloc >
	bool operator<( const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs ) {
		return lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
	};
	template < class T, class Alloc >
	bool operator<=( const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs ) {
		return !( lhs > rhs );
	};
	template < class T, class Alloc >
	bool operator>( const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs ) {
		return lexicographical_compare( rhs.begin(), rhs.end(), lhs.begin(), lhs.end() );
	};
	template < class T, class Alloc >
	bool operator>=( const vector< T, Alloc > &lhs, const vector< T, Alloc > &rhs ) {
		return !( lhs < rhs );
	};
	/* ---------------------------------- swap ---------------------------------- */
	template < class T, class Alloc > void swap( vector< T, Alloc > &x, vector< T, Alloc > &y ) {
		x.swap( y );
	};
} // namespace ft
