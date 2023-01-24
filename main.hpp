/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:03:51 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/23 20:09:56 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/algorithm.hpp"
#include "vector/vector.hpp"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
//	Colors
#define RESET	"\e[0m"
#define RED		"\e[1;31m"
#define GREEN	"\e[1;32m"
#define BLUE	"\e[1;34m"
#define MAGENTA "\e[1;35m"
#define WHITE	"\e[1;37m"
//	Modes
#define DIM	   "\e[2m"
#define ITALIC "\e[3m"
#define ULINE  "\e[4m"
//	Defs
#define TITLE DIM ITALIC ULINE "~ "
//	Special Characters
#define WARNING "\u26A0"
#define CHECK	"\u2713"

class except : public std::runtime_error {
  private:
	std::string msg;

  public:
	except( const std::string &arg, int line ) : std::runtime_error( arg ) {
		std::ostringstream o;
		o << "\n" RED	   WARNING "  Error @ line " << line << " : " << arg << RESET "\n";
		msg = o.str();
	}
	~except() throw() {}
	const char *what() const throw() { return msg.c_str(); }
};

template < class T > void compare( const T ft, const T std, const std::string str,
								   const std::string err, const int line ) {
	std::cout << str << "\tft\t: `" WHITE << ft << RESET "`\t\t"
			  << "std\t: `" WHITE << std << RESET "`\n";
	if ( ft != std ) throw except( "Wrong " + err + " value", line );
};

template < class T >
void check( const ft::vector< T > &ft_vec, const std::vector< T > &std_vec, const int line ) {
	compare( ft_vec.size(), std_vec.size(), "size\t", "size", line );
	compare( ft_vec.capacity(), std_vec.capacity(), "capacity", "capacity", line );
	for ( std::size_t i = 0; i < std_vec.size(); i++ ) {
		std::cout << "@ " << i;
		compare( ft_vec.at( i ), std_vec.at( i ), "", "vector", line );
	}
	std::cout << "\n";
};
