/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include <cstring>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wunused-parameter"

extern "C" {
#include "micropython/py/compile.h"
#include "micropython/py/gc.h"
#include "py/mphal.h"
#include "py/nlr.h"
}

#pragma GCC diagnostic pop

#include "mpy_helpers.hpp"

int setup_micropython() {
    gc_init_port();
    mp_init();
    return 0;
}

void setup_wrapper() {
    execute_script(R"(
import gpio
class switch:
    def __init__(self, id):
        self.id = id
        self.pin = gpio.GPIO(id)

    def turn_off(self):
        print("Turning switch off")
        self.pin.set_low()

    def turn_on(self):
        print("Turning switch on")
        self.pin.set_high()

    def __reset__(self):
        print("Reset switch module on switch " + str(self.id))
        self.pin.set_low()

)");
    execute_script(R"(
class payload:
    def __init__(self, id):
        self.pin = gpio.GPIO(id)

    def __reset__(self):
        print("Reset payload module\r\n")
        self.pin.set_low()
)");
    execute_script(R"(
class com:
    def __init__(self, id):
        self.pin = gpio.GPIO(id)

    def __reset__(self):
        print("Reset COM module")
        self.pin.set_low()
        self.pin.set_high()

)");
}

void run_garbage_collector() { gc_collect(); }

void execute_script(const char src[]) {
    mp_parse_input_kind_t input_kind = MP_PARSE_FILE_INPUT;
    nlr_buf_t nlr {};
    if (nlr_push(&nlr) == 0) {
        // Compile, parse and execute the given string.
        mp_lexer_t* lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, src, strlen(src), 0);
        qstr source_name = lex->source_name;
        mp_parse_tree_t parse_tree = mp_parse(lex, input_kind);
        mp_obj_t module_fun = mp_compile(&parse_tree, source_name, true);
        mp_call_function_0(module_fun);
        nlr_pop();
    } else {
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
    }
}
