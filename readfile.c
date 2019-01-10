/**
 *  CS 537
 *  Project 1 readfile.c
 *  Authors: Kenny Jin, Ying Zhang
 */

#include "readfile.h"

void read_stat(int pid)
{
	// This function does not print the values. Leave this for main.
	FILE *fp;
	char buff[BUFFSIZE];
	char filepath[BUFFSIZE];
	snprintf(filepath, sizeof filepath, "%s%d%s", "/proc/", pid, "/stat"); // generate file path
	fp = fopen(filepath,"r");
	if (fp == NULL)
	{
		printf("Cannot open file\n");
		exit(-1);
	}
	for (int i = 1; i <= 3; i++) {
		if (fscanf(fp, "%s", buff) != 1)
		{
			printf("Cannot read state\n");
			exit(-1);
		}
		state = buff[0]; 
	}
	for (int i = 4; i <= 14; i++) {
		if (fscanf(fp, "%s", buff) != 1)
		{
			printf("Cannot read user time\n");
			exit(-1);
		}
		utime = atoi(buff);
	}
	if (fscanf(fp, "%s", buff) != 1)
	{
		printf("Cannot read system time\n");
		exit(-1);
	}
	stime = atoi(buff);
    fclose(fp);
}

void read_statm(int pid) {
	// This function also prints the size
	FILE *fp;
	char buff[BUFFSIZE]; 
	char filepath[BUFFSIZE];
	int size; // This is the virtual memory size the process uses
	snprintf(filepath, sizeof filepath, "%s%d%s", "/proc/", pid, "/statm"); // generate file path
	fp = fopen(filepath,"r");
	if (fp == NULL)
	{
		printf("Cannot open file\n");
		exit(-1);
	}
	if (fscanf(fp, "%s", buff) != 1)
	{
		printf("Cannot read size\n");
		exit(-1);
	}
	size = atoi(buff);
	printf("vmemory=%d ", size);
	fclose(fp);
}

void read_cmdline(int pid) {
	// This function also prints the cmdline
	FILE *fp;
	char filepath[BUFFSIZE];
	snprintf(filepath, sizeof filepath, "%s%d%s", "/proc/", pid, "/cmdline"); // generate file path
	fp = fopen(filepath,"r");
	if (fp == NULL)
	{
		printf("Cannot open file\n");
		exit(-1);
	}
	// The whole hassle below is to remove the last whitespace of the cmdline.
	// Every \0 needs to be replaced by a whitespace except for the last.
	char c;
	char d;
	int flag = 0; // this indicates whether c is replaced.
	printf("%c",'[');
	do {
		if (flag) {
			c = d;
			flag = 0;
		} else {
			c = fgetc(fp);
		}
      	if (c == '\0') {
      		c = ' '; // If a null character is encountered, turn it into a space
      		d = fgetc(fp);
      		if (feof(fp)) {
      			break;
      		}
      		flag = 1;
      	}
      	if (feof(fp)) {
         	break;
      	}
      	printf("%c", c);
   	} while(1);
	printf("%c",']');
   	fclose(fp);
}

// the function below checks if the process belongs to current user
int check_user_id(int pid, int this_uid){
	FILE *fp;
	char buff[BUFFSIZE]; // This stores the uid of the process
	char filepath[BUFFSIZE];
	snprintf(filepath, sizeof filepath, "%s%d%s", "/proc/", pid, "/status"); // generate file path
	fp = fopen(filepath,"r");
	if (fp == NULL) {
		printf("Cannot open file\n");
		exit(-1);
	}
	// read to the end of the 8th line
	for (int i = 0; i < 8; i++) {
		fgets(buff, sizeof buff, (FILE*)fp);
	}
	if (fscanf(fp, "%s", buff) != 1)
	{
		printf("Cannot read uid\n");
		exit(-1);
	}
	for (int i = 0; i < 4; i++) { // there are 4 numbers in the uid field
		if (fscanf(fp, "%s", buff) != 1)
		{
			printf("Cannot read uid\n");
			exit(-1);
		}
		if (this_uid == atoi(buff))
		{
			return 1;
		}
	}
	return 0;
}