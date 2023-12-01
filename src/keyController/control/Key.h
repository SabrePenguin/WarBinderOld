#ifndef KEY_H
#define KEY_H

#include <vector>
class Key
{
	public:
		Key(int param_key_id, char param_local_key, bool param_modifier);
		//Adds a bind to the key
		int add_bind();
		//Sets the local key
		bool set_local_key(char local_key);
		//Enables the key to be used in a combination
		bool set_modifier(bool enable);
	private:
		//The internal key id of the file
		int key_id;
		//A list of the binds assigned to this key
		std::vector<int> binds;
		//The local key
		char local_key;
		//Indicates a combination key, like shift, ctrl, alt. Can be assigned to regular keys
		bool modifier_key;
};
#endif