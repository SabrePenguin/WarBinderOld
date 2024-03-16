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
		/**
		* @brief Gets the vector of keybinds
		*/
		std::vector<KeyBind*>* get_binds() ;

		/**
		* @brief Clears this key from all the keybinds that use it
		*/
		void clear_key_from_binds() ;
		/**
		* @brief Find and remove the given _bind pointer from the list. Only removes one as
		* the pointers in the vector don't know which combo they're part of, only that they
		* are part of that bind set. This method is only used when called by the KeyBind
		* class.
		* @param _bind: The pointer to remove
		*/
		void call_remove_bind( KeyBind* _bind ) ;
		/**
		* @brief Remove all references of the given _bind pointer. Removes all pointers because
		* the Control doesn't know which combo you'd be deleting otherwise, and the logic wouldn't
		* be fun to make (I may make it later)
		* @param _bind: The pointer to remove all references of.
		*/
		void remove_bind( KeyBind* _bind ) ;
		/**
		* @brief Removes all the binds available to this specific Control
		*/
		void remove_all_binds() ;
		void reset() { binds.clear() ; } ;
	protected:
		//A list of the binds assigned to this key
		std::vector<KeyBind*> binds;
};
#endif // CONTROL_H