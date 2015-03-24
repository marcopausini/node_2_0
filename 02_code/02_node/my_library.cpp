#include "my_library.hpp"

using namespace std;

//
std::string int_to_hex( unsigned int i, bool fill )
{
	std::stringstream stream;
	if (fill){
		//stream << "0x" 
		stream << std::setfill ('0') << std::setw(sizeof(unsigned int)*2) << std::hex << i;
	}
   	else{ stream << std::hex << i;}
  	return stream.str();
}

//
std::vector<std::string> split(const std::string& s)
{
	vector<string> ret;
	typedef string::size_type string_size;
	string_size i = 0;
	
	while (i!=s.size()){
		// ignore spaces -> i indedx of first character not space
		while (i!=s.size() && isspace(s[i])) {++i;}
		// init second delimiter
		string_size j = i;
		// move to next space
		while (j!=s.size() && !isspace(s[j])) {++j;}
		// extract word
		if (i!=j){
			ret.push_back(s.substr(i,j-i));
			i=j;
		}
	}
	return ret;
}

//
bool is_comment( const std::string& line, const std::string& marker )
{
	typedef string::size_type string_size;
	string_size i = 0;
	string_size n = marker.size();
	
	return (line.substr(i,n) == marker);
	
}
