#ifndef KEYBINDCONTROL_H
#define KEYBINDCONTROL_H
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

enum class controller ;
enum class Key_Type ;
class Control ;
class KeyBind ;
class Reader ;
class Device ;
class KeyBindController 
{
	public:
		KeyBindController(std::string _controlfile, std::string _bindfile, std::string _optfile, std::string _language);
		~KeyBindController();
		void add_key(std::string _key_id, std::string _local_key, bool _modifier, char _gamemode);
		void add_new_joystick(std::string _key_id, std::string _local_key);
		void add_new_controller_axis( std::string _key_id, std::string _local_key ) ;
		void add_new_bind(std::string _internal_id, std::string _local_id, char _mode, bool _is_axis, bool _required);
		void set_language(std::string _language);
		void import(std::string _filename) ;
		std::vector<std::tuple<std::string, std::string>> get_keys( ) ;
	private:
		controller check_string( std::string _name ) ;
		std::string check_type( Key_Type t_type ) ;
		//The language to be used. Will determine the csv column to use
		std::string language;
		//The map of system keys. Uses the id as the key, as each is guaranteed to be unique (O(1) time)
		std::unordered_map<std::string, Control*> system_keys ;
		//The map of binds. Uses the local string id as the key to allow for searching later
		std::unordered_map<std::string, KeyBind*> p_binds ;
		std::unique_ptr<Reader> file_handler ;
		std::unordered_map<std::string,std::shared_ptr<Device>> device_list ;
};
#endif // KEYBINDCONTROL_H