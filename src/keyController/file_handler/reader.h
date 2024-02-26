#ifndef READER_H
#define READER_H
#include <string>
#include <vector>
#include <tuple>

enum class Key_Type
{
	KEYBOARD,
	MOUSE,
	CONTROLLER
};

struct Imported_Axis {
	Key_Type axis_type ;
	std::string name, axis ;
	bool inverted, relative, keep_value_for_disabled;
	float dead_zone, multiplier, correction, relSens, relStep;
	int non_linearity;
};

struct Device_Data
{
	bool connected ;
	std::string name, device_id, type ;
	int axes_offset, button_offset, axes_count, button_count ;
};

typedef std::vector<Device_Data> t_device ;
typedef std::vector<std::tuple<std::string, char, std::string>> t_options ;
typedef std::vector<std::tuple<Key_Type, std::string>> t_buttons ;
typedef std::vector<std::tuple<std::string, t_buttons>> t_keys ;
typedef std::vector<Imported_Axis> t_import_axis ;
typedef std::tuple<t_keys, t_import_axis, t_options, t_device, t_options> t_return ;
class Reader
{
	public:
		t_return import_controls( std::string _filename ) ;
	private:
		std::string version ;
		std::string base_path ;
};
#endif // !READER_H