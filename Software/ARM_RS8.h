/* Reed-Solomon encoder
 * Copyright 2004, Phil Karn, KA9Q
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 * 
 * This version modified by Philip Heron <phil@sanslogic.co.uk>
 * 
 */

#ifndef ARM_RS8_H
#define ARM_RS8_H

#include <stdint.h>

// Functions
extern void encode_rs_8(uint8_t *data, uint8_t *parity, int pad);

#endif // ARM_RS8_H_