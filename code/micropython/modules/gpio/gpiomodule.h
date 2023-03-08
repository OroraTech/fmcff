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

extern const mp_obj_type_t gpiomodule_gpio_type;
extern mp_obj_t gpio_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args);
extern void set(mp_obj_t self_in, bool val);
extern void set_high(mp_obj_t self_in);
extern void set_low(mp_obj_t self_in);
extern mp_obj_t get(mp_obj_t self_in);
