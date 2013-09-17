#ifndef TOYBOX_H
#define TOYBOX_H

typedef struct {
  char name[30];
} toy;

typedef struct {
  toy toys[5];
} toybox;

// shared memory key
#define TOYBOX_KEY 0x666
#define BOX_SIZE sizeof(toybox)

#endif
