#include <avr/pgmspace.h>

#ifndef DIALOG_LINES_H
#define DIALOG_LINES_H

#define UPDATE_LINE_BUFFER (strcpy_P(buff, (char*)pgm_read_word(&(dlines[dline_i]))))

#define MAX_STRLENGTH 64

const char LINE_0[] PROGMEM = "Ola, bom dia!";
const char LINE_1[] PROGMEM = "Tudo bem? Como\nvoce esta?";
const char LINE_2[] PROGMEM = "Ja ouvi falar\num pouco sobre\nvoce.";
const char LINE_3[] PROGMEM = "Fodidos ameri-\ncanos...";
const char LINE_4[] PROGMEM = "Nao incluiram\nacento na tabe-\nla ascii.";
const char LINE_5[] PROGMEM = "Por favor, nao\npule para o\nproximo dia-\nlogo.";
const char LINE_6[] PROGMEM = "Esta querendo\nlevar um\nSIGSEGV na sua\ncara?";
const char LINE_7[] PROGMEM = "/@#6 !!(0  ((\"\nł?°ŋħ“«»©«";
const char LINE_8[] PROGMEM = "Brincadeira!\nNenhum acesso e\ninvalido aqui\nno ATMEGA328P.";
const char LINE_9[] PROGMEM = "O maximo que\npode acontecer\ne um cheirinho\nde queimado.";

const char* const dlines[] PROGMEM = {
    LINE_0, LINE_1, LINE_2, LINE_3, LINE_4, LINE_5, LINE_6, LINE_7, LINE_8,
    LINE_9,
};

// Buffer das strings na memória flash representadas na RAM
char buff[MAX_STRLENGTH];

#endif 