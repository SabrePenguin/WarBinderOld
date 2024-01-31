#ifndef DEVICE_H
#define DEVICE_H
#include <string>

class Device
{
	public:
		Device( bool _connected, std::string _name, std::string _device_id, int _axes_offset, 
			int _button_offset, int _button_count, int _axes_count, std::string _type ) ;
		void set_connected(bool _c) ;
		bool get_connected() ;
		void set_name(std::string _n) ;
		void set_id(std::string _i) ;
		void set_axes_offset(int _a) ;
		void set_axes_count(int _a) ;
		void set_button_offset(int _b) ;
		void set_button_count(int _b) ;
		void set_type(std::string _t) ;
	private:
		bool connected ;
		std::string name ;
		std::string device_id ;
		int axes_offset ;
		int button_offset ;
		int button_count ;
		int axes_count ;
		std::string type ;
};

#endif // !DEVICE_H