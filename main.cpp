/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:37:52 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/22 11:30:10 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"
#include <ostream>

# define	compare( ctr1, ctr2 )	compare( ctr1, ctr2, __LINE__ )
# define	check( ctr1, ctr2 )		check( ctr1, ctr2, __LINE__ )

void	testResult( int error_count, const int total_tests, const std::string ctr ) {
	std::cout << MAGENTA "Vector Test " << total_tests << " of " << total_tests << RESET "\n\n";
	if ( std::system( "leaks Containers | grep '0 leaks' > .logs" ) )
		error_count++;
	std::system( "leaks Containers | tail -n +17" );
	if ( error_count )
		std::cout << RED WARNING"  ---------------------- ft::" << ctr
		<< " failed " << error_count << " test" << ( error_count == 1 ? "" : "s" )
		<< " ---------------------- " WARNING RESET "\n\n";
	else
		std::cout << GREEN CHECK" ---------------------- ft::" << ctr
		<< " succeeded all tests ---------------------- " CHECK RESET "\n\n";
}

void	printHead ( std::string str ) {
	(void)str;
	std::cout << BLUE;
	for ( int i = 0; i < 4; i++ ) {
		std::cout << "/* ";
		for ( int j = 0; j < 74; j++ ) {
			if ( i == 1 ) {
				std::cout << ' ';
			}
			else
				std::cout << '-';
		}
		std::cout << "*/\n";
	}
	std::cout << RESET "\n";
}

/*                                   vector                                  */

