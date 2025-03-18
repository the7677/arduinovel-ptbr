#include <avr/pgmspace.h>

// Buffer das strings na memória flash representadas na RAM
char dbuff[MAX_STRLENGTH];

// '*' inverte a cor (negrito). Usar '**' para ignorar.
// // O modo negrito sempre é interrompido ao mudar de linha, e '*' continua ocupando 1 caractere na memória
//                                                                                             v-- Limite, exceto por caracteres especiais com '\'
const char LINE_00[] PROGMEM = "*Ola*, **bom dia!**";
const char LINE_01[] PROGMEM = "Tudo bem? Como\nvoce esta?";
const char LINE_02[] PROGMEM = "Ja ouvi falar\num pouco sobre\nvoce.";
const char LINE_03[] PROGMEM = "Malditos ameri-\ncanos...";
const char LINE_04[] PROGMEM = "Nao incluiram\nacento na tabe-\nla ascii.";
const char LINE_05[] PROGMEM = "Por favor, nao\npule para o\nproximo dialo-\ngo.";
const char LINE_06[] PROGMEM = "Esta querendo\nlevar um\nSIGSEGV na sua\ncara?";
const char LINE_07[] PROGMEM = "/@#6 !!(0  ((\"\n  ?° * *  .     ";
const char LINE_08[] PROGMEM = "Brincadeira!\nNenhum acesso e\ninvalido aqui\nno ATMEGA328P.";
const char LINE_09[] PROGMEM = "O maximo que\npode acontecer\ne um cheirinho\nde queimado.";
const char LINE_10[] PROGMEM = "void\\\n(**reset)() = 0;\nreset();";

const char* const dlines[] PROGMEM = {
    LINE_00, LINE_01, LINE_02, LINE_03, LINE_04, LINE_05, LINE_06, LINE_07, LINE_08,
    LINE_09, LINE_10
};