/**
 * @file slot.h
 * @brief Slot Memory managment
 *
 * @section License
 *
 * Copyright (C) 2021-2023 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneBOOT Ultimate.
 *
 * This software is provided under a commercial license. You may
 * use this software under the conditions stated in the license
 * terms. This source code cannot be redistributed.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 2.1.1
 **/

#ifndef _SLOT_H
#define _SLOT_H

//Dependencies
#include "os_port.h"
#include "error.h"

typedef struct
{
   uint32_t addr;    ///<Slot address
   size_t size;      ///<Slot size
   void *flash;      ///<Pointer to the descriptor of the flash holding the slot
} SlotDesc;

//CycloneBOOT Slot related functions
bool_t isSlotsOverlap(uint32_t addrSlot1, size_t sizeSlot1, uint32_t addrSlot2, size_t sizeSlot2);
bool_t isSlotInBank2(SlotDesc *slot);
bool_t isSlotInExtMem(SlotDesc *slot);
error_t slotRead(SlotDesc *slot, uint32_t offset, uint8_t *buffer, size_t length);
error_t slotErase(SlotDesc *slot);

#endif //!_SLOT_H
