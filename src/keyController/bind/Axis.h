#ifndef AXIS_H
#define AXIS_H
#include <string>
#include "KeyBind.h"

enum class controller
{
	INCREASE,
	DECREASE,
	RESET
};

struct Imported_Axis ;

class Axis: public KeyBind
{
	public:
		Axis( std::string _internal_id, std::string _text_id, char _mode, controller _increase, bool _required);
		~Axis() ;
		void add_control( std::vector<Control*> _control_combo, controller _direction );
		void add_second_bind( std::string _text_id, controller _direction ) ;
		void add_axis( Control* _axis ) ;
		void add_data( Imported_Axis* _data ) ;
		void reset() ;
		std::string get_local_name() ;
		std::vector<std::string> get_axis_names() ;

	private:
		//The local name that represents the moving up of the axis
		std::string increase_local ;
		//The physical axis that controls the game axis
		Control* game_axis ;
		//The collection of vectors that make up the increase control
		std::vector<std::vector<Control*>> control_up;
		//The local name that represents moving down the axis
		std::string decrease_local ;
		//The collection of vectors that make up the decrease control
		std::vector<std::vector<Control*>> control_down;
		//The local name that represents reseting the axis
		std::string reset_local ;
		//The collection of vectors that make up the reset controls
		std::vector<std::vector<Control*>> control_reset ;
		//The internal id of the axis (ie. throttle). Will auto adjust for both increase, decrease, and reset
		std::string internal_id ;
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