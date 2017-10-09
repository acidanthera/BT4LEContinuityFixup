//
//  kern_bt4lefx.cpp
//  BT4LEContiunityFixup
//
//  Copyright © 2017 lvs1974. All rights reserved.
//

#include <Headers/kern_api.hpp>
#include <Headers/kern_util.hpp>

#include "kern_bt4lefx.hpp"


static BT4LEFX *callbackBT4LEFX = nullptr;

static const char *kextIOBluetoothFamily[] { "/System/Library/Extensions/IOBluetoothFamily.kext/Contents/MacOS/IOBluetoothFamily" };

static KernelPatcher::KextInfo kextList[] {
    { "com.apple.iokit.IOBluetoothFamily", kextIOBluetoothFamily, 1, {true, true}, {}, KernelPatcher::KextInfo::Unloaded }
};

static size_t kextListSize {1};

bool BT4LEFX::init()
{
	LiluAPI::Error error = lilu.onKextLoad(kextList, kextListSize,
	[](void *user, KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size)
    {
		callbackBT4LEFX = static_cast<BT4LEFX *>(user);
		callbackBT4LEFX->processKext(patcher, index, address, size);
	}, this);
	
	if (error != LiluAPI::Error::NoError)
    {
		SYSLOG("bt4lefx", "failed to register onKextLoad method %d", error);
		return false;
	}
	
	return true;
}

void BT4LEFX::deinit()
{
}

int BT4LEFX::AppleBroadcomBluetoothHostController_SetControllerFeatureFlags(void *that, unsigned int)
{
    int result = 0;
    
    DBGLOG("bt4lefx", "AppleBroadcomBluetoothHostController::SetControllerFeatureFlags is called");
    if (callbackBT4LEFX && callbackBT4LEFX->orgIOBluetoothHostController_SetControllerFeatureFlags)
    {
        result = callbackBT4LEFX->orgIOBluetoothHostController_SetControllerFeatureFlags(that, 0x0F);
        DBGLOG("bt4lefx", "IOBluetoothHostController::SetControllerFeatureFlags returned %d", result);
    }
    
    return result;
}

void BT4LEFX::processKext(KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size)
{
	if (progressState != ProcessingState::EverythingDone)
    {
		for (size_t i = 0; i < kextListSize; i++)
        {
			if (kextList[i].loadIndex == index)
            {
                if (!(progressState & ProcessingState::IOBluetoothFamilyPatched) && !strcmp(kextList[i].id, "com.apple.iokit.IOBluetoothFamily"))
                {
                    DBGLOG("bt4lefx", "%s", kextList[i].id);
                    
                    auto method_address = patcher.solveSymbol(index, "__ZN36AppleBroadcomBluetoothHostController25SetControllerFeatureFlagsEj");
                    if (method_address) {
                        DBGLOG("bt4lefx", "obtained __ZN36AppleBroadcomBluetoothHostController25SetControllerFeatureFlagsEj");
                        patcher.routeFunction(method_address, reinterpret_cast<mach_vm_address_t>(AppleBroadcomBluetoothHostController_SetControllerFeatureFlags), true);
                        if (patcher.getError() == KernelPatcher::Error::NoError) {
                            DBGLOG("bt4lefx", "routed __ZN36AppleBroadcomBluetoothHostController25SetControllerFeatureFlagsEj");
                        } else {
                            SYSLOG("bt4lefx", "failed to route __ZN36AppleBroadcomBluetoothHostController25SetControllerFeatureFlagsEj");
                        }
                    } else {
                        SYSLOG("bt4lefx", "failed to resolve __ZN36AppleBroadcomBluetoothHostController25SetControllerFeatureFlagsEj");
                    }
                    
                    method_address = patcher.solveSymbol(index, "__ZN25IOBluetoothHostController25SetControllerFeatureFlagsEj");
                    if (method_address) {
                        DBGLOG("bt4lefx", "obtained __ZN25IOBluetoothHostController25SetControllerFeatureFlagsEj");
                        orgIOBluetoothHostController_SetControllerFeatureFlags = reinterpret_cast<t_set_controller_feature_flags>(method_address);
                    } else {
                        SYSLOG("bt4lefx", "failed to resolve __ZN25IOBluetoothHostController25SetControllerFeatureFlagsEj");
                    }

                    progressState |= ProcessingState::IOBluetoothFamilyPatched;
                }
			}
		}
	}
	
	// Ignore all the errors for other processors
	patcher.clearError();
}


