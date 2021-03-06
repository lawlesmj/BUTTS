/**************************************************************************
 * Authors: Douglas Applegate and Mike Lawless
 * Assignment Title: IPC demo
 * **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>


#include "toybox.h" 

int main(){
    pid_t my_pid, pid;
    
    int shmid ;
    key_t shmkey;
    int shmflg ;
    toybox *box;
    
    my_pid = getpid();
    
    shmkey = TOYBOX_KEY ;
    shmflg = IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR ;
    
    printf("\nOnce upon a time...");
    
    //create memory
    shmid = shmget( shmkey , BOX_SIZE , shmflg ) ;
    
    if ( shmid != -1 ) {
        printf("\nThe Parent with id %d bought a toybox labeled \"%d\""
             , my_pid , shmid) ;
    }
    else {
        printf("\nThe Parent with id %d failed to buy a toybox. \"Errno %d\", the parent swears.\n"
             , my_pid , errno ) ;
        exit(-1) ;    
    }
    
    //attach to memory
    box = (toybox *) shmat( shmid, NULL, 0);
    if ( box == (toybox *) -1) {
        fprintf(stderr, "\nThe parent could not open the toybox.");
        fprintf(stderr,"\"Errno %d\", the parent swears.", errno);
        fprintf(stderr, "\nThe parent gives up and terminates himself.\nThe end.\n");
        shmctl( shmid , IPC_RMID , NULL );
        exit(-1);
    }
    
    //fill memory
    strcpy(box->toy1,"Bear");
    printf("\nThe parent creates a toy %s. The parent puts the toy in the box.", box->toy1);
    strcpy(box->toy2,"Ball");
    printf("\nThe parent creates a toy %s. The parent puts the toy in the box.", box->toy2);
    strcpy(box->toy3,"Plastic bag");
    printf("\nThe parent creates a toy %s. The parent puts the toy in the box.", box->toy3);
    
    //detach from memory
    shmdt( box );
    printf("\nThe parent has closed the toybox and will produce a child to use the toys.");
    
    pid = fork();
    
    if(pid<0){
        fprintf(stderr, "\nThe parent was unable to produce a child, terminating parent.");
        exit(-1);
    }
    else if (pid == 0){
        printf("\n\tWhy hello! I'm the child %d boy do I sure want to paly with some toys!", getpid());
        //attach to memory
        box = (toybox *) shmat( shmid, NULL, 0);
        if ( box == (toybox *) -1) {
            fprintf(stderr, "\nI could not open the toybox.");
            fprintf(stderr,"\"Errno %d\", I swears.", errno);
            fprintf(stderr, "\nI gives up and terminates myself.\nThe end.\n");
            shmctl( shmid , IPC_RMID , NULL );
            exit(-1);
        }
        
        //read memory
        printf("\n\tI delightedly play with my toy %s!\n\tIt exploded...", box->toy1);
        printf("\n\tI delightedly play with my toy %s!\n\tIt exploded...", box->toy2);
        printf("\n\tI delightedly play with my toy %s!\n\tIt exploded...", box->toy3);
        
        //detach memory
        shmdt( box );
        printf("\nI close the box and teminate myself.\n");
        
        //exit
        exit(0);
    }
    else{
        printf("\nThe parent waits for its new child to play with the toys.");
        printf("\nIts name is %d", pid);
        wait(NULL);
        printf("\nThe child has been terminated, so the parent destroys the toybox.");
        shmctl( shmid , IPC_RMID , NULL );
        printf("\nThen the parent terminate itself.\nThe End.\n");
        
        exit(0);
    }
}
