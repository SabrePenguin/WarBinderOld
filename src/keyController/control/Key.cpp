#include <string>
#include <vector>
#include "Key.h"
#include "Control.h"
#include "../bind/Bind.h"

Key::Key(int k_id, char local, bool mod) : Control(), key_id( k_id ), local_key( local ), modifier_key( mod ) {

}

void Key::add_bind(Bind* _bind)
{
	binds.push_back(_bind);
}

bool Key::set_local_key(std::string local_key)
{
	return true;
}

bool Key::set_modifier(bool enable)
{
	return true;
}