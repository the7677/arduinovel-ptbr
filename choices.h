#ifndef CHOICES_H
#define CHOICES

// Futuramente colocar na progmem

struct Choice {
    const char strings [2][16];
    int8_t points[2];
};

#define NO_CHOICE NULL

extern const Choice CHOICE_00;

#endif