// Libs
#include <U8g2lib.h>
#include <string.h>

// Inner Files
#include "sprites.h"
#include "timer.h"
#include "dialog_lines.h"

// Controls
#define DOWN(BTN) digitalRead(BTN)
#define A      2
#define DLEFT  3
#define DRIGHT 4

// Sound
#define BUZZER 6
#define MAY_VOICE 440*4

// Fonts
#define FONT_1 u8g2_font_5x7_mr
#define FONT_2 u8g2_font_spleen5x8_mf
#define LINE_START_X 50
#define LINE_START_Y 20
#define LETTER_W     5
#define LETTER_H     8

// Display
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Dialog vars
size_t dcursor = 0;
int dcursor_x  = LINE_START_X;
int dcursor_y  = LINE_START_Y;

size_t dline_i = 0;

inline void drawGame() {
  u8g2.setDrawColor(1);

  u8g2.drawXBM(0, 0, MAY_W, MAY_H, MAY_BITS);

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



void drawDialog() {
  UPDATE_LINE_BUFFER;
  const char c = buff[dcursor];

  switch (c) {
  case '\n':
    dcursor_x = LINE_START_X;
    dcursor_y += LETTER_H;
    break;
  default:
    u8g2.drawGlyph(dcursor_x, dcursor_y, c);
    dcursor_x += LETTER_W;
    break;
  }
}

void updateDialog() {
  UPDATE_LINE_BUFFER;
  
  // Input
  if (DOWN(A)) {
    // Próximo diálogo
    if (dcursor == strlen(buff)) {
      clearDialog();
      dline_i++;
      dcursor = 0;
      dcursor_x = LINE_START_X;
      dcursor_y = LINE_START_Y;

      return; // Não atualiza
    // Ir ao fim do diálogo
    }
  }

  // Update
  if (dcursor < strlen(buff)) {
    dcursor++;
    tone(BUZZER, MAY_VOICE);
    delay(10);
    noTone(BUZZER);
    delay(2);
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

  drawGame();
}

void loop() {
  drawDialog();
  updateDialog();

  u8g2.sendBuffer();
}
