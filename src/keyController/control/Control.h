#ifndef CONTROL_H
#define CONTROL_H
#include <string>
class Control
{
	public:
		virtual int add_bind() {};
		virtual bool set_local_key(std::string local_key) {};
		virtual bool set_modifer(bool enable) {};
};
#endif