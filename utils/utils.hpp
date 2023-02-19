/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:18:08 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/19 15:33:09 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>

namespace ft {
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	/*                                      enable_if                                      */
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	template < bool Cond, class T = void > struct enable_if {};
	template < class T > struct enable_if< true, T > {
		typedef T type;
	}; // enable_if
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	/*                                       is_same                                       */
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	template < class T, class U > struct is_same {
		static const bool value = false;
	}; // is_same : false
	template < class T > struct is_same< T, T > {
		static const bool value = true;
	}; // is_same : true
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	/*                                        equal                                        */
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	template < class InputIterator1, class InputIterator2 >
	bool equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ) {
		while ( first1 != last1 ) {
			if ( !( *first1 == *first2 ) ) return ( false );
			++first1;
			++first2;
		}
		return ( true );
	} // equal : predicate ==
	template < class InputIterator1, class InputIterator2, class BinaryPredicate >
	bool equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
				BinaryPredicate pred ) {
		while ( first1 != last1 ) {
			if ( !pred( *first1, *first2 ) ) return ( false );
			++first1;
			++first2;
		}
		return ( true );
	} // equal : param_predicate
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	/*                               lexicographical_compare                               */
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	template < class InputIterator1, class InputIterator2 >
	bool lexicographical_compare( InputIterator1 first1, InputIterator1 last1,
								  InputIterator2 first2, InputIterator2 last2 ) {
		while ( first1 != last1 ) {
			if ( first2 == last2 || *first2 < *first1 ) return ( false );
			else if ( *first1 < *first2 )
				return ( true );
			++first1;
			++first2;
		}
		return ( first2 != last2 );
	} // lexicographical_compare : compare <
	template < class InputIterator1, class InputIterator2, class Compare >
	bool lexicographical_compare( InputIterator1 first1, InputIterator1 last1,
								  InputIterator2 first2, InputIterator2 last2, Compare comp ) {
		while ( first1 != last1 ) {
			if ( first2 == last2 || comp( *first2, *first1 ) ) return ( false );
			else if ( comp( *first1, *first2 ) )
				return ( true );
			++first1;
			++first2;
		}
		return ( first2 != last2 );
	} // lexicographical_compare : param_compare
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	/*                                     is_integral                                     */
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	template < class T > struct is_integral {
		typedef bool			value_type;
		static const value_type value =
			std::numeric_limits< T >::is_integer && std::numeric_limits< T >::is_specialized;
	}; // is_integral
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	/*                                         pair                                        */
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	template < class T1, class T2 > struct pair {
		/* member types ───────────────────────────────────────────────────────────────────── */
		typedef T1 first_type;
		typedef T2 second_type;
		/* member objects ─────────────────────────────────────────────────────────────────── */
		first_type	first;
		second_type second;
		/* ctors ──────────────────────────────────────────────────────────────────────────── */
		pair() : first( first_type() ), second( second_type() ) {}
		pair( const first_type& a, const second_type& b ) : first( a ), second( b ) {}
		template < class U, class V > pair( const ft::pair< U, V >& pr )
			: first( pr.first ), second( pr.second ) {}
		/* assignment ─────────────────────────────────────────────────────────────────────── */
		pair& operator=( const pair& pr ) {
			first  = pr.first;
			second = pr.second;
			return *this;
		}
	}; // pair
	template < class T1, class T2 >
	bool operator==( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs ) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
	template < class T1, class T2 >
	bool operator!=( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs ) {
		return !( lhs == rhs );
	}
	template < class T1, class T2 >
	bool operator<( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs ) {
		return lhs.first < rhs.first || ( !( rhs.first < lhs.first ) && lhs.second < rhs.second );
	}
	template < class T1, class T2 >
	bool operator<=( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs ) {
		return !( rhs < lhs );
	}
	template < class T1, class T2 >
	bool operator>( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs ) {
		return rhs.first < lhs.first || ( !( lhs.first < rhs.first ) && rhs.second < lhs.second );
	}
	template < class T1, class T2 >
	bool operator>=( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs ) {
		return !( lhs < rhs );
	}
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	/*                                      make_pair                                      */
	/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
	template < class T1, class T2 > pair< T1, T2 > make_pair( const T1 x, const T2 y ) {
		return ft::pair< T1, T2 >( x, y );
	} // make_pair
} // namespace ft
