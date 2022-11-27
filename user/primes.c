#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void primes_func(int fds[]) {
    int fds2[2];
    int n;
    close(fds[1]);

    int read_res = read(fds[0], &n, sizeof(int));
    if (read_res == 0) {
        exit(0);
    }
    pipe(fds2);

    if (fork()) {
        primes_func(fds2);
    } else {
        close(fds2[0]);
        printf("prime %d\n", n);
        int value = n;
        while (read(fds[0], &n, sizeof(int)) != 0)
        {
            if (n % value != 0) {
                write(fds2[1], &n, sizeof(int));
            }
        }
        close(fds2[1]);
        wait((int *) 0);
        exit(0);
    }
}

int
main(int argc, char* argv[])
{
    int pid, i;
    int fds[2];

    if (argc >= 2) {
        fprintf(2, "Primes need not parameter\n");
        exit(0);
    }
    pipe(fds);
    pid = fork();

    if (pid == 0) {
        primes_func(fds);
    } else {
        close(fds[0]);
        for (i = 2; i <= 35; i++) {
                write(fds[1], &i, sizeof(int));
        }
        close(fds[1]);
        wait((int *)0);
    }
    
    exit(0);
}