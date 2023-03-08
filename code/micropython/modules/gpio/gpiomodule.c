/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "gpiomodule.h"

MP_DEFINE_CONST_FUN_OBJ_1(set_obj, (void * (*)(void *))set);
MP_DEFINE_CONST_FUN_OBJ_1(set_high_obj, (void * (*)(void *))set_high);
MP_DEFINE_CONST_FUN_OBJ_1(set_low_obj, (void * (*)(void *))set_low);
MP_DEFINE_CONST_FUN_OBJ_1(get_obj, (void * (*)(void *))get);

STATIC const mp_rom_map_elem_t gpio_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set), MP_ROM_PTR(&set_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_high), MP_ROM_PTR(&set_high_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_low), MP_ROM_PTR(&set_low_obj) },
    { MP_ROM_QSTR(MP_QSTR_get), MP_ROM_PTR(&get_obj) },
};

STATIC MP_DEFINE_CONST_DICT(gpio_locals_dict, gpio_locals_dict_table);

const mp_obj_type_t gpiomodule_gpio_type = {
    { &mp_type_type },
    .name = MP_QSTR_gpio,
    .make_new = gpio_make_new,
    .locals_dict = (mp_obj_dict_t*)&gpio_locals_dict,
};

STATIC const mp_rom_map_elem_t gpiomodule_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_gpio) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_GPIO), (mp_obj_t)&gpiomodule_gpio_type },
};

STATIC MP_DEFINE_CONST_DICT(gpiomodule_module_globals, gpiomodule_globals_table);

// Define module object.
const mp_obj_module_t gpiomodule_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&gpiomodule_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_gpio, gpiomodule_user_cmodule);