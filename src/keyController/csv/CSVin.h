#ifndef CSVIN_H
#define CSVIN_H
#include <vector>
#include <string>
#include <tuple>

std::vector<std::tuple<std::string, char, std::string, bool>> get_control( std::string _filename, std::string _language ) ;

std::vector<std::tuple<std::string, char, std::string, bool>> get_binds( std::string _filename, std::string _language ) ;
#endif // !CSVIN_H