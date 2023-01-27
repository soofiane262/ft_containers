/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <sel-mars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:03:51 by sel-mars          #+#    #+#             */
/*   Updated: 2023/01/27 19:45:11 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>
#include <list>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#define ESC "\e["
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

#define CHECK "\u2713"

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
	std::cout << str << "\tft : `" WHITE << ft << RESET "`\t"
			  << "std : `" WHITE << std << RESET "`\n";
	if ( ft == std ) return;
	throw except( "Wrong " + err + " value", line );
};

template < class T, class ft_ctr, class std_ctr > void
check( ft::stack< T, ft_ctr > &ft_stack, std::stack< T, std_ctr > &std_stack, const int line ) {
	compare( ft_stack.size(), std_stack.size(), "size\t", "size", line );
	if ( !std_stack.empty() ) {
		std::cout << DIM STRIKE;
		for ( int i = 0; i < 40; i++ ) std::cout << ' ';
		std::cout << RESET "\n";
		ft::stack< T, ft_ctr >	 ft_tmp;
		std::stack< T, std_ctr > std_tmp;
		while ( !std_stack.empty() ) {
			ft_tmp.push( ft_stack.top() );
			std_tmp.push( std_stack.top() );
			ft_stack.pop();
			std_stack.pop();
		}
		for ( std::size_t i = 0; !ft_tmp.empty(); i++ ) {
			std::cout << "@ " << i;
			compare( ft_tmp.top(), std_tmp.top(), "\t", "vector", line );
			ft_stack.push( ft_tmp.top() );
			std_stack.push( std_tmp.top() );
			ft_tmp.pop();
			std_tmp.pop();
		}
	}
	std::cout << "\n";
};
