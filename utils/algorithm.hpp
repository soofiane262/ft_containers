/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:18:08 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/23 19:33:23 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <limits>
namespace ft {

	/* -------------------------------------------------------------------------- */
	/*                                    equal                                   */
	/* -------------------------------------------------------------------------- */
	template < class InputIterator1, class InputIterator2 >
	bool equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ) {
		while ( first1 != last1 ) {
			if ( !( *first1 == *first2 ) ) return ( false );
			++first1;
			++first2;
		}
		return ( true );
	};
	template < class InputIterator1, class InputIterator2, class BinaryPredicate >
	bool equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
				BinaryPredicate pred ) {
		while ( first1 != last1 ) {
			if ( !pred( *first1, *first2 ) ) return ( false );
			++first1;
			++first2;
		}
		return ( true );
	};
	/* -------------------------------------------------------------------------- */
	/*                           lexicographical_compare                          */
	/* -------------------------------------------------------------------------- */
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
	};
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
	};
	/* -------------------------------------------------------------------------- */
	/*                                  enable_if                                 */
	/* -------------------------------------------------------------------------- */
	template < bool Cond, class T = void > struct enable_if {};
	template < class T > struct enable_if< true, T > {
		typedef T type;
	};

	template < class T, class U > struct is_same {
		static const bool value = false;
	};
	template < class T > struct is_same< T, T > {
		static const bool value = true;
	};

	/* -------------------------------------------------------------------------- */
	/*                                 is_integral                                */
	/* -------------------------------------------------------------------------- */
	template < class T > struct is_integral {
		typedef bool			value_type;
		static const value_type value =
			std::numeric_limits< T >::is_integer && std::numeric_limits< T >::is_specialized;
	};
} // namespace ft
