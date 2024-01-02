#ifndef AXIS_H
#define AXIS_H
#include <string>
#include "KeyBind.h"
class Axis: public KeyBind
{
	public:
		Axis( std::string _internal_id, std::string _text_id, char _mode, bool _increase, bool _required);
		void add_control( std::vector<Control*> _control_combo, bool _up );
		void add_second_bind( std::string _text_id, bool _up ) ;
	private:
		//The local name that represents the moving up of the axis
		std::string increase_local ;
		//The collection of vectors that make up the increase control
		std::vector<std::vector<Control*>> control_up;
		//The local name that represents moving down the axis
		std::string decrease_local ;
		//The collection of vectors that make up the increase control
		std::vector<std::vector<Control*>> control_down;
		//The internal id of the axis (throttle). Will auto adjust for both increase and decrease
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