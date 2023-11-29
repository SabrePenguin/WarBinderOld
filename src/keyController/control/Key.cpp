#include "Key.h"

Key::Key(int k_id, char local, bool mod) {
	key_id = k_id;
	local_key = local;
	modifier_key = mod;
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