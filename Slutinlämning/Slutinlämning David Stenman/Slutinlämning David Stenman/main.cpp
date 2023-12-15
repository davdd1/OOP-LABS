#include "Device.h"

void main() {
	try
	{
		InterfaceApp Interface;
		Interface.run();
	}
	catch (const std::exception& e)
	{
		cout << "Error: " << e.what() << endl;
	}
}