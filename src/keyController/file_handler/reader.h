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

typedef std::vector<std::tuple<Key_Type, std::string>> t_buttons ;
typedef std::vector<std::tuple<std::string, t_buttons>> t_keys ;
typedef std::tuple<t_keys, std::vector<Imported_Axis>> t_return ;

t_return import_controls( std::string _filename ) ;

#endif // !READER_H