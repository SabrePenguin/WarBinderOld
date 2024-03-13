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
	for( auto iter = binds.begin() ; iter != binds.end() ; iter++ ) ;
		//( *iter )->remove_key( this ) ;
}

/**
 * @brief Find and remove the given _bind pointer from the list. Only removes one as
 * the pointers in the vector don't know which combo they're part of, only that they
 * are part of that bind set. This method is only used when called by the KeyBind
 * class.
 * @param _bind: The pointer to remove
 */
void Control::call_remove_bind( KeyBind* _bind )
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

/**
 * @brief Remove all references of the given _bind pointer. Removes all pointers because
 * the Control doesn't know which combo you'd be deleting otherwise, and the logic wouldn't
 * be fun to make.
 * @param _bind: The pointer to remove all references of.
 */
void Control::remove_bind( KeyBind* _bind )
{
	for( auto iter = binds.begin() ; iter != binds.end() ; iter++ )
	{
		if( *iter == _bind )
		{
			( *iter )->remove_key( this ) ;
			binds.erase( iter ) ;
		}
	}
}