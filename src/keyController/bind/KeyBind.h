#ifndef KEYBIND_H
#define KEYBIND_H
#include <vector>
#include <string>


class Control ;
struct Imported_Axis ;
class KeyBind
{
	public:
		KeyBind(char _mode, char _sub_mode, bool _axis, bool _required, std::string _local_name, std::string _internal_id) ;
		virtual ~KeyBind() ;
		/**
		* @brief Adds a vector of keys to the current Bind.
		* @param _control_combo : vector of implemented Control classes
		*/
		void add_control( std::vector<Control*> _control_combo ) ;
		virtual void add_axis( Control* _axis ) {} ;
		virtual void add_data( Imported_Axis* _imported ) {} ;
		virtual void add_other_controls( KeyBind* _axis_one, KeyBind* _axis_two ) {} ;
		/**
		* @brief Clears the current control for a fresh keybind
		*/
		void reset() ;
		/**
		 * @brief Gets the list of controls from the current Bind
		 * @return A pointer to the vector of vectors
		 */
		std::vector<std::vector<Control*>>* get_control() ;
		/**
		* @brief Searches through the control vector and removes all references to the key given
		* @param _key: The Control pointer to compare to
		* @param _up: Used to allow holding with Axis
		*/
		void remove_key( Control* _key ) ;
		/**
		 * @brief Removes the single key from the vector
		 * @param _key_combo: The vector to edit
		 * @param _key: The Control to remove
		 */
		void remove_single_key( std::vector<Control*>* _key_combo, Control* _key ) ;
		/**
		* @brief Removes the given vector of Controls from the list of available controls
		* @param _key_combo: Pointer to the vector to remove
		*/
		void remove_key_combo( std::vector<Control*>* _key_combo ) ;
		/**
		 * @brief Removes all Control pointers from this KeyBind
		 */
		void remove_all_keys() ;
		/**
		 * @brief Adds a single key to the vector. Doesn't check if it's duplicate.
		 * @param _key_combo: The vector to edit
		 * @param _key: The Control to add
		 */
		void add_single_key( std::vector<Control*>* _key_combo, Control* _key ) ;
		char get_mode() ;
		/**
		* @brief Get the text id of the Bind
		* @return The text id
		*/
		std::string get_local_name() ;
		void set_local_name( std::string _name ) ;
		bool is_axis() ;
	protected:
		//Unfortunate type check
		bool axis ;
		//Second unfortunate type check
		bool is_reset ;
		//The gamemode character representation
		char mode ;
		char sub_mode ; /* Indicates one of four sub-modes */
		//Whether the given control is required to play the game (ie. Fire guns)
		bool required ;
		std::vector<std::vector<Control*>> control;
		std::string local_id ;
		std::string internal_id ;
};

#endif // !KEYBIND_H