#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv)
{
    int nread;
    int i;
    int fd;
    char buf[BUFSIZ];

    if ((fd = open(argv[1], O_RDONLY)) == -1)
    {
        exit(EXIT_FAILURE);
    }
    memset(buf, '\0', BUFSIZ);
    i = 0;
    while ((nread = read(fd, buf, BUFSIZ)) > 0)
    {
        write(STDOUT_FILENO, buf, nread);
    }
    close(STDOUT_FILENO);
    if (nread == -1)
    {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}