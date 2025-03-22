#ifndef CHOICES_H
#define CHOICES

// Futuramente colocar na progmem

struct Choice {
    const char one[16];
    const char two[16];
};

#define NO_CHOICE NULL

extern const Choice CHOICE_00;

#endif