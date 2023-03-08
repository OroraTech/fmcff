/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

extern "C" {
#include "adcsmodule.h"
}
#include <cstdio>
#include <string_view>

struct adcsmodule_adcs_obj_t {
    mp_obj_base_t base;
};

std::string_view mode_to_string(enum adcs_mode mode) {
    switch(mode) {
        case DETUMBLING:
            return "DETUMBLING";
        case SUNPOINTING:
            return "SUNPOINTING";
        case NADIR:
            return "NADIR";
        default:
            return "INVALID";
    }
}

mp_obj_t adcs_make_new() {
    adcsmodule_adcs_obj_t* self = m_new_obj(adcsmodule_adcs_obj_t);
    self->base.type = &adcsmodule_adcs_type;
    return MP_OBJ_FROM_PTR(self);
}

void __adcs_reset__() {
    printf("Reset ADCS module\r\n");
    printf("Switching mode to %s\r\n", mode_to_string(NADIR).data());
}

void switch_mode(__attribute__ ((unused)) mp_obj_t self_in, enum adcs_mode mode) {
    printf("Switching mode to %s\r\n", mode_to_string(mode).data());
}