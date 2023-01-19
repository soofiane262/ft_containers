/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:03:51 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/19 19:41:38 by sel-mars         ###   ########.fr       */
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
    	except( const std::string &arg, const std::string &pb, int line ) : std::runtime_error( arg ) {
        	std::ostringstream o;
        	o << pb << "\n\n" RED WARNING "  Error @ line " << line << " : " << arg << RESET "\n";
        	msg = o.str();
    	}
    	~except() throw() {}
    	const char *what() const throw() {
        	return msg.c_str();
    }
};

template< class T > void	check( const ft::vector< T > ft_vec, const std::vector< T > std_vec, const int line ) {
    std::stringstream o;
	o << "ft_vec.size()\t\t: `" WHITE << ft_vec.size() << RESET "`\t\tstd_vec.size()\t\t: `" WHITE << std_vec.size() << RESET "`";
	if ( ft_vec.size() != std_vec.size() )
		throw except( "Wrong vector size", o.str(), line );
	std::cout << o.rdbuf() << '\n';
	o.str( std::string() );
	o << "ft_vec.capacity()\t: `" WHITE << ft_vec.capacity() << RESET "`\t\tstd_vec.capacity()\t: `" WHITE << std_vec.capacity() << RESET "`";
	if ( ft_vec.capacity() != std_vec.capacity() )
		throw except( "Wrong vector capacity", o.str(), line );
	std::cout << o.rdbuf() << "\n\n";
	for ( std::size_t i = 0; i < std_vec.size(); i++ ) {
		o.str( std::string() );
		o << "ft_vec[" << i << "]\t\t: `" WHITE << ft_vec.at( i ) << RESET "`\t\t" << "std_vec[" << i << "]\t\t: `" WHITE << std_vec.at( i ) << RESET "`";
		if ( ft_vec.at( i ) != std_vec.at( i ) )
			throw except( "Wrong vector value", o.str(), line );
		std::cout << o.rdbuf() << '\n' ;
	}
	std::cout << '\n';
};
