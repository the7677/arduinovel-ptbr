#include "choices.h"

#ifndef EVENTS_H
#define EVENTS_H

enum Expression {
    SMILE,
    HAPPY,
    SERIOUS,
    SAD,
    CONFUSED,
    SOMEONE
};

struct Event {
    const char *expression_sprite;
    const Choice *choice;
};

extern const Event devents[];

#endif