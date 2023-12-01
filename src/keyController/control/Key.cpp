#include "Key.h"

Key::Key(int param_key_id, char param_local_id, bool param_modifier) {
	key_id = param_key_id;
	local_key = param_local_id;
	modifier_key = param_modifier;
}

int Key::add_bind()
{
	return 1;
}

bool Key::set_local_key(char local_key)
{
	return true;
}

bool Key::set_modifier(bool enable)
{
	return true;
}