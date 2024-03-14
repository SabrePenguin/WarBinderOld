/*****************************************************************//**
 * @file   Axis.h
 * @brief  
 * 
 * @author sabrepotato
 * @date   March 2024
 *********************************************************************/
#ifndef AXIS_H
#define AXIS_H
#include <string>
#include "KeyBind.h"

struct Imported_Axis ;

class AxisChange : public KeyBind
{
public:
	/**
	 * AxisChange constructor
	 */
	AxisChange( std::string _internal_id, std::string _text_id, char _mode, bool _required );
	/**
	 * @brief The main method for adding two other keybinds in a triangular relation. Used to
	 * allow for axis controls
	 * @param _axis_one: The first KeyBind
	 * @param _axis_two: The second KeyBind
	 */
	void add_other_controls( KeyBind* _axis_one, KeyBind* _axis_two ) ;
private:
	KeyBind* axis_one ;
	KeyBind* axis_two ;
};


class AxisReset: public AxisChange
{
	public:
		/**
		* @brief The constructor for the axis
		* @param _mode: The gamemode to be passed to KeyBind
		*/
		AxisReset( std::string _internal_id, std::string _text_id, char _mode, bool _required);
		~AxisReset() ;
		/**
		* @brief Adds a singular control axis to the bind axis
		* @param _axis: The Control
		*/
		void add_axis( Control* _axis ) ;
		/**
		* @brief Imports the data from the structure into the class fields
		* @param _data: A structure containing the data
		*/
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