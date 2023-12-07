#ifndef CONTROL_H
#define CONTROL_H
#include <string>
#include <vector>
class Bind;
class Control
{
	public:
		Control() {};
		virtual void add_bind(Bind* _bind) {};
		virtual bool set_local_key(std::string local_key) { return false; };
		virtual bool set_modifer(bool enable) { return false; };
};
#endif // CONTROL_H