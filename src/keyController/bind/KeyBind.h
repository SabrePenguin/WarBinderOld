#ifndef KEYBIND_H
#define KEYBIND_H
#include <vector>
#include <string>

enum class controller
{
	INCREASE,
	DECREASE,
	RESET
};

class Control ;
struct Imported_Axis ;
class KeyBind
{
	public:
		KeyBind(char _mode, bool _axis, bool _required) ;
		virtual ~KeyBind() ;
		virtual void add_control( std::vector<Control*> _control_combo, controller _up ) { return ; };
		virtual void add_second_bind( std::string _text_id, controller _up ) { return ; } ;
		virtual void add_axis( Control* _axis ) { return ; } ;
		virtual void add_data( Imported_Axis* _imported ) { return ; };
		virtual void reset() { return ; } ;
		virtual std::vector<std::vector<Control*>>* get_main_control() { return nullptr ; } ;
		virtual std::vector<std::vector<Control*>>* get_low_control() { return nullptr ; } ;
		virtual std::vector<std::vector<Control*>>* get_upper_control() { return nullptr ; } ;
		/**
		 * @brief Removes the given Control pointer from all key combinations in the dedicated control
		 * @param _key: The pointer to remove
		 * @param _up: The direction to apply to. Non-axis binds do not care what this is
		 */
		virtual void remove_key( Control* _key, controller _up ) {} ;

		char get_mode() ;
		virtual std::string get_local_name() { return std::string(); } ;
		virtual std::vector<std::string> get_axis_names() { return std::vector<std::string>(); } ;
		bool is_axis() ;
	protected:
		//Unfortunate type check
		bool axis ;
		//The gamemode character representation
		char mode ;
		//Whether the given control is required to play the game (ie. Fire guns)
		bool required ;
};

#endif // !KEYBIND_H