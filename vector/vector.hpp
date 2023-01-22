/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:02:04 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/22 13:16:10 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../iterators/vec_iterator.hpp"
# include "../iterators/_reverse_iterator.hpp"
# include <memory>
# include <stdexcept>

namespace	ft {

	template < class T, class Alloc = std::allocator< T > > class	vector {

		public:
		/* ------------------------------------------------------------------------ */
		/*                               Member types                               */
		/* ------------------------------------------------------------------------ */
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef	vec_iterator< value_type >					iterator;
			typedef vec_iterator< const value_type >			const_iterator;
			typedef _reverse_iterator< iterator >				reverse_iterator;
			typedef _reverse_iterator< const_iterator >			const_reverse_iterator;
			typedef	std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;

		private:
		/* ------------------------------------------------------------------------ */
		/*                                Attributes                                */
		/* ------------------------------------------------------------------------ */
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
			value_type*		_container;

		public:
		/* ------------------------------------------------------------------------ */
		/*                               Constructors                               */
		/* ------------------------------------------------------------------------ */
			explicit vector ( const allocator_type& alloc = allocator_type() ) {
				_size = 0;
				_capacity = 0;
				_alloc = alloc;
				_container = NULL;
			};
			explicit vector ( size_type n, const value_type& type = value_type(),
								const allocator_type& alloc = allocator_type() ) {
				_size = n;
				_capacity = n;
				_alloc = alloc;
				_container = NULL;
				if ( n ) {
					_container = _alloc.allocate( n );
					for ( size_type i = 0; i < n; i++ )
						_alloc.construct( _container + i, type );
				}
			};
			// template < class InputIterator >
			// vector ( InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			vector ( const vector& vec ) {
				_size = vec.size();
				_capacity = _size;
				_alloc = vec.get_allocator();
				_container = NULL;
				if ( _capacity )
					_container = _alloc.allocate( _capacity );
				for ( size_type i = 0; i < _size; i++ )
					_alloc.construct( _container + i, vec[ i ] );
			};
			~vector( void ) {
				clear();
				_alloc.deallocate( _container, _capacity );
				_container = NULL;
			}
			// template < class InputIterator >
			// void	assign (InputIterator first, InputIterator last);
			void	assign ( size_type n, const value_type& val ) {
				clear();
				if ( n > _capacity ) {
					if ( _capacity )
						_alloc.deallocate( _container, _capacity );
					_capacity = n;
					_container = _alloc.allocate( _capacity );
				}
				_size = n;
				for ( size_type i = 0; i < _size; i++ )
					_alloc.construct( _container + i, val );
			};
			value_type&	at ( size_type n ) {
				if ( n >= _size )
					throw std::out_of_range( "vector" );
				return ( _container[ n ] );
			};
			const value_type&	at ( size_type n ) const {
				if ( n >= _size )
					throw std::out_of_range( "vector" );
				return ( _container[ n ] );
			};
			value_type&	back( void ) { return ( _container[ _size - 1 ] ); };
			const value_type&	back( void ) const { return ( _container[ _size - 1 ] ); };
			// iterator	begin();
			// const_iterator	begin() const;
			size_type	capacity( void ) const { return ( _capacity ); };
			void clear( void ) {
				for ( size_type i = 0; i < _size; i++ )
					_alloc.destroy( _container + i );
				_size = 0;
			};
			bool	empty( void ) const { return ( ! _size ); };
			// iterator	end( void );
			// const_iterator	end( void ) const;
			// iterator	erase ( iterator position );
			// iterator	erase ( iterator first, iterator last );
			value_type&	front( void ) { return ( _container[ 0 ] ); };
			const value_type&	front( void ) const { return ( _container[ 0 ] ); };
			allocator_type	get_allocator( void ) const { return ( _alloc ); };
			// iterator	insert ( iterator position, const value_type& val );
			// void	insert ( iterator position, size_type n, const value_type& val );
			// template <class InputIterator>
			// void	insert ( iterator position, InputIterator first, InputIterator last );
			size_type	max_size( void ) const { return ( _alloc.max_size() ); };
			value_type&	operator [] ( size_type n ) { return ( _container[ n ] ); };
			const value_type&	operator [] ( size_type n ) const { return ( _container[ n ] ); };
			vector&	operator = ( const vector& x ) {
				if ( this != &x ) {
					clear();
					reserve( x.size() );
					_size = x.size();
					_capacity = x.size();
					_alloc = x.get_allocator();
					for ( size_type i = 0; i < _size; i++ )
						_alloc.construct( _container + i, x[ i ] );
				}
				return ( *this );
			};
			void	pop_back( void ) {
				_alloc.destroy( _container + _size - 1 );
				_size--;
			};
			void	push_back ( const value_type& val ) {
				if ( _size == _capacity ) {
					value_type	temp[ _size ];
					for ( size_type i = 0; i < _size; i++ ) {
						temp[ i ] = _container[ i ];
						_alloc.destroy( _container + i );
					}
					if ( _capacity )
						_alloc.deallocate( _container, _capacity );
					_capacity += _capacity ? _capacity : 1;
					_container = _alloc.allocate( _capacity );
					for ( size_type i = 0; i < _size; i++ )
						_alloc.construct( _container + i, temp[ i ] );
				}
				_alloc.construct( _container + _size, val );
				_size++;
			};
			// reverse_iterator	rbegin( void );
			// const_reverse_iterator	rbegin( void ) const;
			// reverse_iterator	rend( void );
			// const_reverse_iterator	rend( void ) const;
			void	reserve ( size_type n ) {
				if ( n > _capacity ) {
					value_type	temp[ _size ];
					for ( size_type i = 0; i < _size; i++ ) {
						temp[ i ] = _container[ i ];
						_alloc.destroy( _container + i );
					}
					if ( _capacity )
						_alloc.deallocate( _container, _capacity );
					_capacity = n;
					_container = _alloc.allocate( _capacity );
					for ( size_type i = 0; i < _size; i++ )
						_alloc.construct( _container + i, temp[ i ] );
				}
			};
			void	resize ( size_type n, value_type val = value_type() ) {
				if ( n < _size )
					for ( size_type i = _size; i < n; i++ )
						_alloc.destroy( _container + i );
				else if ( n > _size ) {
					reserve( n );
					for ( size_type i = _size; i < n; i++ )
						_alloc.construct( _container + i, val );
				}
				_size = n;
			};
			size_type	size( void ) const { return ( _size ); };
			void	swap ( vector& x ) {
				if ( this != &x ) {
					size_type		tmp_size = x._size;
					size_type		tmp_capacity = x._capacity;
					allocator_type	tmp_alloc = x._alloc;
					value_type		*tmp_container = x._container;
					x._capacity = _capacity;
					x._size = _size;
					x._alloc = _alloc;
					x._container = _container;
					_capacity = tmp_capacity;
					_size = tmp_size;
					_alloc = tmp_alloc;
					_container = tmp_container;
				}
			};

	};

	template < class T, class Alloc >
	bool operator	== ( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {
		if ( lhs.size() != rhs.size() )
			return ( false );
		for ( std::size_t i = 0; i < lhs.size(); i++ )
			if ( lhs[ i ] != rhs[ i ] )
				return ( false );
		return ( true );
	};

	template < class T, class Alloc >
	bool operator	!= ( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {
		return ( ! ( lhs == rhs ) );
	};

	// template < class T, class Alloc >
	// bool operator	<  ( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {
		// return (  );
	// };

	// template < class T, class Alloc >
	// bool operator	<= ( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {
		// return ( ! ( rhs < lhs ) );
	// };

	// template < class T, class Alloc >
	// bool operator	>  ( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {
		// return ( rhs < lhs );
	// };

	// template < class T, class Alloc >
	// bool operator	>= ( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {
		// return ( ! ( lhs < rhs ) );
	// };

	template < class T, class Alloc >
	void	swap ( vector< T, Alloc >& x, vector< T, Alloc >& y ) {
		x.swap( y );
	};

}
