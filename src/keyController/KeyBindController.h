#ifndef KEYBINDCONTROL_H
#define KEYBINDCONTROL_H
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <SDL.h>
#include <atomic>

enum class Key_Type ;
class Control ;
class KeyBind ;
class Reader ;
class Device ;
class DeviceHandler ;
class UserInterface ;

class KeyBindController 
{
	public:
		/**
		* @brief Imports the files and converts them to objects
		* @param _controlfile: The file of the controls and their local names
		* @param _bindfile: The file of all the binds and their names
		* @param _language: The language in the file. Used to find local ids.
		*/
		KeyBindController(std::string _controlfile, std::string _bindfile, std::string _optfile, std::string _language);
		/**
		* @brief Destroys the pointers by hand due to being unable to use smart pointers
		*/
		~KeyBindController();
		/**
		* @brief Sets the language of the keybind controller.
		* @param _language: The language to be used. Must match a language in the csv files.
		*/
		void set_language(std::string _language);
		/**
		* @brief Imports the control file. Must be a .blk file and must follow Gaijin's format
		* @param _filename
		*/
		void import(std::string _filename) ;
		//Add new items to the object

		/**
		* @brief Adds a key pointer to the KeyBindController vector
		* @param _key_id: The internal id. Can be anything, so long as it matches Gaijin's internal id. (ie: 1, button_1)
		* @param _local_key: The local name. Can be anything
		* @param _modifier: Whether the key is a modifier such as "ctrl" or "alt"
		 * @param _type: The type of control (key, mouse, controller)
		*/
		void add_key(std::string _key_id, std::string _local_key, bool _modifier, char _gamemode);
		/**
		* @brief Adds a controller button
		* @param _key_id: The internal id. Can be anything as long as it matches Gaijin's internal id.
		* @param _local_key
		*/
		void add_new_joystick(std::string _key_id, std::string _local_key);
		//Adds a new controller axis bind type
		void add_new_controller_axis( std::string _key_id, std::string _local_key ) ;
		/**
		* @brief Adds a Bind pointer.
		* @param _internal_id: The internal id of the bind name.
		* @param _local_id: The local name of the bind. (ie. "Throttle Up")
		* @param _axis: Determines if the given bind needs to be an axis or regular button
		*/
		void add_new_bind(std::string _internal_id, std::string _local_id, char _mode, bool _is_axis, bool _required);

		/**
		* @brief Gets the internal map with all the binds
		* @return A pointer to the map. Returns reference due to size.
		*/
		std::unordered_map<std::string, KeyBind*>* get_binds_map() ;
		/**
		* @brief Gets the internal map with all the controls
		* @return A pointer to the map. Returns reference due to size.
		*/
		std::unordered_map<std::string, Control*>* get_controls_map() ;

		//Observer pattern
		void notify_device( SDL_Event* cur_event ) ;
		/**
		* @brief Adds a ui observer to the device handler
		* @param _user_interface: The User Interface to add as an observer
		*/
		void add_ui_observer( std::shared_ptr<UserInterface> _user_interface ) ;
		/**
		* @brief Clears the observer to allow the release of the circular references
		*/
		void clear_ui_observers() ;

		/**
		* @brief Checks if the given key exists
		* @param _key_id: The key to search for
		* @return True if the key exists
		*/
		bool check_key_exists( std::string _key_id ) ;
		/**
		* @brief Checks if the given bind exists
		* @param _bind_id: The bind to search for
		* @return True if the bind exists
		*/
		bool check_bind_exists( std::string _bind_id ) ;
		/**
		* @brief Checks if the requested bind is an axis bind
		* @param _key_id: The key to check
		* @return True if it is an axis
		*/
		bool check_bind_is_axis( std::string _key_id ) ;
		/**
		* @brief Assigns the given key to a bind based on the input strings
		* @param _key_id_list: The key to assign to
		* @param _bind_id: The bind to assign to
		* @return True if the bind assignment successful
		*/
		void assign_key_to_bind( std::vector<std::string> _key_id_list, std::string _bind_id ) ;
		/**
		* @brief Remove all references of the given _bind pointer from the sent in Control
		* @param _control: The Control to use
		* @param _bind: The pointer to remove all references of.
		*/
		void remove_bind( Control* _control, KeyBind* _bind ) ;
		/**
		* @brief Removes all the binds available to this specific Control
		* @param _control: The specific Control to use
		*/
		void remove_all_binds( Control* _control ) ;
		/**
		* @brief Searches through the control vector of the given KeyBind and removes all 
		* references to the key given
		* @param _bind: The KeyBind to operate on
		* @param _key: The Control pointer to compare to
		*/
		void remove_key( KeyBind* _bind, Control* _key ) ;
		/**
		 * @brief Removes the single key from the vector of the KeyBind given
		 * @param _bind: The KeyBind to operate on
		 * @param _key_combo: The vector to edit
		 * @param _key: The Control to remove
		 */
		void remove_single_key( KeyBind* _bind, std::vector<Control*>* _key_combo, Control* _key ) ;
		/**
		* @brief Removes the given vector of Controls from the list of available controls in the KeyBind given
		* @param _bind: The KeyBind to operate on
		* @param _key_combo: Pointer to the vector to remove
		*/
		void remove_key_combo( KeyBind* _bind, std::vector<Control*>* _key_combo ) ;
		/**
		 * @brief Removes all Control pointers from this KeyBind
		 * @param _bind: The KeyBind to operate on
		 */
		void remove_all_keys( KeyBind* _bind ) ;
		/**
		 * @brief Adds a single key to the vector inside the given bind. Doesn't check if it's duplicate.
		 * @param _bind: The KeyBind to add to
		 * @param _key_combo: The vector to edit
		 * @param _key: The Control to add
		 */
		void add_single_key( KeyBind* _bind, std::vector<Control*>* _key_combo, Control* _key ) ;
		void set_lock( SDL_Event* _event ) ;
		bool get_lock() ;
		void add_button_to_set( SDL_Event* _event ) ;
	private:
		/**
		* @brief A method to check whether the given button is on the keyboard, mouse, or a controller
		* @param t_key: The enum to check
		* @return A string
		*/
		std::string check_type( Key_Type t_type ) ;
		//Find the position of the character in the string
		int find_pos( std::string str, char ch ) ;
		//The language to be used. Will determine the csv column to use
		std::string language;
		//The map of system keys. Uses the id as the key, as each is guaranteed to be unique (O(1) time)
		//ie. {key3, Control*}
		std::unordered_map<std::string, Control*> system_keys ;
		//The map of binds. Uses the local string id as the key to allow for searching later
		//ie. {dropTank, KeyBind*}
		std::unordered_map<std::string, KeyBind*> system_binds ;
		//The reader that handles all reading of .blk files
		std::unique_ptr<Reader> file_handler ;
		//The primary method of reading in data about the controller
		std::unique_ptr<DeviceHandler> device_handler ;
		//A set of devices.
		std::unordered_map<std::string,std::shared_ptr<Device>> device_list ;
		//Whether or not KeyBindController is accepting controller input
		std::atomic_bool buttons_locked ;
		std::vector<std::pair<int, int>> button_combo;
};
#endif // KEYBINDCONTROL_H