/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include <stdlib.h>

void gc_init_port(void);
void gc_collect(void);
void nlr_jump_fail(void *ptr);
void mp_hal_set_interrupt_char(int c);
int mp_hal_stdin_rx_chr(void);
void mp_hal_stdout_tx_strn(const char *str, size_t len);
