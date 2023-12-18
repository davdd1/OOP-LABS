#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include "Device.h"

Device::Device(string& name)
	: name(name), leftDevice(nullptr), rightDevice(nullptr), parentDevice(nullptr)
{
}

NetworkDevice::NetworkDevice(string name)
	: Device(name)
{
	cout << "NetworkDevice[" << this->getName() << "] was created!" << endl;
}

void NetworkDevice::ping()
{
	cout << "Ping: NetworkDevice[" << this->getName() << "] says Hello!" << endl;
}

AudioDevice::AudioDevice(string name)
	: Device(name)
{
	cout << "AudioDevice[" << this->getName() << "] was created!" << endl;
}

void AudioDevice::ping()
{
	cout << "Ping: AudioDevice[" << this->getName() << "] says Hello!" << endl;
}

//koppla bort två enheter om de finns och är anslutna
void Device::disconnectDevice(Device* device)
{
	cout << "Device[" << device->getName() << "] was disconnected from Device[" << this->getName() << "]" << endl;
	if (leftDevice != nullptr && leftDevice == device)
	{
		leftDevice->dcParentDevice();
		leftDevice = nullptr;
	}
	else if (rightDevice != nullptr && rightDevice == device)
	{
		rightDevice->dcParentDevice();
		rightDevice = nullptr;
	}
	else if (parentDevice != nullptr && parentDevice == device)
	{
		if (leftDevice != nullptr)
		{
			leftDevice->dcParentDevice();
			leftDevice = nullptr;
		}
		if (rightDevice != nullptr)
		{
			rightDevice->dcParentDevice();
			rightDevice = nullptr;
		}
		parentDevice = nullptr;
	}
	else
	{
		cout << "Device is not connected to this device" << endl;
		return;
	}
}

//Printar enheten och dess anslutna enheter om den finns
//med rätt indentering
void Device::printDevice(int level)
{
	for (int i = 0; i < level; ++i)
		cout << "  ";

	cout << "Device: [" << this->getName() << "]" << endl;

	if (leftDevice != nullptr)
		leftDevice->printDevice(level + 1);

	if (rightDevice != nullptr)
		rightDevice->printDevice(level + 1);
}