/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:03:51 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/18 17:21:50 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

#define ESC "\033["
// Cursor
#define CURSOR( ln ) ESC ln "H"
#define CURSOR_HOME	 CURSOR( "0" )
//	Colors
#define RESET	ESC "0m"
#define RED		ESC "1;31m"
#define GREEN	ESC "1;32m"
#define BLUE	ESC "1;34m"
#define MAGENTA ESC "1;35m"
#define WHITE	ESC "1;37m"
//	Modes
#define DIM		ESC "2m"
#define ITALIC	ESC "3m"
#define ULINE	ESC "4m"
#define BLINK	ESC "5m"
#define _BLINK	ESC "25m"
#define STRIKE	ESC "9m"
#define _STRIKE ESC "29m"
//	Defs
#define TITLE DIM ITALIC ULINE "~ "
//	Special Characters
#define WARNING "\u26A0"
#define CHECK	"\u2713"

struct s_randomStruct {
	int			i;
	char	   *char_ptr;
	std::string str;
};

class except : public std::runtime_error {
  private:
	std::string msg;

  public:
	except( const std::string &arg, int line ) : std::runtime_error( arg ) {
		std::ostringstream			o;
		o << "\n" RED BLINK WARNING _BLINK "  Error @ line " << line << " : " << arg << RESET "\n";
		msg = o.str();
	}
	~except() throw() {}
	const char *what() const throw() { return msg.c_str(); }
};

template < class T > void compare( const T ft, const T std, const std::string str,
								   const std::string err, const int line ) {
	std::cout << str << "\tft : `" WHITE << ft << RESET "`\t"
			  << "std : `" WHITE << std << RESET "`\n";
	if ( ft == std ) return;
	throw except( "Wrong " + err + " value", line );
}

template < class T, class U >
void check( const ft::map< T, U > &ft_vec, const std::map< T, U > &std_vec, const int line ) {
	compare( ft_vec.size(), std_vec.size(), "size\t", "size", line );
	compare( ft_vec.capacity(), std_vec.capacity(), "capacity", "capacity", line );
	if ( !std_vec.empty() ) {
		std::cout << DIM STRIKE;
		for ( int i = 0; i < 40; i++ ) std::cout << ' ';
		std::cout << RESET "\n";
		for ( std::size_t i = 0; i < std_vec.size(); i++ ) {
			std::cout << "@ " << i;
			compare( ft_vec.at( i ), std_vec.at( i ), "\t", "vector", line );
		}
	}
	std::cout << "\n";
}
