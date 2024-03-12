#include "Axis.h"
#include <vector>
#include "../control/Control.h"
#include "../file_handler/reader.h"

AxisChange::AxisChange( std::string _internal_id, std::string _text_id, char _mode, bool _required ) :
	KeyBind( _mode, true, _required, _text_id, _internal_id )
{
}

void AxisChange::add_other_controls( KeyBind* _axis_one, KeyBind* _axis_two )
{
	axis_one = _axis_one ;
	axis_two = _axis_two ;
}

/**
 * @brief The constructor for the axis
 * @param _internal_id: The internal id of the data
 * @param _text_id: The text id of the axis
 * @param _mode: The gamemode to be passed to KeyBind
 * @param _increase: Whether the given keybind name corresponds to an increase
 * @param _required: Whether this keybind is required
*/
AxisReset::AxisReset( std::string _internal_id, std::string _text_id, char _mode, bool _required ) :
	AxisChange( _internal_id, _text_id, _mode, _required ), inverted(false), relative(false),
	keep_value_for_disabled( false ), dead_zone( 0.0f ), non_linearity( 0 ), multiplier( 0.0f ),
	correction( 0.0f ), relative_control_sensivity( 0.0f ), relative_control_step( 0.0f )
{
}

AxisReset::~AxisReset()
{
	game_axis = nullptr ;
}


/**
 * @brief Adds a singular control axis to the bind axis
 * @param _axis: The Control
*/
void AxisReset::add_axis( Control* _axis )
{
	//TODO: Rename axes to be more descriptive as single "axis" exists in the superclas
	game_axis = _axis ;
}

/**
 * @brief Imports the data from the structure into the class fields
 * @param _data: A structure containing the data
*/
void AxisReset::add_data( Imported_Axis* _data )
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