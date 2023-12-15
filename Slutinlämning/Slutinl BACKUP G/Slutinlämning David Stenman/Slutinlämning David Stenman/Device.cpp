#include <algorithm>
#include "Device.h"
#include <string>
#include <iostream>
#include <vector>

Device::Device(string& name)
	: name(name), connectedDevice(nullptr)
{
	cout << "Device[" << this->getName() << "] was created!" << endl;
}

void Device::printDevice()
{
	cout << "Device[" << this->getName() << "]";
	if (connectedDevice != nullptr)
		cout << " is connected to Device[" << connectedDevice->getName() << "]";
	cout << endl;
}

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
void DeviceController::createDevice(string name)
{
	if (isNameValid(name))
		Devices.push_back(new Device(name));
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
	if (device1->getConnectedDevice() == nullptr) {
		cout << "Device 1 is not connected to any device" << endl;
		return;
	}
	if (device2->getConnectedDevice() == nullptr) {
		cout << "Device 2 is not connected to any device" << endl;
		return;
	}

	device1->disconnectDevice();
	device2->disconnectDevice();
	cout << "Devices " << device1->getName() << " and " << device2->getName() << " were disconnected!" << endl;
}

void DeviceController::deleteDevice(string name)
{
	for (Device* device : Devices)
	{
		if (device->getName() == name)
		{
			if (device->getConnectedDevice() != nullptr)
				disconnectDevices(name, device->getConnectedDevice()->getName());
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
	if (device1->getConnectedDevice() != nullptr) {
		cout << "Device 1 is already connected to another device" << endl;
		return;
	}
	if (device2->getConnectedDevice() != nullptr) {
		cout << "Device 2 is already connected to another device" << endl;
		return;
	}

	device1->setConnectedDevice(device2);
	device2->setConnectedDevice(device1);
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

void DeviceController::devicePing(string deviceName)
{
	Device* device1 = nullptr;
	for (Device* device : Devices)
	{
		if (device1->getName() == deviceName)
			device1 = device;
	}

	//felhantering
	if (device1 == nullptr) {
		cout << "Device does not exist" << endl;
		return;
	}

	
	cout << "Device[" << device1->getName() << "] says Hello!" << endl;
	if (device1->getConnectedDevice() != nullptr)
		cout << "Device[" << device1->getConnectedDevice()->getName() << "] also says Hello!" << endl;
	
}

void DeviceController::createMenu() {
	int input;
	string name1;
	string name2;
	while (true)
	{
		cout << "What do you want to do?" << endl << "1. Create device" << endl <<
			"2. Delete device" << endl << "3. Connect devices" << endl << "4. Disconnect devices" << endl <<
			"5. Print devices" << endl << "6. Ping device" << endl << "7. Quit" << endl;

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
			cout << "1. Create device" << endl;
			cout << "Enter name: ";
			cin >> name1;
			createDevice(name1);
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
