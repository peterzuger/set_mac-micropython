# set_mac-micropython

## Table of Contents
+ [About](#about)
+ [Getting Started](#getting_started)
+ [Usage](#usage)

## About <a name = "about"></a>
This is a module for [micropython](https://github.com/micropython/micropython)
to set the MAC adresses of LAN/WLAN and Bluetooth interfaces.

## Getting Started <a name = "getting_started"></a>

### Prerequisites
This module is designed for [micropython](https://github.com/micropython/micropython)

```
git clone --recurse-submodules https://github.com/micropython/micropython.git
```

to compile the project, [make](https://www.gnu.org/software/make/),
[gcc](https://gcc.gnu.org/) and [arm-none-eabi-gcc](https://gcc.gnu.org/) is required,
install them from your package manager

### Installing
[micropython-set\_mac](https://github.com/peterzuger/set_mac-micropython) is
mostly designed to work on the stm32 port.

First create a modules folder next to your copy of [micropython](https://github.com/micropython/micropython).

```
project/
├── modules/
│   └──set_mac-micropython/
│       ├──...
│       └──micropython.mk
└── micropython/
    ├──ports/
   ... ├──stm32/
      ...
```

And now put this project in the modules folder.

```
cd modules
git clone https://github.com/peterzuger/set_mac-micropython.git
```

Now that all required changes are made, it is time to build [micropython](https://github.com/micropython/micropython),
for this cd to the top level directory of [micropython](https://github.com/micropython/micropython).
From here, first the mpy-cross compiler has to be built:
```
make -C mpy-cross
```

once this is built, compile your port with:
```
make -C ports/stm32/ USER_C_MODULES=../modules CFLAGS_EXTRA=-DMODULE_SET_MAC_ENABLED=1
```

and you are ready to use set\_mac.

## Usage <a name = "usage"></a>
The module is available by just importing set\_mac:
```
import set_mac
```

The module has one function that can be used as follows:

```
import network
set_mac.set_mac(network.STA_IF, b"\xEB\x7B\xEF\xCC\x28\x80")
set_mac.set_mac(network.AP_IF, b"\xF6\x91\xDB\xC4\x33\x69")
```

This sets the MAC address of `STA_IF` (WLAN station mode) and `AP_IF` (WLAN
access point mode) to the respective address.
