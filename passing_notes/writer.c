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
  msgbuf buf;
  int msgqid;
  key_t key;
  
  key = MSGQUE_KEY;
  
  if((msgqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
    perror("msgget");
    exit(1);
  }
  
  printf("Enter lines of text, ^D to quit:\n");
  buf.mtype = 1;
  buf.note.sender = getpid();
  
  while(fgets(buf.note.text, NOTE_SIZE, stdin) != NULL) {
    int len = strlen(buf.note.text);
    
    if (buf.note.text[len-1] == '\n') buf.note.text[len-1] = '\0';
    if (msgsnd(msgqid, &buf, len+1, 0) == -1) 
    perror("msgsnd");
  }
  
  // destroy the box
  if (msgctl(msgqid, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    exit(1);
  }
  return 0;
}
