#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>

typedef struct node {
    char dat[255];
    struct node *next;
} node_t;

void push(node_t *, char []);
void print_list(node_t *);
void *threadSHM(void *);

int main() {
    
    //node basic pointers def start
    node_t *head = NULL;
    head = malloc(sizeof(node_t));
    head -> next = NULL;
    //END

    //filehandling
    FILE *fp;
    char buff[255];
    fp = fopen("/Users/danish/Documents/CS6/OS/movieworld/collection.txt", "r");
    while (fgets(buff, 255, (FILE*)fp) != NULL)
    {
        push(head, buff);
    }
    fclose(fp);
    print_list(head);
    //strcpy(head -> dat, "yoyo");
    //threading
    pthread_t tid;
    
    pthread_create(&tid, NULL, threadSHM, (void *) head);
    pthread_join(tid, NULL);
    
    //END
    exit(1);
}

void push(node_t *head, char val[255]) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = malloc(sizeof(node_t));
    strcpy(current->next->dat, val);
    current->next->next = NULL;
}

void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%s \n", current->dat);
        current = current->next;
    }
}

void *threadSHM(void * head)
{
    node_t *headOne = (node_t *) head;
    int shm_id;
    key_t key = 1000;
    node_t *shm_ptr, *s;
    shm_id = shmget(key, 255, IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget error (server)");
        return NULL;
    }
    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (node_t *) -1) {
        perror("shmat error(server)");
    }
    s = shm_ptr;
    s = headOne;
    shmdt(shm_ptr);
    //shmctl(shm_id, IPC_RMID, NULL);
    return NULL;
}