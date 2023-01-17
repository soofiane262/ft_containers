/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:37:52 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/17 20:43:38 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <stdexcept>
# include <vector>
# include "vector/Vector.hpp"

int	main( void ) {

	std::cout << std::boolalpha;

	{

		ft::vector< int >	vec( 10, 3 );
		ft::vector< int >	vec2( 8, 1 );


		vec.log();
		std::cout << '\n';
		vec.assign( 6, 2 );
		vec.pop_back();
		vec.log();
		std::cout << '\n';
		try {
			std::cout << "vector at 5 : " << vec.at( 5 ) << '\n';
		} catch ( std::out_of_range except ) {
			std::cout << except.what() << '\n';
		}
		std::cout << "front : " << vec.front() << '\n';
		std::cout << "back : " << vec.back() << '\n';
		std::cout << "empty : " << vec.empty() << '\n';
		std::cout << "max_size : " << vec.max_size() << '\n';

		vec.push_back( 5 );
		vec.log();
		std::cout << "size : " << vec.size() << '\n';
		std::cout << "capacity : " << vec.capacity() << '\n';
		
		vec.reserve( 12 );

		std::cout << "----------------------------------\n";
		std::cout << "vec : \n";
		vec.log();



		std::cout << "vec2 : \n";
		vec2.log();

		std::cout << "debug start\n";
		vec.swap( vec2 );
		std::cout << "debug end\n";
		std::cout << "----------------------------------\n";
		std::cout << "vec : \n";
		vec.log();
		std::cout << "vec2 : \n";
		vec2.log();
	}

	// system( "leaks a.out" );

	return ( 0 );

}
