#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

#include "noteboard.h"

/*
  user processes send notes to mailbox, labeled with their process id (pid)
  
  able to check mailbox, then continue
  able to send mail to mailbox (with specific reciever?)
*/
