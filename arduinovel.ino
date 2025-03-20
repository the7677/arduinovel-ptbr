// v0.13

// Libs
#include <U8g2lib.h>
#include <string.h>
#include <stdlib.h>

// Arquivos internos
#include "sprites.h"
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
#define FONT_1 u8g2_font_5x7_mf
#define FONT_2 u8g2_font_nokiafc22_tf

#define LINE_START_X 50
#define LINE_START_Y 20
#define LETTER_W     5
#define LETTER_H     8

#define CURSOR_CHAR dbuff[var_field.dcursor]
#define NEX_CURSOR_CHAR dbuff[var_field.dcursor+1]

// Display
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset = */ U8X8_PIN_NONE);

// Diálogo
#define UPDATE_DLINE strcpy_P(dbuff, (char*)pgm_read_word(&(dlines[var_field.dline_i])))
#define DLINE_LEN strlen(dbuff)

enum Mode : uint8_t {STARTPAGE, GAME};

// Gambiarrinha para economizar RAM
struct {
  uint8_t draw_color ;: 1  ;
  uint8_t dcursor    ;: 6  ;
  uint8_t dcursor_x  ;: 7  ;
  uint8_t dcursor_y  ;: 6  ;
  uint8_t dline_i    ;: 10 ;
  uint8_t selected   ;: 1  ;
  Mode    mode       ;: 1  ;
} var_field = {1, 0, LINE_START_X, LINE_START_Y, 0, 0, STARTPAGE};

void drawStart() {
  u8g2.setDrawColor(0);

  u8g2.clearBuffer();

  u8g2.setDrawColor(1);

  drawSprite((128-SPLASH_W)/2, 4, SPLASH_W, SPLASH_H, SPLASH_SPRITE);

  u8g2.setFont(FONT_2);
  u8g2.drawStr(42, 60, "> iniciar");
}

void updateStart() {
  if (DOWN(A)) {
    u8g2.setFont(FONT_1);
    drawMayAndBox();
    var_field.mode = GAME;
  }
}

void drawMayAndBox() {
  u8g2.setDrawColor(0);

  u8g2.clearBuffer();

  u8g2.setDrawColor(1);

  drawSprite(0, 0, MAY_W, MAY_H, MAY_SPRITE);

  u8g2.drawLine(43, 31, 46, 25);
  u8g2.drawLine(43, 32, 46, 39);
  u8g2.drawVLine(47, 3, 22);
  u8g2.drawVLine(47, 40, 22);
  u8g2.drawHLine(48, 2, 77);
  u8g2.drawHLine(48, 61, 77);
  u8g2.drawVLine(125, 3, 58);
}

void drawDialog() {
  // Draw
  switch (CURSOR_CHAR) {
  case '\n': // Line break
    var_field.dcursor_x = LINE_START_X;
    var_field.dcursor_y += LETTER_H;
    break;
  case '*': // Negrito
    if (NEX_CURSOR_CHAR != '*') {
      var_field.draw_color = !var_field.draw_color;
      u8g2.setDrawColor(var_field.draw_color);
    }

    var_field.dcursor++;
    // falltrough
  default: // Char print
  print_char:
    u8g2.drawGlyph(var_field.dcursor_x, var_field.dcursor_y, CURSOR_CHAR);
    var_field.dcursor_x += LETTER_W;
    break;
  }
}

void updateDialog() {
  if (var_field.dcursor < DLINE_LEN) {
    var_field.dcursor++;
    PLAY_VOICE(BUZZER_1, MAY_VOICE, MAY_VOICE_MS, MAY_VOICE_PAUSE);
  }

  if (var_field.dcursor == DLINE_LEN && ( DOWN(A) || (DOWN(DLEFT) && var_field.dline_i > 0) )) {
    var_field.dline_i += (DOWN(A)) ? 1 : -1;

    clearDialog();
    var_field.dcursor = 0;
    var_field.dcursor_x = LINE_START_X;
    var_field.dcursor_y = LINE_START_Y;

    UPDATE_DLINE;
  }
}

void clearDialog() {
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

  drawStart();
}

void loop() {
  switch (var_field.mode) {
  case STARTPAGE:
    updateStart();
    break;
  case GAME:
    drawDialog();
    updateDialog();
    break;
  }

  u8g2.sendBuffer();
}
