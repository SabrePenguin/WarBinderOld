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
		Options( T _cur_val, T _max, bool _option ) ;
		virtual std::tuple<T,std::string> get_value() ;
		void set_value( T _value ) ;
	private:
		//The current value
		T value ;
		//The maximum value
		T max ;
		//Whether this exists in the lower or upper section of the .blk file
		bool option ;
};
class Option_Integer : public Options<int>
{
	public:
		Option_Integer( int _cur_val, int _max, bool _option, std::list<std::string> _choices ) ;
		std::tuple<int, std::string> get_value() ;
	private:
		//The list of choices, corresponding to the current value (hence why it's a list)
		std::list<std::string> choices ;
};
#endif // !OPTIONS_H