#ifndef DIALOG_LINES_H
#define DIALOG_LINES_H

#define MAX_STRLENGTH 64

// Buffer das strings na RAM
extern unsigned char dbuff[MAX_STRLENGTH];

extern const unsigned char LINE_00[] PROGMEM;
extern const unsigned char LINE_01[] PROGMEM;
extern const unsigned char LINE_02[] PROGMEM;
extern const unsigned char LINE_03[] PROGMEM;
extern const unsigned char LINE_04[] PROGMEM;
extern const unsigned char LINE_05[] PROGMEM;
extern const unsigned char LINE_06[] PROGMEM;
extern const unsigned char LINE_07[] PROGMEM;
extern const unsigned char LINE_08[] PROGMEM;
extern const unsigned char LINE_09[] PROGMEM;
extern const unsigned char LINE_10[] PROGMEM;
extern const unsigned char LINE_11[] PROGMEM;
extern const unsigned char LINE_12[] PROGMEM;
extern const unsigned char LINE_13[] PROGMEM;
extern const unsigned char LINE_14[] PROGMEM;
extern const unsigned char LINE_15[] PROGMEM;

extern const unsigned char* const dlines[] PROGMEM;

enum Expression {
    SMILE,
    HAPPY,
    SERIOUS,
    SAD,
    CONFUSED,
    SOMEONE
};

struct Event {
    Expression expression;
};

extern const Event devents[];

#endif
