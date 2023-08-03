; @file mpi_arm_v4_keil.s
; @brief ARMv4 (ARM7TDMI) assembly routines for Keil MDK-ARM compiler
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

               macro
               MUL_ACC_CORE
               mov   r5, #0
               ldr   r6, [r1], #4
               umlal r4, r5, r6, r3
               ldr   r6, [r0]
               adds  r6, r6, r4
               adc   r4, r5, #0
               str   r6, [r0], #4
               mend

;***********
;* Exports *
;***********

               export mpiMulAccCore

               preserve8
               arm

               area  |.text|, code, readonly

;*********************************
;* Multiply-accumulate operation *
;*********************************

               align

mpiMulAccCore  proc
               push  {r4-r6}
               mov   r4, #0
               cmp   r2, #16
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
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               sub   r2, r2, #16
               cmp   r2, #16
               bhs   loop1
next1
               cmp   r2, #8
               blo   next2
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               sub   r2, r2, #8
next2
               cmp   r2, #4
               blo   next3
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               MUL_ACC_CORE
               sub   r2, r2, #4
next3
               cmp   r2, #2
               blo   next4
               MUL_ACC_CORE
               MUL_ACC_CORE
               sub   r2, r2, #2
next4
               cmp   r2, #1
               blo   next5
               MUL_ACC_CORE
next5
               cmp   r4, #0
               beq   next6
loop2
               ldr   r6, [r0]
               adds  r6, r6, r4
               str   r6, [r0], #4
               mov   r4, #0
               adcs  r4, r4, #0
               bne   loop2
next6
               pop   {r4-r6}
               bx    r14
               endp

               end
