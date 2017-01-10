#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main()
{

    int choice = 0;
    bool invalid = true;
    pid_t child;

    do
    {
        printf("\n Welcome to movie world ! \n");
        printf("Main Menu - Input to navigate: \n");

        printf("1. View Collection: \n");
        printf("2. Rent a Movie: \n");
        printf("3. End Program: \n");

        printf("Your input: ");
        scanf("%i", &choice);
        switch (choice)
        {
        case 1: //calling filehanlder.c process
            child = fork();
            if (child < 0)
            {
                printf("Fork failed. \n");
                exit(-1);
            }
            else if (child == 0)
            {
                int x = execl("/Users/danish/Documents/CS6/OS/movieworld/two", NULL);
                exit(0);
            }
            else
            {
                wait(NULL);
            }
            break;
        case 2:
            child = fork();
            if (child < 0)
            {
                printf("Fork failed. \n");
                exit(-1);
            }
            else if (child == 0)
            {
                int x = execl("/Users/danish/Documents/CS6/OS/movieworld/three", NULL);
                exit(0);
            }
            else
            {
                wait(NULL);
            }
            break;
        case 3:
            printf("Ending program... \n");
            sleep(1);
            return 0;
            break;
        default:
            printf("Invalid input ! \n Try again. \n");
            invalid = true;
        }
    } while (invalid == true);
    return 0;
}
