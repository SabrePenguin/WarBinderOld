#include <vector>
#include <string>
#include "Bind.h"
#include "KeyBind.h"
#include "../control/Control.h"

/**
 * @brief The constructor
 * @param _internal_id: The internal id of the bind, such as ID_AAM
 * @param _text_id: What will be displayed to the user
 * @param _mode: The gamemode that this belongs to
*/
Bind::Bind(std::string _internal_id, std::string _text_id, char _mode) : 
	KeyBind( _mode ), internal_id(_internal_id), text_id(_text_id)
{

}
