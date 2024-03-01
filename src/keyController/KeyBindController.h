#ifndef KEYBINDCONTROL_H
#define KEYBINDCONTROL_H
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <SDL.h>

enum class controller ;
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
		KeyBindController(std::string _controlfile, std::string _bindfile, std::string _optfile, std::string _language);
		~KeyBindController();
		void set_language(std::string _language);
		void import(std::string _filename) ;
		//Add new items to the object

		//Adds a key
		void add_key(std::string _key_id, std::string _local_key, bool _modifier, char _gamemode);
		//Adds the joystick subtype
		void add_new_joystick(std::string _key_id, std::string _local_key);
		//Adds a new controller axis bind type
		void add_new_controller_axis( std::string _key_id, std::string _local_key ) ;
		//Adds a new bind type
		void add_new_bind(std::string _internal_id, std::string _local_id, char _mode, bool _is_axis, bool _required);

		//Get all the key info
		std::vector<std::tuple<std::string, std::string>> get_key_details( ) ;
		//Get all the bind info
		std::vector<std::tuple<std::string, std::string>> get_bind_details( ) ;

		//Observer pattern
		void notify_device( SDL_Event* cur_event ) ;
		void add_ui_observer( std::shared_ptr<UserInterface> _user_interface ) ;
		void clear_ui_observers() ;

		//Key assignment details

		//
		bool check_key_exists( std::string _key_id ) ;
		bool check_bind_exists( std::string _bind_id ) ;
		bool check_bind_is_axis( std::string _key_id ) ;
		void assign_key_to_bind( std::vector<std::string> _key_id_list, std::string _bind_id ) ;
		void assign_key_to_axis( std::vector<std::string> _key_id_list, std::string _axis_id, controller _which ) ;
		bool assign_bind_to_key() ;
	private:
		//Checks the given string for one of a set of beginnings
		controller check_string( std::string _name ) ;
		//Checks the Key_Type given
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
};
#endif // KEYBINDCONTROL_H