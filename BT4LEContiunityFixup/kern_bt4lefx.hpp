//
//  kern_ngfx.hpp
//  BT4LEContiunityFixup
//
//  Copyright © 2017 lvs1974. All rights reserved.
//

#ifndef kern_bt4lefx_hpp
#define kern_bt4lefx_hpp

#include <Headers/kern_patcher.hpp>


class BT4LEFX {
public:
	bool init();
	void deinit();
	
private:
	/**
	 *  Patch kext if needed and prepare other patches
	 *
	 *  @param patcher KernelPatcher instance
	 *  @param index   kinfo handle
	 *  @param address kinfo load address
	 *  @param size    kinfo memory size
	 */
	void processKext(KernelPatcher &patcher, size_t index, mach_vm_address_t address, size_t size);

    
    /**
     *  IOBluetoothHostController_SetControllerFeatureFlags
     */
    using t_set_controller_feature_flags = int (*) (void *, unsigned int);
    
    
    /**
     *  Hooked methods / callbacks
     */
    static int AppleBroadcomBluetoothHostController_SetControllerFeatureFlags(void *that, unsigned int a2);
	
    t_set_controller_feature_flags   orgIOBluetoothHostController_SetControllerFeatureFlags {nullptr};
    
	/**
	 *  Current progress mask
	 */
	struct ProcessingState {
		enum {
			NothingReady = 0,
			IOBluetoothFamilyPatched = 2,
			EverythingDone = IOBluetoothFamilyPatched,
		};
	};
    int progressState {ProcessingState::NothingReady};
};

#endif /* kern_bt4lefx_hpp */
