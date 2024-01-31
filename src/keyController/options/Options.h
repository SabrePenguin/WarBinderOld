#ifndef OPTIONS_H
#define OPTIONS_H
#include <list>
#include <string>
#include <tuple>
#include <array>

template <class T>
class Options
{
	public:
		Options( T _cur_val, T _max ) ;
		virtual std::tuple<T,std::string> get_value() ;
		void set_value( T _value ) ;
	private:
		T value ;
		T max ;
};
class Option_Integer : public Options<int>
{
	public:
		Option_Integer( int _cur_val, int _max, std::list<std::string> _choices ) ;
		std::tuple<int, std::string> get_value() ;
	private:
		std::list<std::string> choices ;
};
#endif // !OPTIONS_H