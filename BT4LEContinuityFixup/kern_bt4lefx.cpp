//
//  kern_bt4lefx.cpp
//  BT4LEContinuityFixup
//
//  Copyright © 2017 lvs1974. All rights reserved.
//

#include <Headers/kern_api.hpp>
#include <Headers/kern_util.hpp>

#include "kern_bt4lefx.hpp"

static BT4LEFX *callbackBT4LEFX = nullptr;

static const char *kextIOBluetoothFamily[] { "/System/Library/Extensions/IOBluetoothFamily.kext/Contents/MacOS/IOBluetoothFamily" };

static KernelPatcher::KextInfo kextIOBluetooth { "com.apple.iokit.IOBluetoothFamily", kextIOBluetoothFamily, 1, {true, true}, {}, KernelPatcher::KextInfo::Unloaded };

bool BT4LEFX::init()
{
	callbackBT4LEFX = this;

	lilu.onKextLoadForce(&kextIOBluetooth, 1,
	[](void *user, KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size) {
		callbackBT4LEFX->processKext(patcher, index, address, size);
	}, this);

	return true;
}

void BT4LEFX::deinit()
{
}

int BT4LEFX::AppleBroadcomBluetoothHostController_SetControllerFeatureFlags(void *that, unsigned int)
{
	DBGLOG("bt4lefx", "AppleBroadcomBluetoothHostController::SetControllerFeatureFlags is called");
	int result = FunctionCast(AppleBroadcomBluetoothHostController_SetControllerFeatureFlags,
							  callbackBT4LEFX->orgIOBluetoothHostController_SetControllerFeatureFlags)(that, 0x0F);
	DBGLOG("bt4lefx", "IOBluetoothHostController::SetControllerFeatureFlags returned %d", result);

	return result;
}

void BT4LEFX::processKext(KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size)
{
	if (kextIOBluetooth.loadIndex == index) {
		DBGLOG("bt4lefx", "%s", kextIOBluetooth.id);
		
		const char* symbol = (getKernelVersion() > KernelVersion::Yosemite) ?
			"__ZN25IOBluetoothHostController25SetControllerFeatureFlagsEj" :
			"__ZN24IOBluetoothHCIController25SetControllerFeatureFlagsEj";

		KernelPatcher::RouteRequest request {
				symbol,
				AppleBroadcomBluetoothHostController_SetControllerFeatureFlags,
				orgIOBluetoothHostController_SetControllerFeatureFlags
		};
		patcher.routeMultiple(index, &request, 1, address, size);
		if (patcher.getError() == KernelPatcher::Error::NoError) {
			DBGLOG("bt4lefx", "routed %s", symbol);
		} else {
			SYSLOG("bt4lefx", "failed to resolve %s, error = %d", symbol, patcher.getError());
			patcher.clearError();
		}
	}
}
