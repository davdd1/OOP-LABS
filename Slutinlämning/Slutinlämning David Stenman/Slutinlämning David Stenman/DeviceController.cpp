#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include "DeviceController.h"
#include "Device.h"

DeviceController::DeviceController()
{
}

//kolla om namnets input är giltigt
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

//skapa enhet om namnet är giltigt
void DeviceController::createDevice(string name, int deviceType)
{
	if (deviceType == 1 && isNameValid(name))
		Devices.push_back(new NetworkDevice(name));
	else if (deviceType == 2 && isNameValid(name))
		Devices.push_back(new AudioDevice(name));
}

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
	if (device2->getLeftDevice() == nullptr && device2->getRightDevice() == nullptr) {
		cout << "Device 2 is not connected to any device" << endl;
		return;
	}

	device1->disconnectDevice(device2);
	device2->disconnectDevice(device1);
	cout << "Devices " << device1->getName() << " and " << device2->getName() << " were disconnected!" << endl;
}

void DeviceController::deleteDevice(string name)
{
	for (Device* device : Devices)
	{
		if (device->getName() == name)
		{
			if (device->getLeftDevice() != nullptr)
				disconnectDevices(name, device->getLeftDevice()->getName());
			if (device->getRightDevice() != nullptr)
				disconnectDevices(name, device->getRightDevice()->getName());
			Devices.erase(std::remove(Devices.begin(), Devices.end(), device), Devices.end());
			delete device;
			return;
		}
	}
	cout << "Device does not exist" << endl;
}

void DeviceController::connectDevices(string deviceName1, string deviceName2)
{
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
	if (device1->getLeftDevice() != nullptr && device1->getRightDevice() != nullptr) {
		cout << device1->getName() << " is already connected to two devices" << endl;
		return;
	}
	if (device2->getParentDevice() != nullptr) {
		cout << device2->getName() << " is already connected to another device" << endl;
		return;
	}

	if (device1->getLeftDevice() != nullptr) {
		if (!isInTree(device1, device2->getName())) {
			cout << "Devices are already connected" << endl;
			return;
		}
		device1->setLeftDevice(device2);
		device2->setParentDevice(device1);
		return;
	}
	if (device1->getRightDevice() == nullptr) {
		device1->setRightDevice(device2);
		return;
	}

	cout << "Devices " << device1->getName() << " and " << device2->getName() << " were connected!" << endl;
}


void DeviceController::printDevices()
{
	for (Device* device : Devices)
	{
		device->printDevice();
	}
	cout << endl;
}

//traverserar genom trädet, returner true om det redan finns en koppling med en enhet med namnet för att undvika cykler
bool DeviceController::isInTree(Device* device, string name)
{
	if (device->getLeftDevice() != nullptr)
	{
		if (device->getLeftDevice()->getName() == name)
			return true;
		if (isInTree(device->getLeftDevice(), name))
			return true;
	}
	if (device->getRightDevice() != nullptr)
	{
		if (device->getRightDevice()->getName() == name)
			return true;
		if (isInTree(device->getRightDevice(), name))
			return true;
	}
	return false;
}

void DeviceController::devicePing(string deviceName)
{
	Device* device1 = nullptr;
	for (Device* device : Devices)
	{
		if (device->getName() == deviceName)
			device1 = device;
	}

	//felhantering
	if (device1 == nullptr) {
		cout << "Device does not exist" << endl;
		return;
	}
	device1->ping();
}

void DeviceController::createMenu() {
	int input;
	string name1;
	string name2;
	while (true)
	{
		cout << endl << "-----------------------------------" << "\n\n" << "What do you want to do?" << endl << 
			"1. Create device" << endl << "2. Delete device" << endl << "3. Connect devices" << endl << 
			"4. Disconnect devices" << endl <<"5. Print devices" << endl << "6. Ping device" << endl << "7. Quit" << endl << endl;
		cout << "Enter choice: ";

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
			cout << "Enter type:" << endl << "1. NetworkDevice \n2. AudioDevice" << endl;
			cin >> type;
			createDevice(name1, type);
		}
		else if (input == 2)
		{
			cout << "2. Delete device" << endl;
			cout << "Enter name: ";
			cin >> name1;
			deleteDevice(name1);
		}
		else if (input == 3)
		{
			cout << "3. Connect devices" << endl;
			cout << "Enter name of first device: ";
			cin >> name1;
			cout << "Enter name of second device: ";
			cin >> name2;
			connectDevices(name1, name2);
		}
		else if (input == 4)
		{
			cout << "4. Disconnect devices" << endl;
			cout << "Enter name of first device: ";
			cin >> name1;
			cout << "Enter name of second device: ";
			cin >> name2;
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
			devicePing(name1);
		}
		else if (input == 7)
		{
			cout << "7. Quit" << endl;
			cout << "See you next time!" << endl;
			break;
		}
	}
}

void InterfaceApp::run()
{
	controller.createMenu();
}