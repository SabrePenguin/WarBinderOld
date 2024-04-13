#include <unordered_map>
#include <string>
#include <tuple>
#include "Options.h"


template<class T> 
Options<T>::Options( T _cur_val, T _max, bool _option, char _mode, std::string _section )
	: max( _max ), value( _cur_val ), option( _option ), mode( _mode ), section( _section )
{
}


template<class T>
std::tuple<T, std::string> Options<T>::get_value()
{
	return { this->value, "" } ;
}


template<class T>
void Options<T>::set_value( T _value )
{
	this->value = _value ;
}


Option_Integer::Option_Integer( int _cur_val, int _max, bool _option, std::list<std::string> _choices, char _mode, std::string _section )
	: Options<int>( _cur_val, _max, _option, _mode, _section ), choices( _choices )
{
}


Option_Integer::~Option_Integer()
{
	choices.clear() ;
}


std::tuple<int, std::string> Option_Integer::get_value()
{
	int val = std::get<0>(Options::get_value()) ;
	return { val, ( *std::next(this->choices.begin(), val) ) } ;
}