/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:02:04 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/20 21:09:38 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <memory>
# include <stdexcept>

namespace	ft {

	template < class T, class Alloc = std::allocator< T > > class	vector {

		private:
		/* ------------------------------------------------------------------------ */
		/*                                Attributes                                */
		/* ------------------------------------------------------------------------ */
			std::size_t		_size;
			std::size_t		_capacity;
			Alloc			_alloc;
			T*				_container;

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
			// typedef iterator	a random access iterator to value_type	convertible to const_iterator
			// typedef const_iterator	a random access iterator to const value_type	
			// typedef reverse_iterator	reverse_iterator<iterator>	
			// typedef const_reverse_iterator	reverse_iterator<const_iterator>	
			// typedef difference_type	a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
			typedef std::size_t									size_type;
		/* ------------------------------------------------------------------------ */
		/*                               Constructors                               */
		/* ------------------------------------------------------------------------ */
			explicit vector ( const Alloc& alloc = Alloc() ) {
				_size = 0;
				_capacity = 0;
				_alloc = alloc;
				_container = NULL;
			};
			explicit vector ( std::size_t n, const T& type = T(), const Alloc& alloc = Alloc() ) {
				_size = n;
				_capacity = n;
				_alloc = alloc;
				_container = NULL;
				if ( n ) {
					_container = _alloc.allocate( n );
					for ( std::size_t i = 0; i < n; i++ )
						_alloc.construct( _container + i, type );
				}
			};
			// template < class InputIterator > vector ( InputIterator first, InputIterator last, const Alloc& alloc = Alloc());
			vector ( const vector& vec ) {
				_size = vec.size();
				_capacity = _size;
				_alloc = vec.get_allocator();
				_container = NULL;
				if ( _capacity )
					_container = _alloc.allocate( _capacity );
				for ( std::size_t i = 0; i < _size; i++ )
					_alloc.construct( _container + i, vec[ i ] );
			};
		/* ------------------------------------------------------------------------ */
		/*                                Destructors                               */
		/* ------------------------------------------------------------------------ */
			~vector( void ) {
				clear();
				_alloc.deallocate( _container, _capacity );
				_container = NULL;
			}
		/* ------------------------------------------------------------------------ */
		/*                            ft::vector::assign                            */
		/* -------------------------------- ..::.. -------------------------------- */
			// template < class InputIterator > void	assign (InputIterator first, InputIterator last);
			void	assign ( std::size_t n, const T& val ) {
				clear();
				if ( n > _capacity ) {
					if ( _capacity )
						_alloc.deallocate( _container, _capacity );
					_capacity = n;
					_container = _alloc.allocate( _capacity );
				}
				_size = n;
				for ( std::size_t i = 0; i < _size; i++ )
					_alloc.construct( _container + i, val );
			};
		/* ------------------------------------------------------------------------ */
		/*                              ft::vector::at                              */
		/* -------------------------------- ..::.. -------------------------------- */
			T&	at ( std::size_t n ) {
				if ( n >= _size )
					throw std::out_of_range( "vector" );
				return ( _container[ n ] );
			};
			const T&	at ( std::size_t n ) const {
				if ( n >= _size )
					throw std::out_of_range( "vector" );
				return ( _container[ n ] );
			};
		/* ------------------------------------------------------------------------ */
		/*                             ft::vector::back                             */
		/* -------------------------------- ..::.. -------------------------------- */
			T&	back( void ) { return ( _container[ _size - 1 ] ); };
			const T&	back( void ) const { return ( _container[ _size - 1 ] ); };
		/* ------------------------------------------------------------------------ */
		/*                             ft::vector::begin                            */
		/* -------------------------------- ..::.. -------------------------------- */
			// iterator	begin();
			// const_iterator	begin() const;
		/* ------------------------------------------------------------------------ */
		/*                           ft::vector::capacity                           */
		/* -------------------------------- ..::.. -------------------------------- */
			std::size_t	capacity( void ) const { return ( _capacity ); };
		/* ------------------------------------------------------------------------ */
		/*                             ft::vector::clear                            */
		/* -------------------------------- ..::.. -------------------------------- */
			void clear( void ) {
				for ( std::size_t i = 0; i < _size; i++ )
					_alloc.destroy( _container + i );
				_size = 0;
			};
		/* ------------------------------------------------------------------------ */
		/*                             ft::vector::empty                            */
		/* -------------------------------- ..::.. -------------------------------- */
			bool	empty( void ) const { return ( ! _size ); };
		/* ------------------------------------------------------------------------ */
		/*                              ft::vector::end                             */
		/* -------------------------------- ..::.. -------------------------------- */
			// iterator	end( void );
			// const_iterator	end( void ) const;
		/* ------------------------------------------------------------------------ */
		/*                             ft::vector::erase                            */
		/* -------------------------------- ..::.. -------------------------------- */
			// iterator	erase ( iterator position );
			// iterator	erase ( iterator first, iterator last );
		/* ------------------------------------------------------------------------ */
		/*                             ft::vector::front                            */
		/* -------------------------------- ..::.. -------------------------------- */
			T&	front( void ) { return ( _container[ 0 ] ); };
			const T&	front( void ) const { return ( _container[ 0 ] ); };
		/* ------------------------------------------------------------------------ */
		/*                         ft::vector::get_allocator                        */
		/* -------------------------------- ..::.. -------------------------------- */
			Alloc	get_allocator( void ) const { return ( _alloc ); };
		/* ------------------------------------------------------------------------ */
		/*                            ft::vector::insert                            */
		/* -------------------------------- ..::.. -------------------------------- */
			// iterator	insert ( iterator position, const value_type& val );
			// void	insert ( iterator position, size_type n, const value_type& val );
			// template <class InputIterator> void	insert ( iterator position, InputIterator first, InputIterator last );
		/* ------------------------------------------------------------------------ */
		/*                           ft::vector::max_size                           */
		/* -------------------------------- ..::.. -------------------------------- */
			std::size_t	max_size( void ) const { return ( _alloc.max_size() ); };
		/* ------------------------------------------------------------------------ */
		/*                          ft::vector::operator[]                          */
		/* -------------------------------- ..::.. -------------------------------- */
			T&	operator [] ( std::size_t n ) { return ( _container[ n ] ); };
			const T&	operator [] ( std::size_t n ) const { return ( _container[ n ] ); };
		/* ------------------------------------------------------------------------ */
		/*                           ft::vector::operator=                          */
		/* -------------------------------- ..::.. -------------------------------- */
			vector&	operator = ( const vector& x ) {
				if ( this != &x ) {
					clear();
					reserve( x.size() );
					_size = x.size();
					_capacity = x.size();
					_alloc = x.get_allocator();
					for ( std::size_t i = 0; i < _size; i++ )
						_alloc.construct( _container + i, x[ i ] );
				}
				return ( *this );
			};
		/* ------------------------------------------------------------------------ */
		/*                           ft::vector::pop_back                           */
		/* -------------------------------- ..::.. -------------------------------- */
			void	pop_back( void ) {
				_alloc.destroy( _container + _size - 1 );
				_size--;
			};
		/* ------------------------------------------------------------------------ */
		/*                           ft::vector::push_back                          */
		/* -------------------------------- ..::.. -------------------------------- */
			void	push_back ( const T& val ) {
				if ( _size == _capacity ) {
					T	temp[ _size ];
					for ( std::size_t i = 0; i < _size; i++ ) {
						temp[ i ] = _container[ i ];
						_alloc.destroy( _container + i );
					}
					if ( _capacity )
						_alloc.deallocate( _container, _capacity );
					_capacity += _capacity ? _capacity : 1;
					_container = _alloc.allocate( _capacity );
					for ( std::size_t i = 0; i < _size; i++ )
						_alloc.construct( _container + i, temp[ i ] );
				}
				_alloc.construct( _container + _size, val );
				_size++;
			};
		/* ------------------------------------------------------------------------ */
		/*                            ft::vector::rbegin                            */
		/* -------------------------------- ..::.. -------------------------------- */
			// reverse_iterator	rbegin( void );
			// const_reverse_iterator	rbegin( void ) const;
		/* ------------------------------------------------------------------------ */
		/*                             ft::vector::rend                             */
		/* -------------------------------- ..::.. -------------------------------- */
			// reverse_iterator	rend( void );
			// const_reverse_iterator	rend( void ) const;
		/* ------------------------------------------------------------------------ */
		/*                            ft::vector::reserve                           */
		/* -------------------------------- ..::.. -------------------------------- */
			void	reserve ( std::size_t n ) {
				if ( n > _capacity ) {
					T	temp[ _size ];
					for ( std::size_t i = 0; i < _size; i++ ) {
						temp[ i ] = _container[ i ];
						_alloc.destroy( _container + i );
					}
					if ( _capacity )
						_alloc.deallocate( _container, _capacity );
					_capacity = n;
					_container = _alloc.allocate( _capacity );
					for ( std::size_t i = 0; i < _size; i++ )
						_alloc.construct( _container + i, temp[ i ] );
				}
			};
		/* ------------------------------------------------------------------------ */
		/*                            ft::vector::resize                            */
		/* -------------------------------- ..::.. -------------------------------- */
			void	resize ( std::size_t n, T val = T() ) {
				if ( n < _size )
					for ( std::size_t i = _size; i < n; i++ )
						_alloc.destroy( _container + i );
				else if ( n > _size ) {
					reserve( n );
					for ( std::size_t i = _size; i < n; i++ )
						_alloc.construct( _container + i, val );
				}
				_size = n;
			};
		/* ------------------------------------------------------------------------ */
		/*                             ft::vector::size                             */
		/* -------------------------------- ..::.. -------------------------------- */
			std::size_t	size( void ) const { return ( _size ); };
		/* ------------------------------------------------------------------------ */
		/*                             ft::vector::swap                             */
		/* ------------------------------------------------------------------------ */
		/* -------------------------------- ..::.. -------------------------------- */
			void	swap ( vector& x ) {
				if ( this != &x ) {
					vector	temp = x;
					x._capacity = _capacity;
					x._size = _size;
					x._alloc = _alloc;
					x._container = _container;
					_capacity = temp._capacity;
					_size = temp._size;
					_alloc = temp._alloc;
					_container = temp._container;
				}
			};

	};

	template < class T, class Alloc > bool operator	== ( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {
		if ( lhs.size() != rhs.size() )
			return ( false );
		for ( std::size_t i = 0; i < lhs.size(); i++ )
			if ( lhs[ i ] != rhs[ i ] )
				return ( false );
		return ( true );
	};

	template < class T, class Alloc > bool operator	!= ( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {
		return ( ! ( lhs == rhs ) );
	};

	// template < class T, class Alloc > bool operator	<  ( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {
		// return (  );
	// };

	// template < class T, class Alloc > bool operator	<= ( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {
		// return (  );
	// };

	// template < class T, class Alloc > bool operator	>  ( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {
		// return (  );
	// };

	// template < class T, class Alloc > bool operator	>= ( const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs ) {
		// return (  );
	// };

	template < class T, class Alloc > void	swap ( vector< T, Alloc >& x, vector< T, Alloc >& y ) {
		x.swap( y );
	};

}
