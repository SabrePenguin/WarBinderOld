#include "KeyBind.h"
#include "Control.h"

KeyBind::KeyBind( char _mode, char _sub_mode, bool _axis,
	bool _required, std::string _local_name, std::string _internal_id) :
	mode( _mode ), sub_mode( _sub_mode ),  axis( _axis ), required( _required ), 
	local_id( _local_name ), internal_id( _internal_id ), is_reset( false )
{

}

KeyBind::~KeyBind()
{
	for( auto iter = control.begin() ; iter != control.end() ; ++iter )
	{
		//No need to delete, controls are deleted by hand
		iter->clear() ;
	}
	control.clear() ;
}


void KeyBind::add_control( std::vector<Control*> _control_combo )
{
	this->control.push_back( _control_combo );
}


void KeyBind::reset()
{
	this->control.clear() ;
}


void KeyBind::remove_key( Control* _key )
{
	for( auto inner_vector = control.begin() ; inner_vector != control.end() ; )
	{
		for( auto control_pointer = inner_vector->begin() ; control_pointer != inner_vector->end() ; )
		{
			if( *control_pointer == _key )
			{
				control_pointer = inner_vector->erase( control_pointer ) ;
			}
			else
			{
				++control_pointer ;
			}
		}

		if( inner_vector->size() == 0 )
		{
			inner_vector = control.erase( inner_vector ) ;
		}
		else
		{
			++inner_vector ;
		}
	}
}


void KeyBind::remove_single_key( std::vector<Control*>* _key_combo, Control* _key )
{
	for( auto iter = control.begin() ; iter != control.end() ; ++iter )
	{
		if( *iter == *_key_combo )
		{
			// Call each Control individually and remove this KeyBind from it
			for( auto remove_control = iter->begin() ; remove_control != iter->end() ; ++remove_control )
			{
				if( *remove_control == _key )
				{
					( *remove_control )->call_remove_bind( this ) ;
					//A successful removal needs to be deleted, and then broken out because there needs to be no
					//other searches
					iter->erase( remove_control ) ;
					break ;
				}
			}
			if( iter->size() == 0 )
				control.erase( iter ) ;
			break ;
		}
	}
}


void KeyBind::remove_key_combo( std::vector<Control*>* _key_combo )
{
	for( auto iter = control.begin() ; iter != control.end() ; ++iter )
	{
		if( *iter == *_key_combo )
		{
			// Call each Control individually and remove this KeyBind from it
			for( auto remove_control = iter->begin() ; remove_control != iter->end() ; ++remove_control )
			{
				( *remove_control )->call_remove_bind( this ) ;
			}
			control.erase( iter ) ;
			break ;
		}
	}
}


void KeyBind::remove_all_keys()
{
	for( auto iter = control.begin() ; iter != control.end() ; )
	{
		for( auto remove_control = iter->begin() ; remove_control != iter->end() ; ++remove_control )
		{
			( *remove_control )->call_remove_bind( this ) ;
		}
		iter = control.erase( iter ) ;
	}
}


void KeyBind::add_single_key( std::vector<Control*>* _key_combo, Control* _key )
{
	for( auto iter = control.begin() ; iter != control.end() ; ++iter )
	{
		if( *iter == *_key_combo )
		{
			iter->push_back( _key ) ;
		}
	}
}


std::string KeyBind::get_local_name()
{
	return this->local_id ;
}


void KeyBind::set_local_name( std::string _name )
{
	this->local_id = _name ;
}


char KeyBind::get_mode() 
{
	return this->mode ;
}


bool KeyBind::is_axis()
{
	return this->axis ;
}


std::vector<std::vector<Control*>>* KeyBind::get_control()
{
	return &this->control ;
}