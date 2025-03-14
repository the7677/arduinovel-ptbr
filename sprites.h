#include <avr/pgmspace.h>

#ifndef SPRITES_H
#define SPRITES_H

#define MAX_SPRITE_SIZE (64*40) /* bits */ / 8 /* -> bytes */
// * O importante é a quantidade de pixels ser menor ou igual ao produto de 64x40

#define SPRITE sbuff

// Buffer dos sprites na memória flash representadas na RAM
extern char sbuff[MAX_SPRITE_SIZE];

#define MAY_W 40
#define MAY_H 64
#define LOAD_MAY_SPRITE memcpy_P(sbuff, MAY_BITS, (MAY_W * MAY_H)/8)
extern const char MAY_BITS[] PROGMEM;

#define SPLASH_W 64
#define SPLASH_H 40
#define LOAD_SPLASH_SPRITE memcpy_P(sbuff, SPLASH_BITS, (SPLASH_W * SPLASH_H)/8)
extern const char SPLASH_BITS[] PROGMEM;

#endif