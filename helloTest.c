#define _DEFAULT_SOURCE
#include <stdio.h>
#include <string.h>
#define BUFSIZE 100

// https://stackoverflow.com/questions/43116/how-can-i-run-an-external-program-from-c-and-parse-its-output

int main(void) {
	char *cmd = "./hello";
	char buf[BUFSIZE];
    char line[BUFSIZE];
    int bytesRead = 0;
	FILE *fp;

	if ((fp = popen(cmd,"r")) == NULL) {
        fprintf(stderr,"Error opening pipe!\n");
        return -1;
    }
    while (fgets(line,BUFSIZE,fp) != NULL) {
        if (bytesRead + strlen(line) > BUFSIZE) {
            fprintf(stderr,"Error: input exceeded %d bytes\n",BUFSIZE);
            return -1;
        }
        strncpy(buf+bytesRead,line,BUFSIZE - bytesRead);
        bytesRead += strlen(line);
    }
    if (pclose(fp) != 0) {
        fprintf(stderr,"Error: failed to close pipe!");
        return -1;
    }
    printf("buffer: %s\n",buf);
    if (strncmp("Hello World!\n",buf,BUFSIZE) == 0) {
        printf("Hello World: SUCCESS\n");
        return 0;
    } else {
        printf("HELLO WORLD: FAILURE\n");
        return -1;
    }
}

