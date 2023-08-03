; @file mpi_arm_v7m_iar.s
; @brief ARMv7-M (Cortex-M3/M4/M7) assembly routines for IAR EWARM compiler
;
; @section License
;
; Copyright (C) 2021-2023 Oryx Embedded SARL. All rights reserved.
;
; This file is part of CycloneBOOT Ultimate.
;
; This software is provided under a commercial license. You may
; use this software under the conditions stated in the license
; terms. This source code cannot be redistributed.
;
; @author Oryx Embedded SARL (www.oryx-embedded.com)
; @version 2.1.1

;**********
;* Macros *
;**********

MUL_ACC_CORE   macro
               mov   r5, #0
               ldr   r6, [r1], #4
               umlal r4, r5, r6, r3
               ldr   r6, [r0]
               adds  r6, r6, r4
               adc   r4, r5, #0
               str   r6, [r0], #4
               endm

;***********
;* Exports *
;***********

               public mpiMulAccCore

               rseg  CODE:CODE(2)
               thumb

;*********************************
;* Multiply-accumulate operation *
;*********************************

mpiMulAccCore
               push  {r4-r6}
               mov   r4, #0
               cmp   r2, #8
               blo   next1
loop1
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               sub   r2, r2, #8
               cmp   r2, #8
               bhs   loop1
next1
               cmp   r2, #1
               blo   next2
loop2
               MUL_ACC_CORE
               subs  r2, r2, #1
               bne   loop2
next2
               cbz   r4, next3
loop3
               ldr   r6, [r0]
               adds  r6, r6, r4
               str   r6, [r0], #4
               mov   r4, #0
               adcs  r4, r4, #0
               bne   loop3
next3
               pop   {r4-r6}
               bx    r14

               end
