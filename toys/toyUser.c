/**************************************************************************
 * Authors: Douglas Applegate and Mike Lawless
 * Assignment Title: IPC demo
 * **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "toybox.h" 

int main(){
    pid_t my_pid, pid;
    int shmid;
    key_t shmkey;
    int shmflag;
    
    my_pid = getpid();
    shmkey = TOYBOX_KEY;
    shmflag = IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR ;
    
    shmid = shmget( shmkey, BOX_SIZE, shmflag);
    
    if ( shmid != -1 ) {
        printf("\nThe Parent with id %d  bought a toybox labeled \"%d\"\n"
             , my_pid , shmid) ;
    }
    else {
        printf("\nFailed to access shared memory \"0x%X\". errno=%d\n"
             , shmkey , errno ) ;
        exit(-1) ;    
    }
}
