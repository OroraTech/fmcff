/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

extern "C" {
#include "gpiomodule.h"
}
#include "gpio.hpp"
#include <new>

namespace gpiomodule {

CycleCount cycles {};
static std::span<stm::periphs::gpio::Gpio> g_gpios {};

void setup_gpiomodule(std::span<stm::periphs::gpio::Gpio> gpios) {
    g_gpios = gpios;
}
}

struct gpiomodule_gpio_obj_t {
    mp_obj_base_t base;
    gpiomodule::GPIO handler;
};

mp_obj_t gpio_make_new(__attribute__((unused)) const mp_obj_type_t* type, __attribute__((unused)) size_t n_args, __attribute__((unused)) size_t n_kw, const mp_obj_t* args) {
    gpiomodule_gpio_obj_t* self = m_new_obj(gpiomodule_gpio_obj_t);
    self->base.type = &gpiomodule_gpio_type;
    new ((void*)&self->handler) gpiomodule::GPIO(gpiomodule::g_gpios, mp_obj_get_int(args[0]));
    return MP_OBJ_FROM_PTR(self);
}

void set(mp_obj_t self_in, bool val) {
    gpiomodule_gpio_obj_t* self = static_cast<gpiomodule_gpio_obj_t*>(MP_OBJ_TO_PTR(self_in));
    self->handler.set(mp_obj_get_int(mp_obj_new_bool(val)));
}

void set_high(mp_obj_t self_in) {
    gpiomodule_gpio_obj_t* self = static_cast<gpiomodule_gpio_obj_t*>(MP_OBJ_TO_PTR(self_in));
    self->handler.set_high();
}

void set_low(mp_obj_t self_in) {
    gpiomodule_gpio_obj_t* self = static_cast<gpiomodule_gpio_obj_t*>(MP_OBJ_TO_PTR(self_in));
    self->handler.set_low();
}

mp_obj_t get(mp_obj_t self_in) {
    gpiomodule_gpio_obj_t* self = static_cast<gpiomodule_gpio_obj_t*>(MP_OBJ_TO_PTR(self_in));
    return mp_obj_new_bool(self->handler.get());
}
