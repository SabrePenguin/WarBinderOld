#ifndef DEVICE_H
#define DEVICE_H
#include <string>

class Device
{
	public:
		Device( bool _connected, std::string _name, std::string _device_id, int _axes_offset, 
			int _button_offset, int _button_count, int _axes_count, std::string _type ) ;
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