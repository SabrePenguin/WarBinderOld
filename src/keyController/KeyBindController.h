#ifndef KEYBINDCONTROL_H
#define KEYBINDCONTROL_H
#include <string>
#include <vector>

void helloWorld();
class Control;
class Bind;
class KeyBindController 
{
	public:
		KeyBindController();
		~KeyBindController();
		void add_key(int _key_id, std::string _local_key);
		void add_modifier_key(int _key_id, std::string _local_key);
		void add_new_control(int _key_id, std::string _local_key);
	private:
		std::string name;
		std::vector<Control*> system_keys;
};
#endif // KEYBINDCONTROL_H