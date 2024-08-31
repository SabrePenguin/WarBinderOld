#ifndef CSVIN_H
#define CSVIN_H
#include <vector>
#include <string>
#include <tuple>
#include <list>

/**
 * @brief A vector of tuples. Tuple is in order <internal id, mode, local_name, modifier>
 */
typedef std::vector<std::tuple<std::string, char, std::string, bool>> t_control_raw ;

/**
 * @brief A vector of tuples. Tuple is in order <internal id, mode, sub mode, section, local name, axis, required>
 */
typedef std::vector<std::tuple<std::string, char, char, std::string, std::string, bool, bool>> t_binds_raw ;

/**
 * @brief A vector of tuples. Tuple is in order of <internal id, section, option type, local name,
 *  base value, highest value, parameter, and list of options>
 */
typedef 
std::vector<std::tuple<std::string, std::string, char, char, std::string, float, float, bool, std::list<std::string>>> 
t_options_raw ;

/**
 * @brief Reads in the control_list.csv and selects the language, then returns a vector of keys
 * @param _filename: The name of the file to import
 * @param _language: The language to import
 * @return a t_control_raw
*/
t_control_raw get_control( std::string _filename, std::string _language ) ;

/**
 * @brief A version of a csv parser that takes out only 2 pieces of information per row
 * @param _filename: The name of the file
 * @param _language: The language to use
 * @return a t_binds_raw
*/
t_binds_raw get_binds( std::string _filename, std::string _language ) ;

/**
 * @brief A csv parser that generates a list of options in the system
 * @param _filename: The name of the file
 * @param _language: The language to use
 * @return A vector of tuple with data about each aspect in the following order:
 * internal_name, section, type, mode, local_name, value, max_value, param or not, options
*/
t_options_raw get_options( std::string _filename, std::string _language ) ;

#endif // !CSVIN_H