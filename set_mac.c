/**
 * @file   set_mac-micropython/set_mac.c
 * @author Peter Züger
 * @date   22.03.2023
 * @brief  set Micropython MAC address from Python
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2023 Peter Züger
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "py/mpconfig.h"

#if defined(MODULE_SET_MAC_ENABLED) && MODULE_SET_MAC_ENABLED == 1

#include "py/obj.h"
#include "py/objarray.h"
#include "py/runtime.h"
#include "mphalport.h"

#define MAC_COUNT 4
#define MAC_LENGTH 6
static uint8_t macs[MAC_COUNT][MAC_LENGTH] = {0};

void mp_hal_get_mac(int idx, uint8_t buf[MAC_LENGTH]) {
    if(idx <= 0 && idx <= MAC_COUNT){
        if(macs[idx][0] != 0){
            memcpy(buf, macs[idx], MAC_LENGTH);
            return;
        }
    }
    mp_hal_generate_laa_mac(idx, buf);
}

STATIC mp_obj_t set_mac_set_mac(mp_obj_t idx_in, mp_obj_t mac_in){
    mp_uint_t idx = mp_obj_int_get_uint_checked(idx_in);

    if(idx >= MAC_COUNT)
        mp_raise_ValueError(MP_ERROR_TEXT("MAC index out of range"));

    size_t size;

    // raises TypeError
    const uint8_t* mac = (const uint8_t*)mp_obj_str_get_data(mac_in, &size);

    if(size != MAC_LENGTH){
        mp_raise_ValueError(MP_ERROR_TEXT("MAC has the wrong size"));
    }

    memcpy(macs[idx], mac, size);

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(set_mac_set_mac_fun_obj, set_mac_set_mac);


STATIC const mp_rom_map_elem_t set_mac_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_set_mac) },
    { MP_ROM_QSTR(MP_QSTR_set_mac),  MP_ROM_PTR(&set_mac_set_mac_fun_obj)     },
};

STATIC MP_DEFINE_CONST_DICT(
    mp_module_set_mac_globals,
    set_mac_globals_table
    );

const mp_obj_module_t mp_module_set_mac = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_set_mac_globals,
};

MP_REGISTER_MODULE(MP_QSTR_set_mac, mp_module_set_mac);

#endif /* defined(MODULE_SET_MAC_ENABLED) && MODULE_SET_MAC_ENABLED == 1 */
