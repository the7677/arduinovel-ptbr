// v0.15

// Libs
#include <U8g2lib.h>
#include <string.h>
#include <stdlib.h>

// Arquivos internos
#include "events.h"
#include "dialog_lines.h"
#include "sprites.h"

// Controles
#define DOWN(BTN) digitalRead(BTN)
#define A      2
#define DLEFT  3
#define DRIGHT 4

// Som
#define BUZZER_1 6

#define MAY_VOICE 440 * 4 + (rand() % 76 /* número da sorte*/)
#define MAY_VOICE_MS 10
#define MAY_VOICE_PAUSE 2

#define CHOICE_SOUND 440 * 6
#define CHOICE_MS 20
#define CHOICE_PAUSE 100

#define PLAY_SOUND(BUZZER, SOUND, MS, PAUSE) tone(BUZZER, SOUND); delay(MS); noTone(BUZZER); delay(PAUSE)

// Texto
#define FONT_1 u8g2_font_5x7_mf
#define FONT_2 u8g2_font_nokiafc22_tf

#define LINE_START_X 50
#define LINE_START_Y 20
#define LETTER_W     5
#define LETTER_H     8

#define CHOICE_X     50
#define CHOICE_ONE_Y 50
#define CHOICE_TWO_Y CHOICE_ONE_Y + LETTER_H

#define CURSOR_CHAR strbuff[vars.dcursor]
#define NEX_CURSOR_CHAR strbuff[vars.dcursor+1]

// Display
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset = */ U8X8_PIN_NONE);

// Diálogo e Escolhas
#define DLINE_TO_BUFF strcpy_P(strbuff, (char*)pgm_read_word(&(dlines[vars.dline_i])))
#define DLINE_LEN strlen(strbuff)

// Buffer das strings na RAM
#define MAX_STRLENGTH 64
unsigned char strbuff[MAX_STRLENGTH];

enum Mode : uint8_t {STARTPAGE, DIALOG, CHOICE};

// Gambiarrinha para economizar RAM
struct {
  uint8_t draw_color : 1  ;
  uint8_t dcursor    : 6  ;
  uint8_t dcursor_x  : 7  ;
  uint8_t dcursor_y  : 6  ;
  uint8_t dline_i    : 10 ;
  uint8_t selected   : 1  ;
  int8_t points      : 6  ;
  Mode    mode       : 3  ;
} vars = {1, 0, LINE_START_X, LINE_START_Y, 0, 0, 0,   STARTPAGE};

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
    vars.mode = DIALOG;
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
  u8g2.drawVLine(47, 40, 21);
  u8g2.drawHLine(48, 2, 77);
  u8g2.drawHLine(48, 61, 77);
  u8g2.drawVLine(125, 3, 58);
}

void handleEvents() {
  drawSprite(EXPRESSION_X, EXPRESSION_Y, EXPRESSION_W, EXPRESSION_H, devents[vars.dline_i].expression_sprite);

  switch (vars.dline_i) {
  case 1:
    if (vars.dcursor == DLINE_LEN) vars.mode = CHOICE;
    break;
  }
}

void drawDialog() {
  // Debug
  char buff[2];
  sprintf(buff, "%d", vars.points);
  u8g2.drawStr(0, LETTER_H, buff);

  // Draw
  switch (CURSOR_CHAR) {
  case '\n': // Line break
    vars.dcursor_x = LINE_START_X;
    vars.dcursor_y += LETTER_H;
    break;
  case '*': // Negrito
    if (NEX_CURSOR_CHAR != '*') {
      vars.draw_color = !vars.draw_color;
      u8g2.setDrawColor(vars.draw_color);
    }

    vars.dcursor++;
    // falltrough
  default: // Char print
  print_char:
    u8g2.drawGlyph(vars.dcursor_x, vars.dcursor_y, CURSOR_CHAR);
    vars.dcursor_x += LETTER_W;
    break;
  }
}

void updateDialog() {
  if (vars.dcursor < DLINE_LEN) {
    vars.dcursor++;
    PLAY_SOUND(BUZZER_1, MAY_VOICE, MAY_VOICE_MS, MAY_VOICE_PAUSE);
  }

  if (vars.dcursor == DLINE_LEN) {
    if (DOWN(A) || DOWN(DRIGHT)) {
      vars.dline_i++;
      goto clear;
    }

    if (DOWN(DLEFT) && vars.dline_i > 0) {
      vars.dline_i--;
      goto clear;
    }

    return;

    clear:
      clearDialog();
      vars.dcursor = 0;
      vars.dcursor_x = LINE_START_X;
      vars.dcursor_y = LINE_START_Y;

      DLINE_TO_BUFF;
  }
}

void clearDialog() {
  u8g2.setDrawColor(0);
  u8g2.drawBox(48, 3, 77, 58);
  u8g2.setDrawColor(1);
}

void drawChoice() {
  u8g2.setDrawColor(0);
  u8g2.drawBox(CHOICE_X, CHOICE_ONE_Y - LETTER_H, LETTER_W, LETTER_H * 2);
  u8g2.setDrawColor(1);

  switch (vars.selected) {
  case 0:
    u8g2.drawGlyph(CHOICE_X, CHOICE_ONE_Y, '>');
    break;
  case 1:
    u8g2.drawGlyph(CHOICE_X, CHOICE_TWO_Y, '>');
    break;
  }

  u8g2.setDrawColor(1);

  u8g2.drawUTF8(CHOICE_X + LETTER_W * 2, CHOICE_ONE_Y, devents[vars.dline_i].choice->strings[0]);
  u8g2.drawUTF8(CHOICE_X + LETTER_W * 2, CHOICE_TWO_Y, devents[vars.dline_i].choice->strings[1]);
}

void updateChoice() {
  if (DOWN(DLEFT) || DOWN(DRIGHT)) {
    vars.selected = !vars.selected;
    PLAY_SOUND(BUZZER_1, CHOICE_SOUND, CHOICE_MS, CHOICE_PAUSE);
  }

  if (DOWN(A)) {
    vars.points += devents[vars.dline_i].choice->points[vars.selected];
    vars.mode = DIALOG;

    vars.dline_i++;

    clearDialog();
    vars.dcursor = 0;
    vars.dcursor_x = LINE_START_X;
    vars.dcursor_y = LINE_START_Y;

    DLINE_TO_BUFF;
  }
}

void setup() {
  pinMode(A, INPUT);
  pinMode(DLEFT, INPUT);
  pinMode(DRIGHT, INPUT);
  
  u8g2.begin();
  u8g2.setContrast(0);
  u8g2.setFont(FONT_1);

  DLINE_TO_BUFF;

  drawStart();
}

void loop() {
  switch (vars.mode) {
  case STARTPAGE:
    updateStart();
    break;
  case DIALOG:
    handleEvents();
    drawDialog();
    updateDialog();
    break;
  case CHOICE:
    drawChoice();
    updateChoice();
    break;
  }

  u8g2.sendBuffer();
}
