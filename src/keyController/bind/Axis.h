#ifndef AXIS_H
#define AXIS_H
#include "Bind.h"
class Axis: public Bind
{
	public:
		Axis();
	private:
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
#endif