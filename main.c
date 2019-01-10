/**
 *	CS 537
 *	Project 1 main.c
 *	Authors: Kenny Jin, Ying Zhang
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "optproc.h"
#include "readfile.h"
#include "opendir.h"

void make_decision(Opt_info *opt_info);

/**
 *	main function. 
 *	This function takes command line inputs and prints information as specified.
 */
int main(int argc, char *argv[]) {
    Opt_info *opt_info = get_opt_info(argc, argv);
    make_decision(opt_info);
    free(opt_info);
}

/**
 *	The function below makes display decision accroding to user input
 *	@param opt_info The information about all the cmdline input
 */
void make_decision(Opt_info *opt_info) {
	if (!opt_info -> p) {
		// If the option -p is not specified, print all user processes
		print_user_process(opt_info); 
	} else {
		// If pid is specified, print this process
		print_one_process(opt_info -> pid, opt_info);
	}
}


