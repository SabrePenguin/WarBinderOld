#ifndef CONTROL_H
#define CONTROL_H
#include <string>
#include <vector>
class Bind;
class Control
{
	public:
		Control(char _mode) : mode( _mode ) { } ;
		virtual void add_bind(Bind* _bind) {};
		virtual bool set_local_key(std::string local_key) { return false; };
		virtual bool set_modifer(bool enable) { return false; };
		char get_mode() { return mode ; } ;
		void set_mode( char _mode ) { this->mode = _mode ; } ;
		template <typename T>
		T get_id() { return T(); };
		virtual bool is_modifier() { return false; };
	protected:
		char mode;
		//A list of the binds assigned to this key
		std::vector<Bind*> binds;
};
#endif // CONTROL_H