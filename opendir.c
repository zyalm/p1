/**
 *	CS 537
 *	Project 1 opendir.c
 *	Authors: Kenny Jin, Ying Zhang
 */

#include "opendir.h"


void print_one_process(int pid, Opt_info *opt_info) {
	printf("%d: ", pid);
	read_stat(pid);
	if (opt_info -> s) {
		printf("%c ", state);
	}
	if (opt_info -> U) {
		printf("utime=%d ", utime);
	}
	if (opt_info -> S) {
		printf("stime=%d ", stime);
	}
	if (opt_info -> v) {
		read_statm(pid);
	}
	if (opt_info -> c) {
		read_cmdline(pid);
	}
	printf("\n");
}

void print_user_process(Opt_info *opt_info) {
	DIR *dir;
	struct dirent *entry;
	int this_uid = getuid();
	if ((dir = opendir("/proc")) == NULL) {
		perror("opendir() error");
		exit(-1);
	} else {
		while (((entry = readdir(dir)) != NULL)) {
			int num = atoi(entry -> d_name);
			if (num == 0 && entry->d_name[0] != 0){ // when we encounter a non-number directory, skip
        		continue;
      		}
      		if (check_user_id(num, this_uid)){ // if the uid matches the current user id, print the process
      			print_one_process(num, opt_info);
      		}
		}
	}
}

void print_all_process(Opt_info *opt_info) {
	DIR *dir;
	struct dirent *entry;
	if ((dir = opendir("/proc")) == NULL) {
		perror("opendir() error");
		exit(-1);
	} else {
		while (((entry = readdir(dir)) != NULL)) {
			int num = atoi(entry -> d_name);
			if (num == 0 && entry->d_name[0] != 0){ // when we encounter a non-number directory, skip
        		continue;
      		}
      			print_one_process(num, opt_info);
		}
	}
}

