#include <vector>
#include <string>
#include "Bind.h"
#include "../control/Control.h"
#include "../control/Key.h"

Bind::Bind(std::string _internal_id, std::string _text_id) : internal_id(_internal_id), text_id(_text_id)
{

}
/**
 * @brief Adds a vector of keys to the current Bind.
 * @param _control_combo : vector of implemented Control classes
*/
void Bind::add_control(std::vector<Control*> _control_combo)
{

}