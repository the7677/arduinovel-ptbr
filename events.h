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
};

extern const Event devents[];

#endif