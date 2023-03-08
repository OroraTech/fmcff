/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "py/runtime.h"
#pragma GCC diagnostic pop

enum adcs_mode { 
    DETUMBLING = 0, 
    SUNPOINTING = 1, 
    NADIR = 2 
};

extern const mp_obj_type_t adcsmodule_adcs_type;
extern mp_obj_t adcs_make_new();
extern void __adcs_reset__();
extern void switch_mode(mp_obj_t self_in, enum adcs_mode mode);
