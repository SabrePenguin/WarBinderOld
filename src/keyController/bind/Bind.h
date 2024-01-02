#ifndef BIND_H
#define BIND_H
#include <vector>
#include <string>
#include "KeyBind.h"
class Control;

class Bind : public KeyBind
{
	public:
		Bind( std::string _internal_id, std::string _text_id, char _mode );
	private:
		//The internal id of the bind (ID_AAM)
		std::string internal_id;
		//The local name of the bind (Fire AAM)
		std::string text_id;
};


#endif