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
		KeyBind(char _mode, bool _axis, bool _required, std::string _local_name, std::string _internal_id) ;
		virtual ~KeyBind() ;
		virtual void add_control( std::vector<Control*> _control_combo ) ;
		virtual void add_second_bind( std::string _text_id, controller _up ) ;
		virtual void add_axis( Control* _axis ) ;
		virtual void add_data( Imported_Axis* _imported ) ;
		virtual void reset() ;
		/**
		 * @brief Gets the list of controls from the current Bind
		 * @return A pointer to the vector of vectors
		 */
		std::vector<std::vector<Control*>>* get_control() ;
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
		std::vector<std::vector<Control*>> control;
		std::string local_id ;
		std::string internal_id ;
};

#endif // !KEYBIND_H