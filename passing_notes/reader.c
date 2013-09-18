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
  
  if((msqid = msgget(key, 0644)) == -1) {
    perror("msgget");
    exit(1);
  }
  
  printf("**Ready to receive notes.\n");
  buf.mtype = 1;
  while(1){
    if(msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
      perror("msgrcv");
      exit(1);
    }
    printf("** \"%s\"\n** --from %d", buf.note.text, buf.note.sender);
  }
  
  return 0;
}
