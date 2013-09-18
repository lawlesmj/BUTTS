#include <sys/types.h>

#ifndef PASSING_NOTES_H
#define PASSING_NOTES_H

#define MSGQUE_KEY 0xF00D

typedef struct {
  long mtype;
  struct {
    pid_t sender;
    char text[128];
  } note;
} msgbuf;

#define NOTE_SIZE sizeof(msgbuf) - sizeof(long)

#endif
