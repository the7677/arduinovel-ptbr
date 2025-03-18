#include <avr/pgmspace.h>

#ifndef SPRITES_H
#define SPRITES_H

// Buffer para um pixel por vez do sprite na RAM
extern char pixel_buff;

// Sprites

#define MAY_W 40
#define MAY_H 64
extern const char MAY_SPRITE[] PROGMEM;

#define SPLASH_W 64
#define SPLASH_H 40
extern const char SPLASH_SPRITE[] PROGMEM;

// Função para carregar sprites com menos memória, largura precisa ser par
// Corta sprite em secções verticais, precisando alocar menos RAM
void drawSprite(int x, int y, int width, int height, const char *sprite);

#endif