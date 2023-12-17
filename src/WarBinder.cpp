// WarBinder.cpp : Defines the entry point for the application.
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
	//key1.add_new_bind("one_test", "One Test");
	//key1.add_key("2", "hi");
	return 0;
}
