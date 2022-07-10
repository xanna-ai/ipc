#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LaunchChildProcess(int* file_pipes, const char* ChildProcessName, char* param);

int main (int argc, char** argv)
{
    const char* Reader = "Reader";
    char* Message = argv[1];
    char* Key = argv[2];
    char* Result = argv[3];

    int file_pipes1[2];
    int file_pipes2[2];
    pid_t fork_result;

    int nbytes = 0;
    char c1, c2, c3;

    LaunchChildProcess(file_pipes1, Reader, Message);
    LaunchChildProcess(file_pipes2, Reader, Key);

    int outfd = open(Result, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    while ( (nbytes = read(file_pipes1[0], &c1, 1)) > 0)
    {
        nbytes = read(file_pipes2[0], &c2, 1);
        if (nbytes == 0)
            lseek(file_pipes2[0], 0, SEEK_SET);
        c3 = c1^c2;    
        write(outfd, &c3, 1);
    }
    if (nbytes == -1)  
    {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

void LaunchChildProcess(int* file_pipes, const char* ChildProcessName, char* param)
{
    pid_t fork_result;

    if (pipe(file_pipes) == -1)
    {
        exit(EXIT_FAILURE);
        //error
    }

    if ((fork_result = fork()) == -1)
    {
        exit(EXIT_FAILURE);
        //error
    }

    if (fork_result == (pid_t)0)    //chid process
    {
        close(1);
        dup(file_pipes[1]);
        close(file_pipes[1]);
        close(file_pipes[0]);
        execl(ChildProcessName, ChildProcessName, param, (char*)0);
    }else{
        close(file_pipes[1]);
    }
}