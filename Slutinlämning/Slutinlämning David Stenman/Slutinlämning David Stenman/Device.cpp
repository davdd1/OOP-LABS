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
	cout << "NetworkDevice[" << this->getName() << "] says Hello!" << endl;
	if (getLeftDevice() != nullptr)
		cout << "  and NetworkDevice[" << getLeftDevice()->getName() << "] also says Hello!";
	if (getRightDevice() != nullptr)
		cout << "  and NetworkDevice[" << getRightDevice()->getName() << "] also says Hello!";
}

AudioDevice::AudioDevice(string name)
	: Device(name)
{
	cout << "AudioDevice[" << this->getName() << "] was created!" << endl;
}

void Device::pingAllChildren() {
	{
		// If this device has a left child, ping it and all its children
		if (getLeftDevice() != nullptr)
		{
			cout << "Device[" << getLeftDevice()->getName() << "] says Hello!" << endl;
			getLeftDevice()->pingAllChildren();
		}

		// If this device has a right child, ping it and all its children
		if (getRightDevice() != nullptr)
		{
			cout << "Device[" << getRightDevice()->getName() << "] says Hello!" << endl;
			getRightDevice()->pingAllChildren();
		}
	}
}

void AudioDevice::ping()
{
	// If this device is the root (no parent), ping all children
	if (getParentDevice() == nullptr)
	{
		cout << "AudioDevice[" << this->getName() << "] says Hello!" << endl;
		pingAllChildren();
	}
	// If this device is not the root, pass the ping to the parent
	else
	{
		getParentDevice()->ping();
	}
}

void Device::disconnectDevice(Device* device)
{
	if (leftDevice == device)
	{
		leftDevice->dcParentDevice();
		leftDevice = nullptr;
	}
	else if (rightDevice == device)
	{
		rightDevice->dcParentDevice();
		rightDevice = nullptr;
	}
	else
	{
		cout << "Device is not connected to this device" << endl;
		return;
	}
	cout << "Device[" << device->getName() << "] was disconnected from Device[" << this->getName() << "]" << endl;
}

void Device::printDevice()
{
	cout << "Device[" << this->getName() << "]";

	if (leftDevice != nullptr || rightDevice != nullptr)
	{

		if (leftDevice != nullptr) {
			cout << " is connected to Device[" << leftDevice->getName() << "]";
			if (rightDevice != nullptr)
				cout << " and Device[" << rightDevice->getName() << "]";
		}
		else
		{
			cout << " is connected to Device[" << rightDevice->getName() << "]";
			if (leftDevice != nullptr)
				cout << " and Device[" << leftDevice->getName() << "]";
		}
	}
	cout << endl;
}


