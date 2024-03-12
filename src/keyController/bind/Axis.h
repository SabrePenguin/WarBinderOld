#ifndef AXIS_H
#define AXIS_H
#include <string>
#include "KeyBind.h"

struct Imported_Axis ;

class AxisChange : public KeyBind
{
public:
	AxisChange( std::string _internal_id, std::string _text_id, char _mode, bool _required );
	void add_other_controls( KeyBind* _axis_one, KeyBind* _axis_two ) ;
private:
	KeyBind* axis_one ;
	KeyBind* axis_two ;
};


class AxisReset: public AxisChange
{
	public:
		AxisReset( std::string _internal_id, std::string _text_id, char _mode, bool _required);
		~AxisReset() ;
		void add_axis( Control* _axis ) ;
		void add_data( Imported_Axis* _data ) ;

	private:
		//The physical axis that controls the game axis
		Control* game_axis ;
		//Is the axis inverted
		bool inverted;
		//Is the axis relative
		bool relative;
		//Keep the current axis level when disabled
		bool keep_value_for_disabled;
		//The size of the internal deadzone
		float dead_zone;
		//The curve
		int non_linearity;
		float multiplier;
		float correction;
		float relative_control_sensivity;
		float relative_control_step;
};


#endif // AXIS_H