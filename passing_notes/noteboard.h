/**************************************************************************
* Authors: Douglas Applegate and Mike Lawless
* Assignment Title: IPC demo
* **************************************************************************/

#include <sys/types.h>

#ifndef PASSING_NOTES_H
#define PASSING_NOTES_H

#define MSGQUE_KEY 0xF00D

typedef struct {
  long mtype;
  pid_t sender;
  char text[1];
} note_t;

#define NOTE_SIZE(N) (sizeof(note_t) - sizeof(long) + sizeof(char) * (N-1))

#endif
