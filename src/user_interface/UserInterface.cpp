#include "UserInterface.h"
#include <memory>

UserInterface::UserInterface( std::shared_ptr<KeyBindController> _controller )
	: controller( _controller )
{
}