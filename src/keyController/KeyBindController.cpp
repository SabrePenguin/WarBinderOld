#include <iostream>
#include <vector>
#include "KeyBindController.h"
#include "Control.h"
#include "Key.h"
#include "Bind.h"
#include "CSVin.h"

using namespace std;

void helloWorld() {
	Key key("3", "a", true);
	Key* test_key = new Key("3", "a", true);
	Bind* test_bind = new Bind("1", "AAA");
	std::vector<Control*> keys;
	test_key->add_bind(test_bind);
	keys.push_back(test_key);
	cout << "Hello World" << endl;
}

KeyBindController::KeyBindController(std::string _controlfile, std::string _bindfile, std::string _language) : 
	language(_language) 
{
	get_control( _controlfile, _language ) ;
	get_binds( _bindfile, _language ) ;
}

KeyBindController::~KeyBindController() 
{
	for (auto iterator = this->system_keys.begin(); iterator!= this->system_keys.end(); ++iterator) 
	{
		cout << iterator->first << endl;
		delete(iterator->second);
	}
	this->system_keys.clear();
	for (auto iterator = this->p_binds.begin(); iterator != this->p_binds.end(); ++iterator)
	{
		cout << iterator->first << endl;
		delete(iterator->second);
	}
	this->p_binds.clear();
}

void KeyBindController::add_key(std::string _key_id, std::string _local_key)
{
	Key* new_key = new Key(_key_id, _local_key);
	this->system_keys.insert({ _key_id, new_key });
	//Test block. Will be removed
	std::vector<Control*> asdf;
	asdf.push_back(new_key);
	//this->add_keys_to_bind("One Test", asdf);
	cout << "success" << endl;
}

void KeyBindController::add_modifier_key(std::string _key_id, std::string _local_key)
{
	Key* new_key = new Key(_key_id, _local_key, true);
	this->system_keys.insert({ _key_id, new_key });
}

void KeyBindController::add_new_control(std::string _key_id, std::string _local_key)
{
}

void KeyBindController::add_new_bind(std::string _internal_id, std::string _local_id)
{
	Bind* new_bind = new Bind(_internal_id, _local_id);
	this->p_binds.insert({ _local_id, new_bind });
}

void KeyBindController::set_language(std::string _language)
{
	this->language = _language;
}


/* Remove for now to just fix up the add functions
bool KeyBindController::add_keys_to_bind(std::string _bind_name, std::vector<Control*> _added_keys)
{
	//Find block
	auto iterator = this->p_binds.find(_bind_name);
	if(iterator == this->p_binds.end())
		return false;
	//Block checks if the key combination contains all modifiers except 1. In the future, this will ask use if they would like to enable all mods.
	int i = 0;
	bool success = false;
	for (auto key_iterator = _added_keys.begin(); key_iterator != _added_keys.end(); ++key_iterator)
	{
		if ((*key_iterator)->is_modifier())
		{
			i++;
		}
		if (i+2 >= _added_keys.size())
		{
			iterator->second->add_control(_added_keys);
			success = true;
			break;
		}
	}

	//Block adds the bind to all keys in the list
	if (success)
	{
		for (auto key_iterator = _added_keys.begin(); key_iterator != _added_keys.end(); ++key_iterator)
		{
			(*key_iterator)->add_bind(iterator->second);
		}
	}
	return success;
}
*/
