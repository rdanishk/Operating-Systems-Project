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

// void push(node_t *, char []);
void print_list(node_t *);

int main() {
    printf("Renting movie ");
    int shm_id;
    key_t key = 1000;
    node_t *shm_ptr, *s;
    shm_ptr = malloc(sizeof(node_t));
    shm_id = shmget(key, 255, 0666);
    if(shm_id < 0) {
        perror("shmget error (client)");
        return 0;
    }
    shm_ptr = shmat(shm_id, NULL, 0);
    if(shm_ptr == (node_t *) -1) {
        perror("shmat error (client)");
        return 0;
    }
    s = shm_ptr;
    print_list(s);

    shmdt(shm_ptr);
    return 0;
}

void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%s \n", current->dat);
        current = current->next;
    }
}