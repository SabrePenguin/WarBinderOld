#include "Axis.h"
#include <vector>
#include "../control/Control.h"
#include "../file_handler/reader.h"

/**
 * @brief The constructor for the axis
 * @param _internal_id: The internal id of the data
 * @param _text_id: The text id of the axis
 * @param _mode: The gamemode to be passed to KeyBind
 * @param _increase: Whether the given keybind name corresponds to an increase
 * @param _required: Whether this keybind is required
*/
Axis::Axis( std::string _internal_id, std::string _text_id, char _mode, controller _increase, bool _required ) :
	KeyBind( _mode, true, _required ), internal_id( _internal_id ), inverted( false ), relative( false ),
	keep_value_for_disabled( false ), dead_zone( 0.0f ), non_linearity( 0 ), multiplier( 0.0f ),
	correction( 0.0f ), relative_control_sensivity( 0.0f ), relative_control_step( 0.0f )
{
	if( _increase == controller::INCREASE )
		this->increase_local = _text_id ;
	else if( _increase == controller::DECREASE )
		this->decrease_local = _text_id ;
	else
		this->reset_local = _text_id ;
}

Axis::~Axis()
{
	for( auto iter = control_up.begin() ; iter != control_up.end() ; iter++ )
	{
		//No need to delete, controls are deleted by hand
		iter->clear() ;
	}
	control_up.clear() ;
	for( auto iter = control_down.begin() ; iter != control_down.end() ; iter++ )
	{
		//No need to delete, controls are deleted by hand
		iter->clear() ; 
	}
	control_down.clear() ;
	for( auto iter = control_reset.begin() ; iter != control_reset.end() ; iter++ )
	{
		//No need to delete, controls are deleted by hand
		iter->clear() ; 
	}
	control_reset.clear() ;
	game_axis = nullptr ;
}

/**
 * @brief Adds a control vector to the bind
 * @param _control_combo: A vector of Control pointers
 * @param _direction: The direction in which the vector is going (increase, decrease, reset)
*/
void Axis::add_control( std::vector<Control*> _control_combo, controller _direction )
{
	if( _direction == controller::INCREASE )
		this->control_up.push_back( _control_combo );
	else if( _direction == controller::DECREASE )
		this->control_down.push_back( _control_combo );
	else
		this->control_reset.push_back( _control_combo ) ;
}

/**
 * @brief Adds an additional string to the local names
 * @param _text_id: The local
 * @param _direction: The direction which the local string corresponds to
*/
void Axis::add_second_bind( std::string _text_id, controller _direction )
{
	if( _direction == controller::INCREASE )
		this->increase_local = _text_id ;
	else if( _direction == controller::DECREASE )
		this->decrease_local = _text_id ;
	else
		this->reset_local = _text_id ;
}

/**
 * @brief Adds a singular control axis to the bind axis
 * @param _axis: The Control
*/
void Axis::add_axis( Control* _axis )
{
	//TODO: Rename axes to be more descriptive as single "axis" exists in the superclas
	game_axis = _axis ;
}

/**
 * @brief Imports the data from the structure into the class fields
 * @param _data: A structure containing the data
*/
void Axis::add_data( Imported_Axis* _data )
{
	inverted = _data->inverted ;
	keep_value_for_disabled = _data->keep_value_for_disabled ;
	dead_zone = _data->dead_zone ;
	non_linearity = _data->non_linearity ;
	multiplier = _data->multiplier ;
	correction = _data->correction ;
	relative = _data->relative ;
	relative_control_sensivity = _data->relSens ;
	relative_control_step = _data->relStep ;
}

/**
 * @brief Resets the data in the vectors and the axes
*/
void Axis::reset()
{
	this->control_down.clear() ;
	this->control_up.clear() ;
	this->control_reset.clear() ;
	this->game_axis = nullptr ;
}

/**
 * @brief Gets the local name
 * @return A string of the local name
*/
std::string Axis::get_local_name()
{
	return std::string();
}

/**
 * @brief Gets a vector of the local names
 * @return A vector of strings
*/
std::vector<std::string> Axis::get_axis_names()
{
	std::vector<std::string> names ;
	if( this->decrease_local.length() > 0 )
		names.push_back( this->decrease_local ) ;
	if( this->increase_local.length() > 0 )
		names.push_back( this->increase_local ) ;
	if( this->reset_local.length() > 0 )
		names.push_back( this->reset_local ) ;
	return names ;
}
