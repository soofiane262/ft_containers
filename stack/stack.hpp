/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:46:28 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/24 13:28:05 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../vector/vector.hpp"

namespace ft {
	template < class T, class Container = vector< T > > class stack {
	  public:
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type  size_type;
		typedef Container					   container_type;

	  private:
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
		Container c;

	  public:
		explicit stack( const Container& ctnr = Container() ) : c( ctnr ) {}
		bool			  empty( void ) const { return c.empty(); }
		size_type		  size( void ) const { return c.size(); }
		value_type&		  top( void ) { return c.back(); }
		const value_type& top( void ) const { return c.back(); }
		void			  push( const value_type& val ) { c.push_back( val ); }
		void			  pop( void ) { c.pop_back(); }
	};
	template < class T, class Container >
	bool operator==( const stack< T, Container >& lhs, const stack< T, Container >& rhs ) {
		return lhs.c == rhs.c;
	}
	template < class T, class Container >
	bool operator!=( const stack< T, Container >& lhs, const stack< T, Container >& rhs ) {
		return lhs.c != rhs.c;
	}
	template < class T, class Container >
	bool operator<( const stack< T, Container >& lhs, const stack< T, Container >& rhs ) {
		return lhs.c < rhs.c;
	}
	template < class T, class Container >
	bool operator<=( const stack< T, Container >& lhs, const stack< T, Container >& rhs ) {
		return lhs.c <= rhs.c;
	}
	template < class T, class Container >
	bool operator>( const stack< T, Container >& lhs, const stack< T, Container >& rhs ) {
		return lhs.c > rhs.c;
	}
	template < class T, class Container >
	bool operator>=( const stack< T, Container >& lhs, const stack< T, Container >& rhs ) {
		return lhs.c >= rhs.c;
	}
} // namespace ft
