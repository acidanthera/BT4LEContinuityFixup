BT4LEContinuityFixup
===================

[![Build Status](https://travis-ci.org/acidanthera/BT4LEContinuityFixup.svg?branch=master)](https://travis-ci.org/acidanthera/BT4LEContinuityFixup) [![Scan Status](https://scan.coverity.com/projects/16403/badge.svg?flat=1)](https://scan.coverity.com/projects/16403)

An open source kernel extension providing patches for IOBluetoothFamily.

#### Features
- This tool makes the necessary changes to enable OS X 10.10 and 10.11 Continuity features on compatible hardware. 
Continuity features activated by this patch include Handoff, Instant Hotspot, and New Airdrop. 
OS X 10.11 (El Capitan) dongle support is not stable yet! (https://github.com/dokterdok/Continuity-Activation-Tool/)

#### Boot-args
- `-bt4lefxoff` disables kext loading
- `-bt4lefxdbg` turns on debugging output
- `-bt4lefxbeta` enables loading on unsupported osx

#### Credits
- [Apple](https://www.apple.com) for macOS  
- [vit9696](https://github.com/vit9696) for [Lilu.kext](https://github.com/vit9696/Lilu)
- [Sherlocks](http://www.insanelymac.com/forum/user/980913-sherlocks/) for the idea & testing
- [dokterdok](https://github.com/dokterdok/Continuity-Activation-Tool/) for patch
- [lvs1974](https://applelife.ru/members/lvs1974.53809/) for writing the software and maintaining it