int	main( void ) {

	if ( ! std::system ( NULL ) ) {
		std::cout << RED "No command processor available\n";
		exit ( 1 );
	}
	std::system( "touch .logs; clear && printf '\e[3J'" );
	std::cout << std::boolalpha;
	srand( time( NULL ) );

	int					error_count = 0;
	int					test_idx = 0;
	int					total_tests;

	{

		{
			std::stringstream	ss;
			std::system( "cat main.cpp | grep 'Vector Test' | wc -l | awk '{print $1}' > .logs" );
			std::ifstream	logFile(".logs" );
			ss << logFile.rdbuf();
			ss >> total_tests;
			total_tests--;
		}
		printHead( "vector" );
		try { std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests << RESET "\n\n";
			// Default constructor
			ft::vector< int >	ft_vec;
			std::vector< int >	std_vec;
			check( ft_vec, std_vec );
			// push_back()
			for ( int i = 0, end = ( rand() % 10 ) + 1, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_vec.push_back( n );
				std_vec.push_back( n );
			}
			check( ft_vec, std_vec );
			// Copy constructor
			ft::vector< int >	ft_vec2( ft_vec );
			std::vector< int >	std_vec2( std_vec );
			check( ft_vec2, std_vec2 );
			// Copy assignement operator
			ft::vector< int >	ft_vec3;
			std::vector< int >	std_vec3;
			ft_vec3 = ft_vec;
			std_vec3 = std_vec;
			check( ft_vec3, std_vec3 );
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception& e ) {
			std::cout << e.what() << '\n';
			error_count++;
		} std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET << std::endl;
		while ( std::getchar() != '\n' );
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try { std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests << RESET "\n\n";
			int	size = ( rand() % 10 ) + 1;
			int	value = ( rand() % 10 );
			// Parametrized Constructor
			ft::vector< int >	ft_vec( size, value );
			std::vector< int >	std_vec( size, value );
			check( ft_vec, std_vec );
			size = ( rand() % 10 ) + 1;
			value = ( rand() % 10 );
			// assign()
			ft_vec.assign( size, value );
			std_vec.assign( size, value );
			check( ft_vec, std_vec );
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception& e ) {
			std::cout << e.what() << '\n';
			error_count++;
		} std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET << std::endl;
		while ( std::getchar() != '\n' );
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try { std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests << RESET "\n\n";
			// Default Constructor
			ft::vector< int >	ft_vec;
			std::vector< int >	std_vec;
			// push_back()
			for ( int i = 0, end = ( rand() % 10 ) + 1, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_vec.push_back( n );
				std_vec.push_back( n );
			}
			check( ft_vec, std_vec );
			// Const copy constructor
			const ft::vector< int >	c_ft_vec( ft_vec );
			const std::vector< int >	c_std_vec( std_vec );
			// T& back() and const T& back()
			std::cout << "back";
			compare( ft_vec.back(), std_vec.back() );
			std::cout << "c_back";
			compare( c_ft_vec.back(), c_std_vec.back() );
			// T& front() and const T& front()
			std::cout << "front";
			compare( ft_vec.front(), std_vec.front() );
			std::cout << "c_front";
			compare( c_ft_vec.front(), c_std_vec.front() );
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception& e ) {
			std::cout << e.what() << '\n';
			error_count++;
		} std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET << std::endl;
		while ( std::getchar() != '\n' );
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try { std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests << RESET "\n\n";
			int	size = ( rand() % 10 ) + 1;
			int	value = ( rand() % 10 );
			// Parametrized Constructor
			ft::vector< int >	ft_vec( size, value );
			std::vector< int >	std_vec( size, value );
			check( ft_vec, std_vec );
			size = ( rand() % 10 ) + 1;
			value = ( rand() % 10 );
			// clear()
			ft_vec.clear();
			std_vec.clear();
			// push_back()
			for ( int i = 0, end = ( rand() % 10 ) + 1, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_vec.push_back( n );
				std_vec.push_back( n );
			}
			check( ft_vec, std_vec );
			// clear()
			ft_vec.clear();
			std_vec.clear();
			check( ft_vec, std_vec );
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception& e ) {
			std::cout << e.what() << '\n';
			error_count++;
		} std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET << std::endl;
		while ( std::getchar() != '\n' );
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try { std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests << RESET "\n\n";
			// Default constructor
			ft::vector< int >	ft_vec;
			std::vector< int >	std_vec;
			// push_back()
			for ( int i = 0, end = ( rand() % 10 ) + 1, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_vec.push_back( n );
				std_vec.push_back( n );
			}
			check( ft_vec, std_vec );
			// pop_back()
			for ( int i = 0, end = std_vec.capacity() / 2; i < end; i++ ) {
				ft_vec.pop_back();
				std_vec.pop_back();
			}
			check( ft_vec, std_vec );
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception& e ) {
			std::cout << e.what() << '\n';
			error_count++;
		} std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET << std::endl;
		while ( std::getchar() != '\n' );
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try { std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests << RESET "\n\n";
			// Default constructor
			ft::vector< int >	ft_vec;
			std::vector< int >	std_vec;
			// push_back()
			for ( int i = 0, end = ( rand() % 10 ) + 1, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_vec.push_back( n );
				std_vec.push_back( n );
			}
			check( ft_vec, std_vec );
			// reserve() n <= capacity()
			ft_vec.reserve( 1 );
			std_vec.reserve( 1 );
			check( ft_vec, std_vec );
			// reserve() n > capacity
			ft_vec.reserve( 35 );
			std_vec.reserve( 35 );
			check( ft_vec, std_vec );
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception& e ) {
			std::cout << e.what() << '\n';
			error_count++;
		} std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET << std::endl;
		while ( std::getchar() != '\n' );
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try { std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests << RESET "\n\n";
			// Default constructor
			ft::vector< int >	ft_vec;
			std::vector< int >	std_vec;
			// push_back()
			for ( int i = 0, end = ( rand() % 10 ) + 1, n; i < end; i++ ) {
				n = ( rand() % 10 );
				ft_vec.push_back( n );
				std_vec.push_back( n );
			}
			check( ft_vec, std_vec );
			// resize() n <= capacity()
			ft_vec.resize( 35 );
			std_vec.resize( 35 );
			check( ft_vec, std_vec );
			// resize() n > capacity
			ft_vec.resize( 5 );
			std_vec.resize( 5 );
			check( ft_vec, std_vec );
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception& e ) {
			std::cout << e.what() << '\n';
			error_count++;
		} std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET << std::endl;
		while ( std::getchar() != '\n' );
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		try { std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests << RESET "\n\n";
			// Default constructor
			ft::vector< int >	ft_vec;
			std::vector< int >	std_vec;
			ft::vector< int >	ft_vec2;
			std::vector< int >	std_vec2;
			// push_back()
			for ( int i = 0, end = ( rand() % 5 ) + 1, n1, n2; i < end; i++ ) {
				n1 = ( rand() % 10 );
				ft_vec.push_back( n1 );
				std_vec.push_back( n1 );
				n2 = ( rand() % 10 );
				ft_vec2.push_back( n2 );
				std_vec2.push_back( n2 );
			}
			check( ft_vec, std_vec );
			check( ft_vec2, std_vec2 );
			// swap()
			ft::swap( ft_vec, ft_vec2 );
			std::swap( std_vec, std_vec2 );
			check( ft_vec, std_vec );
			check( ft_vec2, std_vec2 );
			std::cout << "\n" GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception& e ) {
			std::cout << e.what() << '\n';
			error_count++;
		} std::cout << WHITE << "Press \u21B5  to proceed with the next vector test" << RESET << std::endl;
		while ( std::getchar() != '\n' );
		std::system( "printf '\e[H\e[J\e[3J'" );
		printHead( "vector" );
		// endOf vector tests
		testResult( error_count, total_tests, "vector");
		std::cout << WHITE << "Press \u21B5  to proceed with the next container" << RESET << std::endl;
		while ( std::getchar() != '\n' );
		std::system( "printf '\e[H\e[J'" );

	}

	std::system( "rm -f .logs" );

	return ( 0 );

}
