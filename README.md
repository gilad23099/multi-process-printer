# Semaphore-Controlled Number Printer

This C program creates 5 child processes using `fork()`. Each process prints numbers from 1 to 100 in round-robin order. Synchronization is achieved using System V semaphores (`semget`, `semctl`, `semop`). Only one process is allowed to print at a time. Initially, semaphores are set so that only the first process can start. Each child waits on its semaphore (with `sem_op = -4`), prints its number (incrementing by 5 each time), then increases all other semaphores by 1 to allow the next processes to proceed. This ensures ordered and non-overlapping output.

**Compile:** `gcc -o sem assignment2_github.c`  
**Run:** `./sem`  
**Output:** `1 , 2 , 3 , ... , 100`

Semaphores are removed at the end using `IPC_RMID`. The code uses `union semun` for semaphore control and `struct sembuf` to define operations. It's a clean example of process synchronization and shared resource management.
