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
  
  if((msgqid = msgget(key, 0644)) == -1) {
    perror("msgget");
    exit(1);
  }
  
  printf("**Ready to receive notes.\n");
  while(1){
    if(msgrcv(msgqid, note, NOTE_SIZE(max_string_length), 0, 0) == -1) {
      perror("msgrcv");
      exit(1);
    }
    printf("** \"%s\"\n** --from %d\n", note->text, note->sender);
  }
  
  return 0;
}
