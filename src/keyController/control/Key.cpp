/*****************************************************************//**
 * @file   Key.cpp
 * @brief  
 * 
 * @author sabrepotato
 * @date   March 2024
 *********************************************************************/
#include <string>
#include <vector>
#include "Key.h"
#include "Control.h"
#include "../bind/KeyBind.h"


Key::Key(std::string _key_id, std::string _local_key, bool _modifier) : 
	Control(), key_id( _key_id ), local_key( _local_key ), modifier_key( _modifier )
{
}


void Key::add_bind( KeyBind* _bind )
{
	binds.push_back(_bind);
}


bool Key::check_conflict( KeyBind* _bind )
{
	for( std::vector<KeyBind*>::iterator it_bind = binds.begin() ; it_bind != binds.end() ; ++it_bind )
	{
		//Mode comparison. 'c' is common and should always be compared with
		char cur_mode = _bind->get_mode() ;
		if( cur_mode == (*it_bind)->get_mode() || cur_mode == 'c' )
			return false ;
	}
	return true ;
}


bool Key::set_modifier(bool enable)
{
	return true;
}


std::string Key::get_id()
{
	return this->key_id;
}


bool Key::is_modifier()
{
	return this->modifier_key;
}


std::string Key::get_local_name()
{
	return this->local_key ;
}