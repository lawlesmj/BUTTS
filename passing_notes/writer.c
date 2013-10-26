/**************************************************************************
* Authors: Douglas Applegate and Mike Lawless
* Assignment Title: IPC demo
* **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

#include "noteboard.h"

int main() {
  note_t * note;
  int msgqid;
  int max_string_length;
  key_t key;
  
  max_string_length = 144;
  
  note = (note_t *) malloc(sizeof(note_t) + sizeof(char) * (max_string_length - 1));
  if(note == NULL) {
    printf("Error allocating note of size %d.", max_string_length);
    exit(1);
  }
  
  key = MSGQUE_KEY;
  
  if((msgqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
    perror("msgget");
    exit(1);
  }
  
  printf("Enter lines of text, ^D to quit:\n");
  note->mtype = 1;
  note->sender = getpid();
  
  while(fgets(note->text, max_string_length, stdin) != NULL) {
    int len = strlen(note->text);
    
    if (note->text[len-1] == '\n') note->text[len-1] = '\0';
    if (msgsnd(msgqid, note, NOTE_SIZE(len+1), 0) == -1) perror("msgsnd");
  }
  
  // destroy the box
  if (msgctl(msgqid, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    free(note);
    exit(1);
  }
  
  free(note);
  return 0;
}
