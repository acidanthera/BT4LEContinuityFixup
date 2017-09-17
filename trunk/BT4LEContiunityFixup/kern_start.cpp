//
//  kern_start.cpp
//  BT4LEContiunityFixup
//
//  Copyright © 2017 lvs1974. All rights reserved.
//

#include <Headers/plugin_start.hpp>
#include <Headers/kern_api.hpp>

#include "kern_bt4lefx.hpp"

static BT4LEFX bt4lefx;

static const char *bootargOff[] {
	"-bt4lefxoff"
};

static const char *bootargDebug[] {
	"-bt4lefxdbg"
};

static const char *bootargBeta[] {
	"-bt4lefxbeta"
};

PluginConfiguration ADDPR(config) {
	xStringify(PRODUCT_NAME),
    parseModuleVersion(xStringify(MODULE_VERSION)),
	bootargOff,
	sizeof(bootargOff)/sizeof(bootargOff[0]),
	bootargDebug,
	sizeof(bootargDebug)/sizeof(bootargDebug[0]),
	bootargBeta,
	sizeof(bootargBeta)/sizeof(bootargBeta[0]),
	KernelVersion::MountainLion,
	KernelVersion::HighSierra,
	[]() {
		bt4lefx.init();
	}
};





