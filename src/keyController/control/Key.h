#ifndef KEY_H
#define KEY_H

#include <vector>
#include <string>
#include "Control.h"
class KeyBind;
class Key : public Control
{
	public:
		/**
		* @brief Modifier key constructor
		* @param _local_key: Local key ("backspace", "a", "1")
		* @param _modifier: Modifier key, such as ctrl or alt
		*/
		Key( std::string k_id, std::string local, bool mod ) ;
		/**
		* @brief Adds a single Bind or Axis class to the internal vector
		* @param _bind : A single Bind that gets added to the vector
		*/
		void add_bind( KeyBind* _bind ) ;
		/**
		* @brief Enables or disables whether the key is a modifier key.
		* This enables using keys such as 'a' and 'z' like 'ctrl' and 'alt'
		* @param enable: Enable modifier key
		* @return The current state of the key
		*/
		bool set_modifier( bool enable ) ;
		std::string get_id( ) ;
		bool is_modifier( ) ;
		/**
		* @brief A method to check if the given bind has any internal conflicts (mode to mode). TODO
		* @param _bind: The bind to check
		* @return True if the bind is good to use
		*/
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