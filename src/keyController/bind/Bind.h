#ifndef BIND_H
#define BIND_H
#include <vector>
#include <string>
#include "KeyBind.h"
class Control;
enum class controller ;

class Bind : public KeyBind
{
	public:
		Bind( std::string _internal_id, std::string _text_id, char _mode, bool _required );
		~Bind() ;
		void add_control( std::vector<Control*> _control_combo, controller _up );
		void reset() ;
		std::string get_local_name() ;
	private:
		//The internal id of the bind (ID_AAM)
		std::string internal_id;
		//The local name of the bind (Fire AAM)
		std::string text_id;
		//The collection of vectors that make up the controls
		std::vector<std::vector<Control*>> control;
};


#endif