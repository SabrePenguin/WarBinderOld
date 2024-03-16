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
		/**
		* @brief The basic Options constructor
		* @tparam T: Int, Boolean, or Float
		* @param _cur_val: The current value from the user
		* @param _max: The maximum value it can be. For booleans, this is true
		* @param _option: Whether this option is a middle or lower file section (may be removed)
		*/
		Options( T _cur_val, T _max, bool _option ) ;
		/**
		* @brief Gets the value of the parameter type
		* @tparam T: Int, Boolean, or Float
		* @return The current value of options, with an empty string for subclass specialization
		*/
		virtual std::tuple<T,std::string> get_value() ;
		/**
		* @brief Sets the value of the current option
		* @tparam T: Int, Boolean, or Float
		* @param _value: The new value to change to
		*/
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
		/**
		* @brief The specialized Options setting for lists of text
		* @param _cur_val: The current value
		* @param _max: The maximum amount of choices
		* @param _option: If this option belongs in the upper or lower section of the file
		* @param _choices: A list of all the choices
		*/
		Option_Integer( int _cur_val, int _max, bool _option, std::list<std::string> _choices ) ;
		~Option_Integer() ;
		/**
		* @brief The overloaded method for getting the list of options. Used for visually inspecting the options.
		* @return A tuple with the integer option and the associated string
		*/
		std::tuple<int, std::string> get_value() ;
	private:
		//The list of choices, corresponding to the current value (hence why it's a list)
		std::list<std::string> choices ;
};
#endif // !OPTIONS_H