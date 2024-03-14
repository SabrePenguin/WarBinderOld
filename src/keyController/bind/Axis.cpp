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


void AxisReset::add_axis( Control* _axis )
{
	//TODO: Rename axes to be more descriptive as single "axis" exists in the superclas
	game_axis = _axis ;
}


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