/********************************************************************
 * Dependencies:    See INCLUDES section below
 * Processor:       PICxxxx
 * Compiler:        XCxx
 * Board:           ---
 * Author:          Sherwin Tiongson
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement:
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the "Company") for its PICmicro? Microcontroller is intended and
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
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <xc.h>

#include "fifo_static.h"

/*!
 * @name  fifo_static_count().
 * @brief Returns the number of elements in the fifo buffer.
 * @return Number of elements in the fifo buffer.
 */
uint8_t fifo_static_count ( fifo_buffer_t const *b)
{
    return (b ? (b->head - b->tail) : 0);
}



/*!
 * @name  fifo_static_full().
 * @brief Returns the empty/full status of the fifo buffer.
 * @return Returns true if the fifo buffer is full, false if it is not.
 */
bool fifo_static_full ( fifo_buffer_t const *b)
{
	return (b ? (fifo_static_count(b) == b->buffer_len) : true);
}



/*!
 * @name  fifo_static_empty().
 * @brief Returns the empty/full status of the fifo buffer
 * @return Returns true if the fifo buffer is empty, false if it is not.
 */
bool fifo_static_empty( fifo_buffer_t const *b)
{
    return (b ? (fifo_static_count(b) == 0) : true);
}



/*!
 * @name  fifo_static_peek().
 * @brief Looks at the data from the head of the list without removing it.
 * @return byte of data, or zero if nothing in the list.
 */
uint8_t fifo_static_peek( fifo_buffer_t const *b)
{
    if (b)
    {
        return (b->buffer[b->tail % b->buffer_len]);
    }
    return 0;
}




/*!
 * @name  fifo_static_get().
 * @brief Gets the data from the front of the list, and removes it
 * @return the data, or zero if nothing in the list
 */
fifo_resp_t fifo_static_get( fifo_buffer_t* b, uint8_t* byte_out)
{
    if (!fifo_static_empty(b)) {
        *byte_out = b->buffer[b->tail % b->buffer_len];
        b->tail++;
        b->status = FIFO_STATIC_OK;
    } else {
    	b->status = FIFO_STATIC_EMPTY;
    }
    return  b->status;
}




/*!
 * @name  fifo_static_put().
 * @brief Adds an element of data to the FIFO.
 */
fifo_resp_t fifo_static_put( fifo_buffer_t* b, uint8_t data_byte)
{
	if (b)
        {
		/* limit the fifo to prevent overwriting */
		if (!fifo_static_full(b))
                {
			b->buffer[b->head % b->buffer_len] = data_byte;
			b->head++;
			b->status = FIFO_STATIC_OK;
		} else
                {
			b->status = FIFO_STATIC_FULL;
		}
	}
    return b->status;
}




/*!
 * @name  fifo_static_refresh().
 * @brief Refresh FIFO count to ZERO.
 */
void fifo_static_refresh( fifo_buffer_t * b)
{
    if (b) {
        b->head = 0;
        b->tail = 0;
        b->status = FIFO_STATIC_OK;
    }
    return;
}



/*!
 * @name  fifo_static_init().
 * @brief Configures the fifo buffer.
 */
void fifo_static_init( fifo_buffer_t* b )
{
    if (b) {
        b->head = 0;
        b->tail = 0;
        b->buffer_len = FIFO_STATIC_SIZE;
        b->status = FIFO_STATIC_OK;
        memset((void*) b->buffer, 0x00, FIFO_STATIC_SIZE);
    }
    return;
}



/*!
 * @name  fifo_static_getStatus().
 * @brief Get fifo status.
 */
fifo_resp_t fifo_static_getStatus( fifo_buffer_t const *b )
{
	return b->status;
}
/* end of file */
