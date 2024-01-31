#include <unordered_map>
#include <string>
#include <tuple>
#include "Options.h"

/**
 * @brief The basic Options constructor
 * @tparam T: Int, Boolean, or Float
 * @param _cur_val: The current value from the user
 * @param _max: The maximum value it can be. For booleans, this is true
 * @param _option: Whether this option is a middle or lower file section (may be removed)
*/
template<class T> 
Options<T>::Options( T _cur_val, T _max, bool _option )
	: max( _max ), value( _cur_val ), option( _option )
{
}

/**
 * @brief Gets the value of the parameter type
 * @tparam T: Int, Boolean, or Float
 * @return The current value of options, with an empty string for subclass specialization
*/
template<class T>
std::tuple<T, std::string> Options<T>::get_value()
{
	return { this->value, "" } ;
}

/**
 * @brief Sets the value of the current option
 * @tparam T: Int, Boolean, or Float
 * @param _value: The new value to change to
*/
template<class T>
void Options<T>::set_value( T _value )
{
	this->value = _value ;
}

/**
 * @brief The specialized option setting for lists of text
 * @param _cur_val: The current value
 * @param _max: The maximum amount of choices
 * @param _option: If this option belongs in the upper or lower section of the file
 * @param _choices: A list of all the choices
*/
Option_Integer::Option_Integer( int _cur_val, int _max, bool _option, std::list<std::string> _choices )
	: Options<int>( _cur_val, _max, _option ), choices( _choices )
{
}

/**
 * @brief The overloaded method for getting the list of options. Used for visually inspecting the options.
 * @return A tuple with the integer option and the associated string
*/
std::tuple<int, std::string> Option_Integer::get_value()
{
	int val = std::get<0>(Options::get_value()) ;
	return { val, ( *std::next(this->choices.begin(), val) ) } ;
}