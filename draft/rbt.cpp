/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:57:44 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/03 22:21:52 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbt.hpp"

#include <cstdlib>
#include <vector>

int main( void ) {
	std::system( "clear" );
	{
		rbt< int > n;
		n.insert( 3 );
		n.insert( 4 );
		n.insert( 5 );
		// n.insert( 3 );
		// n.insert( 2 );
		// n.insert( 4 );
		// n.insert( 5 );
		// n.insert( 2 );
		// n.del( 6 );
		// n.del( 4 );
		// n.del( 2 );
	}
	// std::system( "leaks a.out" );

	return 0;
}
