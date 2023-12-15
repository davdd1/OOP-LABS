#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "DeviceController.h"

class Device
{
private:
	const string name;
	Device* connectedDevice = nullptr;
public:
	Device(string& name);
	~Device() { cout << "Device deleted!" << endl; }
	string getName() { return name; }
	Device* getConnectedDevice() { return connectedDevice; }
	void setConnectedDevice(Device* device) { connectedDevice = device; }
	void disconnectDevice() { connectedDevice = nullptr; }
	void printDevice(); //Printar enheten och dess anslutna enhet om den finns
};