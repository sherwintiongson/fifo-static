/********************************************************************
 * Dependencies:    See INCLUDES section below
 * Processor:       PICxxx
 * Compiler:        XCx
 * Author:          Sherwin Tiongson
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement:
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the "Company") for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company's customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *********************************************************************
 ********************************************************************/
#ifndef FIFO_STATIC_H
#define	FIFO_STATIC_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum fifo_resp_e
{
    FIFO_STATIC_OK = 0,
    FIFO_STATIC_EMPTY,
    FIFO_STATIC_FULL,
    FIFO_STATIC_NULL_HANDLER,
    FIFO_STATIC_NULL_BUFFER,
    FIFO_STATIC_ILLEGAL_SIZE,
} fifo_resp_t;
    
#define FIFO_STATIC_SIZE   200
typedef struct fifo_buffer_s
{
    volatile uint8_t head;     							/*! last in byte */
    volatile uint8_t tail;     							/*! first in byte */
    volatile uint8_t buffer[FIFO_STATIC_SIZE]; 			/*! block of memory or array of data */
    volatile uint8_t buffer_len;     					/*! length of fifo */
    volatile fifo_resp_t status;
} fifo_buffer_t;

// Public functions
void fifo_static_init( fifo_buffer_t* b);
fifo_resp_t fifo_static_getStatus( fifo_buffer_t const *b );
bool fifo_static_full ( fifo_buffer_t const *b);
bool fifo_static_empty( fifo_buffer_t const *b);
uint8_t fifo_static_peek( fifo_buffer_t const *b);
fifo_resp_t fifo_static_get( fifo_buffer_t * b, uint8_t* byte_out);
fifo_resp_t fifo_static_put( fifo_buffer_t * b, uint8_t data_byte);
uint8_t fifo_static_count( fifo_buffer_t const *b);
void fifo_static_refresh( fifo_buffer_t * b);

#ifdef	__cplusplus
}
#endif

#endif	/* FIFO_STATIC_H */
/* end of file */

