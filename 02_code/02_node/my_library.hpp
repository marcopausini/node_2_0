/****************************************
* my_library
*****************************************/

#ifndef _MY_LYBRARY_HPP_
#define _MY_LYBRARY_HPP_

#include <iostream>
#include <sstream>
#include <iomanip> 
#include <string>
#include <vector>
#include <cstring>
#include <cctype>

	// convert integer to hex string
	std::string int_to_hex( unsigned int i, bool fill );
	
	// break string into words separated by white space
	std::vector<std::string> split(const std::string& s);
	
	// detect if a line is comment
	bool is_comment( const std::string& line, const std::string& marker);

#endif
