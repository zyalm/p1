/**
 *	CS 537
 *	Project 1 opendir.h
 *	Authors: Kenny Jin, Ying Zhang
 */

#ifndef HEADER_OPENDIR
#define HEADER_OPENDIR

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "readfile.h"
#include "optproc.h"

/**
 *	Print the information about one process according to pid
 *	@param pid The process id of the process to be printed
 *	@param opt_info The command line option information
 */
void print_one_process(int pid, Opt_info *opt_info);

/**
 *	Print the information about all processes
 *	@param opt_info The command line option information
 */
void print_all_process(Opt_info *opt_info);

/**
 *	Print the information about all processes belong to current user
 *	@param opt_info The command line option information
 */
void print_user_process(Opt_info *opt_info);

#endif