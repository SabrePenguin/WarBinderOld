#ifndef AXIS_H
#define AXIS_H
#include <string>
#include "KeyBind.h"
class Axis: public KeyBind
{
	public:
		Axis( std::string _internal_id, std::string _text_id, char _mode );
	private:
		//The control that represents the moving up of the axis
		std::string increase_key ;
		//The control that represents moving down the axis
		std::string decrease_key ;
		//The internal id of the axis (range_min)
		std::string internal_id ;
		bool inverted;
		bool relative;
		bool keep_value_for_disabled;
		float dead_zone;
		int non_linearity;
		float multiplier;
		float correction;
		float relative_control_sensivity;
		float relative_control_step;
};
#endif // AXIS_H