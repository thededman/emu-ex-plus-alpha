/*  This file is part of Imagine.

	Imagine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Imagine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Imagine.  If not, see <http://www.gnu.org/licenses/> */

#define LOGTAG "BTInput"
#include <imagine/bluetooth/BluetoothAdapter.hh>
#include <imagine/bluetooth/Wiimote.hh>
#include <imagine/bluetooth/Zeemote.hh>
#include <imagine/bluetooth/IControlPad.hh>
#include <imagine/base/Base.hh>
#include <imagine/base/Timer.hh>
#include <imagine/util/container/ArrayList.hh>

StaticArrayList<BluetoothInputDevice*, Input::MAX_BLUETOOTH_DEVS_PER_TYPE * 2> btInputDevList;
StaticArrayList<BluetoothInputDevice*, Input::MAX_BLUETOOTH_DEVS_PER_TYPE> btInputDevPendingList;

#ifdef CONFIG_BLUETOOTH_SERVER
#include <imagine/bluetooth/PS3Controller.hh>
static PS3Controller *pendingPS3Controller = nullptr;
static BluetoothPendingSocket pendingSocket;
static BluetoothAdapter::OnStatusDelegate onServerStatus;
static Base::Timer unregisterHIDServiceCallback;
#endif
static bool hidServiceActive = false;

namespace Bluetooth
{
static bool testSupportedBTDevClasses(const uchar devClass[3])
{
	return Wiimote::isSupportedClass(devClass) ||
			IControlPad::isSupportedClass(devClass) ||
			Zeemote::isSupportedClass(devClass);
}

static void removePendingDevs()
{
	if(btInputDevPendingList.size())
		logMsg("removing %d devices in pending list", btInputDevPendingList.size());
	for(auto e : btInputDevPendingList)
	{
		delete e;
	}
	btInputDevPendingList.clear();
}

#ifdef CONFIG_BLUETOOTH_SERVER
bool listenForDevices(BluetoothAdapter &bta, const BluetoothAdapter::OnStatusDelegate &onScanStatus)
{
	if(bta.inDetect || hidServiceActive)
	{
		return false;
	}
	onServerStatus = onScanStatus;
	bta.onIncomingL2capConnection() =
		[](BluetoothAdapter &bta, BluetoothPendingSocket &pending)
		{
			if(!pending)
			{
				// TODO: use different status type for this
				//onServerStatus(bta, BluetoothAdapter::SOCKET_OPEN_FAILED, 0);
			}
			else if(pending.channel() == 0x13 && pendingPS3Controller)
			{
				logMsg("request for PSM 0x13");
				pendingPS3Controller->open2Int(bta, pending);
				pendingPS3Controller = nullptr;
			}
			else if(pending.channel() == 0x11)
			{
				logMsg("request for PSM 0x11");
				pendingSocket = pending;
				pending.requestName(
					[](BluetoothAdapter &bta, const char *name, BluetoothAddr addr)
					{
						if(!name)
						{
							onServerStatus(bta, BluetoothAdapter::SCAN_NAME_FAILED, 0);
							pendingSocket.close();
							return;
						}
						logMsg("name: %s", name);
						if(pendingSocket)
						{
							if(strstr(name, "PLAYSTATION(R)3"))
							{
								auto *dev = new PS3Controller(addr);
								if(!dev)
								{
									logErr("out of memory");
									return;
								}
								dev->open1Ctl(bta, pendingSocket);
								pendingSocket = {};
								pendingPS3Controller = dev;
							}
						}
					}
				);
			}
			else
			{
				logMsg("unknown request for PSM 0x%X", pending.channel());
				pending.close();
			}
		};

	logMsg("registering HID PSMs");
	hidServiceActive = true;
	bta.setL2capService(0x13, true,
		[](BluetoothAdapter &bta, uint success, int arg)
		{
			if(!success)
			{
				hidServiceActive = false;
				onServerStatus(bta, BluetoothAdapter::INIT_FAILED, 0);
				return;
			}
			logMsg("INT PSM registered");
			// now register the 2nd PSM
			bta.setL2capService(0x11, true,
				[](BluetoothAdapter &bta, uint success, int arg)
				{
					if(!success)
					{
						bta.setL2capService(0x13, false, {});
						hidServiceActive = false;
						onServerStatus(bta, BluetoothAdapter::INIT_FAILED, 0);
						return;
					}
					logMsg("CTL PSM registered");
					onServerStatus(bta, BluetoothAdapter::SCAN_COMPLETE, 0);
					// both PSMs are registered
					unregisterHIDServiceCallback.callbackAfterSec(
						[&bta]()
						{
							logMsg("unregistering HID PSMs from timeout");
							bta.setL2capService(0x11, false, {});
							bta.setL2capService(0x13, false, {});
							hidServiceActive = false;
						},
						8);
				}
			);
		}
	);

	return true;
}
#endif

bool scanForDevices(BluetoothAdapter &bta, BluetoothAdapter::OnStatusDelegate onScanStatus)
{
	if(!bta.inDetect && !hidServiceActive)
	{
		removePendingDevs();
		return bta.startScan(onScanStatus,
			[](BluetoothAdapter &, const uchar devClass[3]) // on device class
			{
				logMsg("class: %X:%X:%X", devClass[0], devClass[1], devClass[2]);
				return testSupportedBTDevClasses(devClass);
			},
			[&onScanStatus](BluetoothAdapter &bta, const char *name, BluetoothAddr addr) // on device name
			{
				if(!name)
				{
					onScanStatus(bta, BluetoothAdapter::SCAN_NAME_FAILED, 0);
					return;
				}
				if(btInputDevPendingList.isFull())
				{
					logWarn("reached max devices for scan");
					return;
				}
				if(strstr(name, "Nintendo RVL-CNT-01"))
				{
					auto *dev = new Wiimote(addr);
					if(!dev)
					{
						logErr("out of memory");
						return;
					}
					btInputDevPendingList.push_back(dev);
				}
				else if(strstr(name, "iControlPad-"))
				{
					auto *dev = new IControlPad(addr);
					if(!dev)
					{
						logErr("out of memory");
						return;
					}
					btInputDevPendingList.push_back(dev);
				}
				else if(strstr(name, "Zeemote JS1"))
				{
					auto *dev = new Zeemote(addr);
					if(!dev)
					{
						logErr("out of memory");
						return;
					}
					btInputDevPendingList.push_back(dev);
				}
			}
		);
	}
	return 0;
}

void closeDevices(BluetoothAdapter *bta)
{
	if(!bta)
		return; // Bluetooth was never used
	logMsg("closing all BT input devs");
	while(btInputDevList.size())
	{
		btInputDevList.front()->removeFromSystem();
	}
}

uint pendingDevs()
{
	return btInputDevPendingList.size();
}

void connectPendingDevs(BluetoothAdapter *bta)
{
	logMsg("connecting to %d devices", btInputDevPendingList.size());
	for(auto e : btInputDevPendingList)
	{
		if(e->open(*bta) != OK)
		{
			delete e;
		}
		// e is added to btInputDevList
	}
	btInputDevPendingList.clear();
}

void closeBT(BluetoothAdapter *&bta)
{
	if(!bta)
		return; // Bluetooth was never used
	if(bta->inDetect)
	{
		logMsg("keeping BT active due to scan");
		return;
	}
	removePendingDevs();
	closeDevices(bta);
	bta->close();
	bta = nullptr;
}

uint devsConnected()
{
	return btInputDevList.size();
}
}
