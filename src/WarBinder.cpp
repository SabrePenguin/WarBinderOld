// WarBinder.cpp : The entry point of the program.
//

#include "WarBinder.h"
#include "KeyBindController.h"

using namespace std;

int main()
{
	cout << "Starting Program" << endl;
	KeyBindController key1("../../../../control_list.csv",
		"../../../../wt_bind_list.csv",
		"english");
	key1.import( "../../../../controller_settings.blk" ) ;
	return 0;
}
