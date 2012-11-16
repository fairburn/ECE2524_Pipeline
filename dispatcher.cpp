#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
using namespace std;

int main()
{
	int p[2];
	int buf[16];
	pipe(p); // create a pipe
	
	pid_t gen_pid, con_pid, pid;
	
	pid = fork();
	
	if( pid == 0 ) // child
	{
		gen_pid = getpid();
		dup2(p[1], 1); // connect output to write end of pipe
		close(p[0]); // close read end of pipe
		execv("generator", NULL); // execute generator
	} 
	
	else // parent
	{
		con_pid = fork();
		if( con_pid == 0 ) // create second child
		{
			con_pid = getpid();
			dup2(p[0], 0); // connect input to read end of pipe
			close(p[1]); // close write end of pipe
			execv("consumer", NULL);
		}
		else
		{
			sleep(1);
			kill(gen_pid, SIGTERM);
			int status;
			waitpid(gen_pid, &status, WNOHANG);
		}
		// the consumer execution doesn't give any output like this...
		
		return 0;
	}
		
}