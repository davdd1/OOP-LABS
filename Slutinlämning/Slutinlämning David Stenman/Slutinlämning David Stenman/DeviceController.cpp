#include <algorithm>
#include "DeviceController.h"
#include "Device.h"

DeviceController::DeviceController()
{
}

//kolla om namnets input �r giltigt
bool DeviceController::isNameValid(string name) {
	if (name.empty()) {
		cout << "Name cannot be empty" << endl;
		return false;
	}
	if (name.length() > 20)
	{
		cout << "Name cannot be longer than 20 characters" << endl;
		return false;
	}
	if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != string::npos)
	{
		cout << "Name can only contain letters and numbers" << endl;
		return false;
	}
	if (name.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos)
	{
		cout << "Name must contain at least one letter" << endl;
	}
	if (name.find_first_of("01234567890") == 0)
	{
		cout << "Name cannot start with a number" << endl;
		return false;
	}

	for (Device* device : Devices)
	{
		if (device->getName() == name) {
			cout << "Device already exists" << endl;
			return false;
		}
	}

	return true;
}

//skapa enhet om namnet �r giltigt
void DeviceController::createDevice(string name, int deviceType)
{
	if (deviceType == 1 && isNameValid(name))
		Devices.push_back(new NetworkDevice(name));
	else if (deviceType == 2 && isNameValid(name))
		Devices.push_back(new AudioDevice(name));
}

//koppla bort tv� enheter om de finns och �r anslutna
void DeviceController::disconnectDevices(string deviceName1, string deviceName2)
{
	Device* device1 = nullptr;
	Device* device2 = nullptr;
	for (Device* device : Devices)
	{
		if (device->getName() == deviceName1)
			device1 = device;
		if (device->getName() == deviceName2)
			device2 = device;
	}

	//felhantering
	if (device1 == nullptr) {
		cout << "Device 1 does not exist" << endl;
		return;
	}
	if (device2 == nullptr) {
		cout << "Device 2 does not exist" << endl;
		return;
	}
	if (device1->getLeftDevice() == nullptr && device1->getRightDevice() == nullptr) {
		cout << "Device 1 is not connected to any device" << endl;
		return;
	}
	if (device2->getParentDevice() == nullptr) {
		cout << "Device 2 is not connected to any parent device" << endl;
		return;
	}

	device1->disconnectDevice(device2);
	cout << "Devices " << device1->getName() << " and " << device2->getName() << " were disconnected!" << endl;
}


//ta bort enhet om den finns, samt alla barnenheter
void DeviceController::deleteDevice(Device* deviceDel)
{
	if (deviceDel == nullptr) {
		cout << "Device does not exist" << endl;
		return;
	}
	if (deviceDel->getLeftDevice() != nullptr) {
		deleteDevice(deviceDel->getLeftDevice());
	}
	if (deviceDel->getRightDevice() != nullptr) {
		deleteDevice(deviceDel->getRightDevice());
	}

	//hitta enheten i vektorn och ta bort den
	auto it = std::find(Devices.begin(), Devices.end(), deviceDel);
	if (it != Devices.end())
	{
		if (deviceDel->getParentDevice() != nullptr)
			deviceDel->disconnectDevice(deviceDel->getParentDevice());
		delete deviceDel;
		Devices.erase(it);
	}
	else
		cout << "Device does not exist" << endl;
}

//anslut tv� enheter om de finns och inte redan �r anslutna
void DeviceController::connectDevices(string deviceName1, string deviceName2)
{
	if (deviceName1 == deviceName2) {
		cout << "Devices cannot connect to themselves" << endl;
		return;
	}

	//hitta enheterna med namnen
	Device* device1 = nullptr;
	Device* device2 = nullptr;
	for (Device* device : Devices)
	{
		if (device->getName() == deviceName1)
			device1 = device;
		if (device->getName() == deviceName2)
			device2 = device;
	}

	//felhantering
	if (device1 == nullptr) {
		cout << "Device 1 does not exist" << endl;
		return;
	}
	if (device2 == nullptr) {
		cout << "Device 2 does not exist" << endl;
		return;
	}
	if (device2->getParentDevice() != nullptr) {
		cout << device2->getName() << " is already connected to another device" << endl;
		return;
	}
	if ((device1->getLeftDevice() != nullptr && device1->getLeftDevice()->getName() == deviceName2) || (device1->getRightDevice() != nullptr && device1->getRightDevice()->getName() == deviceName2)) {
		cout << "Devices are already connected" << endl;
		return;
	}

	//kolla om det blir en cykel
	Device* temp = device1;
	while (temp->getParentDevice() != nullptr) {
		if (temp->getParentDevice()->getName() == deviceName2) {
			cout << "Cycles are not allowed" << endl;
			return;
		}
		temp = temp->getParentDevice();
	}
	if (device1->getLeftDevice() == nullptr) { //kolla om enheten har ledig v�nsterplats
		device1->setLeftDevice(device2);
		device2->setParentDevice(device1);
	}
	else if (device1->getRightDevice() == nullptr) { //kolla om enheten har ledig h�gerplats
		device1->setRightDevice(device2);
		device2->setParentDevice(device1);
	}
	else {
		cout << "Device already has two connections" << endl;
		return;
	}

	cout << "Devices " << device1->getName() << " and " << device2->getName() << " were connected!" << endl;
}

