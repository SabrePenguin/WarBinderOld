#ifndef KEY_H
#define KEY_H

#include <vector>
#include <string>
#include "Control.h"
class KeyBind;
class Key : public Control
{
	public:
		Key( std::string k_id, std::string local, bool mod ) ;
		void add_bind( KeyBind* _bind ) ;
		//Enables the key to be used in a combination
		bool set_modifier( bool enable ) ;
		std::string get_id( ) ;
		bool is_modifier( ) ;
		bool check_conflict( KeyBind* _bind ) ;
		std::string get_local_name() ;
	private:
		//The internal key id of the file
		std::string key_id ;
		//The local key
		std::string local_key ;
		//Indicates a combination key, like shift, ctrl, alt. Can be assigned to regular keys
		bool modifier_key ;
};
#endif