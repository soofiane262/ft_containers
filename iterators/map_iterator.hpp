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

#include "iterator_traits.hpp"

#include <iterator> // bidirectional_iterator_tag

namespace ft {
	template < class NodeType > class map_iterator {
	  private:
		template < class FirstType, class SecondType >
		friend bool operator==( const ft::map_iterator< FirstType >&  lhs,
								const ft::map_iterator< SecondType >& rhs );
		template < class FirstType, class SecondType >
		friend bool operator!=( const ft::map_iterator< FirstType >&  lhs,
								const ft::map_iterator< SecondType >& rhs );

	  public:
		/* Member Types ───────────────────────────────────────────────────────────────────── */
		typedef typename NodeType::value_type			 value_type;
		typedef typename NodeType::reference			 reference;
		typedef typename NodeType::pointer				 pointer;
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
		map_iterator& operator=( map_iterator& other ) {
			if ( this != &other ) _nd = other._nd;
			return *this;
		}
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
			++_nd;
			return tmp;
		}
		map_iterator& operator--( void ) {
			_nd = _nd->previous();
			return *this;
		}
		map_iterator operator--( int ) {
			map_iterator tmp = *this;
			--_nd;
			return tmp;
		}
	};

	template < class FirstType, class SecondType >
	bool operator==( const ft::map_iterator< FirstType >&  lhs,
					 const ft::map_iterator< SecondType >& rhs ) {
		return lhs._nd == rhs._nd;
	}
	template < class FirstType, class SecondType >
	bool operator!=( const ft::map_iterator< FirstType >&  lhs,
					 const ft::map_iterator< SecondType >& rhs ) {
		return lhs._nd != rhs._nd;
	}
} // namespace ft
