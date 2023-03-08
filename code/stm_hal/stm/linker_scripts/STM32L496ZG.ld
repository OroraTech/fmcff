/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

MEMORY
{
    FLASH (rx) : ORIGIN = 0x8000000,  LENGTH = 1024K
    RAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 320K
}

REGION_ALIAS("ROM_REGION", FLASH)