//printa alla enheter och deras anslutna enheter
void DeviceController::printDevices()
{
	if (Devices.empty())
		cout << "No devices to print" << endl;
	for (Device* device : Devices)
	{
		//bara printa roten av tr�den
		if (device->getParentDevice() == nullptr)
			device->printDevice(0); //b�rja med level 0 f�r r�tt indentering
	}
	cout << endl;
}

//pinga en enhet och dess f�r�ldrarenheter
void DeviceController::devicePing(Device* deviceP)
{
	if (deviceP == nullptr)
		return;
	devicePing(deviceP->getParentDevice());
	deviceP->ping();
}

//hitta enhet med namn
Device* DeviceController::findDevice(string deviceName)
{
	for (Device* device : Devices)
	{
		if (device->getName() == deviceName)
			return device;
	}
	return nullptr;
}

//skapa menyn/interfacet
void DeviceController::createMenu() {
	int input;
	string name1;
	string name2;
	while (true)
	{
		cout << endl << "-----------------------------------" << "\n\n" << "What do you want to do?" << endl <<
			"1. Create device" << endl << "2. Delete device" << endl << "3. Connect devices" << endl <<
			"4. Disconnect devices" << endl << "5. Print devices" << endl << "6. Ping device" << endl << "7. Quit" << endl << endl;
		cout << "Enter choice: ";

		//// Handle blank input
		//if (cin.peek() == '\n') {
		//	cin.ignore();
		//	cout << "Invalid input. Please enter a number." << endl;
		//	continue;
		//}

		cin >> input;
		while (!(input > 0 && input < 8))
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid input" << endl;
			cin >> input;
		}
		if (input == 1)
		{
			int type;
			cout << "1. Create device" << endl;
			cout << "Enter name: ";
			cin >> name1;
			cin.ignore();
			cout << "Enter type:" << endl << "1. NetworkDevice \n2. AudioDevice" << endl;
			cin >> type;
			while(type < 1 || type > 2)
			{
				cin.ignore();
				cout << "Invalid input. Please enter a choice, 1 or 2?" << endl;
				cin >> type;
			}
			createDevice(name1, type);
				
		}
		else if (input == 2)
		{
			cout << "2. Delete device" << endl;
			cout << "Enter name: ";
			cin >> name1;
			cin.ignore();
			deleteDevice(findDevice(name1));
		}
		else if (input == 3)
		{
			cout << "3. Connect devices" << endl;
			cout << "Enter name of first device: ";
			cin >> name1;
			cout << "Enter name of second device: ";
			cin >> name2;
			if (name1 != name2)
				connectDevices(name1, name2);
			else
				cout << "Cant connect to the same device";
		}
		else if (input == 4)
		{
			cout << "4. Disconnect devices" << endl;
			cout << "Enter name of first device: ";
			cin >> name1;
			cin.ignore();
			cout << "Enter name of second device: ";
			cin >> name2;
			cin.ignore();
			disconnectDevices(name1, name2);
		}
		else if (input == 5)
		{
			cout << "5. Print devices" << endl;
			printDevices();
		}
		else if (input == 6)
		{
			cout << "6. Ping device" << endl;
			cout << "Enter device name: ";
			cin >> name1;
			cin.ignore();
			devicePing(findDevice(name1));
		}
		else if (input == 7)
		{
			cout << "7. Quit" << endl;
			cout << "See you next time!" << endl;
			break;
		}
	}
}

//k�r menyn
void InterfaceApp::run()
{
	controller.createMenu();
}