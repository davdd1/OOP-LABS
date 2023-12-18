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
	void createDevice(string name, int deviceType);	//skapa en enhet
	void deleteDevice(Device* deviceDel);			//Ta bort en enhet om den finns
	void connectDevices(string deviceName1, string deviceName2);	//koppla ihop två enheter om de finns och inte är anslutna
	void disconnectDevices(string deviceName1, string deviceName2); //koppla bort två enheter om de finns och är anslutna
	void printDevices();							//Printar alla enheter och deras anslutna enheter
	bool isNameValid(string name);					//Kollar om namnet är giltigt
	void devicePing(Device* deviceP);		//Pingar en enhet och spelar upp en beep om enheten är ansluten
	Device* findDevice(string deviceName);			//Hittar en enhet i vektorn med namnet
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