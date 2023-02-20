/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:03:51 by sel-mars          #+#    #+#             */
/*   Updated: 2023/02/20 16:38:16 by sel-mars         ###   ########.fr       */
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

template < class TIter, class UIter > void
compare( TIter ft_it, UIter std_it, const std::string str, const std::string err, const int line ) {
	std::cout << str << "\tft : `" WHITE << ft_it->first << " => " << ft_it->second << RESET "`\t"
			  << "std : `" WHITE << std_it->first << " => " << std_it->second << RESET "`\n";
	if ( ft_it->first == std_it->first && ft_it->second == std_it->second ) return;
	throw except( "Wrong " + err + " value", line );
}

template < class T, class U >
void check( ft::map< T, U > &ft_mp, std::map< T, U > &std_mp, const int line ) {
	compare( ft_mp.size(), std_mp.size(), "size\t", "size", line );
	if ( !std_mp.empty() ) {
		std::cout << DIM STRIKE;
		for ( int i = 0; i < 40; i++ ) std::cout << ' ';
		std::cout << RESET "\n";
		typename ft::map< T, U >::iterator	ft_it;
		typename std::map< T, U >::iterator std_it;
		for ( ft_it = ft_mp.begin(), std_it = std_mp.begin();
			  ft_it != ft_mp.end() || std_it != std_mp.end(); ++ft_it, ++std_it ) {
			compare( ft_it, std_it, "", "map", line );
		}
	}
	std::cout << "\n";
}
