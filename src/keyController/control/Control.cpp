#include "Control.h"
#include "KeyBind.h"


std::vector<KeyBind*>* Control::get_binds()
{
	 return &binds ;
}

/**
 * @brief Clears this key from all the keybinds that use it
 */
void Control::clear_key_from_binds() 
{
	for( auto iter = binds.begin() ; iter != binds.end() ; iter++ )
		( *iter )->remove_key( this ) ;
}

/**
 * @brief Find and remove the given _bind pointer from the list
 * @param _bind: The pointer to remove
 */
void Control::remove_bind(KeyBind* _bind)
{
	for( auto iter = binds.begin() ; iter != binds.end() ; iter++ )
	{
		if( ( *iter ) == _bind )
		{
			binds.erase( iter ) ;
			break ;
		}
	}
}