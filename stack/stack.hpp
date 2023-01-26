/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:46:28 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/27 00:53:51 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../vector/vector.hpp"

#include <cstddef>

namespace ft {
	template < class T, class Container = vector< T > > class stack {
	  public:
		/* ------------------------------------------------------------------------ */
		/*                               Member Types                               */
		/* ------------------------------------------------------------------------ */
		typedef T									value_type;
		typedef Container							container_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference const_reference;

		template < class U, class U_Container > friend bool
		operator==( const stack< U, U_Container >& lhs, const stack< U, U_Container >& rhs );
		template < class U, class U_Container > friend bool
		operator!=( const stack< U, U_Container >& lhs, const stack< U, U_Container >& rhs );
		template < class U, class U_Container > friend bool
		operator<( const stack< U, U_Container >& lhs, const stack< U, U_Container >& rhs );
		template < class U, class U_Container > friend bool
		operator<=( const stack< U, U_Container >& lhs, const stack< U, U_Container >& rhs );
		template < class U, class U_Container > friend bool
		operator>( const stack< U, U_Container >& lhs, const stack< U, U_Container >& rhs );
		template < class U, class U_Container > friend bool
		operator>=( const stack< U, U_Container >& lhs, const stack< U, U_Container >& rhs );

	  protected:
		container_type c;

	  public:
		/* ------------------------------------------------------------------------ */
		/*                             Member Functions                             */
		/*                                  ..::..                                  */
		/* ------------------------------ Constructor ----------------------------- */
		explicit stack( const container_type& ctnr = container_type() ) : c( ctnr ) {};
		/* ------------------------------ Destructor ------------------------------ */
		~stack() {};
		/* ------------------------------ operator = ------------------------------ */
		stack& operator=( const stack& other ) {
			c = other.c;
			return *this;
		};
		/* ------------------------------------------------------------------------ */
		/*                              Element Access                              */
		/*                                  ..::..                                  */
		/* ---------------------------------- top --------------------------------- */
		reference		top( void ) { return c.back(); };
		const_reference top( void ) const { return c.back(); };
		/* ------------------------------------------------------------------------ */
		/*                                 Capacity                                 */
		/*                                  ..::..                                  */
		/* --------------------------------- empty -------------------------------- */
		bool empty( void ) const { return c.empty(); };
		/* --------------------------------- size --------------------------------- */
		size_type size( void ) const { return c.size(); };
		/* ------------------------------------------------------------------------ */
		/*                                 Modifiers                                */
		/*                                  ..::..                                  */
		/* --------------------------------- push --------------------------------- */
		void push( const value_type& val ) { c.push_back( val ); };
		/* ---------------------------------- pop --------------------------------- */
		void pop( void ) { c.pop_back(); };
	};
	template < class T, class Container >
	bool operator==( const stack< T, Container >& lhs, const stack< T, Container >& rhs ) {
		return lhs.c == rhs.c;
	};
	template < class T, class Container >
	bool operator!=( const stack< T, Container >& lhs, const stack< T, Container >& rhs ) {
		return lhs.c != rhs.c;
	};
	template < class T, class Container >
	bool operator<( const stack< T, Container >& lhs, const stack< T, Container >& rhs ) {
		return lhs.c < rhs.c;
	};
	template < class T, class Container >
	bool operator<=( const stack< T, Container >& lhs, const stack< T, Container >& rhs ) {
		return lhs.c <= rhs.c;
	};
	template < class T, class Container >
	bool operator>( const stack< T, Container >& lhs, const stack< T, Container >& rhs ) {
		return lhs.c > rhs.c;
	};
	template < class T, class Container >
	bool operator>=( const stack< T, Container >& lhs, const stack< T, Container >& rhs ) {
		return lhs.c >= rhs.c;
	};
} // namespace ft
