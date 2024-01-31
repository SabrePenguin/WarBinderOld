#ifndef CSVIN_H
#define CSVIN_H
#include <vector>
#include <string>
#include <tuple>
#include <list>

std::vector<std::tuple<std::string, char, std::string, bool>> get_control( std::string _filename, std::string _language ) ;

std::vector<std::tuple<std::string, char, std::string, bool, bool>> get_binds( std::string _filename, std::string _language ) ;
//internal_name, type, local_name, value, max_value, param or not, options
std::vector<std::tuple<std::string, char, std::string, float, float, bool, std::list<std::string>>>
	get_options( std::string _filename, std::string _language ) ;
#endif // !CSVIN_H