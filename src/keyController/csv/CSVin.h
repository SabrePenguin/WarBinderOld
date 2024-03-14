#ifndef CSVIN_H
#define CSVIN_H
#include <vector>
#include <string>
#include <tuple>
#include <list>

/**
 * @brief Reads in the control_list.csv and selects the language, then returns a vector of keys
 * @param _filename: The name of the file to import
 * @param _language: The language to import
 * @return A vector of tuples in the <id, local_name, modifier> format
*/
std::vector<std::tuple<std::string, char, std::string, bool>> get_control( std::string _filename, std::string _language ) ;

/**
 * @brief A version of a csv parser that takes out only 2 pieces of information per row
 * @param _filename: The name of the file
 * @param _language: The language to use
 * @return A vector of tuples with 5 parameters
*/
std::vector<std::tuple<std::string, char, std::string, bool, bool>> get_binds( std::string _filename, std::string _language ) ;
//
/**
 * @brief A csv parser that generates a list of options in the system
 * @param _filename: The name of the file
 * @param _language: The language to use
 * @return A vector of tuple with data about each aspect in the following order:
 * internal_name, type, local_name, value, max_value, param or not, options
*/
std::vector<std::tuple<std::string, char, std::string, float, float, bool, std::list<std::string>>>
	get_options( std::string _filename, std::string _language ) ;
#endif // !CSVIN_H