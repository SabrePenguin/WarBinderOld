#include "Control.h"
#include "KeyBind.h"


std::vector<KeyBind*>* Control::get_binds()
{
	 return &binds ;
}

/**
 * TODO
 */
void Control::clear_key_from_binds() 
{
	for( auto iter = binds.begin() ; iter != binds.end() ; iter++ ) ;
		//( *iter )->remove_key( this ) ;
}


void Control::call_remove_bind( KeyBind* _bind )
{
	for( auto iter = binds.begin() ; iter != binds.end() ; ++iter )
	{
		if( ( *iter ) == _bind )
		{
			iter = binds.erase( iter ) ;
			break ;
		}
	}
}


void Control::remove_bind( KeyBind* _bind )
{
	for( auto iter = binds.begin() ; iter != binds.end() ; )
	{
		if( *iter == _bind )
		{
			( *iter )->remove_key( this ) ;
			iter = binds.erase( iter ) ;
		}
		else
		{
			++iter ;
		}
	}
}


void Control::remove_all_binds()
{
	for( auto iter = binds.begin() ; iter != binds.end() ; ++iter )
	{
		( *iter )->remove_key( this ) ;
	}
	binds.clear() ;
}