/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:03:51 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/22 19:59:27 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <vector>
# include "vector/vector.hpp"
# include <iostream>
# include <algorithm>
# include <sstream>
# include <string>
# include <stdexcept>
# include <cstdlib>
# include <ctime>
# include <fstream>

# define	RESET	"\e[0m"
# define	RED		"\e[1;31m"
# define	GREEN	"\e[1;32m"
# define	BLUE	"\e[1;34m"
# define	MAGENTA	"\e[1;35m"
# define	WHITE	"\e[1;37m"

# define	WARNING	"\u26A0"
# define	CHECK	"\u2713"

class	except : public std::runtime_error {

	private:
    	std::string msg;

	public:
    	except( const std::string &arg, int line ) : std::runtime_error( arg ) {
        	std::ostringstream o;
        	o << "\n" RED WARNING "  Error @ line " << line << " : " << arg << RESET "\n";
        	msg = o.str();
    	}
    	~except() throw() {}
    	const char *what() const throw() {
        	return msg.c_str();
    }
};

template< class T > void	compare( const T& ft_vec, const T& std_vec, const int line ) {
	(void)line;
	std::cout << "\tft_vec\t\t: `" WHITE << ft_vec << RESET "`\t\t" << "std_vec\t\t\t: `" WHITE << std_vec << RESET "`\n";
	if ( ft_vec != std_vec )
		throw except( "Wrong vector value", line );
};

template< class T > void	check( const ft::vector< T >& ft_vec, const std::vector< T >& std_vec, const int line ) {
	std::cout << "ft_vec.size()\t\t: `" WHITE << ft_vec.size() << RESET "`\t\tstd_vec.size()\t\t: `" WHITE << std_vec.size() << RESET "`\n";
	if ( ft_vec.size() != std_vec.size() )
		throw except( "Wrong vector size", line );
	std::cout << "ft_vec.capacity()\t: `" WHITE << ft_vec.capacity() << RESET "`\t\tstd_vec.capacity()\t: `" WHITE << std_vec.capacity() << RESET "`\n\n";
	if ( ft_vec.capacity() != std_vec.capacity() )
		throw except( "Wrong vector capacity", line );
	for ( std::size_t i = 0; i < std_vec.size(); i++ ) {
		std::cout << "@ " << i;
		compare( ft_vec.at( i ), std_vec.at( i ), line );
	}
	std::cout << "\n";
};
