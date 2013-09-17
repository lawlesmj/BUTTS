#ifndef TOYBOX_H
#define TOYBOX_H

// shared memory key
#define TOYBOX_KEY 0x666

typedef struct {
  char name[30];
} toy;

typedef struct {
  toy toys[5];
} toybox;

#endif
