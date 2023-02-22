/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:09:54 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/19 15:38:06 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>	// ptrdiff_t
#include <iterator> // bidirectional_iterator_tag

namespace ft {
	template < class T, class NodeType > class map_iterator {
	  private:
		template < class T1, class NodeType1, class T2, class NodeType2 >
		friend bool operator==( const ft::map_iterator< T1, NodeType1 >& lhs,
								const ft::map_iterator< T2, NodeType2 >& rhs );
		template < class T1, class NodeType1, class T2, class NodeType2 >
		friend bool operator!=( const ft::map_iterator< T1, NodeType1 >& lhs,
								const ft::map_iterator< T2, NodeType2 >& rhs );

	  public:
		/* Member Types ───────────────────────────────────────────────────────────────────── */
		typedef std::ptrdiff_t							 difference_type;
		typedef T										 value_type;
		typedef value_type*								 pointer;
		typedef value_type&								 reference;
		typedef typename std::bidirectional_iterator_tag iterator_category;

	  protected:
		NodeType* _nd;

	  public:
		/* ctors ──────────────────────────────────────────────────────────────────────────── */
		map_iterator( void ) : _nd( NULL ) {};
		map_iterator( NodeType* other ) : _nd( other ) {}
		/* dtor ───────────────────────────────────────────────────────────────────────────── */
		~map_iterator( void ) { _nd = NULL; }
		/* assignment ─────────────────────────────────────────────────────────────────────── */
		map_iterator& operator=( const map_iterator& other ) {
			if ( this != &other ) _nd = other._nd;
			return *this;
		}
		/* conversion ─────────────────────────────────────────────────────────────────────── */
		reference operator*( void ) const { return _nd->_elt; }
		pointer	  operator->( void ) const { return &( operator*() ); }
		/* operations ─────────────────────────────────────────────────────────────────────── */
		map_iterator& operator++( void ) {
			_nd = _nd->next();
			return *this;
		}
		map_iterator operator++( int ) {
			map_iterator tmp = *this;
			_nd				 = _nd->next();
			return tmp;
		}
		map_iterator& operator--( void ) {
			_nd = _nd->previous();
			return *this;
		}
		map_iterator operator--( int ) {
			map_iterator tmp = *this;
			_nd				 = _nd->previous();
			return tmp;
		}
	};

	template < class T1, class NodeType1, class T2, class NodeType2 >
	bool operator==( const ft::map_iterator< T1, NodeType1 >& lhs,
					 const ft::map_iterator< T2, NodeType2 >& rhs ) {
		return lhs._nd->eq( rhs._nd );
	}
	template < class T1, class NodeType1, class T2, class NodeType2 >
	bool operator!=( const ft::map_iterator< T1, NodeType1 >& lhs,
					 const ft::map_iterator< T2, NodeType2 >& rhs ) {
		return lhs._nd->diff( rhs._nd );
	}

} // namespace ft
