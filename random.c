
int ret;
int fdout;

for(i=0;i<numsimplecommands; i++) {
//redirect input
	dup2(fdin, 0);
	close(fdin);
//setup output
	if (i == numsimplecommands­1){
	// Last simple command 
		if(outfile){
		fdout=open(outfile,â€¦â€¦);
		}
		else {
		// Use default output
			fdout=dup(tmpout);
		}
	}
	else {
	// Not last simple command --create pipe
		int fdpipe[2];
		pipe(fdpipe);
		fdout=fdpipe[1];
		fdin=fdpipe[0];
	}// if/else
	// Redirect output
	dup2(fdout,1);
	close(fdout);
	ret=fork(); 
	if(ret==0) {
		execvp(scmd[i].args[0], scmd[i].args);
		perror(â€œexecvpâ€);
		exit(1);
	}
} 