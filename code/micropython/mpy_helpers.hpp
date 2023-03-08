/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

int setup_micropython();
void setup_wrapper();
void run_garbage_collector();
void execute_script(const char src[]);
