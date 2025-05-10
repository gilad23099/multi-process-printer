#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
#define  NUMOFSEMS 5

void increaseAllButI(int i);

int semid, status;
struct sembuf sops[1];
union semun
{
    int val;
    struct semid_ds * buff;
    unsigned short *array;
    struct seminfo *_buf;
};
union semun semarg;

int main()
{
       semid = semget ( IPC_PRIVATE , NUMOFSEMS , 0666 ); // create 5 semaphores
       if (semid == -1)
       {
          perror("semget failed");
          exit(1);
       }       
       for(int i = 0; i < NUMOFSEMS ; i++)
       {     
            semarg.val = NUMOFSEMS-i-1;       
            if (semctl(semid, i, SETVAL, semarg) == -1) 
            {
                perror("semctl SETVAL failed");
                exit(1);
            }
            
       }
       
       sops->sem_flg = 0;
       for(int i = 0;i < NUMOFSEMS; i++)
       {
       
            pid_t pid = fork();
            if (pid == -1) 
            {
                perror("fork failed");
                exit(1);
            }
   
            if(pid == 0)
            {
                
                for(int j=i; j < 100 ; j += NUMOFSEMS)
                {
                       sops->sem_num=i;
                       sops->sem_op=-4;
                       if (semop(semid, sops, 1) == -1) 
                       {
                           perror("semop failed");
                           exit(1);
                       }
                       
                       //comma after all numbers except 100
                       if (j != 99) 
                       {
                           printf("%d , ", j + 1);         
                       } 
                       else 
                       {
                           printf("%d", j + 1); 
                       }
                       fflush(stdout);
                       increaseAllButI(i);
                }
                exit(0);
            
            }
       }
       for(int i = 0; i < NUMOFSEMS; i++) wait(NULL); // wait for all descendents
       printf("\n");
       if (semctl(semid, 0, IPC_RMID, semarg) == -1) 
       {
           perror("semctl IPC_RMID failed");
           exit(1);
       }
       
}       
       
void increaseAllButI(int i){
     
     int k;
     for(k=0;k< NUMOFSEMS;k++)
     {
     
           if(k!=i)
           {
                sops->sem_num = k;
                sops->sem_op = 1;
                if (semop(semid, sops, 1) == -1) 
                {
                    perror("semop failed");
                    exit(1);
                }
                
           }
     }
}       
       
       
       
       






























