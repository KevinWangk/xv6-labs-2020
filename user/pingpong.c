#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[]) 
{
    int n,pid;
    int fds[2];
    char buf[100];
   
    if (argc >= 2) {
        fprintf(2, "PingPong need not parameter\n");
        exit(0);
    }
    pipe(fds);
    // read = fds[0], write = fds[1]
    pid = fork();

    if (pid == 0) {
        
        n = read(fds[0], buf, sizeof(buf));
        if (n == 1) {
            printf("%d: received ping\n", getpid());
            write(fds[1], "\n", 1);
            exit(0);
        } else {
            printf("buf size: %d\n", sizeof(buf));
            printf("n == %d\n", n);
            fprintf(2, "Ping need one byte\n");
            exit(1);
        }
    } else {
        write(fds[1], "\n", 1);
        wait((int *) 0);
        n = read(fds[0], buf, sizeof(buf));
        if (n == 1) {
            printf("%d: received pong\n", getpid());
            write(fds[1], "\n", 1);
            exit(0);
        } else {
            fprintf(2, "Pong need one byte\n");
            exit(1);
        }


    }
    exit(0);


}