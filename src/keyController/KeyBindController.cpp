#include <iostream>
#include <vector>
#include "KeyBindController.h"
#include "Control.h"
#include "Key.h"
#include "Bind.h"

using namespace std;

void helloWorld() {
	Key key(3, 'a', true);
	Key* test_key = new Key(3, 'a', true);
	Bind* test_bind = new Bind();
	std::vector<Control*> keys;
	test_key->add_bind(test_bind);
	keys.push_back(test_key);
	cout << "Hello World" << endl;
}