/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "adcsmodule.h"

MP_DEFINE_CONST_FUN_OBJ_1(switch_mode_obj, (void * (*)(void *))switch_mode);
MP_DEFINE_CONST_FUN_OBJ_1(__adcs_reset___obj, (void * (*)(void *))__adcs_reset__);

STATIC const mp_rom_map_elem_t adcs_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_switch_mode), MP_ROM_PTR(&switch_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR___adcs_reset__), MP_ROM_PTR(&__adcs_reset___obj) },
};

STATIC MP_DEFINE_CONST_DICT(adcs_locals_dict, adcs_locals_dict_table);

const mp_obj_type_t adcsmodule_adcs_type = {
    { &mp_type_type },
    .name = MP_QSTR_adcs,
    .make_new = adcs_make_new,
    .locals_dict = (mp_obj_dict_t*)&adcs_locals_dict,
};

STATIC const mp_rom_map_elem_t adcsmodule_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_adcs) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_ADCS), (mp_obj_t)&adcsmodule_adcs_type },
};

STATIC MP_DEFINE_CONST_DICT(adcsmodule_module_globals, adcsmodule_globals_table);

// Define module object.
const mp_obj_module_t adcsmodule_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&adcsmodule_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_adcs, adcsmodule_user_cmodule);