#ifndef CONTROL_H
#define CONTROL_H
#include <string>
#include <vector>
class KeyBind;
class Control
{
	public:
		Control() {} ;
		virtual ~Control() 
		{
			//Keybinds will get deleted on their own
			reset() ;
		};
		virtual void add_bind(KeyBind* _bind) {};
		virtual bool set_local_key(std::string local_key) { return false; };
		virtual bool set_modifer(bool enable) { return false; };
		virtual bool is_modifier() { return false; };
		virtual bool check_conflict( KeyBind* _bind ) { return false; } ;
		virtual std::string get_local_name() { return "" ; } ;
		std::vector<KeyBind*>* get_binds() { return &binds ; } ;
		void reset() { binds.clear() ; } ;
	protected:
		//A list of the binds assigned to this key
		std::vector<KeyBind*> binds;
};
#endif // CONTROL_H