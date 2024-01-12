#ifndef READER_H
#define READER_H
#include <string>
#include <vector>
#include <tuple>

struct Imported_Axis {
	std::string name, axis ;
	bool inverted, relative, keep_value_for_disabled;
	float dead_zone, multiplier, correction, relSens, relStep;
	int non_linearity;
};

std::vector<std::tuple<std::string, std::vector<std::string>>> import_controls( std::string _filename ) ;

#endif // !READER_H