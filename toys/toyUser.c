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
    toybox box;
    
    my_pid = getpid();
    shmkey = TOYBOX_KEY;
    shmflag = IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR ;
    
    printf("\nOnce upon a time...");
    
    //create memory
    shmid = shmget( shmkey, BOX_SIZE, shmflag);
    
    if ( shmid != -1 ) {
        printf("\nThe Parent with id %d bought a toybox labeled \"%d\""
             , my_pid , shmid) ;
    }
    else {
        printf("\nThe Parent with id %d failed to buy a toybox. \"Errno %d\", the parent swears."
             , my_pid , errno ) ;
        exit(-1) ;    
    }
    
    //attach to memory
    p = (toybox *) shmat( shmid, NULL, 0);
    if ( p == (toybox *) -1) {
        printf("\nThe parent could not open the toybox. The parent gives up and terminates himself. The end.");
        exit(-1);
    }
    
    box->toy1 = "Bear";
    printf("\nThe parent creates a toy %s. The parent puts the toy in the box.", box->toy1);
    box->toy2 = "Bat";
    printf("\nThe parent creates a toy %s. The parent puts the toy in the box.", box->toy2);
    box->toy3 = "Plastic bag"
    printf("\nThe parent creates a toy %s. The parent puts the toy in the box.", box->toy3);
    
   
}
