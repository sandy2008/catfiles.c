#include <sys/types.h>  /* open, write */
#include <stdio.h>      /* perror */
#include <stdlib.h>     /* exit */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open, creat */
#include <sys/uio.h>    /* write */
#include <unistd.h>     /* close, write, read */

int main(int argc, char *argv[]){

	if (argc == 1){
		printf("No Input Files");
		exit(1);
	}
	
	int i, j = 0; //initilize loop parameters
	int fd[1]; //fd[0] is context.txt and fd[1] is temp file fd
	
	char buff[1000];
	
	for (i = 0; i < 1000; i ++){
		buff[i] = ' '; //initilize buffer
	}
	fd[0] = open("context.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	if (fd[0] == -1) {
    	perror("open");
    	exit(1);
  	}
  	
  	  for (i=1;i<argc;i++){
    printf("open file is : %s\n",argv[i]);  

    if ((fd[1] = open(argv[i], O_RDONLY)) != -1) {
	printf("Success open\n");
	
	if((j = read(fd[1],buff,sizeof(buff))) !=  -1){ 
         printf("Success read\n");
		 write(fd[0],buff,j);        
	     printf("Success write\n");
	} else {                                   //Read error
	 perror("read");
     close(fd[0]);
     close(fd[1]);
     exit(1);
	 }
     
	 close(fd[1]);     //open fd[1] close
	 } else {                                  //error
	 perror("open");
	 close(fd[0]);
	 close(fd[1]);
	 exit(1);
	 }
	
     }// end read file
      printf("all file writed.");
      close(fd[0]);   // open fd[0](concat.txt) close
  
   
	

}