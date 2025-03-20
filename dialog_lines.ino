#include <avr/pgmspace.h>

// Importante: A codificação deste arquivo precisa estar em ISO 8859-1 para uma leitura correta.

// Buffer das strings na memória flash representadas na RAM
unsigned char dbuff[MAX_STRLENGTH];

// '*' inverte a cor (negrito). Usar '**' para ignorar.
// // O modo negrito interrompe ao mudar de linha, e '*' continua ocupando 1 caractere na memória.
//                                                                                             v-- Limite, exceto por caracteres especiais com '\'
const unsigned char LINE_00[] PROGMEM = "*Ola, bom dia!";
const unsigned char LINE_01[] PROGMEM = "Tudo bem? Como\nvoce esta?";
const unsigned char LINE_02[] PROGMEM = "Malditos ameri-\ncanos...";
const unsigned char LINE_03[] PROGMEM = "Nao incluiram\nacento na tabe-\nla ascii.";
const unsigned char LINE_04[] PROGMEM = "Mas olha só!\nAgora há com-\npatibilidade!!";
const unsigned char LINE_05[] PROGMEM = "Só precisei\ntrocar de UTF8\npara ISO\n8859-1.";
const unsigned char LINE_06[] PROGMEM = "...";
const unsigned char LINE_07[] PROGMEM = "Por favor, não\npule para o\npróximo diálo-\ngo.";
const unsigned char LINE_08[] PROGMEM = "O espaço na me-\nmória está\nacabando...";
const unsigned char LINE_09[] PROGMEM = "Está querendo\nlevar um\nSIGSEGV na sua\ncara?";
const unsigned char LINE_10[] PROGMEM = "/@#6 !!(0  ((\"\n  ?Â° * *  . ?   ";
const unsigned char LINE_11[] PROGMEM = "Brincadeira!\nNenhum acesso é\ninvalido aqui\nno ATMEGA328P.";
const unsigned char LINE_12[] PROGMEM = "O máximo que\npode acontecer\né um cheirinho\nde queimado.";
const unsigned char LINE_13[] PROGMEM = "Mas é sério,\na memória está\nacabando.";
const unsigned char LINE_14[] PROGMEM = "\"The fog is\ncoming.\"";
const unsigned char LINE_15[] PROGMEM = "void\\\n(**reset)() = 0;\nreset();";

const unsigned char* const dlines[] PROGMEM = {
    LINE_00, LINE_01, LINE_02, LINE_03, LINE_04, LINE_05, LINE_06, LINE_07, LINE_08,
    LINE_09, LINE_10, LINE_11, LINE_12, LINE_13, LINE_14, LINE_15
};