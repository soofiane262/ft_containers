/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:37:52 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/19 19:50:28 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

# define	check( ctr1, ctr2 )	check( ctr1, ctr2, __LINE__ )

void	testResult( int error_count, std::string ctr ) {
	if ( error_count )
		std::cout << RED WARNING"  ---------------------- ft::" << ctr << " failed " << error_count << " test" << ( error_count == 1 ? "" : "s" ) << " ---------------------- " WARNING RESET "\n\n";
	else
		std::cout << GREEN CHECK" ---------------------- ft::" << ctr << " succeeded all tests ---------------------- " CHECK RESET "\n\n";
}

std::string	ft_exec( std::string command ) {
	char buffer[ 128 ];
	std::string result = std::string();

	std::FILE* pipe = popen( command.c_str(), "r" );
	if ( ! pipe )
		exit( 1 );

	while ( ! feof( pipe ) ) {

	if ( fgets( buffer, 128, pipe ) != NULL )
		result += buffer;
	}

	pclose( pipe );
	return ( result );
}

int	main( void ) {

	std::cout << std::boolalpha;
	srand( time( NULL ) );

	int					error_count = 0;
	int					test_idx = 0;
	int					total_tests;
	std::stringstream	ss;

	ss << ft_exec( "cat main.cpp | grep 'Vector Test' | wc -l" );
	ss >> total_tests;
	total_tests--;

	{

		std::cout << BLUE "/* ------------------------------------------------------------------------- */\n"
		<< "/*                                   vector                                  */\n"
		<< "/* ------------------------------------------------------------------------- */\n" RESET "\n";

		try { std::cout << MAGENTA "Vector Test " << ++test_idx << " of " << total_tests << RESET "\n\n";

			ft::vector< int >	ft_vec;
			std::vector< int >	std_vec;

			check( ft_vec, std_vec );

			int	n;
			for ( int i = 0, end = 200; i < end; i++ ) {
				n = rand() % 100;
				ft_vec.push_back( n );
				std_vec.push_back( n );
			check( ft_vec, std_vec );
			}
			check( ft_vec, std_vec );

			std::cout << GREEN CHECK " Sucess" RESET "\n\n";
		} catch ( std::exception& e ) {
			std::cout << e.what() << '\n';
			error_count++;
		}

		testResult( error_count, "vector");

	}

	std::system( "leaks Containers | tail -n +17" );

	return ( 0 );

}
