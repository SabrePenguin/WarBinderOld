#ifndef KEYBINDCONTROL_H
#define KEYBINDCONTROL_H
#include <string>
#include <vector>
#include <unordered_map>

class Control;
class Bind;
class KeyBindController 
{
	public:
		KeyBindController(std::string _controlfile, std::string _bindfile, std::string _language);
		~KeyBindController();
		void add_key(std::string _key_id, std::string _local_key, bool _modifier, char _gamemode);
		void add_new_control(std::string _key_id, std::string _local_key);
		void add_new_bind(std::string _internal_id, std::string _local_id, bool _axis);
		void set_language(std::string _language);
		//bool add_keys_to_bind(std::string _bind_name, std::vector<Control*> _added_keys);
	private:
		//The language to be used. Will determine the csv column to use
		std::string language;
		//The map of system keys. Uses the id as the key, as each is guaranteed to be unique (O(1) time)
		std::unordered_map<std::string, Control*> system_keys;
		//The map of binds. Uses the local string id as the key to allow for searching later
		std::unordered_map<std::string, Bind*> p_binds;
};
#endif // KEYBINDCONTROL_H