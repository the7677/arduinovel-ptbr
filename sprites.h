#include <avr/pgmspace.h>

#ifndef SPRITES_H
#define SPRITES_H

// Sprites

#define SPLASH_W 64
#define SPLASH_H 40
extern const char SPLASH_SPRITE[] PROGMEM;

#define MAY_W 40
#define MAY_H 64
extern const char MAY_SPRITE[] PROGMEM;

#define EXPRESSION_X 18
#define EXPRESSION_Y 20
#define EXPRESSION_W 16
#define EXPRESSION_H 16
extern const char EXPRESSION_SMILE[] PROGMEM;
extern const char EXPRESSION_HAPPY[] PROGMEM;
extern const char EXPRESSION_SERIOUS[] PROGMEM;
extern const char EXPRESSION_SAD[] PROGMEM;
extern const char EXPRESSION_CONFUSED[] PROGMEM;
extern const char EXPRESSION_SOMEONE[] PROGMEM;

// Função para carregar sprites com menos memória, largura precisa ser par
// Corta sprite em secções verticais, precisando alocar menos RAM
void drawSprite(int x, int y, int width, int height, const char *sprite);

#endif