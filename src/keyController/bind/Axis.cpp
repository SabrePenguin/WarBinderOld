#include "Axis.h"
#include <vector>
#include "../control/Control.h"
#include "Axis.h"

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

void Axis::add_control( std::vector<Control*> _control_combo, controller _direction )
{
	if( _direction == controller::INCREASE )
		this->control_up.push_back( _control_combo );
	else if( _direction == controller::DECREASE )
		this->control_down.push_back( _control_combo );
	else
		this->control_reset.push_back( _control_combo ) ;
}

void Axis::add_second_bind( std::string _text_id, controller _direction )
{
	if( _direction == controller::INCREASE )
		this->increase_local = _text_id ;
	else if( _direction == controller::DECREASE )
		this->decrease_local = _text_id ;
	else
		this->reset_local = _text_id ;
}