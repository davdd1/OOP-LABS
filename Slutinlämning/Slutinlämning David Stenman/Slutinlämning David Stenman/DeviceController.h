#pragma once
#include <string>
#include <iostream>
#include <vector>

using std::string; using std::endl; using std::cout; using std::cin; using std::vector;

class Device;

class DeviceController
{
private:
	vector <Device*> Devices;
public:
	DeviceController();
	~DeviceController(){}
	void createMenu();								//skapa menyn/interfacet
	void createDevice(string name, int deviceType);
	void deleteDevice(string name);
	void connectDevices(string deviceName1, string deviceName2);
	void disconnectDevices(string deviceName1, string deviceName2);
	void printDevices();							//Printar alla enheter och deras anslutna enheter
	bool isNameValid(string name);
	void devicePing(string deviceName);		//Pingar en enhet och spelar upp en beep om enheten är ansluten
	bool isInTree(Device* device, string name);				//Kollar om en enhet är ansluten till trädet
};

class InterfaceApp
{
private:
	DeviceController controller;
public:
	InterfaceApp(){}
	~InterfaceApp(){}
	void run();
};