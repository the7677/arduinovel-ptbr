// Libs
#include <U8g2lib.h>
#include <string.h>
#include <stdlib.h>

// Arquivos internos
#include "sprites.h"
#include "timer.h"
#include "dialog_lines.h"

// Controles
#define DOWN(BTN) digitalRead(BTN)
#define A      2
#define DLEFT  3
#define DRIGHT 4

// Som
#define BUZZER_1 6

#define MAY_VOICE 440 * 4 + (rand() % 76)
#define MAY_VOICE_MS 10
#define MAY_VOICE_PAUSE 2

#define PLAY_VOICE(BUZZER, VOICE, MS, PAUSE) tone(BUZZER, VOICE); delay(MS); noTone(BUZZER); delay(PAUSE)

// Texto
#define FONT_1 u8g2_font_5x7_mr
#define FONT_2 u8g2_font_spleen5x8_mf
#define LINE_START_X 50
#define LINE_START_Y 20
#define LETTER_W     5
#define LETTER_H     8

#define CURSOR_CHAR dbuff[dcursor]

#define UPDATE_DLINE strcpy_P(dbuff, (char*)pgm_read_word(&(dlines[dline_i])))
#define DLINE_LEN strlen(dbuff)

// Sprites
#define SPRITE sbuff

#define MAY_TO_BUFFER memcpy_P(sbuff, MAY_BITS, (MAY_W * MAY_H)/8)
#define SPLASH_TO_BUFFER memcpy_P(sbuff, SPLASH_BITS, (SPLASH_W * SPLASH_H)/8)

// Display
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Diálogo
size_t dcursor = 0;
int8_t dcursor_x  = LINE_START_X;
int8_t dcursor_y  = LINE_START_Y;

size_t dline_i = 0;

inline void drawGame() {
  u8g2.setDrawColor(1);

  MAY_TO_BUFFER;
  u8g2.drawXBM(0, 0, MAY_W, MAY_H, SPRITE);

  u8g2.drawLine(43, 31, 46, 25);
  u8g2.drawLine(43, 32, 46, 39);
  u8g2.drawFrame(47, 2, 79, 60);

  u8g2.setDrawColor(0);

  u8g2.drawLine(47, 25, 47, 39);
  u8g2.drawPixel(47, 2);
  u8g2.drawPixel(47, 61);
  u8g2.drawPixel(125, 2);
  u8g2.drawPixel(125, 61);

  u8g2.setDrawColor(1);
}

inline void drawDialog() {
  switch (CURSOR_CHAR) {
  case '\n':
    dcursor_x = LINE_START_X;
    dcursor_y += LETTER_H;
    break;
  default:
    u8g2.drawGlyph(dcursor_x, dcursor_y, CURSOR_CHAR);
    dcursor_x += LETTER_W;
    break;
  }
}

inline void updateDialog() {
  // Input
  // Próximo diálogo
  if (DOWN(A) && dcursor == DLINE_LEN) {
    clearDialog();
    dline_i++;
    UPDATE_DLINE;
    dcursor = 0;
    dcursor_x = LINE_START_X;
    dcursor_y = LINE_START_Y;

    return;
  // Ir ao fim do diálogo
  }

  // Update
  if (dcursor < DLINE_LEN) {
    dcursor++;
    PLAY_VOICE(BUZZER_1, MAY_VOICE, MAY_VOICE_MS, MAY_VOICE_PAUSE);
  }
}

inline void clearDialog() {
  u8g2.setDrawColor(0);
  u8g2.drawBox(48, 3, 77, 58);
  u8g2.setDrawColor(1);
}

void setup() {
  pinMode(A, INPUT);
  pinMode(DLEFT, INPUT);
  pinMode(DRIGHT, INPUT);
  
  u8g2.begin();
  u8g2.setContrast(0);
  u8g2.setFont(FONT_1);

  UPDATE_DLINE;

  drawGame();
}

void loop() {
  drawDialog();
  updateDialog();

  u8g2.sendBuffer();
}
