BT4LEContinuityFixup
===================

[![Build Status](https://travis-ci.com/acidanthera/BT4LEContinuityFixup.svg?branch=master)](https://travis-ci.com/acidanthera/BT4LEContinuityFixup) [![Scan Status](https://scan.coverity.com/projects/16403/badge.svg?flat=1)](https://scan.coverity.com/projects/16403)

An open source kernel extension providing patches for IOBluetoothFamily.

#### Special Notes
- In lieu of this kext, users are encouraged to test [this patch](https://github.com/acidanthera/bugtracker/issues/1173#issuecomment-702022932). If it functions as expected, this project will be [archived](https://github.com/acidanthera/bugtracker/issues/1173#issuecomment-702074550) and the aforementioned patch should be used instead.

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
